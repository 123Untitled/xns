#ifndef XNS_TUPLE_HEADER
#define XNS_TUPLE_HEADER

// local headers
#include "types.hpp"
#include "move.hpp"
#include "forward.hpp"
#include "is_same.hpp"
#include "identity.hpp"
#include "is_all_unique.hpp"
#include "indexed_element.hpp"
#include "type_at.hpp"
#include "index_of.hpp"
#include "integer_sequence.hpp"
#include "in_place.hpp"

// c++ standard library headers
#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {



	// -- T U P L E  C L A S S ------------------------------------------------

	template <typename... A>
	class tuple final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = tuple<A...>;

			/* size type */
			using size_type = xns::size_t;


		private:

			// -- private static constants ------------------------------------

			/* size */
			static constexpr size_type num_elements = sizeof...(A);


			// -- private structs ---------------------------------------------

			/* element */
			template <size_type, typename T>
			struct element { T value; };

			/* impl */
			template <typename>
			struct impl;

			/* specialization for index sequence */
			template <size_type... I>
			struct impl<xns::index_sequence<I...>> final : public self::element<I, A>... {


				// -- public types --------------------------------------------

				/* self type */
				using self = impl<xns::index_sequence<I...>>;


				// -- public lifecycle ----------------------------------------

				/* default constructor */
				inline constexpr impl(void) noexcept
				// fold expression to default-initialize tuple elements
				: element<I, A>{}... {}

				/* variadic constructor */
				template <typename... U>
				inline constexpr impl(U&&... args)
				// fold expression to initialize tuple elements
				: element<I, A>{xns::forward<U>(args)}... {}

				/* copy constructor */
				inline constexpr impl(const self& other)
				// fold expression to copy-initialize tuple elements
				: element<I, A>{other}... {}

				/* move constructor */
				inline constexpr impl(self&& other) noexcept
				// fold expression to move-initialize tuple elements
				: element<I, A>{xns::move(other)}... {}

				/* destructor */
				inline constexpr ~impl(void) noexcept = default;


				// -- public assignment operators -----------------------------

				/* copy assignment operator */
				inline constexpr auto operator=(const self& other) -> self& {
					// INFO: check for self-assignment is not necessary (see below)
					// because this check is already done in the tuple::operator=()
					((element<I, A>::operator=(other)), ...);
					// return self-reference
					return *this;
				}

				/* move assignment operator */
				inline constexpr auto operator=(self&& other) noexcept -> self& {
					// INFO: check for self-assignment is not necessary (see below)
					// because this check is already done in the tuple::operator=()
					((element<I, A>::operator=(xns::move(other))), ...);
					// return self-reference
					return *this;
				}

			};



			// -- private types -----------------------------------------------

			/* sequence type */
			using sequence = xns::index_sequence_for<A...>;

			/* indexed type */
			template <size_type I>
			using indexed = xns::type_at<I, A...>;

			/* element from index */
			template <size_type I>
			using element_at = self::element<I, indexed<I>>;

			/* element from type */
			template <typename T>
			using element_from = element<xns::index_of<T, A...>(), T>;

			/* index of type */
			template <typename T>
			static constexpr xns::size_t _index_of = xns::index_of<T, A...>();


			// -- private members ---------------------------------------------

			/* implementation */
			self::impl<sequence> _impl;




			// -- private lifecycle -------------------------------------------



		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline constexpr tuple(void) noexcept
			: _impl{} {}

			/* variadic constructor */
			template <typename... U> requires (sizeof...(U) == sizeof...(A))
			inline constexpr tuple(U&&... args)
			: _impl{xns::forward<U>(args)...} {}

			/* copy constructor */
			inline constexpr tuple(const self& tuple)
			: _impl{tuple._impl} {}

			/* move constructor */
			inline constexpr tuple(self&& tuple) noexcept
			: _impl{xns::move(tuple._impl)} {}

			/* destructor */
			inline constexpr ~tuple(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self& other) -> self& {
				// check for self-assignment
				if (this == &other)
					return *this;
				// copy data
				_impl = other._impl;
				// return self-reference
				return *this;
			}

			/* move assignment operator */
			constexpr auto operator=(self&& other) noexcept -> self& {
				// check for self-assignment
				if (this == &other)
					return *this;
				// move data
				_impl = xns::move(other._impl);
				// return self-reference
				return *this;
			}


		// -- friends ---------------------------------------------------------

		/* get tuple element reference as friend */
		template <xns::size_t I, typename... T>
		friend constexpr auto get(xns::tuple<T...>&) noexcept -> xns::indexed_element<I, xns::tuple<T...>>&;

		/* get tuple element rvalue reference as friend */
		template <xns::size_t I, typename... T>
		friend constexpr auto get(xns::tuple<T...>&&) noexcept -> xns::indexed_element<I, xns::tuple<T...>>&&;

		/* get constant tuple element reference as friend */
		template <xns::size_t I, typename... T>
		friend constexpr auto get(const xns::tuple<T...>&) noexcept -> const xns::indexed_element<I, xns::tuple<T...>>&;

		/* get constant tuple element rvalue reference as friend */
		template <xns::size_t I, typename... T>
		friend constexpr auto get(const xns::tuple<T...>&&) noexcept -> const xns::indexed_element<I, xns::tuple<T...>>&&;


		/* get tuple element reference as friend */
		template <typename U, typename... T>
		friend constexpr auto get(xns::tuple<T...>&) noexcept -> U&;

		/* get tuple element rvalue reference as friend */
		template <typename U, typename... T>
		friend constexpr auto get(xns::tuple<T...>&&) noexcept -> U&&;

		/* get constant tuple element reference as friend */
		template <typename U, typename... T>
		friend constexpr auto get(const xns::tuple<T...>&) noexcept -> const U&;

		/* get constant tuple element rvalue reference as friend */
		template <typename U, typename... T>
		friend constexpr auto get(const xns::tuple<T...>&&) noexcept -> const U&&;

		/* make tuple as friend */
		template <typename... T>
		friend constexpr auto make_tuple(T&&...) -> xns::tuple<T...>;

	}; 


	/* deduction guide */
	template <typename... A>
	//tuple(A&&...) -> tuple<xns::remove_cvr<A>...>;
	tuple(A&&...) -> tuple<A...>;




	/* get tuple element reference */
	template <xns::size_t I, typename... T>
	constexpr auto get(xns::tuple<T...>& tuple) noexcept -> xns::indexed_element<I, xns::tuple<T...>>& {
		// check if index is in range
		static_assert(I < sizeof...(T), "[xns::get] Index out of range.");
		// get tuple element type
		using elem_t = typename xns::tuple<T...>::template element_at<I>;
		// return a reference to the tuple element
		return tuple._impl.elem_t::value;
	}

	/* get tuple element rvalue reference */
	template <xns::size_t I, typename... T>
	constexpr auto get(xns::tuple<T...>&& tuple) noexcept -> xns::indexed_element<I, xns::tuple<T...>>&& {
		// check if index is in range
		static_assert(I < sizeof...(T), "[xns::get] Index out of range.");
		// get tuple element type
		using elem_t = typename xns::tuple<T...>::template element_at<I>;
		// return a rvalue reference to the tuple element
		return xns::move(tuple._impl.elem_t::value);
	}

	/* get constant tuple element reference */
	template <xns::size_t I, typename... T>
	constexpr auto get(const xns::tuple<T...>& tuple) noexcept -> const xns::indexed_element<I, xns::tuple<T...>>& {
		// check if index is in range
		static_assert(I < sizeof...(T), "[xns::get] Index out of range.");
		// get tuple element type
		using elem_t = typename xns::tuple<T...>::template element_at<I>;
		// return a constant reference to the tuple element
		return tuple._impl.elem_t::value;
	}

	/* get constant tuple element rvalue reference */
	template <xns::size_t I, typename... T>
	constexpr auto get(const xns::tuple<T...>&& tuple) noexcept -> const xns::indexed_element<I, xns::tuple<T...>>&& {
		// check if index is in range
		static_assert(I < sizeof...(T), "[xns::get] Index out of range.");
		// get tuple element type
		using elem_t = typename xns::tuple<T...>::template element_at<I>;
		// return a constant rvalue reference to the tuple element
		return xns::move(tuple._impl.elem_t::value);
	}


	namespace impl {

		template <typename... A>
		struct tuple_size;

		template <typename... A>
		struct tuple_size<xns::tuple<A...>>
		: xns::integral_constant<xns::size_t, sizeof...(A)> {};

	}

	template <typename T>
	inline constexpr auto tuple_size = impl::tuple_size<xns::remove_cvrp<T>>::value;



	/* get tuple element reference */
	template <typename U, typename... T>
	constexpr auto get(xns::tuple<T...>& tuple) noexcept -> U& {
		// check if type is in tuple
		static_assert(xns::is_one_of<U, T...>, "[xns::get] Type is not in tuple.");
		// require all types to be unique
		static_assert(xns::is_unique<U, T...>, "[xns::get] Type is ambiguous, because it is not unique.");
		// get tuple element type
		using elem_t = typename xns::tuple<T...>::template element_from<U>;
		// return a reference to the tuple element
		return tuple._impl.elem_t::value;
	}

	/* get tuple element rvalue reference */
	template <typename U, typename... T>
	constexpr auto get(xns::tuple<T...>&& tuple) noexcept -> U&& {
		// check if type is in tuple
		static_assert(xns::is_one_of<U, T...>, "[xns::get] Type is not in tuple.");
		// require all types to be unique
		static_assert(xns::is_unique<U, T...>, "[xns::get] Type is ambiguous, because it is not unique.");
		// get tuple element type
		using elem_t = typename xns::tuple<T...>::template element_from<U>;
		// return a rvalue reference to the tuple element
		return xns::move(tuple._impl.elem_t::value);
	}

	/* get constant tuple element reference */
	template< typename U, typename... T>
	constexpr auto get(const xns::tuple<T...>& tuple) noexcept -> const U& {
		// check if type is in tuple
		static_assert(xns::is_one_of<U, T...>, "[xns::get] Type is not in tuple.");
		// require all types to be unique
		static_assert(xns::is_unique<U, T...>, "[xns::get] Type is ambiguous, because it is not unique.");
		// get tuple element type
		using elem_t = typename xns::tuple<T...>::template element_from<U>;
		// return a constant reference to the tuple element
		return tuple._impl.elem_t::value;
	}

	/* get constant tuple element rvalue reference */
	template< typename U, typename... T>
	constexpr auto get(const xns::tuple<T...>&& tuple) noexcept -> const U&& {
		// check if type is in tuple
		static_assert(xns::is_one_of<U, T...>, "[xns::get] Type is not in tuple.");
		// require all types to be unique
		static_assert(xns::is_unique<U, T...>, "[xns::get] Type is ambiguous, because it is not unique.");
		// get tuple element type
		using elem_t = typename xns::tuple<T...>::template element_from<U>;
		// return a constant rvalue reference to the tuple element
		return xns::move(tuple._impl.elem_t::value);
	}



	// -- T U P L E  C O N C A T E N A T I O N --------------------------------

	template <typename... A>
	constexpr auto tuple_cat(A&&... tuples) {
		// not implemented yet...
		// 0.
	}


	// -- I S  T U P L E ------------------------------------------------------

	namespace impl {

		template <typename T>
		struct is_tuple final {
			constexpr static bool value = false;
		};

		template <typename... A>
		struct is_tuple<xns::tuple<A...>> final {
			constexpr static bool value = true;
		};

	}

	/* is tuple concept */
	template <typename T>
	concept is_tuple = impl::is_tuple<xns::remove_cvrp<T>>::value;


	// -- make tuple ----------------------------------------------------------

	/* make tuple */
	template <typename... A>
	constexpr auto make_tuple(A&&... args) -> xns::tuple<A...> {
		//using tag = typename xns::tuple<A...>::private_tag;
		return xns::tuple<A...>{xns::forward<A>(args)...};
	}





}

#endif









