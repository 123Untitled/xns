#ifndef XNS_TYPE_AT_HEADER
#define XNS_TYPE_AT_HEADER

#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- T Y P E  A T --------------------------------------------------------

	namespace ___impl {


		template <unsigned ___idx, typename... ___params>
		class ___type_at final {


			// -- assertions --------------------------------------------------

			/* check if pack is not empty */
			static_assert(sizeof...(___params) > 0,
					"type_at: parameter pack is empty.");

			/* check if index is valid */
			static_assert(___idx < sizeof...(___params),
					"type_at: index is out of range.");


			private:

				// -- private implementation ----------------------------------

				/* forward declaration */
				template <unsigned, typename...>
				struct ___;

				/* specialization for ___n == ___idx */
				template <unsigned ___n, typename ___type, typename... ___types> requires (___n == ___idx)
				struct ___<___n, ___type, ___types...> final {
					using type = ___type;
					___xns_not_instantiable(___);
				};

				/* specialization for ___n < ___idx */
				template <unsigned ___n, typename ___type, typename... ___types> requires (___n < ___idx)
				struct ___<___n, ___type, ___types...> final {
					using type = typename ___<___n + 1U, ___types...>::type;
					___xns_not_instantiable(___);
				};


			public:

				// -- public types --------------------------------------------

				/* type indexed by IDX */
				using type = typename ___<0U, ___params...>::type;


				// -- public lifecycle ----------------------------------------

				/* non-instantiable class */
				___xns_not_instantiable(___type_at);

		}; // class ___type_at

	} // namespace ___impl


	/* type at */
	template <unsigned ___idx, typename... ___params>
	using type_at = typename xns::___impl::___type_at<___idx, ___params...>::type;

} // namespace xns

#endif // XNS_TYPE_AT_HEADER
