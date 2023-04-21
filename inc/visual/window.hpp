#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include "color.hpp"
#include "types.hpp"
#include "escape.hpp"
#include "terminal.hpp"
#include "vector.hpp"
#include "border.hpp"
#include "rect.hpp"
#include "event.hpp"
#include "unique.hpp"
#include "window_traits.hpp"
#include "debug.hpp"
#include "shared_ptr.hpp"
#include "list.hpp"

#include <iostream>


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	/* forward declaration */

	struct WindowBase;
	template <pane_c P, split_c S>
	struct Window;
	template <split_c S>
	struct SplitWindow;




	// -- W I N D O W  M A N A G E R ------------------------------------------

	class WindowManager final {

		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* non-instanciable class */
			NON_INSTANCIABLE(WindowManager);


			// -- M E T H O D S -----------------------------------------------

			/* add window */
			static void add(WindowBase*);

			/* remove window */
			static void remove(WindowBase*);


			template <class T>
			static void split(void);

			static void new_root(void) noexcept;

			template <split_c S>
			static void new_split(void) {
				// code here...
				Term::Wsize width, height;
				Term::get_terminal_size(width, height);

				using Split = SplitWindow<S>;

				_root.make<Split>(Xf::Rect{0, 0, width, height});

			}


			static void draw_all(void) noexcept;

			static void debug_window(void) noexcept;



		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			static UniquePtr<WindowBase> _root;


	};




	// -- W I N D O W  B A S E  C L A S S -------------------------------------

	struct WindowBase {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* reinject type */
			using Type = WindowBase;

			/* size type */
			using Size = UInt64;

			/* pointer type */
			using Pointer = WindowBase*;


			// -- C O N S T R U C T O R S -------------------------------------

			/* deleted default constructor */
			WindowBase(void) = delete;

			/* rect constructor */
			WindowBase(const Xf::Rect& rect);

			/* non-assignable class */
			NON_ASSIGNABLE(WindowBase);

			/* destructor */
			virtual ~WindowBase(void) = default;


			// -- V I R T U A L  M E T H O D S --------------------------------

			/* draw */
			virtual void draw(int&) = 0;

			/* debug */
			virtual void debug(int) = 0;

			/* split window */
			//virtual void split(void) = 0;


			/*
			virtual Evntmode* get_left(void) = 0;

			virtual Evntmode* get_right(void) = 0;
			*/


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* coordinates */
			Xf::Rect   _rect;

			/* border */
			Xf::Border _border;


			// -- F R I E N D S -----------------------------------------------

			/*
			friend Window<pane_one_t, vsplit_t>;
			friend Window<pane_two_t, vsplit_t>;
			friend Window<pane_one_t, hsplit_t>;
			friend Window<pane_two_t, hsplit_t>;
			*/
	};





	// -- S P L I T  W I N D O W -----------------------------------------------

	template <split_c S>
	struct SplitWindow final : public WindowBase {

		private:

			// -- P R I V A T E  E N U M S ------------------------------------

			enum { ONE, TWO };


		public:

			// -- A L I A S E S -----------------------------------------------

			/* reinject type */
			using Self = SplitWindow<S>;

			/* window one type */
			using WinOne = Window<pane_one_t, S>;

			/* window two type */
			using WinTwo = Window<pane_two_t, S>;

			/* parent type */
			using Parent = SplitWindow<S>*;

			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			SplitWindow(void) = delete;

			/* rect constructor */
			SplitWindow(const Rect& rect, const Size ratio = 50)
			: WindowBase{rect}, _panes{ }, _ratio{ratio} {

				if (rect.empty()) { Debug::print("empty rect"); return; }
				helper_constructor();
			}

			/* split constructor */
			template <pane_c P, split_c T>
			SplitWindow(const Rect& rect, Window<P, T>* win)
			: WindowBase{rect}, _panes{ }, _ratio{50} {

				if (rect.empty()) { Debug::print("empty rect"); return; }
				_split_ctor(win);
			}



			template <split_c T>
			void _split_ctor(Window<pane_one_t, T>* win) requires(hsplit_c<S>) {
				// compute pane 1 height
				const Size p_h1 = win->_rect.h * _ratio / 100;
				// compute pane 2 height
				const Size p_h2 = win->_rect.h - p_h1;

				Rect r1{_rect.x, _rect.y,        _rect.w, p_h1};
				Rect r2{_rect.x, _rect.y + p_h1, _rect.w, p_h2};


				_panes[ONE].template make<WinOne>(r1, this); // INFO: moved window
				_panes[TWO].template make<WinTwo>(r2, this);

			}

			template <split_c T>
			void _split_ctor(Window<pane_two_t, T>* win) requires(hsplit_c<S>) {
				// compute pane 1 height
				const Size p_h1 = win->_rect.h * _ratio / 100;
				// compute pane 2 height
				const Size p_h2 = win->_rect.h - p_h1;

				Rect r1{_rect.x, _rect.y,        _rect.w, p_h1};
				Rect r2{_rect.x, _rect.y + p_h1, _rect.w, p_h2};

				_panes[ONE].template make<WinOne>(r1, this);
				_panes[TWO].template make<WinTwo>(r2, this); // INFO: moved window

			}


			template <split_c T>
			void _split_ctor(Window<pane_one_t, T>* win) requires(vsplit_c<S>) {
				// compute pane 1 width
				const Size p_w1 = _rect.w * _ratio / 100;
				// compute pane 2 width
				const Size p_w2 = _rect.w - p_w1;

				Rect r1{_rect.x,        _rect.y, p_w1, _rect.h};
				Rect r2{_rect.x + p_w1, _rect.y, p_w2, _rect.h};

				_panes[ONE].template make<WinOne>(r1, this); // INFO: moved window
				_panes[TWO].template make<WinTwo>(r2, this);

			}

			template <split_c T>
			void _split_ctor(Window<pane_two_t, T>* win) requires(vsplit_c<S>) {
				// compute pane 1 width
				const Size p_w1 = _rect.w * _ratio / 100;
				// compute pane 2 width
				const Size p_w2 = _rect.w - p_w1;

				Rect r1{_rect.x,        _rect.y, p_w1, _rect.h};
				Rect r2{_rect.x + p_w1, _rect.y, p_w2, _rect.h};

				_panes[ONE].template make<WinOne>(r1, this);
				_panes[TWO].template make<WinTwo>(r2, this); // INFO: moved window

			}

			/* helper constructor vsplit */
			void helper_constructor(void) requires(vsplit_c<S>) {
				// compute pane 1 width
				const Size p_w1 = (_rect.w * _ratio / 100) - 1;
				// compute pane 2 width
				const Size p_w2 = _rect.w - (p_w1 + 1);

				Rect r1{_rect.x,        _rect.y, p_w1, _rect.h};
				Rect r2{_rect.x + p_w1 + 1, _rect.y, p_w2, _rect.h};

				// allocate windows
				_panes[ONE].template make<WinOne>(r1, this);
				_panes[TWO].template make<WinTwo>(r2, this);

			}

			/* helper constructor hsplit */
			void helper_constructor(void) requires(hsplit_c<S>) {
				// compute pane 1 height
				const Size p_h1 = _rect.h * _ratio / 100;
				// compute pane 2 height
				const Size p_h2 = _rect.h - p_h1;

				Rect r1{_rect.x, _rect.y,        _rect.w, p_h1};
				Rect r2{_rect.x, _rect.y + p_h1, _rect.w, p_h2};
				// allocate windows
				_panes[ONE].template make<WinOne>(r1, this);
				_panes[TWO].template make<WinTwo>(r2, this);
			}


			/* non-assignable class */
			NON_ASSIGNABLE(SplitWindow);

			/* destructor */
			~SplitWindow(void) override {
				Debug::print("dtor: \"split\"\n");
			}


			// -- O V E R R I D E S -------------------------------------------

			/* draw override */
			void draw(int& i) override {
				if (_panes[0]) { _panes[0]->draw(i); } else { Debug::print("pane 1 is null"); }
				if (_panes[1]) { _panes[1]->draw(i); } else { Debug::print("pane 2 is null"); }
			}

			void debug(int i) override {
				for (int j = 0; j < i; j++) {
					Xf::Debug::print("  ");
				}
				if constexpr (vsplit_c<S>) {
					Xf::Debug::print("\x1b[32mV_split\x1b[0m %dx%d\n", _rect.w, _rect.h);
				} else if constexpr (hsplit_c<S>) {
					Xf::Debug::print("\x1b[35mH_split\x1b[0m %dx%d\n", _rect.w, _rect.h);
				}
				// print split info
				_panes[0]->debug(i + 1);
				_panes[1]->debug(i + 1);
			}


			/* split pane one */
			template <split_c T, pane_one_c P>
			void split(Window<P, S>* window) {
				Debug::print("split pane one\n");
				Pane unique = Xf::move(_panes[0]);
				_panes[ONE].template make<SplitWindow<T>>(unique->_rect, window);
			}

			/* split pane two */
			template <split_c T, pane_two_c P>
			void split(Window<P, S>* window) {
				Debug::print("split pane two\n");
				Pane unique = Xf::move(_panes[1]);
				_panes[TWO].template make<SplitWindow<T>>(unique->_rect, window);
			}

			/*
			template <pane_one_c P>
			Evntmode* search_left(void) requires(vsplit_c<S>) {

			}

			template <pane_two_c P>
			Evntmode* search_left(void) requires(vsplit_c<S>) {
				return _panes[ONE].template search_left<P>();

			}

			Evntmode* get_left(void) {
				return _panes[ONE].get_left();
			}*/



			// -- A L I A S E S -----------------------------------------------

			/* size type */
			using Size = UInt64;

			/* pane type */
			using Pane = UniquePtr<WindowBase>;

			/* array type */
			using PArray = Array<Pane, 2>;


		//protected:

			// -- P R O T E C T E D  M E M B E R S ----------------------------

			PArray _panes;

			Size _ratio;


	};





	// -- W I N D O W  C L A S S ----------------------------------------------

	template <pane_c P, split_c S>
	struct Window final : public WindowBase {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* size type */
			using Size = UInt64;

			/* self type */
			using Self = Window<P, S>;

			/* parent type */
			using Parent = SplitWindow<S>*;



			// -- C O N S T R U C T O R S -------------------------------------

			/* deleted default constructor */
			Window(void) = delete;

			/* rect constructor */
			Window(const Xf::Rect& rect, SplitWindow<S>* parent = nullptr)
			:   WindowBase{rect},
				_parent{parent},
				_mode{Event::instance().new_mode()} {
				// code here...
				subscribe();
			}

			Window(const Rect& rect, Evntmode&& mode, Parent parent)
			:   WindowBase{rect},
				_parent{parent},
				//_mode{Xf::move(mode)} { // WARNING: this causes a segfault
				// because the mode use deleted object instance
				_mode{Event::instance().new_mode()} {
				// code here...
				subscribe();
			}

			void subscribe(void) {

				using Ev = Xf::Evntype;

				// set event callback
				_mode.subscribe(Ev::ESC,     &Window::exit,    this);
				_mode.subscribe(Ev::CR,      &Window::v_split, this);
				_mode.subscribe(Ev::SPACE,   &Window::h_split, this);
				//_mode.subscribe(Ev::LEFT,    &Window::move_left,    this);

				Event::instance().stack_mode(_mode, Evntopt::FORCE);
			}


			/* non-assignable class */
			NON_ASSIGNABLE(Window);

			/* destructor */
			~Window(void) override {
				_DTOR("Window");
			}


			// -- M E T H O D S -----------------------------------------------

			/* set rect */
			void set_rect(const Xf::Rect& rect) {
				// set rect
				_rect = rect;
				// set border
				_border.set(rect);
			}


			/* exit window */
			void exit(void) {

				if (Event::instance().is_mode(_mode)) {
					Debug::print("IS MODE\n");
				}

				Xf::Event::instance().unstack_mode();
				Xf::Debug::print("unstack window mode\n");
			}

			/* update window */
			void update(void) { }


			// -- O V E R R I D E S -------------------------------------------

			/* draw window */
			void draw(int& i) override {
				if (Xf::Event::instance().is_mode(_mode)) {
					// set color
					//Xf::Escape::draw<Xf::hex_color_t>(0x37FFDA, true);
					Xf::Escape::hex_color(0x37FFDA, true);
				}
				// draw border
				_border.draw();
				// reset color
				//Xf::Escape::draw<Xf::reset_style_t>();
				Xf::Escape::reset_style();
				++i;
			}

			void debug(int i) override {
				for (int j = 0; j < i; ++j) {
					Xf::Debug::print("  ");
				}
				if (Xf::Event::instance().is_mode(_mode)) {
					Xf::Debug::print("\x1b[37;1m");
				}
				if constexpr (pane_one_c<P>) {
					Xf::Debug::print("pane one");
				} else if constexpr (pane_two_c<P>) {
					Xf::Debug::print("pane two");
				}
				Xf::Debug::print(" %dx%d\n", _rect.w, _rect.h);
				Xf::Debug::print("\x1b[0m");
			}

			/* split window */
			void v_split(void) {
				// check if window is too small
				if (_rect.w < 10) { Debug::print("too small\n"); return; }
				// check if parent exists
				if (!_parent) {
					Debug::print("no parent\n");
					// let window manager handle it
					WindowManager::new_split<vsplit_t>();
					return;
				}
				Debug::print("let parent split\n");
				// let parent handle it
				_parent->template split<vsplit_t>(this);
			}

			/* split window */
			void h_split(void) {
				// check if window is too small
				if (_rect.h < 10) { Debug::print("too small\n"); return; }
				// check if parent exists
				if (!_parent) {
					Debug::print("no parent\n");
					// let window manager handle it
					WindowManager::new_split<hsplit_t>();
					return;
				}
				Debug::print("let parent split\n");
				// let parent handle it
				_parent->template split<hsplit_t>(this);
			}

			/* move left */
			void move_left(void) {
				if (_parent) {
					;//Evntmode* mode = _parent->search_left(this);
				}
			}

			/*Evntmode* search_left(void) {
				return &_mode;
			}*/


			// -- P R I V A T E  M E M B E R S --------------------------------

			Parent _parent;

			Evntmode _mode;


	};





	class Win {

		public:

			Win(void) = delete;

			Win(const Xf::Rect& rect) : _rect(rect) { }

			~Win(void) = default;


		private:

			/* coordinates */
			Xf::Rect   _rect;

			/* border */
			Xf::Border _border;

			/* children */
			Xf::List<Win> _children;

			/* parent */
			Win* _parent;
	};








}

#endif
