#ifndef PATH_HEADER
#define PATH_HEADER

#include "output.hpp"
#include "types.hpp"
#include "string.hpp"
#include "vector.hpp"
#include "literal.hpp"
#include "safe_enum.hpp"
#include "tuple.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- path type -----------------------------------------------------------

	/* path type definition */
	struct path_type_def {
		// integral type
		using type = xns::u8;
		// enum type
		enum enum_type : type {
			ABSOLUTE,
			RELATIVE,
			UNDEFINED,
			MAX
		};
	};

	/* path type */
	using path_type = xns::safe_enum<path_type_def>;


	// -- segment type --------------------------------------------------------

	/* segment type definition */
	struct segment_type_def {
		// integral type
		using type = xns::u8;
		// enum type
		enum enum_type : type {
			PARENT,
			ENTITY,
			MAX
		};
	};

	/* segment type */
	using segment_type = xns::safe_enum<segment_type_def>;


	// -- path access ---------------------------------------------------------

	/* path access definition */
	struct path_access_def {
		// integral type
		using type = xns::u8;
		// enum type
		enum enum_type : type {
			STR,
			SEG,
			MAX
		};
	};

	/* path access */
	using path_access = xns::safe_enum<path_access_def>;


	// -- P A T H  C L A S S --------------------------------------------------

	template <xns::is_string T>
	class path {


		public:

			// -- T Y P E S ---------------------------------------------------

			/* string type */
			using string_type  = T;

			/* self type */
			using self         = path<string_type>;

			/* character type */
			using char_t       = typename string_type::char_t;

			/* segment2 type */
			using segment      = xns::tuple<string_type, segment_type>;

			/* segment list type */
			using segment_list = xns::vector<segment>;

			/* size type */
			using size_type    = typename segment_list::size_type;

			/* string size type */
			using string_size  = typename string_type::size_type;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			path(void)
			: _segments{}, _type{path_type::UNDEFINED} {
				// nothing to do...
			}

			/* path constructor */
			path(const string_type& path)
			: _segments{}, _type{path_type::UNDEFINED} {
				// resolve path
				resolve(path);
			}

			/* non-copyable class */
			NON_COPYABLE(path);

			/* move constructor */
			path(path&& other) noexcept
			: _segments{xns::move(other._segments)}, _type{other._type} {
				// nothing to do...
			}

			/* destructor */
			~path(void) = default;


			// -- A S S I G N M E N T -----------------------------------------

			/* path assignment */
			path& assign(const string_type& path) {
				// resolve path
				resolve(path);
				// return self reference
				return *this;
			}

			/* move assignment */
			path& assign(path&& other) noexcept {
				// check for self-assignment
				if (this != &other) {
					// move members
					_segments = xns::move(other._segments);
					_type     = other._type;
				} // return self reference
				return *this;
			}


			// -- A S S I G N M E N T  O P E R A T O R S ----------------------

			/* path assignment operator */
			path& operator=(const string_type& path) {
				// return path assignment
				return assign(path);
			}

			/* move assignment operator */
			path& operator=(path&& other) noexcept {
				// return move assignment
				return assign(xns::move(other));
			}


			// -- S E G M E N T  A C C E S S O R S ----------------------------

			/* get segment */
			const segment& operator[](const size_type index) const {
					// return string segment
					return _segments[index];
			}

			/* get segment string */
			const string_type& string(const size_type index) const {
				// return string segment
				return _segments[index].template get<0>();
			}

			/* get segment type */
			segment_type type(const size_type index) const {
				// return segment type
				return _segments[index].template get<1>();
			}





			// -- A C C E S S O R S -------------------------------------------

			/* segment count */
			size_type count(void) const {
				// return segment count
				return _segments.size();
			}

			/* empty path */
			bool empty(void) const {
				// return empty path
				return _segments.empty();
			}

			/* path type */
			path_type type(void) const {
				// return path type
				return _type;
			}


			// -- C O M P A R I S O N  O P E R A T O R S ----------------------

			/* path type equality */
			bool operator==(const path_type type) const {
				// return path type equality
				return _type == type;
			}

			/* path type inequality */
			bool operator!=(const path_type type) const {
				// return path type inequality
				return _type != type;
			}




		private:


			// -- P R I V A T E  E N U M S ------------------------------------

			/* enum for character types */
			enum {
				EOS = 0x00, // end of string
				SEP = 0x2f, // separator
				CUR = 0x2e, // current directory
				PAR = 0x2e2e // parent directory
			};



			// -- P R I V A T E  M E T H O D S --------------------------------

			/* resolve path */
			void resolve(const string_type& path) {

				// clear previous segments if any
				_segments.clear();
				// allocate space for segments
				_segments.reserve(16);

				// loop over characters in path
				for (string_size x = 0, z = 0; x < path.size(); x += z, z = 0) {

					// skip separator
					while (path[x] == SEP) { ++x; }
					// count characters
					while (path[x + z] != EOS && path[x + z] != SEP) { ++z; }
					// check for empty segment
					if (z == 0) { continue; }
					// skip current segment
					if (z == 1 && path[x] == CUR) { continue; }

					// check for parent segment
					if (z == 2 && path[x] == CUR && path[x + 1] == CUR) {
						// check for previous parent segment
						if (_segments.empty()
							|| _segments.back().template get<1>() == segment_type::PARENT) {
							// add parent segment
							_segments.emplace_back(string_type{&path[x], z}, segment_type::PARENT);
						} // else remove previous segment
						else { _segments.pop_back(); }
					}

					// add entity segment
					else {
						_segments.emplace_back(string_type{&path[x], z}, segment_type::ENTITY);
					}
				}

				// set path type
				if (!path.empty() && path[0] == SEP) {
					// set absolute path type
					_type = path_type::ABSOLUTE;
				} // set relative path type
				else { _type = path_type::RELATIVE; }

			}



			// -- M E M B E R S -----------------------------------------------

			/* path segments */
			segment_list _segments;

			/* path type */
			path_type _type;


	};



}


#endif

