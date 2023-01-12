#ifndef INPUT_HEADER
#define INPUT_HEADER

#include "Term.hpp"
#include "Types.hpp"

#include <unistd.h>
#include <string>
#include <list>

#define BUFFER_SIZE		256

class Input {
	public:
	struct Observer;
	enum class KeyEvent {
		KEY_UP, KEY_DOWN, KEY_LEFT,
		KEY_RIGHT, KEY_ESCAPE, KEY_ENTER,
		EVNT_NBR
	};

	public:
	static void getEvent(void);
	static void subscript(Observer* obs, const KeyEvent key);
	// contructor / operator safe delete
	Input(void)						= delete;
	~Input(void)					= delete;
	Input(const Input&)				= delete;
	Input(Input&&)					= delete;
	Input& operator=(const Input&)	= delete;
	Input& operator=(Input&&)		= delete;

	public:
	struct Observer {
		friend class Input;
		// member functions array typedef
		typedef void (Observer::*Keyfn)(void);
		// default constructor
		Observer(void);
		// destructor
		virtual ~Observer(void)					= 0;
		// abstract member functions
		virtual void onKeyUp(void)		{ /**/ };
		virtual void onKeyDown(void)	{ /**/ };
		virtual void onKeyLeft(void)	{ /**/ };
		virtual void onKeyRight(void)	{ /**/ };
		virtual void onKeyEscape(void)	{ /**/ };
		virtual void onKeyEnter(void)	{ /**/ };
		// static member functions array
		static const Keyfn _keyfn[static_cast<UInt64>(KeyEvent::EVNT_NBR)];
		// contructor / operator safe delete
		Observer(const Observer&)				= delete;
		Observer(Observer&& )					= delete;
		Observer& operator=(const Observer&)	= delete;
		Observer& operator=(Observer&& )		= delete;

	};

	private:
	template<class T>
	using List = std::list<T>;
	typedef std::string String;

	static String	_input;
	static char		_buff[BUFFER_SIZE + 1];
	static SInt64	_readed;

	static List<Observer*> _observers[static_cast<UInt64>(KeyEvent::EVNT_NBR)];

	static void callObservers(const KeyEvent key);


	static SInt64 readInput(void);
	static void processInput(void);
	static void processEscape(void);
	static void processArrow(void);
};

#endif
