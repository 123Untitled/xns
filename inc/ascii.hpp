#ifndef ASCII_HEADER
#define ASCII_HEADER

#include "types.hpp"
#include "macro.hpp"
#include "array.hpp"

#include <string>
#include <climits>

#define ZERO_ASCII		48
#define BASE			10

#define WHITE_SPACE		"\x09\x0a\x0b\x0c\x0d\x20"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- A S C I I  C L A S S ------------------------------------------------

	class Ascii {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* character type */
			using Char = char;

			/* string type */
			using String = std::string;

			/* size type */
			using Size = UInt64;


			// -- C O N S T R U C T O R S -------------------------------------

			/* non-instanciable class */
			NON_INSTANCIABLE(Ascii);


		private:


			// -- E L E M E N T  S T R U C T ----------------------------------

			struct Element {

				String base8;
				String base10;
				String base16;
				String symbol;
				String description;

			};

			static Xf::Array<Element, UINT8_MAX + 1> _array;

	};

};


/*

"0", "00", "NUL", "Null"
"1", "01", "SOH", "Start of Header"
"2", "02", "STX", "Start of Text"
"3", "03", "ETX", "End of Text
"4", "04", "EOT", "End of Transmission
"5", "05", "ENQ", "Enquiry
"6", "06", "ACK", "Acknowledge
"7", "07", "BEL", "Bell
"8", "08", "BS    Backspace
"9", "09", "HT    Horizontal Tab

"10" "0A LF    Line Feed
"11" "0B VT    Vertical Tab
"12" "0C FF    Form Feed
"13" "0D CR    Carriage Return
"14" "0E SO    Shift Out
"15" "0F SI    Shift In
"16" "10 DLE   Data Link Escape
"17" "11 DC1   Device Control 1
"18" "12 DC2   Device Control 2
"19" "13 DC3   Device Control 3
"20" "14 DC4   Device Control 4
"21" "15 NAK   Negative Acknowledge
"22" "16 SYN   Synchronize
"23" "17 ETB   End of Transmission Block
"24" "18 CAN   Cancel
"25" "19 EM    End of Medium
"26" "1A SUB   Substitute
"27" "1B ESC   Escape
"28" "1C FS    File Separator
"29" "1D GS    Group Separator
"30" "1E RS    Record Separator
"31" "1F US    Unit Separator
"32" "20 space Space
"33" "21 !     Exclamation mark
"34" "22 "     Double quote
"35" "23 #     Number
"36" "24 $     Dollar sign
"37" "25 %     Percent
"38" "26 &     Ampersand
"39" "27 '     Single quote
"40" "28 (     Left parenthesis
"41" "29 )     Right parenthesis
"42" "2A *     Asterisk
"43" "2B +     Plus
"44" "2C ,     Comma
"45" "2D -     Minus
"46" "2E .     Period
"47" "2F /     Slash
"48" "30 0     Zero
"49" "31 1     One
"50" "32 2     Two
"51" "33 3     Three
"52" "34 4     Four
"53" "35 5     Five
"54" "36 6     Six
"55" "37 7     Seven
"56" "38 8     Eight
"57" "39 9     Nine
"58" "3A :     Colon
"59" "3B ;     Semicolon
"60" "3C <     Less than
"61" "3D =     Equality sign
"62" "3E >     Greater than
"63" "3F ?     Question mark
"64" "40 @     At sign
"65" "41 A     Capital A
"66" "42 B     Capital B
"67" "43 C     Capital C
"68" "44 D     Capital D
"69" "45 E     Capital E
"70" "46 F     Capital F
"71" "47 G     Capital G
"72" "48 H     Capital H
"73" "49 I     Capital I
"74" "4A J     Capital J
"75" "4B K     Capital K
"76" "4C L     Capital L
"77" "4D M     Capital M
"78" "4E N     Capital N
"79" "4F O     Capital O
"80" "50 P     Capital P
"81" "51 Q     Capital Q
"82" "52 R     Capital R
"83" "53 S     Capital S
"84" "54 T     Capital T
"85" "55 U     Capital U
"86" "56 V     Capital V
"87" "57 W     Capital W
"88" "58 X     Capital X
"89" "59 Y     Capital Y
"90" "5A Z     Capital Z
"91" "5B [     Left square bracket
"92" "5C \     Backslash
"93" "5D ]     Right square bracket
"94" "5E ^     Caret / circumflex
"95" "5F _     Underscore
"96" "60 `     Grave / accent
"97" "61 a     Small a
"98" "62 b     Small b
"99" "63 c     Small c
"100" 64 d     Small d
"101" 65 e     Small e
"102" 66 f     Small f
"103" 67 g     Small g
"104" 68 h     Small h
"105" 69 i     Small i
"106" 6A j     Small j
"107" 6B k     Small k
"108" 6C l     Small l
"109" 6D m     Small m
"110" 6E n     Small n
"111" 6F o     Small o
"112" 70 p     Small p
"113" 71 q     Small q
"114" 72 r     Small r
"115" 73 s     Small s
"116" 74 t     Small t
"117" 75 u     Small u
"118" 76 v     Small v
"119" 77 w     Small w
"120" 78 x     Small x
"121" 79 y     Small y
"122" 7A z     Small z
"123" 7B {     Left curly bracket
"124" 7C |     Vertical bar
"125" 7D }     Right curly bracket
"126" 7E ~     Tilde
"127" 7F DEL   Delete
*/

#endif
