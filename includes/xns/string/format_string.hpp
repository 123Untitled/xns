#ifndef XNS_FORMAT_STRING_HEADER
#define XNS_FORMAT_STRING_HEADER


#include "xns/type_traits/type_categories/is_char.hpp"
#include "xns/string/string.hpp"


namespace xns {

	constexpr const char* str = R"(

	)";


	// -- F O R M A T E D  S T R I N G  I T E R A T O R -----------------------

	/* formatted string iterator */
	template <xns::is_char T>
	class formated_string_iterator {

		public:


			// -- public types ------------------------------------------------

			/* self type */
			using self = formated_string_iterator<T>;

			/* const pointer type */
			using const_pointer = const T*;

			/* size type */
			using size_type = typename basic_string<T>::size_type;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			formated_string_iterator(void) = delete;

			/* constructor */
			template <xns::is_string S>
			constexpr formated_string_iterator(const S& str, const xns::size_t size) noexcept
			: _min{str.data()},
			  _max{str.data() + str.size()},
			  _size{size},
			  _view{} {
				*this += size;
			}

			/* destructor */
			~formated_string_iterator(void) noexcept = default;


			// -- public boolean operators ------------------------------------

			/* boolean operator */
			constexpr operator bool(void) const noexcept {
				return _view.empty() == false;
				// return validity
				return _min < _max;
			}

			/* not operator */
			constexpr bool operator!(void) const noexcept {
				// return invalidity
				return _min >= _max;
			}


			// -- public accessors --------------------------------------------

			/* dereference operator */
			constexpr basic_string_view<T> operator*(void) const noexcept {
				return _view;
			}



			// -- public increment operators ----------------------------------

			/* prefix increment operator */
			constexpr self& operator++(void) noexcept {

				*this += 1;

				return *this;
			}


			constexpr self operator+=(const size_type size) noexcept {

				size_type x = 0;
				const_pointer pos = _min;

				// loop over string
				while ((pos < _max) && (x < size)) {

					// check for escape character
					if (*pos == 27) {
						// skip escape sequence
						while (pos < _max && *pos != 'm') {
							++pos;
						}
						(pos < _max) && ++pos;
						continue;
					}
					// count characters
					while (pos < _max && *pos != 27 && x < size) {
						++x; ++pos;
					}
				}

				// skip trailing escape sequence
				while (pos < _max && *pos == 27) {
					while (pos < _max && *pos != 'm') {
						++pos;
					}
					(pos < _max) && ++pos;
				}

				size_type len = static_cast<size_type>(pos - _min);

				_view = basic_string_view<T>{_min, len};

				_min = pos;


				return *this;
			}






		private:


			/* range min */
			const_pointer _min;

			/* range max */
			const_pointer _max;

			/* line size */
			xns::size_t _size;

			/* view */
			basic_string_view<T> _view;





	}; // formated_string_iterator

	// deduction guide
	template <xns::is_string S>
	formated_string_iterator(const S&, const xns::size_t) -> formated_string_iterator<typename S::char_t>;



	// -- F O R M A T E D  S T R I N G ----------------------------------------

	// -- forward declarations ------------------------------------------------

	template <xns::is_char T>
	class basic_fmt_string;

	/* c-string ascii type */
	using fmt_string = basic_fmt_string<char>;

	/* wide string type */
	using wfmt_string = basic_fmt_string<wchar_t>;

	/* utf-8 string type */
	using u8fmt_string = basic_fmt_string<char8_t>;

	/* utf-16 string type */
	using u16fmt_string = basic_fmt_string<char16_t>;

	/* utf-32 string type */
	using u32fmt_string = basic_fmt_string<char32_t>;


	// -- basic_fmt_string ----------------------------------------------------

	/* formatted string */
	template <xns::is_char T>
	class basic_fmt_string {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = basic_fmt_string<T>;



			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr basic_fmt_string(void) noexcept = default;

			/* string copy constructor */
			constexpr basic_fmt_string(const basic_string<T>& string) noexcept
			: _string{string},
			  _size{vlength(string)} {
			}

			/* string move constructor */
			constexpr basic_fmt_string(basic_string<T>&& string) noexcept
			: _string{xns::move(string)},
			  _size{vlength(_string)} {
			}

			template <class... A>
			constexpr basic_fmt_string(A&&... args) noexcept
			: _string{xns::forward<A>(args)...},
			  _size{vlength(_string)} {
			}

			/* destructor */
			~basic_fmt_string(void) noexcept = default;


			// -- public accessors --------------------------------------------

			/* string size */
			constexpr xns::size_t vsize(void) const noexcept {
				return _size;
			}

			/* string object */
			constexpr xns::basic_string<T>& string(void) noexcept {
				return _string;
			}

			/* const string object */
			constexpr const xns::basic_string<T>& string(void) const noexcept {
				return _string;
			}


			// -- public modifiers --------------------------------------------

			/* compute length */
			constexpr void compute_length(void) noexcept {
				_size = vlength(_string);
			}


		private:

			// -- private methods ---------------------------------------------

			/* compute length */
			static constexpr typename basic_string<T>::size_type vlength(const basic_string<T>& str) noexcept {

				typename basic_string<T>::size_type x = 0;

				bool escape = false;

				// loop over string
				for (typename basic_string<T>::size_type i = 0; i < str.size(); ++i) {

					escape == false
					? str[i] == 27   ? escape = true : ++x
					: str[i] == 'm' && (escape = false);
				}

				return x;
			}

			// -- private members ---------------------------------------------

			/* string */
			xns::basic_string<T> _string;

			/* visual length */
			xns::size_t _size;

	};


	// -- sub-formated string -------------------------------------------------

	/* sub-formated string */
	template <class T>
	auto sub_fmt_string(const T& str, const xns::size_t size) noexcept -> basic_string<typename T::char_t> {

		using const_pointer = typename T::const_ptr;
		using size_type = typename T::size_type;

		size_type x = 0;
		const_pointer ptr = str.data();
		const_pointer end = str.data() + str.size();
		const_pointer esc = nullptr;
		size_type m = 0;

		// loop over string
		while ((ptr < end) && (x < size)) {

			// check for escape character
			if (*ptr == 27) {
				m = 0;
				esc = ptr;
				// skip escape sequence
				while (ptr < end && *ptr != 'm') {
					++ptr; ++m;
				}
				++m;
				(ptr < end) && ++ptr;

				continue;
			}
			// count characters
			while (ptr < end && *ptr != 27 && x < size) {
				++x; ++ptr;
			}
		}

		basic_string<typename T::char_t> result;

		x = 0;
		if (esc) {
			result.append(basic_string_view<typename T::char_t>{esc, m});

			/*
			for (size_type i = 0; i < result.size(); ++i) {

				char c = result[i];

				if (c == 27) {
					std::cout << "e";
				}
				else {
					std::cout << c;
				}

			}
			std::cout << std::endl;
			*/
		}


		result.append(basic_string_view<typename T::char_t>{ptr,
				(size_type)(end - ptr)});

		return result;
	}














	// -- S C R O L L A B L E  S T R I N G ------------------------------------

	// class to encapsulate a string used for being displayed on a screen
	// in a scrollable view

	template <xns::is_char T>
	class scrollable {

		private:

			// -- T Y P E S ---------------------------------------------------

			/* size type */
			using size_type = typename xns::basic_string<T>::size_type;

			// -- M E M B E R S -----------------------------------------------

			/* string */
			xns::basic_string<T> _str;

			/* view size */
			size_type _view_size; // size of view

			/* start position */
			size_type _view_start; // offset from start of string

			/* view position */
			size_type _string_cursor; // position in string

			/* view position */
			size_type _screen_cursor; // position in view

			/* scroll offset */
			size_type _scrolloff; // vim-like scroll offset (half of view size)



		public:

			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* default constructor */
			scrollable(void) noexcept
			: _str{}, _view_size{0}, _view_start{0}, _string_cursor{0}, _screen_cursor{0} {
			}

			/* destructor */
			~scrollable(void) noexcept = default;


			// -- P U B L I C  S E T T E R S ----------------------------------

			/* set view size */
			void set_view_width(const size_type width) noexcept {
				// set view size and scroll offset (half of view size)
				_scrolloff = (_view_size = width) / 2;
			}





			// -- P U B L I C  M O D I F I E R S ------------------------------

			/* insert */
			void insert(const xns::basic_string<T>& input) {
				_str.insert(_string_cursor, input);
				_string_cursor += input.length();
				_compute();
			}

			/* backspace */
			void backspace(void) {
				// check if cursor is not at start
				if (_string_cursor > 0) {
					// decrement cursor position
					//--_string_cursor;
					_str.erase(--_string_cursor);
					_compute();
				}
			}

			/* erase */
			void erase(void) {
				// check if cursor is not at end
				if (_str.not_empty()) {
					// erase character
					_str.erase(_string_cursor);
					_compute();
				}
			}


			/* move left */
			bool move_left(void) {
				// check if cursor is not at start
				if (_string_cursor > 0) {
					// decrement cursor position
					--_string_cursor;
					// compute view
					_compute();
					// return true
					return true;
				} // return false
				return false;
			}

			/* move right */
			bool move_right(void) {
				// check if cursor is not at end
				if (_string_cursor < _str.length()) {
					// increment cursor position
					++_string_cursor;
					// compute view
					_compute();
					// return true
					return true;
				} // return false
				return false;
			}

			/* reset */
			void reset(void) {
				// reset all members
				_str.clear();
				_view_start = 0;
				_string_cursor = 0;
				_screen_cursor = 0;
			}


			// -- P U B L I C  A C C E S S O R S ------------------------------

			/* const pointer */
			typename xns::basic_string<T>::const_pointer view_pointer(void) const {
				// return constant pointer to first display element
				return _str.pointer() + _view_start;
			}

			/* view size */
			size_type view_size(void) const {
				// check if string is smaller than view size
				if (_str.length() < _view_size) {
					// return string length
					return _str.length();
				} // else return view size
				return _view_size;
			}

			/* get screen cursor position */
			size_type cursor_position(void) const {
				// return screen cursor position
				return _screen_cursor;
			}

			/* string */
			xns::basic_string<T>& string(void) {
				// return string
				return _str;
			}

			/* const string */
			const xns::basic_string<T>& string(void) const {
				// return string
				return _str;
			}




		private:

			// -- P R I V A T E  M E T H O D S --------------------------------

			/* ajust after move */
			// implement scrolloff like in vim
			// let cursor be at the middle of the view

			void _compute(void) {


				// VERSION: LOCKED ON RIGHT

				/*
				if (_str.length() < _view_size) {
					_view_start = 0;
					_screen_cursor = _string_cursor;
					return;
				}
				else {
					if (_string_cursor >= _view_size) {
						_view_start = _string_cursor - _view_size;
						_screen_cursor = _view_size;
					}
					else {
						_view_start = 0;
						_screen_cursor = _string_cursor;
					}
					return;

				}
				return;


				// VERSION: NO SCROLLOFF

				// check if cursor is before view
				if (_string_cursor < _view_start) {
					// move view start to cursor
					_view_start = _string_cursor;
				}

				else if (_string_cursor >= _view_start + _view_size) {
					// move view start to cursor
					_view_start = _string_cursor - _view_size;
				}

				// compute view position
				_screen_cursor = _string_cursor - _view_start;


				return;

				*/


				// VERSION: SCROLLOFF

				// If string_cursor is closer to the start of the string than the scrolloff
				if (_string_cursor < _scrolloff) {
					_view_start = 0;
				}

				// string_cursor is closer to the end than the scrolloff
				else if (_string_cursor > _str.length() - _scrolloff) {
					_view_start = _str.length() - _view_size;
					if (_view_start < 0) {
						_view_start = 0;
					}
				}

				// string_cursor is somewhere in the middle
				else {
					_view_start = _string_cursor - _scrolloff;
				}


				// If the string is shorter than the view
				if (_str.length() < _view_size) {
					// Start the view at the beginning
					_view_start = 0;
					// And position the cursor relative to the start of the string
					_screen_cursor = _string_cursor;
				}
				else {
					// Otherwise compute screen cursor position normally
					_screen_cursor = _string_cursor - _view_start;
				}

			}

	};




} // namespace xns

#endif // XNS_FORMAT_STRING_HEADER
