#ifndef UNIQUE_HPP
#define UNIQUE_HPP

#include "Types.hpp"
#include "allocator.hpp"

#include <iostream>

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- U N I Q U E  P T R  C L A S S ---------------------------------------

	template <typename T>
	class UniquePtr final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* value type */
			using Value = T;

			/* size type */
			using Size = UInt64;

			/* reference type */
			using Reference = Value&;

			/* const reference type */
			using ConstReference = const Value&;

			/* move reference type */
			using MoveReference = Value&&;

			/* pointer type */
			using Pointer = Value*;

			/* const pointer type */
			using ConstPointer = const Value*;

			/* allocator type */
			using Allocator = Xf::Allocator<Value>;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			UniquePtr(void)
			: _pointer{nullptr} {
				std::cout << "default constructor" << std::endl;
				// code here...
			}

			/* deleted copy constructor */
			UniquePtr(const UniquePtr&) = delete;

			/* move constructor */
			UniquePtr(UniquePtr&& other) noexcept
			: _pointer{other._pointer} {
				std::cout << "move constructor" << std::endl;
				// code here...
				other._pointer = nullptr;
			}

			/* destructor */
			~UniquePtr(void) {
				// check if pointer is not null
				if (_pointer != nullptr) {
					// destroy object
					Allocator::destroy(_pointer);
					// deallocate pointer
					Allocator::deallocate(_pointer);
				}
			}

			template <typename... A>
			UniquePtr(A&&... arguments)
			: _pointer{Allocator::allocate()} {
				std::cout << "template constructor" << std::endl;
				// construct pointer
				Allocator::construct(_pointer, arguments...);
			}

			// -- O P E R A T O R S -------------------------------------------

			/* deleted copy operator */
			UniquePtr& operator=(const UniquePtr&) = delete;

			/* move operator */
			UniquePtr& operator=(UniquePtr&& other) noexcept {
				// check self assignment
				if (this != &other) {
					// clear this
				    this->~UniquePtr();
					// move pointer
					_pointer = other._pointer;
					// set other pointer to null
					other._pointer = nullptr;
				} // return self reference
				return *this;
			}

			/* clear operator */
			UniquePtr& operator=(Nullptr) {
				// clear this
				this->~UniquePtr();
				// initialize pointer
				_pointer = nullptr;
				// return self reference
				return *this;
			}

			/* dereference operator */
			Reference operator*(void) {
				return *_pointer;
			}

			/* const dereference operator */
			ConstReference operator*(void) const {
				return *_pointer;
			}


		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			/* pointer */
			Pointer _pointer;



	};

};

#endif

