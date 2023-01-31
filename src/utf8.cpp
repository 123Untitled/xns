#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <string>


using UInt8   = uint8_t;
using UInt32  = uint32_t;
using Size    = uint32_t;

// UTF-8 parser

enum ByteType {
	NU, // null
	IN, // invalid
	B1, // 1 byte
	B2, // 2 bytes
	B3, // 3 bytes
	B4, // 4 bytes

	S1, // 3 bytes special case 1
	S2, // 3 bytes special case 2

	S3, // 4 bytes special case 1
	S4, // 4 bytes special case 2

	C1, // continuation 1 (S2) (S4) (B2) (B3) (B4)
	C2, // continuation 2 (S2) (S3) (B2) (B3) (B4)
	C3, // continuation 3 (S1) (S3) (B2) (B3) (B4)
	TBYTE_MAX
};


/* lookup table for byte type */
static const ByteType byte_type[UINT8_MAX + 1] = {

	// null character
	[0x00]          = NU,

	// 1 byte sequence
	[0x01 ... 0x7F] = B1,

	// continuation 1
	[0x80 ... 0x8F] = C1,

	// continuation 2
	[0x90 ... 0x9F] = C2,

	// continuation 3
	[0xA0 ... 0xBF] = C3,

	// invalid byte
	[0xC0 ... 0xC1] = IN,

	// 2 bytes sequence
	[0xC2 ... 0xDF] = B2,

	// 3 bytes sequence special
	[0xE0]          = S1,

	// 3 bytes sequence
	[0xE1 ... 0xEC] = B3,

	// 3 bytes sequence special
	[0xED]          = S2,

	// 3 bytes sequence
	[0xEE ... 0xEF] = B3,

	// 4 bytes sequence special
	[0xF0]          = S3,

	// 4 bytes sequence
	[0xF1 ... 0xF3] = B4,

	// 4 bytes sequence special
	[0xF4]          = S4,

	// invalid byte
	[0xF5 ... 0xFF] = IN,

};

/* automate state */
enum State {
	__ERROR, ____END,
	A1_BYTE, A2_BYTE,
	A3_BYTE, B3_BYTE, C3_BYTE, A3_NXT2,
	A4_BYTE, B4_BYTE, C4_BYTE, A4_NXT2, A4_NXT3,
	STATE_MAX
};

/* machine action */
struct Table final {
	State state;
	void* jump;
};

int get_cell_size(const std::string& str) {
	wchar_t wc;
	(void)mbtowc(&wc, str.c_str(), str.size());
	return wcwidth(wc);
}


