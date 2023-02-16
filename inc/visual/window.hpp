#ifndef WINDOW_HEADER
#define WINDOW_HEADER

//#include "Box.hpp"

#include "types.hpp"
#include "escape.hpp"
#include "vector.hpp"
#include "border.hpp"
#include "rect.hpp"
#include "event.hpp"

#include <iostream>


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- W I N D O W  C L A S S ----------------------------------------------

	class Window {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* size type */
			using Size = UInt64;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			Window(void);

			/* rect constructor */
			Window(const Xf::Rect& rect);

			/* window constructor */
			Window(Window* parent);

			/* non-assignable class */
			NON_ASSIGNABLE(Window);

			/* destructor */
			virtual ~Window(void);


			// -- M E T H O D S -----------------------------------------------

			/* set */
			void set(const Xf::Rect& rect);

			/* update window */
			void update(void);

			/* exit window */
			void exit(void);

			/* select left window */
			void select_left(void);

			// -- V I R T U A L  M E T H O D S --------------------------------

			/* draw window */
			virtual void draw(void);




		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			bool _visible;

			bool _active;

			bool _selected;

			int _depth;

			Xf::Rect _rect;

			Window* _parent;

			Xf::Border _border;

			Xf::Vector<Window*> _children;

			Xf::Evntmode _mode;


	};


	// -- C W I N D O W  C L A S S -- container for windows -------------------

	class CWindow : public Window {

		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			CWindow(void);

			/* size and position constructor */
			CWindow(const UInt w, const UInt h, const UInt x, const UInt y);

			/* copy constructor */
			CWindow(const CWindow& other);

			/* move constructor */
			CWindow(CWindow&& other) noexcept;

			/* destructor */
			virtual ~CWindow(void);


			// -- O P E R A T O R S -------------------------------------------

		private:

			// -- M E M B E R S -----------------------------------------------

			Vector<Window*> _windows;



	};

	// -- W I N D O W  M A T R I X --------------------------------------------

	template <typename T>
	class WindowMatrix {
	};


};





		//enum class SplitType : bool {
		//	HORIZONTAL,
		//	VERTICAL
		//};

		//enum class ContainerType {
		//	BLOCK,
		//	BOX
		//};


		//Block* split_block(const ContainerType ctype, const SplitType stype);

		//virtual void draw(void);

		//Block*  _sub;
		//Block** _alloc;
		//UInt    _w, _h, _x, _y;
		//char    ch;

		//inline static char c = 'a';


#endif
