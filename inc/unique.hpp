#ifndef UNIQUE_HPP
#define UNIQUE_HPP

#include "types.hpp"
#include "allocator.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include <type_traits>


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
				// code here...
			}

			/* non-copyable class */
			NON_COPYABLE(UniquePtr);

			/* forward constructor */
			/*template <typename... A>
			UniquePtr(A&&... arguments)
			: _pointer{Allocator::allocate()} {
				// construct pointer
				if (_pointer != nullptr) {
					Allocator::construct(_pointer, Xf::forward<A>(arguments)...);
				}
			}*/

			/* move constructor */
			UniquePtr(UniquePtr&& other) noexcept
			: _pointer{other._pointer} {
				// invalidate other pointer
				other._pointer = nullptr;
			}

			template<class>
			friend class UniquePtr;

			/* move constructor */
			template <class U>
			UniquePtr(UniquePtr<U>&& other) noexcept requires std::derived_from<U, T>
			: _pointer{other._pointer} {
				// invalidate other pointer
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


			// -- O P E R A T O R S -------------------------------------------

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

			/* pointer operator */
			Pointer operator->(void) {
				return _pointer;
			}

			/* const pointer operator */
			ConstPointer operator->(void) const {
				return _pointer;
			}

			/* bool operator */
			explicit operator bool(void) const {
				return _pointer != nullptr;
			}

			/* bool not operator */
			bool operator!(void) const {
				return _pointer == nullptr;
			}


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* pointer */
			Pointer pointer(void) {
				return _pointer;
			}

			/* const pointer */
			ConstPointer pointer(void) const {
				return _pointer;
			}

			/* make unique */
			template <typename... A>
			void make(A&&... arguments) {
				// call destructor
				this->~UniquePtr();
				// allocate pointer
				_pointer = Allocator::allocate();
				// construct pointer
				if (_pointer != nullptr) {
					Allocator::construct(_pointer, Xf::forward<A>(arguments)...);
				}
			}

			template <class D, typename... A>
			void make(A&&... arguments) requires std::derived_from<D, T> {
				// call destructor
				this->~UniquePtr();
				// allocate pointer
				D* pointer = Xf::Allocator<D>::allocate();
				// construct pointer
				if (pointer != nullptr) {
					Xf::Allocator<D>::construct(pointer, Xf::forward<A>(arguments)...);
				}
				_pointer = pointer;
			}

			/* set */
			void set_pointer(Pointer pointer) {
				// call destructor
				this->~UniquePtr();
				// set pointer
				_pointer = pointer;
			}

			/* clear */
			void clear(void) {
				// call destructor
				this->~UniquePtr();
				// initialize pointer
				_pointer = nullptr;
			}

			/* release */
			Pointer release(void) {
				// get pointer
				Pointer release = _pointer;
				// initialize pointer
				_pointer = nullptr;
				// return pointer
				return release;
			}


		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			/* pointer */
			Pointer _pointer;

	};

	/* make unique */
	template <typename T, typename... A>
	UniquePtr<T> make_unique(A&&... arguments) {
		// create unique pointer
		UniquePtr<T> unique;
		// make unique
		unique.make(Xf::forward<A>(arguments)...);
		// return unique pointer
		return unique;
	}


	// -- U N I Q U E  F D  C L A S S ---------------------------------------

	class UniqueFd final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* file descriptor type */
			using Fd = pid_t;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			UniqueFd(void);

			/* file descriptor constructor */
			UniqueFd(Fd fd);

			/* deleted copy constructor */
			UniqueFd(const UniqueFd&) = delete;

			/* move constructor */
			UniqueFd(UniqueFd&& other) noexcept;

			/* destructor */
			~UniqueFd(void);


			// -- O P E R A T O R S -------------------------------------------

			/* deleted copy operator */
			UniqueFd& operator=(const UniqueFd&) = delete;

			/* move operator */
			UniqueFd& operator=(UniqueFd&& other) noexcept;

			/* bool operator */
			explicit operator bool(void) const;

			/* bool not operator */
			bool operator!(void) const;


			// -- M E T H O D S -----------------------------------------------

			/* get file descriptor */
			Fd get(void) const;

			/* duplicate */
			UniqueFd duplicate(void) const;

			/* duplicate 2 */
			void duplicate(UniqueFd& other) const;


			//

			/* make fd */
			static UniqueFd make_fd(const Fd);


		private:

			// -- E N U M S --------------------------------------------------

			/* invalid file descriptor */
			enum : int  { NULLFD = -1 };

			// -- M E M B E R S -----------------------------------------------

			/* file descriptor */
			Fd _fd;

	};



};

#endif

