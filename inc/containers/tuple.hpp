#ifndef TUPLE_HEADER
#define TUPLE_HEADER

#include "allocator.hpp"

#include "identity.hpp"
#include "types.hpp"
#include "forward.hpp"
#include "move.hpp"
#include "is_same.hpp"

#include "pack_type.hpp"
#include "integer_sequence.hpp"

#include "function.hpp"

#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- T U P L E  C L A S S ------------------------------------------------

	template <class... A>
	class tuple final {


		// -- A S S E R T I O N S ---------------------------------------------

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
			using Indexed = xns::pack_type<IDX, A...>;


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
							"TUPLE ARE NOT THE SAME !!!");
			}

			/* move constructor */
			constexpr tuple(self&& tuple) noexcept
			: _impl{xns::move(tuple._impl)} {
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
			template <size_type IDX, class T = Indexed<IDX>>
			constexpr auto& get(void) {
				// return a reference to the tuple element
				return _impl.element<IDX, T>::value;
			}

			/* get constant tuple element */
			template <size_type IDX, class T = Indexed<IDX>>
			constexpr const auto& get(void) const {
				// return a constant reference to the tuple element
				return _impl.element<IDX, T>::value;
			}





			//template <size_type... IDX>
			//constexpr void _iterate(xns::index_seq<IDX...>) {
			//	using namespace std;
			//	((cout << _impl.element<IDX, A>::value << "\n"), ...);
			//}

			//template <size_type... IDX, class R, class... U>
			//constexpr void _iterate(xns::index_seq<IDX...>, xns::function<R(U...)>&& f) {
			//	((f(_impl.element<IDX, A>::value)), ...);
			//}

			/* iterate by calling a template function on each tuple element */
			template <size_type... IDX, class F>
			constexpr void _iterate(xns::index_seq<IDX...>, F&& f) {
				((f(_impl.element<IDX, A>::value)), ...);
			}
			// is it okey ??
			// answer: yes, it is okey

			//constexpr void iterate(void) {
			//	_iterate(sequence{});
			//}

			/* the calling function must be a template function */
			template <class F>
			constexpr void iterate(F&& f) {
				//_iterate(sequence{}, xns::forward<f>);
				_iterate(sequence{}, [&f](auto&&... args) {
					f(xns::forward<decltype(args)>(args)...);
				});
			}

			//template <class R, class... U>
			//constexpr void iterate(xns::function<R(U...)>&& f) {
			//	_iterate(sequence{}, xns::forward<f>);
			//}







	};

	/* deduction guide */
	template <class... A>
	tuple(A&&...) -> tuple<A...>;







}

#endif









