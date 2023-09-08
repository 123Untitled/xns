#ifndef SEGMENT_HEADER
#define SEGMENT_HEADER

// local headers
#include "types.hpp"
#include "allocator.hpp"
#include "memory.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S E G M E N T  C L A S S --------------------------------------------

	// this class is a list of vectors
	// goal is to speed up list operations by using vectors

	template <typename T>
	class segment final {


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type = T;

			/* self type */
			using self = xns::segment<T>;

			/* size type */
			using size_type = xns::size_t;

			/* reference type */
			using reference = value_type&;

			/* const reference type */
			using const_reference = const value_type&;

			/* move reference type */
			using move_reference = value_type&&;

			/* pointer type */
			using mutable_pointer = value_type*;

			/* const pointer type */
			using const_pointer = const value_type*;


		private:

			// -- private forward declarations --------------------------------

			/* block */
			struct block;


			// -- private types -----------------------------------------------

			/* block pointer type */
			using block_ptr = block*;

			/* allocator type */
			using allocator = xns::memory::pool<block>;


			struct block final {


				// -- types ---------------------------------------------------

				/* allocator type */
				using allocator = xns::allocator<value_type>;


				// -- lifecycle -----------------------------------------------

				/* deleted default constructor */
				block(void) = delete;

				/* capacity constructor */
				inline explicit block(size_type capacity)
				: _data{allocator::allocate(capacity)}, _capacity{capacity}, _size{0}, _next{nullptr}, _weak{false} {}

				/* weak constructor */
				inline explicit block(mutable_pointer data, const size_type capacity, const size_type size)
				: _data{data}, _capacity{capacity}, _size{size}, _next{nullptr}, _weak{true} {}

				/* non-assignable struct */
				NON_ASSIGNABLE(block);

				/* destructor */
				inline ~block(void) noexcept {
					// check if weak
					if (_weak == true) { return; }
					// else deallocate data
					destroy_block();
					free_block();
				}

				// -- public accessors ----------------------------------------

				/* available */
				inline auto available(void) const noexcept -> size_type {
					return _capacity - _size;
				}


				// -- public modifiers ----------------------------------------

				/* push back */
				inline auto push_back(const_reference value) noexcept -> void {
					allocator::construct(_data + _size, value);
					++_size;
				}


				/* destroy block */
				auto destroy_block(void) noexcept -> void {
					// loop over block
					for (size_type i = 0; i < _size; ++i) {
						// destroy element
						allocator::destroy(_data + i);
					}
				}

				/* free block */
				auto free_block(void) noexcept -> void {
					// deallocate block
					allocator::deallocate(_data);
				}


				// -- public members --------------------------------------

				/* data pointer */
				mutable_pointer _data;

				/* capacity */
				size_type _capacity;

				/* size */
				size_type _size;

				/* next block */
				block_ptr _next;

				/* is weak */
				bool _weak;


			};


			// -- private enum ------------------------------------------------

			/* block size */
			enum : size_type {
				DEFAULT_BLOCK_SIZE = 16
			};


			// -- private members ---------------------------------------------

			/* head */
			block_ptr _head;

			/* tail */
			block_ptr _tail;

			/* size */
			size_type _size;

			/* block number */
			size_type _block_number;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline segment(void) noexcept
			: _head{nullptr}, _tail{nullptr}, _size{0}, _block_number{0} {}

			/* copy constructor */
			inline segment(const self& other) {
				// not implemented yet...
			}

			/* move constructor */
			inline segment(self&& other) noexcept
			: _head{other._head}, _tail{other._tail}, _size{other._size} {
				// invalidate other
				other.init();
			}

			/* destructor */
			inline ~segment(void) noexcept {
				// not implemented yet...
			}



			// -- public modifiers --------------------------------------------

			/* push back */
			template <typename U>
			inline auto push_back(U&& value) noexcept -> void {
				// check if empty
				if (_head == nullptr) {
					// create new block
					_head = _tail = allocator::make(DEFAULT_BLOCK_SIZE);
					++_block_number;
				}
				// check if tail is full
				else if (_tail->available() == 0) {
					// create new block
					_tail->_next = allocator::make(_tail->_capacity * 2);
					// set tail
					_tail = _tail->_next;
					++_block_number;
				}
				// push back value
				_tail->push_back(xns::forward<U>(value));
				// increment size
				++_size;
			}


			/* subscript operator */
			inline auto operator[](size_type index) noexcept -> reference {
				// get block
				block_ptr block = _head;
				size_type i = block->_size;
				// loop through blocks
				while (i <= index) {

					i += block->_size;
					index -= block->_size;
					// get next block
					block = block->_next;
				}
				// return value
				return block->_data[index];
			}


			/* print */
			auto print(void) -> void {

				constexpr const char* type[] = {
					"\x1b[32mblock\x1b[0m",
					"\x1b[31mweak\x1b[0m" };

				block_ptr block = _head;

				while (block) {

					block->_weak
						? std::cout << type[1]
						: std::cout << type[0];

					std::cout << " [" << block->_size << "] [" << block->_capacity << "] ";


					for (size_type i = 0; i < block->_size; ++i) {
						std::cout << block->_data[i] << " ";
					}

					std::cout << std::endl;

					block = block->_next;
				}

			}

			auto flatten(void) -> void {

				// check if empty
				if (_head == nullptr) { return; }

				if (_block_number == 1) { return; }

				block_ptr block = allocator::make(_size * 2);

				size_type i = 0;

				// loop through blocks
				while (_head) {

					// get data pointer
					mutable_pointer data = _head->_data;

					// move data
					for (size_type j = 0; j < _head->_size; ++j) {
						block::allocator::construct(block->_data + i, xns::move(data[j]));
						// block::allocator::destroy(data + j);
						++i;
					}


					// get next block
					block_ptr next = _head->_next;
					// deallocate block
					allocator::store(_head);
					// set head to next
					_head = next;
				}

				// set head to block
				_head = block;
				// set tail to block
				_tail = block;
				// set size
				block->_size = _size;
			}



			// -- public accessors --------------------------------------------

			/* size */
			inline auto size(void) const noexcept -> size_type {
				return _size;
			}

			/* block number */
			inline auto block_number(void) const noexcept -> size_type {
				return _block_number;
			}



		private:

			// -- private methods ---------------------------------------------

			/* init */
			inline auto init(void) noexcept -> void {
				// initialize members
				_head = _tail = nullptr;
				_size = 0;
			}





	};

}

#endif // SEGMENT_HEADER
