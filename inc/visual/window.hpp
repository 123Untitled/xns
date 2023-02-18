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

				_root.set_pointer(new SplitWindow<S>{{0, 0, width, height}});
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

		public:

			// -- A L I A S E S -----------------------------------------------

			/* reinject type */
			using Type = SplitWindow<S>;

			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			SplitWindow(void) = delete;

			/* rect constructor */
			SplitWindow(const Rect& rect, const Size ratio = 50)
			: WindowBase{rect}, _panes{ }, _ratio{ratio} {

				if (rect.empty()) { return; }
				helper_constructor();
			}

			/* split constructor */
			template <pane_c P, split_c T>
			SplitWindow(const Rect& rect, Window<P, T>* win)
			: WindowBase{rect}, _panes{ }, _ratio{50} {

				if (rect.empty()) { return; }
				_split_ctor(win);
			}



			template <split_c T>
			void _split_ctor(Window<pane_one_t, T>* win) requires(hsplit_c<S>) {
				// compute pane 1 height
				const Size p_h1 = win->_rect.h * _ratio / 100;
				// compute pane 2 height
				const Size p_h2 = win->_rect.h - p_h1;

				// WARNING: need to set new window parent !
				//win->set_rect();
				//win->set_parent(this);
				// allocate windows
				//_panes[0].set_pointer(win);
				_panes[0].set_pointer(new Window<pane_one_t, S>{{_rect.x, _rect.y,        _rect.w, p_h1}, Xf::move(win->_mode), this});

				_panes[1].set_pointer(new Window<pane_two_t, S>{{_rect.x, _rect.y + p_h1, _rect.w, p_h2}, this});
			}

			template <split_c T>
			void _split_ctor(Window<pane_two_t, T>* win) requires(hsplit_c<S>) {
				// compute pane 1 height
				const Size p_h1 = win->_rect.h * _ratio / 100;
				// compute pane 2 height
				const Size p_h2 = win->_rect.h - p_h1;
				// WARNING: need to set new window parent !
				//win->set_rect({_rect.x, _rect.y + p_h1, _rect.w, p_h2});
				//win->set_parent(this);
				// allocate windows
				//_panes[1].set_pointer(win);
				_panes[1].set_pointer(new Window<pane_two_t, S>{{_rect.x, _rect.y + p_h1, _rect.w, p_h2}, Xf::move(win->_mode), this});
				_panes[0].set_pointer(new Window<pane_one_t, S>{{_rect.x, _rect.y,        _rect.w, p_h1}, this});
			}


			template <split_c T>
			void _split_ctor(Window<pane_one_t, T>* win) requires(vsplit_c<S>) {
				// compute pane 1 width
				const Size p_w1 = _rect.w * _ratio / 100;
				// compute pane 2 width
				const Size p_w2 = _rect.w - p_w1;

				// WARNING: need to set new window parent !
				//win->set_rect({_rect.x, _rect.y, p_w1, _rect.h});
				//win->set_parent(this);
				// allocate windows
				//_panes[0].set_pointer(win);
				_panes[0].set_pointer(new Window<pane_one_t, S>{{_rect.x, _rect.y, p_w1, _rect.h}, Xf::move(win->_mode), this});
				_panes[1].set_pointer(new Window<pane_two_t, S>{{_rect.x + p_w1, _rect.y, p_w2, _rect.h}, this});
			}

			template <split_c T>
			void _split_ctor(Window<pane_two_t, T>* win) requires(vsplit_c<S>) {
				// compute pane 1 width
				const Size p_w1 = _rect.w * _ratio / 100;
				// compute pane 2 width
				const Size p_w2 = _rect.w - p_w1;

				// WARNING: need to set new window parent !
				//win->set_rect({_rect.x + p_w1, _rect.y, p_w2, _rect.h});
				//win->set_parent(this);
				// allocate windows
				//_panes[1].set_pointer(win);

				_panes[1].set_pointer(new Window<pane_two_t, S>{{_rect.x + p_w1, _rect.y, p_w2, _rect.h}, Xf::move(win->_mode), this});
				_panes[0].set_pointer(new Window<pane_one_t, S>{{_rect.x, _rect.y, p_w1, _rect.h}, this});
			}





			/* helper constructor vsplit */
			void helper_constructor(void) requires(vsplit_c<S>) {
				// compute pane 1 width
				const Size p_w1 = _rect.w * _ratio / 100;
				// compute pane 2 width
				const Size p_w2 = _rect.w - p_w1;
				// allocate windows
				_panes[0].set_pointer(new Window<pane_one_t, S>{{_rect.x,        _rect.y, p_w1, _rect.h}, this});
				_panes[1].set_pointer(new Window<pane_two_t, S>{{_rect.x + p_w1, _rect.y, p_w2, _rect.h}, this});
			}

			/* helper constructor hsplit */
			void helper_constructor(void) requires(hsplit_c<S>) {
				// compute pane 1 height
				const Size p_h1 = _rect.h * _ratio / 100;
				// compute pane 2 height
				const Size p_h2 = _rect.h - p_h1;
				// allocate windows
				_panes[0].set_pointer(new Window<pane_one_t, S>{{_rect.x, _rect.y,        _rect.w, p_h1}, this});
				_panes[1].set_pointer(new Window<pane_two_t, S>{{_rect.x, _rect.y + p_h1, _rect.w, p_h2}, this});
			}


			/* non-assignable class */
			NON_ASSIGNABLE(SplitWindow);

			/* destructor */
			~SplitWindow(void) override = default;


			// -- O V E R R I D E S -------------------------------------------

			/* draw override */
			void draw(int& i) override {
				if (_panes[0]) { _panes[0]->draw(i); }
				if (_panes[1]) { _panes[1]->draw(i); }
			}

			void debug(int i) override {
				for (int j = 0; j < i; j++) {
					Xf::Debug::print("  ");
				}
				if constexpr (vsplit_c<S>) {
					Xf::Debug::print("\x1b[32mV_split\x1b[0m\n");
				} else if constexpr (hsplit_c<S>) {
					Xf::Debug::print("\x1b[35mH_split\x1b[0m\n");
				}
				// print split info
				_panes[0]->debug(i + 1);
				_panes[1]->debug(i + 1);
			}


			/* split pane one */
			template <split_c T, pane_one_c P>
			void split(Window<P, S>* window) {

				Rect rect = _panes[0]->_rect; // INFO: rect is in window class
				_panes[0].release();
				_panes[0].set_pointer(new SplitWindow<T>{rect, window});
			}

			/* split pane two */
			template <split_c T, pane_two_c P>
			void split(Window<P, S>* window) {

				Rect rect = _panes[1]->_rect; // INFO: rect is in window class
				_panes[1].release();
				_panes[1].set_pointer(new SplitWindow<T>{rect, window});
			}


			// -- A L I A S E S -----------------------------------------------

			/* size type */
			using Size = UInt64;

			/* array type */
			using Array = Array<UniquePtr<WindowBase>, 2>;


		//protected:

			// -- P R O T E C T E D  M E M B E R S ----------------------------

			Array _panes;

			Size _ratio;


		//private:

			// -- P R I V A T E  M E T H O D S --------------------------------


	};





	// -- W I N D O W  C L A S S ----------------------------------------------

	template <pane_c P, split_c S>
	struct Window final : public WindowBase {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* size type */
			using Size = UInt64;


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

			Window(const Rect& rect, Evntmode&& mode, SplitWindow<S>* parent)
			:   WindowBase{rect},
				_parent{parent},
				_mode{Xf::move(mode)} {
				// code here...
			}

			void subscribe(void) {
				using Ev = Xf::Evntype;
				// set event callback
				_mode.subscribe(Ev::ESC,  &Window::exit, this);
				_mode.subscribe(Ev::CR,   &Window::v_split, this);
				_mode.subscribe(Ev::SPACE,   &Window::h_split, this);
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
					Xf::Escape::draw<Xf::Escape::hex_color_t>(0x37FFDA, true);
				}
				// draw border
				_border.draw();
				// reset color
				Xf::Escape::draw<Xf::Escape::reset_style_t>();
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
					Xf::Debug::print("pane one\n");
				} else if constexpr (pane_two_c<P>) {
					Xf::Debug::print("pane two\n");
				}
				Xf::Debug::print("\x1b[0m");
			}

			/* split window */
			void v_split(void) {

				if (!_parent) {
					WindowManager::new_split<vsplit_t>();
					return; } // INFO: need to handle this

				if (_rect.w < 10) { return; }

				_parent->template split<vsplit_t>(this);
			}

			/* split window */
			void h_split(void) {

				if (!_parent) {
					WindowManager::new_split<hsplit_t>();
					return; } // INFO: need to handle this

				if (_rect.h < 10) { return; }

				_parent->template split<hsplit_t>(this);
			}


			// -- P R I V A T E  M E M B E R S --------------------------------

			/*bool _visible;
			bool _active;
			bool _selected;*/

			SplitWindow<S>* _parent;

			Evntmode _mode;


	};






}



#endif
