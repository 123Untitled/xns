#ifndef XNS_OCTREE_HEADER
#define XNS_OCTREE_HEADER

// local headers
#include "xns/macros.hpp"
#include "xns/types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- O C T R E E ---------------------------------------------------------

	template <typename T>
	class octree final {

		private:

			// -- forward declarations ----------------------------------------

			class node;


			// -- private types -----------------------------------------------

			/* node pointer type */
			using node_ptr = node*;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self       = xns::octree<T>;

			/* value type */
			using value_type = T;

			/* reference type */
			using mut_ref    = value_type&;

			/* const reference type */
			using const_ref  = const value_type&;

			/* pointer type */
			using mut_ptr    = value_type*;

			/* const pointer type */
			using const_ptr  = const value_type*;

			/* size type */
			using size_type  = xns::size_t;


		private:

			// -- private members ---------------------------------------------

			/* root */
			node_ptr _root;

			/* size */
			size_type _size;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline octree(void) noexcept
			: _root{nullptr}, _size{0} {}

			/* destructor */
			inline ~octree(void) noexcept {
			}



		private:


			enum class octant : unsigned char {
				O1 = 0b00000001,
				O2 = 0b00000010,
				O3 = 0b00000100,
				O4 = 0b00001000,
				O5 = 0b00010000,
				O6 = 0b00100000,
				O7 = 0b01000000,
				O8 = 0b10000000,
			};


			class node final {

				public:

					// -- public types ----------------------------------------

					/* self type */
					using self = xns::octree<T>::node;


					node(void) = default;
					node(const self&) = default;
					node(self&&) = default;
					~node(void) = default;

					auto operator=(const self&) -> self& = default;
					auto operator=(self&&) noexcept -> self& = default;

				private:

					// -- private data ----------------------------------------

					/* octant data */
					value_type _data;

					/* children */
					node_ptr _children[8];

					/* parent */
					node_ptr _parent;



			};

	};

}

#endif // XNS_OCTREE_HEADER
