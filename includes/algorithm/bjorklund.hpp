#ifndef XNS_BJORKLUND_HPP
#define XNS_BJORKLUND_HPP


#include "vector.hpp"
#include "fragmentation.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- B J O R K L U N D ---------------------------------------------------

	class bjorklund final {


		public:

			// -- public types ------------------------------------------------

			/* size type */
			using size_type = xns::size_t;


			// -- public static methods ---------------------------------------

			static auto generate(const size_type, const size_type) -> xns::vector<size_type>;


		private:

			// -- private lifecycle -------------------------------------------

			/* deleted default constructor */
			bjorklund(void) = delete;

			/* argument constructor */
			bjorklund(const size_type, const size_type) noexcept;

			/* non-assignable class */
			unassignable(bjorklund);

			/* destructor */
			~bjorklund(void) noexcept = default;

			/* forward declaration */
			struct node;


			// -- private types -----------------------------------------------

			/* allocator type */
			using allocator = xns::allocator<node>;

			/* node pointer */
			using node_ptr = node*;


			// -- private members ---------------------------------------------

			/* step count */
			size_type _step;

			/* pulse count */
			size_type _pulse;

			/* front */
			node_ptr _front;

			/* back */
			node_ptr _back;


			// -- private methods ---------------------------------------------

			/* generate euclidean rhythm */
			auto generate_impl(void) -> xns::vector<size_type>;

			/* compute */
			auto compute(size_type&, size_type&) noexcept -> void;


			// -- private class -----------------------------------------------

			struct node {

				/* deleted default constructor */
				node(void) = delete;

				/* data constructor */
				inline node(const size_type) noexcept;

				/* non-assignable struct */
				unassignable(node);

				/* destructor */
				inline ~node(void) noexcept = default;


				auto push(node_ptr) noexcept -> void;

				// -- members -------------------------------------------------

				/* step trigger */
				size_type _data;

				/* next sub step */
				node_ptr _up;

				/* last sub step */
				node_ptr _last;


			};

	};

}

#endif