void parser(const char* str) {


	static const Table _automate[STATE_MAX][TBYTE_MAX] = {

		{  /* __ERROR */
			[0 ... TBYTE_MAX - 1] = { __ERROR, &&_error }
		},

		{  /* ____END */
			{ ____END, &&___end }, // NU null
			[1 ... TBYTE_MAX - 1] = { __ERROR, &&_error }
		},


		// -- O N E  B Y T E --------------------------------------------------

		/* A1_BYTE */ {
			{ ____END, &&___end }, // NU null
			{ __ERROR, &&_error }, // IN invalid
			{ A1_BYTE, &&___one }, // B1 1 byte
			{ A2_BYTE, &&__jump }, // B2 2 bytes
			{ A3_BYTE, &&__jump }, // B3 3 bytes
			{ A4_BYTE, &&__jump }, // B4 4 bytes
			{ B3_BYTE, &&__jump }, // S1 3 bytes special case
			{ C3_BYTE, &&__jump }, // S2 3 bytes special case
			{ B4_BYTE, &&__jump }, // S3 4 bytes special case
			{ C4_BYTE, &&__jump }, // S4 4 bytes special case
			[10 ... TBYTE_MAX - 1] = { __ERROR, &&_error }
		},


		// -- T W O  B Y T E S ------------------------------------------------

		{  /* A2_BYTE */
			[0 ... 9] = { __ERROR, &&_error },
			[10 ... TBYTE_MAX - 1] = { A1_BYTE, &&___two }
		},


		// -- T H R E E  B Y T E S --------------------------------------------

		{  /* A3_BYTE */
			[0 ... 9] = { __ERROR, &&_error },
			[10 ... TBYTE_MAX - 1] = { A3_NXT2, &&__jump } // continuation
		},

		{  /* B3_BYTE */
			[0 ... 9] = { __ERROR, &&_error },
			{ __ERROR, &&_error }, // C1 continuation
			{ __ERROR, &&_error }, // C2 continuation
			{ A3_NXT2, &&__jump }, // C3 continuation
		},

		{  /* C3_BYTE */
			[0 ... 9] = { __ERROR, &&_error },
			{ A3_NXT2, &&__jump }, // C1 continuation
			{ A3_NXT2, &&__jump }, // C2 continuation
			{ __ERROR, &&_error }, // C3 continuation
		},

		{  /* A3_NXT2 */
			[0 ... 9] = { __ERROR, &&_error },
			[10 ... TBYTE_MAX - 1] = { A1_BYTE, &&___three } // continuation
		},


		// -- F O U R  B Y T E S ----------------------------------------------

		{  /* A4_BYTE */
			[0 ... 9] = { __ERROR, &&_error },
			[10 ... TBYTE_MAX - 1] = { A4_NXT2, &&__jump } // continuation
		},

		{  /* B4_BYTE */
			[0 ... 9] = { __ERROR, &&_error },
			{ __ERROR, &&_error }, // C1 error
			[11 ... TBYTE_MAX - 1] = { A4_NXT2, &&__jump }, // C2 C3 continuation
		},

		{  /* C4_BYTE */
			[0 ... 9] = { __ERROR, &&_error },
			{ A4_NXT2, &&__jump }, // C1 continuation
			[11 ... TBYTE_MAX - 1] = { __ERROR, &&_error }, // C2 C3 error
		},

		{  /* A4_NXT2 */
			[0 ... 9] = { __ERROR, &&_error },
			[10 ... TBYTE_MAX - 1] = { A4_NXT3, &&__jump } // all continuation
		},

		{  /* A4_NXT3 */
			[0 ... 9] = { __ERROR, &&_error },
			[10 ... TBYTE_MAX - 1] = { A1_BYTE, &&___four } // continuation
		},


	};




	if (!str) { return; }
	const UInt8* ptr = reinterpret_cast<const UInt8*>(str);

	std::vector<std::string> utf8;

	#define PUSH_UTF8(s) utf8.push_back(std::string{reinterpret_cast<const char*>(ptr - (s)), s})

	// initial state
	State state = A1_BYTE;

	// -- L O O K U P  T A B L E  S T A T E  M A C H I N E --------------------

	__jump:
	const Table& table = _automate[state][byte_type[*(ptr++)]];
	state = table.state;
	// jump to the next state
	goto *table.jump;

	___one:
	/* add one byte */
	PUSH_UTF8(1);
	/* lookup next byte */
	goto __jump;

	___two:
	/* add two bytes */
	PUSH_UTF8(2);
	/* lookup next byte */
	goto __jump;

	___three:
	/* add three bytes */
	PUSH_UTF8(3);
	/* lookup next byte */
	goto __jump;

	___four:
	/* add four bytes */
	PUSH_UTF8(4);
	/* lookup next byte */
	goto __jump;


	// -- E R R O R -----------------------------------------------------------

	_error:
	write(STDOUT_FILENO, "error\n", 6);
	// exit function
	return;


	// -- E N D  O F  S T R I N G ---------------------------------------------

	___end:
	write(STDOUT_FILENO, "end\n", 4);

	// print all utf8 characters
	for (const auto& s : utf8) {
		std::cout << "size[" << s.size() << "][" << get_cell_size(s) << "]   '" << std::flush;
		write(STDOUT_FILENO, s.c_str(), s.size());
		std::cout << "'\n";
	}


	// exit function
	return;

}


	//write(STDOUT_FILENO, "1 byte: ", 8);
	//write(STDOUT_FILENO, ptr - 1, 1);
	//write(STDOUT_FILENO, "\n", 1);
	//write(STDOUT_FILENO, "2 bytes: ", 9);
	//write(STDOUT_FILENO, ptr - 2, 2);
	//write(STDOUT_FILENO, "\n", 1);
	//write(STDOUT_FILENO, "3 bytes:", 9);
	//write(STDOUT_FILENO, ptr - 3, 3);
	//write(STDOUT_FILENO, "\n", 1);
	//write(STDOUT_FILENO, "4 bytes: ", 9);
	//write(STDOUT_FILENO, ptr - 4, 4);
	//write(STDOUT_FILENO, "\n", 1);






