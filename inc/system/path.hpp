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


	// -- P A T H  C L A S S --------------------------------------------------

	class path {

		private:

			// -- P R I V A T E  E N U M S ------------------------------------

			/* segment type */
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


		public:

			// -- T Y P E S ---------------------------------------------------

			/* character type */
			using char_t = char;

			/* string type */
			using string = xns::string<char_t>;

			/* segment2 type */
			using segment = xns::tuple<xns::string<char_t>, segment_type>;

			/* segment list type */
			using segment_list = xns::vector<segment>;

			/* size type */
			using size_type = typename segment_list::size_type;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			path(void);

			/* path constructor */
			path(const string&);

			/* non-copyable class */
			NON_COPYABLE(path);

			/* move constructor */
			path(path&&) noexcept;

			/* destructor */
			~path(void) = default;


			// -- A S S I G N M E N T -----------------------------------------

			/* path assignment */
			path& assign(const string&);

			/* move assignment */
			path& assign(path&&) noexcept;


			// -- A S S I G N M E N T  O P E R A T O R S ----------------------

			/* path assignment operator */
			path& operator=(const string&);

			/* move assignment operator */
			path& operator=(path&&) noexcept;


			// -- S E G M E N T  A C C E S S O R S ----------------------------

			/* get segment */
			const segment& operator[](const size_type) const;


			// -- A C C E S S O R S -------------------------------------------

			/* segment count */
			size_type count(void) const;


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
			void resolve(const string&);



			// -- M E M B E R S -----------------------------------------------

			/* path segments */
			segment_list _segments;

			/* path type */
			path_type _type;


	};



}




#endif

