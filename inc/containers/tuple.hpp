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

#include <iostream>


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- T U P L E  C L A S S ------------------------------------------------

	template <class... A>
	class Tuple final {

		/* check number of elements */
		static_assert(sizeof...(A) > 1, "TUPLE MUST HAVE AT LEAST ONE ELEMENT");


		public:

			// -- P U B L I C  A L I A S E S ----------------------------------

			/* self type */
			using Self = Tuple<A...>;

			/* size type */
			using Size = SizeT;



		private:

			// -- T U P L E  E L E M E N T  S T R U C T -----------------------

			template <SizeT IDX, class Value>
			struct Element {

				// -- M E M B E R S -------------------------------------------

				/* value */
				Value value;

			};


			// -- I M P L E M E N T A T I O N  C L A S S ----------------------

			/* forward declaration */
			template <class>
			struct TupleImpl;

			/* specialization for index sequence */
			template <Size... IDX>
			struct TupleImpl<Xf::IndexSeq<IDX...>> final : public Element<IDX, A>... {


				// -- A L I A S E S -------------------------------------------

				/* self type */
				using SelfImpl = TupleImpl<Xf::IndexSeq<IDX...>>;


				// -- C O N S T R U C T O R S ---------------------------------

				/* default constructor */
				TupleImpl(void)
				// fold expression to default-initialize tuple elements
				: Element<IDX, A>{ }... {
					// code here...
				}

				/* variadic constructor */
				template <class... U>
				TupleImpl(U&&... args) requires (sizeof...(U) > 1)
				// fold expression to initialize tuple elements
				: Element<IDX, A>{xns::forward<U>(args)}... {
					// code here...
				}

				/* copy constructor */
				TupleImpl(const SelfImpl& other)
				// fold expression to copy-initialize tuple elements
				: Element<IDX, A>{other}... {
					// code here...
				}

				/* move constructor */
				TupleImpl(SelfImpl&& other) noexcept
				// fold expression to move-initialize tuple elements
				: Element<IDX, A>{xns::move(other)}... {
					// code here...
				}

				/* destructor */
				~TupleImpl(void) noexcept {
					// code here...
				}


				// -- A S S I G N M E N T  O P E R A T O R S ------------------

				/* copy assignment operator */
				SelfImpl& operator=(const SelfImpl& other) {
					// INFO: check for self-assignment is not necessary (see below)
					// because this check is already done in the Tuple::operator=()
					((Element<IDX, A>::operator=(other)), ...);
					// return self-reference
					return *this;
				}

				/* move assignment operator */
				SelfImpl& operator=(SelfImpl&& other) noexcept {
					// INFO: check for self-assignment is not necessary (see below)
					// because this check is already done in the Tuple::operator=()
					((Element<IDX, A>::operator=(xns::move(other))), ...);
					// return self-reference
					return *this;
				}

			};



			// -- P R I V A T E  A L I A S E S --------------------------------

			/* sequence type */
			using Seq = Xf::IndexSeqFor<A...>;

			/* implementation type */
			using Impl = TupleImpl<Seq>;

			/* indexed type */
			template <Size IDX>
			using Indexed = Xf::PackType_t<IDX, A...>;


			// -- P R I V A T E  M E M B E R S --------------------------------

			Impl impl;


		public:

			/* default constructor */
			Tuple(void)
			: impl{} {
				// code here...
			}

			/* variadic constructor */
			template <class... U> requires (sizeof...(U) > 1)
			Tuple(U&&... args)
			: impl{xns::forward<U>(args)...} {
				// code here...
			}

			/* copy constructor */
			Tuple(const Self& tuple)
			: impl{tuple.impl} {
				// code here...
			}

			/* copy constructor static assert overload */
			template <class... U>
			Tuple(const Tuple<U...>&) {
				// check if tuple types are the same

				// need TO CHECK THIS REIMPLEMENTATION
				static_assert(xns::is_same< xns::identity_pack<A...>,
											xns::identity_pack<U...>>,
							"TUPLE ARE NOT THE SAME !!!");
			}

			/* move constructor */
			Tuple(Self&& tuple) noexcept
			: impl{xns::move(tuple.impl)} {
				// code here...
			}


			// -- P U B L I C  A S S I G N M E N T  O P E R A T O R S ---------

			/* copy assignment operator */
			Self& operator=(const Self& other) {
				// check for self-assignment
				if (this != &other) {
					// copy data
					impl = other.impl;
				} // return self-reference
				return *this;
			}

			/* move assignment operator */
			Self& operator=(Self&& other) noexcept {
				// check for self-assignment
				if (this != &other) {
					// move data
					impl = xns::move(other.impl);
				} // return self-reference
				return *this;
			}


			// -- P U B L I C  A C C E S S O R S ------------------------------

			/* get tuple element */
			template <Size IDX, class T = Indexed<IDX>>
			auto& get(void) {
				// return a reference to the tuple element
				return impl.Element<IDX, T>::value;
			}

			/* get constant tuple element */
			template <Size IDX, class T = Indexed<IDX>>
			const auto& get(void) const {
				// return a constant reference to the tuple element
				return impl.Element<IDX, T>::value;
			}





			template <SizeT... IDX>
			void _iterate(Xf::IndexSeq<IDX...>) {
				using namespace std;
				((cout << impl.Element<IDX, A>::value << "\n"), ...);
			}

			void iterate(void) {
				_iterate(Seq{});
			}







	};

	/* deduction guide */
	template <class... A>
	Tuple(A&&...) -> Tuple<A...>;







}

#endif









