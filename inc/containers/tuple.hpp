#ifndef TUPLE_HEADER
#define TUPLE_HEADER

#include "allocator.hpp"

#include "identity.hpp"
#include "types.hpp"
#include "forward.hpp"
#include "move.hpp"
#include "is_same.hpp"

#include "type_at.hpp"
#include "integer_sequence.hpp"
#include "index_of.hpp"

#include "function.hpp"

#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- T U P L E -----------------------------------------------------------

	template <class... A>
	class tuple final {


		// -- assertions ------------------------------------------------------

		/* check number of elements */
		static_assert(sizeof...(A) > 1, "TUPLE MUST HAVE AT LEAST 2 ELEMENTS!");


		public:

			// -- T Y P E S ---------------------------------------------------

			/* self type */
			using self = tuple<A...>;

			/* size type */
			using size_type = xns::size_t;


		private:

			// -- C O N S T A N T S -------------------------------------------

			/* size */
			static constexpr size_type num_elements = sizeof...(A);


			// -- T U P L E  E L E M E N T  S T R U C T -----------------------

			template <size_type IDX, class value_type>
			struct element {

				// -- M E M B E R S -------------------------------------------

				/* value */
				value_type value;

			};


			// -- I M P L E M E N T A T I O N  C L A S S ----------------------

			/* forward declaration */
			template <class>
			struct impl;

			/* specialization for index sequence */
			template <size_type... IDX>
			struct impl<xns::index_seq<IDX...>> final : public element<IDX, A>... {


				// -- A L I A S E S -------------------------------------------

				/* self type */
				using self = impl<xns::index_seq<IDX...>>;


				// -- C O N S T R U C T O R S ---------------------------------

				/* default constructor */
				inline constexpr impl(void)
				// fold expression to default-initialize tuple elements
				: element<IDX, A>{ }... {
					// code here...
				}

				/* variadic constructor */
				template <class... U>
				inline constexpr impl(U&&... args) requires (sizeof...(U) > 1)
				// fold expression to initialize tuple elements
				: element<IDX, A>{xns::forward<U>(args)}... {
					// code here...
				}

				/* copy constructor */
				inline constexpr impl(const self& other)
				// fold expression to copy-initialize tuple elements
				: element<IDX, A>{other}... {
					// code here...
				}

				/* move constructor */
				inline constexpr impl(self&& other) noexcept
				// fold expression to move-initialize tuple elements
				: element<IDX, A>{xns::move(other)}... {
					// code here...
				}

				/* destructor */
				inline constexpr ~impl(void) noexcept {
					// code here...
				}


				// -- A S S I G N M E N T  O P E R A T O R S ------------------

				/* copy assignment operator */
				inline constexpr self& operator=(const self& other) {
					// INFO: check for self-assignment is not necessary (see below)
					// because this check is already done in the Tuple::operator=()
					((element<IDX, A>::operator=(other)), ...);
					// return self-reference
					return *this;
				}

				/* move assignment operator */
				inline constexpr self& operator=(self&& other) noexcept {
					// INFO: check for self-assignment is not necessary (see below)
					// because this check is already done in the Tuple::operator=()
					((element<IDX, A>::operator=(xns::move(other))), ...);
					// return self-reference
					return *this;
				}

			};



			// -- P R I V A T E  A L I A S E S --------------------------------

			/* sequence type */
			using sequence = xns::index_seq_for<A...>;

			/* indexed type */
			template <size_type IDX>
			using indexed = xns::type_at<IDX, A...>;

			/* index of type */
			template <class T>
			static constexpr xns::size_t _index_of = xns::index_of<T, A...>();


			// -- P R I V A T E  M E M B E R S --------------------------------

			impl<sequence> _impl;


		public:

			/* default constructor */
			constexpr tuple(void)
			: _impl{} {
				// code here...
			}

			/* variadic constructor */
			template <class... U> requires (sizeof...(U) > 1)
			constexpr tuple(U&&... args)
			: _impl{xns::forward<U>(args)...} {
				// code here...
			}

			/* copy constructor */
			constexpr tuple(const self& tuple)
			: _impl{tuple._impl} {
				// code here...
			}

			/* copy constructor static assert overload */
			template <class... U>
			constexpr tuple(const tuple<U...>&) {
				// check if tuple types are the same

				// need TO CHECK THIS REIMPLEMENTATION
				static_assert(xns::is_same< xns::identity_pack<A...>,
											xns::identity_pack<U...>>,
							"): CAN'T CONSTRUCT TUPLE FROM DIFFERENT TYPES! :(");
			}

			/* move constructor */
			constexpr tuple(self&& tuple) noexcept
			: _impl{xns::move(tuple._impl)} {
				std::cout << "move constructor" << std::endl;
				// code here...
			}


			// -- P U B L I C  A S S I G N M E N T  O P E R A T O R S ---------

			/* copy assignment operator */
			constexpr self& operator=(const self& other) {
				// check for self-assignment
				if (this != &other) {
					// copy data
					_impl = other._impl;
				} // return self-reference
				return *this;
			}

			/* move assignment operator */
			constexpr self& operator=(self&& other) noexcept {
				// check for self-assignment
				if (this != &other) {
					// move data
					_impl = xns::move(other._impl);
				} // return self-reference
				return *this;
			}


			// -- P U B L I C  A C C E S S O R S ------------------------------

			/* get tuple element */
			template <size_type IDX>
			constexpr auto& get(void) {
				// check if index is in range
				static_assert(IDX < num_elements, "): INDEX OUT OF RANGE! :(");
				// return a reference to the tuple element
				return _impl.element<IDX, indexed<IDX>>::value;
			}

			/* get constant tuple element */
			template <size_type IDX>
			constexpr const auto& get(void) const {
				// check if index is in range
				static_assert(IDX < num_elements, "): INDEX OUT OF RANGE! :(");
				// return a constant reference to the tuple element
				return _impl.element<IDX, indexed<IDX>>::value;
			}

			/* get tuple size */
			constexpr size_type size(void) const {
				// return the tuple size
				return num_elements;
			}


			// -- setters -----------------------------------------------------

			/* set tuple element by copy */
			template <size_type IDX>
			constexpr void set(const indexed<IDX>& value) {
				// set tuple element
				_impl.element<IDX, indexed<IDX>>::value = value;
			}

			/* set tuple element by move */
			template <size_type IDX>
			constexpr void set(indexed<IDX>&& value) {
				// set tuple element
				_impl.element<IDX, indexed<IDX>>::value = xns::move(value);
			}



		// -- friends ---------------------------------------------------------

		/* get tuple element with index as friend */
		template <xns::size_t, class... U>
		friend constexpr auto& get(tuple<U...>&);

		/* get constant tuple element with index as friend */
		template <xns::size_t, class... U>
		friend constexpr const auto& get(const tuple<U...>&);

		/* get tuple element with type as friend */
		template <class T, class... U>
		friend constexpr auto& get(tuple<U...>&);

		/* get constant tuple element with type as friend */
		template <class T, class... U>
		friend constexpr const auto& get(const tuple<U...>&);




	};

	/* deduction guide */
	template <class... A>
	tuple(A&&...) -> tuple<A...>;


	/* get tuple element with index */
	template <xns::size_t IDX, class... A>
	constexpr auto& get(tuple<A...>& tuple) {
		// check if index is in range
		static_assert(IDX < sizeof...(A), "): INDEX OUT OF RANGE! :(");
		// return a reference to the tuple element
		return tuple._impl.template element<IDX, typename xns::tuple<A...>::template indexed<IDX>>::value;
	}

	/* get constant tuple element with index */
	template <xns::size_t IDX, class... A>
	constexpr const auto& get(const tuple<A...>& tuple) {
		// check if index is in range
		static_assert(IDX < sizeof...(A), "): INDEX OUT OF RANGE! :(");
		// return a constant reference to the tuple element
		return tuple._impl.template element<IDX, typename xns::tuple<A...>::template indexed<IDX>>::value;
	}

	/* get tuple element with type */
	//template <class T, class... A>
	//constexpr auto& get(tuple<A...>& tuple) {
	//	// check if type is in tuple
	//	static_assert(xns::is_one_of<T, A...>, "): TYPE NOT IN TUPLE! :(");
	//	// get type index
	//	constexpr auto index = xns::tuple<A...>::template _index_of<T>;
	//	// return a reference to the tuple element
	//	return tuple._impl.template element<index, typename xns::tuple<A...>::template indexed<index>>::value;
	//}

	///* get constant tuple element with type */
	//template <class T, class... A>
	//constexpr const auto& get(const tuple<A...>& tuple) {
	//	// check if type is in tuple
	//	static_assert(xns::is_one_of<T, A...>, "): TYPE NOT IN TUPLE! :(");
	//	// get type index
	//	constexpr auto index = xns::tuple<A...>::template _index_of<T>;
	//	// return a constant reference to the tuple element
	//	return tuple._impl.template element<index, typename xns::tuple<A...>::template indexed<index>>::value;
	//}

}

#endif









