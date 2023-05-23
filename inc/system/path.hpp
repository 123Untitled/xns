#ifndef PATH_HEADER
#define PATH_HEADER

#include "types.hpp"
#include "string.hpp"
#include "vector.hpp"
#include "literal.hpp"
#include "safe_enum.hpp"


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
			MAX
		};
	};

	/* path type */
	using path_type = xns::safe_enum<path_type_def>;


	template <class S, class P, class C>
	concept common_char = xns::is_all_same< xns::literal_char<S>,
											xns::literal_char<P>,
											xns::literal_char<C>>;



	// -- P A T H  C L A S S --------------------------------------------------

	template <xns::is_literal S, xns::is_literal P, xns::is_literal C>
	class path {


		// -- A S S E R T I O N S ---------------------------------------------

		/* require common character type */
		static_assert(xns::common_char<S, P, C>, "LITERALS MUST HAVE THE SAME CHARACTER TYPE");


		public:

			// -- T Y P E S ---------------------------------------------------

			/* character type */
			using char_t = xns::literal_char<S>;

			/* segment type */
			using segment = xns::string<char_t>;

			/* segment list type */
			using segment_list = xns::vector<segment, xns::moveable_t>;

			/* size type */
			using size_type = typename segment_list::size;


			// -- F R I E N D S -----------------------------------------------

			/* make template arguments friends */
			template <xns::is_literal T, xns::is_literal U, xns::is_literal V>
			friend class path;

			/* make path a friend */
			template <xns::is_literal T, xns::is_literal U, xns::is_literal V>
			friend auto make_path(const xns::string<literal_char<T>>&) -> xns::path<T, U, V>;

			/* make path overloads friends */
			template <class T, class U>
			friend auto make_path(const xns::string<U>&);


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			path(void) { }

			/* non-copyable class */
			NON_COPYABLE(path);

			/* move constructor */
			path(path&&) noexcept;

			/* destructor */
			~path(void) = default;


			// -- M O V E  O P E R A T O R S ----------------------------------

			/* move assignment operator */
			path& operator=(path&&) noexcept;

			using test = void (*)(void);

		private:

			// -- M E M B E R S -----------------------------------------------

			/* path segments */
			segment_list _segments;

			/* path type */
			path_type _type;



	};




	// -- F R I E N D  F U N C T I O N S --------------------------------------

	/* make path */
	template <class T>
	auto make_path(const xns::string<char>& input) {

		using S = decltype(T{}.template get<0>());
		using P = decltype(T{}.template get<1>());
		using C = decltype(T{}.template get<2>());

		xns::path<S, P, C> path;
		path._segments = input.template split<xns::moveable_t> (S::data());

		for (unsigned i = 0; i < path._segments.length(); ++i) {
			std::cout << path._segments[i] << std::endl;
		}



	}


	/* make path */
	/*template <xns::is_literal S, xns::is_literal P, xns::is_literal C>
	auto make_path(const xns::string<literal_char<S>>& input) -> xns::path<S, P, C> {

		xns::path<S, P, C> path;
		path._segments = input.template split<xns::moveable_t> (S::data());

		for (unsigned i = 0; i < path._segments.length(); ++i) {
			std::cout << path._segments[i] << std::endl;
		}

		return path;


	}*/





}




#endif

