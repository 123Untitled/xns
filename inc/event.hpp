#ifndef EVENT_HEADER
#define EVENT_HEADER

#include "macro.hpp"
#include "move.hpp"
#include "forward.hpp"
#include "types.hpp"
#include "list.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include "array.hpp"
#include "function.hpp"

#include <iostream>
#include <string>


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	/* event */
	enum class Evntype : UInt8 {
		NUL,          // null character (ctrl+space)
		SOH,          // start of heading (ctrl+a)
		STX,          // start of text (ctrl+b)
		ETX,          // end of text (ctrl+c)
		EOT,          // end of transmission (ctrl+d)
		ENQ,          // enquiry (ctrl+e)
		ACK,          // acknowledge (ctrl+f)
		BEL,          // bell (ctrl+g)
		BS,           // backspace
		HT,           // horizontal tab
		LF,           // line feed
		VT,           // vertical tab
		FF,           // form feed
		CR,           // carriage return
		SO,           // shift out
		SI,           // shift in
		DLE,          // data link escape
		DC1,          // device control 1
		DC2,          // device control 2
		DC3,          // device control 3
		DC4,          // device control 4
		NAK,          // negative acknowledge
		SYN,          // synchronous idle
		ETB,          // end of transmission block
		CAN,          // cancel
		EM,           // end of medium
		SUB,          // substitute
		ESC,          // escape
		FS,           // file separator
		GS,           // group separator
		RS,           // record separator
		US,           // unit separator
		SPACE,        // space
		EXCLAMATION,  // !
		DOUBLE_QUOTE, // "
		HASH,         // #
		DOLLAR,       // $
		PERCENT,      // %
		AMPERSAND,    // &
		SINGLE_QUOTE, // '
		LEFT_PAREN,   // (
		RIGHT_PAREN,  // )
		ASTERISK,     // *
		PLUS,         // +
		COMMA,        // ,
		MINUS,        // -
		PERIOD,       // .
		SLASH,        // /
		ZERO,         // 0
		ONE,          // 1
		TWO,          // 2
		THREE,        // 3
		FOUR,         // 4
		FIVE,         // 5
		SIX,          // 6
		SEVEN,        // 7
		EIGHT,        // 8
		NINE,         // 9
		COLON,        // :
		SEMICOLON,    // ;
		LESS_THAN,    // <
		EQUAL,        // =
		GREATER_THAN, // >
		QUESTION,     // ?
		AT,           // @
		MAJ_A,        // A
		MAJ_B,        // B
		MAJ_C,        // C
		MAJ_D,        // D
		MAJ_E,        // E
		MAJ_F,        // F
		MAJ_G,        // G
		MAJ_H,        // H
		MAJ_I,        // I
		MAJ_J,        // J
		MAJ_K,        // K
		MAJ_L,        // L
		MAJ_M,        // M
		MAJ_N,        // N
		MAJ_O,        // O
		MAJ_P,        // P
		MAJ_Q,        // Q
		MAJ_R,        // R
		MAJ_S,        // S
		MAJ_T,        // T
		MAJ_U,        // U
		MAJ_V,        // V
		MAJ_W,        // W
		MAJ_X,        // X
		MAJ_Y,        // Y
		MAJ_Z,        // Z
		LEFT_BRACKET, // [
		BACKSLASH,    //
		RIGHT_BRACKET,// ]
		CARET,        // ^
		UNDERSCORE,   // _
		BACKQUOTE,    // `
		MIN_A,        // a
		MIN_B,        // b
		MIN_C,        // c
		MIN_D,        // d
		MIN_E,        // e
		MIN_F,        // f
		MIN_G,        // g
		MIN_H,        // h
		MIN_I,        // i
		MIN_J,        // j
		MIN_K,        // k
		MIN_L,        // l
		MIN_M,        // m
		MIN_N,        // n
		MIN_O,        // o
		MIN_P,        // p
		MIN_Q,        // q
		MIN_R,        // r
		MIN_S,        // s
		MIN_T,        // t
		MIN_U,        // u
		MIN_V,        // v
		MIN_W,        // w
		MIN_X,        // x
		MIN_Y,        // y
		MIN_Z,        // z
		LEFT_BRACE,   // {
		PIPE,         // |
		RIGHT_BRACE,  // }
		TILDE,        // ~
		DEL,          // delete

		// escape sequences
		UP,           // \x1b[A
		DOWN,         // \x1b[B
		LEFT,         // \x1b[D
		RIGHT,        // \x1b[C

		// special events
		TERMINAL_RESIZE, // terminal resize

		EVNT_MAX
	};


	// -- E V E N T  C L A S S ------------------------------------------------

	class Event final {

		private:

			// -- P R I V A T E  A L I A S E S --------------------------------

			/* string type */
			using String = std::string;

			/* object pointer */
			template <typename C>
			using Pointer = C*;

			/* event prototype */
			template <typename C>
			using EventMethod = void(C::*)(void);

			/* event function prototype */
			using EventFunction = void(*)(void);

			/* input prototype */
			template <typename C>
			using InputMethod = void(C::*)(const String&);

			/* input function prototype */
			using InputFunction = void(*)(const String&);



			// -- P R I V A T E  C O N S T R U C T O R S ----------------------

			/* default constructor */
			Event(void);

			/* non-assignable class */
			NON_ASSIGNABLE(Event);

			/* destructor */
			~Event(void);


		public:

			// -- S T A T I C  M E T H O D S ----------------------------------

			/* get singleton instance */
			static Event& instance(void);


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* add mode */
			void add_mode(String&&);

			/* set mode by name */
			bool set_mode(const String&);

			/* apply mode */
			void apply_mode(void);

			/* subscribe to event [method] */
			template <typename C>
			void subscribe_event(const String& mode, const Evntype type, EventMethod<C> method, Pointer<C> instance) {
				// check invalid pointers
				if (!method || !instance) { return; }
				// check event type
				if (type < Evntype::EVNT_MAX) {
					// get event subscriber vector
					EventVector* subscribers = get_event_subscribers(mode, type);
					// check pointer
					if (!subscribers) { return; }
					// add new subscriber
					subscribers->emplace_back(method, instance);
				}
			}

			void subscribe_event(const String& mode, const Evntype type, EventFunction method);

			/* subscribe to input */
			template <typename C>
			void subscribe_input(const String& mode, InputMethod<C> method, Pointer<C> instance) {
				// check invalid pointers
				if (!method || !instance) { return; }
				// get input subscriber vector
				InputVector* subscribers = get_input_subscribers(mode);
				// check pointer
				if (!subscribers) { return; }
				// add new subscriber
				subscribers->emplace_back(method, instance);
			}

			/* unsubscribe to event */
			template <typename C>
			void unsubscribe_event(const String& mode, const Evntype type, EventMethod<C> method, Pointer<C> instance) {

				/* -> */ return; // INFO: this method is not implemented yet

				//// check invalid type
				//if (type >= Evntype::EVNT_MAX) { return; }
				//// get subscriber vector
				//EventVector* subscribers = get_event_subscribers(mode, type);
				//// check pointer
				//if (!subscribers) { return; }
				//// loop through all observers
				//for (Size x = 0; x < subscribers->size(); ++x) { }
			}

			/* call all event subscribers */
			void call_event(const Evntype);

			/* call all input subscribers */
			void call_input(const String&);



		private:

			// -- P R I V A T E  A L I A S E S --------------------------------

			/* input vector type */
			using InputVector = Xf::Vector<Xf::PolyMethod<void(const std::string&)>>;


			/* event vector type */
			using EventVector = Xf::Vector<Xf::PolyMethod<void(void)>>;

			/* event array type */
			using EventArray = Xf::Array<EventVector, IDX(Evntype::EVNT_MAX)>;


			/* mode type */
			using Mode = Xf::Pair<InputVector, EventArray>;

			/* mode pair type */
			using Modepair = Xf::Pair<std::string, Mode>;

			/* mode list type */
			using Modelist = Xf::Vector<Modepair>;


			// -- P R I V A T E  M E T H O D S --------------------------------

			/* get mode */
			Mode* get_mode(const std::string& mode);

			/* get event subscribers */
			EventVector* get_event_subscribers(const String& mode, const Evntype type);

			/* get input subscribers */
			InputVector* get_input_subscribers(const String& mode);

			/* mode exists */
			bool mode_exists(const std::string& mode) const;

			/* get current mode index */
			Size get_current_idx(void) const;



			// -- P R I V A T E  M E M B E R S --------------------------------

			/* mode list */
			Modelist _modes;

			/* current mode */
			Mode* _current;

			/* mode to apply */
			Mode* _apply;


			// -- S T A T I C  P R I V A T E  M E M B E R S -------------------

			/* singleton instance */
			static Event _instance;

	};


};




#endif