int main(void) {

	const char* lc_type = std::getenv("LC_CTYPE");
	if (!lc_type) {
		std::cerr << "LC_CTYPE is not set" << std::endl;
		return EXIT_FAILURE;
	}
	// locale
	setlocale(LC_CTYPE, lc_type);

	// test 2 bytes sequence
	//parser("é à è ù ç");
	// test 2 bytes and 1 byte sequence
	parser("é à è ù ç hello world");
	// test 3 bytes sequence
	parser("😀😁😂");
	// test special characters
	parser("€£¥₩₪₫₭₮₯₰₱₲₳₴₵₶₷₸₹₺₻₼₽₾₿");
	// test special case

	parser("中文");
	parser("合 Ԥ");
	//parser("\xE0\xA0\x70"); // U+0800


	return 0;
	// random test
	for (int x = 0; x < 100000; ++x) {

		// random string
		std::string str;
		for (int i = 0; i < 100; ++i) {
			str += static_cast<char>(rand() % 256);
		}

		// parse
		parser(str.c_str());


	}

	// test invalid sequence
	//parser("hello \xF0\x90\x80 world");

	return 0;
}









// interface
class UtfBase {
	public:
		virtual ~UtfBase() = default;
		virtual void print() const = 0;
};

// implementation
class Utf1 final : public UtfBase {

	private:

		char _ch[1];

	public:

		Utf1(const char* p)
		: _ch{*(p + 0)} {
		}

		void print(void) const override {
			write(1, "1 byte: ", 8);
			write(1, _ch, 1);
			write(1, "\n", 1);
		}

		Utf1& operator=(const Utf1&) = delete;


};

class Utf2 final : public UtfBase {
	public:

		Utf2(const char* p)
		: _ch{*(p + 0), *(p + 1)} {
		}

		void print(void) const override {
			write(1, "2 bytes: ", 9);
			write(1, _ch, 2);
			write(1, "\n", 1);
		}

	private:
		char _ch[2];
};






// first octet always is in range 0x00 - 0x7F or 0xC2 - 0xF4

// 1 byte sequence -> range: 0x00 - 0x7F
// size: 1 byte (no continuation bytes)
// mask : 0x00

// 2 bytes sequence -> range: 0xC2 - 0xDF
// size: 2 bytes (continuation 0x80 - 0xBF)
// mask : 0x1F

// 3 bytes sequence -> range: 0xE0 - 0xEF
// size: 3 bytes (continuation 0x80 - 0xBF)
// mask : 0x0F
// special case -> range 0xE0
// next byte range: 0xA0 - 0xBF
// special case -> range 0xED
// next byte range: 0x80 - 0x9F

// 4 bytes sequence -> range: 0xF0 - 0xF4
// size: 4 bytes (continuation 0x80 - 0xBF)
// mask : 0x07
// special case -> range 0xF0
// next byte range: 0x90 - 0xBF
// special case -> range 0xF4
// next byte range: 0x80 - 0x8F

// invalid sequence -> range: 0x80 - 0xC1
// invalid sequence -> range: 0xF5 - 0xFF


// lookup table for all possible octet values




// state machine for utf8 validation
// all state name need to have the same length !!!

// initial state                                          '__START'
// error state                                            '__ERROR'
// end state                                              '____END'

// in 1 byte, wait for next start byte                    'A1_BYTE'

// in 2 bytes, wait for continuation byte                 'A2_BYTE'
// in continuation byte, wait for next start byte         'A2_NXT2'

// in 3 bytes, wait for continuation byte                 'A3_BYTE'
// in 3 bytes (sc), wait for continuation byte            'B3_BYTE'
// in 3 bytes (sc), wait for continuation byte            'C3_BYTE'
// in continuation byte, wait for continuation byte       'A3_NXT2'
// in continuation byte (sc), wait for continuation byte  'B3_NXT2'
// in continuation byte (sc), wait for continuation byte  'C3_NXT2'
// in continuation byte, wait for next start byte         'A3_NXT3'

// in 4 bytes, wait for continuation byte                 'A4_BYTE'
// in 4 bytes (sc), wait for continuation byte            'B4_BYTE'
// in 4 bytes (sc), wait for continuation byte            'C4_BYTE'
// in continuation byte, wait for continuation byte       'A4_NXT2'
// in continuation byte (sc), wait for continuation byte  'B4_NXT2'
// in continuation byte (sc), wait for continuation byte  'C4_NXT2'
// in continuation byte, wait for continuation byte       'A4_NXT3'
// in continuation byte, wait for next start byte         'A4_NXT4'


