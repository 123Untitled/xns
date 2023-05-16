#ifndef WEAK_POINTER_HEADER
#define WEAK_POINTER_HEADER

#include "types.hpp"
#include "allocator.hpp"
#include "inheritance.hpp"



// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	/* unique pointer forward declaration */
	template <class>
	class UniquePointer;

	/* shared pointer forward declaration */
	template <class>
	class SharedPointer;


	// -- W E A K  P O I N T E R  C L A S S -----------------------------------

	template <class T>
	class WeakPointer final {

		public:

			// -- F R I E N D S -----------------------------------------------

			/* derived types as friend */
			template <class>
			friend class WeakPointer;


			// -- P U B L I C  A L I A S E S ----------------------------------

			/* value type */
			using Value     = T;

			/* self type */
			using Self      = WeakPointer<Value>;

			/* reference type */
			using Reference = Value&;

			/* move reference type */
			using MoveRef   = Value&&;

			/* pointer type */
			using Pointer   = Value*;

			/* const reference type */
			using ConstRef  = const Value&;

			/* const pointer type */
			using ConstPtr  = const Value*;

			/* size type */
			using Size      = SizeT;


			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* default constructor */
			WeakPointer(void) noexcept
			: _data{nullptr} {
				// code here...
			}

			/* nullptr constructor */
			WeakPointer(Xf::Nullptr) noexcept
			: WeakPointer{ } {
				// code here...
			}

			/* pointer constructor */
			WeakPointer(Pointer ptr) noexcept
			: _data{ptr} {
				// code here...
			}

			/* unique pointer constructor */
			template <class D>
			WeakPointer(const Xf::UniquePointer<D>& unique) noexcept
			requires (Xf::is_base_of_c<T, D>)
			: _data{unique._data} {
				// code here...
			}

			/* shared pointer constructor */
			template <class D>
			WeakPointer(const Xf::SharedPointer<D>& shared) noexcept
			requires (Xf::is_base_of_c<T, D>)
			: _data{shared._data} {
				// code here...
			}

			/* copy constructor */
			WeakPointer(const Self& other) noexcept
			: _data{other._data} {
				// code here...
			}

			/* derived copy constructor */
			template <class D>
			WeakPointer(const WeakPointer<D>& other) noexcept
			requires (Xf::is_base_of_c<T, D>)
			: _data{other._data} {
				// code here...
			}

			/* move constructor */
			WeakPointer(Self&& other) noexcept
			: _data{other._data} {
				// invalidate other
				other._data = nullptr;
			}

			/* derived move constructor */
			template <class D>
			WeakPointer(WeakPointer<D>&& other) noexcept
			requires (Xf::is_base_of_c<T, D>)
			: _data{other._data} {
				// invalidate other
				other._data = nullptr;
			}

			/* destructor */
			~WeakPointer(void) noexcept = default;


			// -- P U B L I C  A S S I G N M E N T ----------------------------

			/* nullptr assignment */
			Self& assign(Xf::Nullptr) noexcept {
				// assign null pointer
				_data = nullptr;
				// return self reference
				return *this;
			}

			/* pointer assignment */
			Self& assign(Pointer ptr) noexcept {
				// assign pointer
				_data = ptr;
				// return self reference
				return *this;
			}

			/* copy assignment */
			Self& assign(const Self& other) noexcept {
				// assign other data
				_data = other._data;
				// return self reference
				return *this;
			}

			/* derived copy assignment */
			template <class D>
			Self& assign(const WeakPointer<D>& other) noexcept
			requires (Xf::is_base_of_c<T, D>) {
				// assign other data
				_data = other._data;
				// return self reference
				return *this;
			}

			/* move assignment */
			Self& assign(Self&& other) noexcept {
				// check for self assignment
				if (this != &other) {
					// assign other data
					_data = other._data;
					// invalidate other
					other._data = nullptr;
				} // return self reference
				return *this;
			}

			/* derived move assignment */
			template <class D>
			Self& assign(WeakPointer<D>&& other) noexcept
			requires (Xf::is_base_of_c<T, D>) {
				// check for self assignment
				if (this != &other) {
					// assign other data
					_data = other._data;
					// invalidate other
					other._data = nullptr;
				} // return self reference
				return *this;
			}

			/* unique pointer assignment */
			template <class D>
			Self& assign(const Xf::UniquePointer<D>& ptr) noexcept
			requires (Xf::is_base_of_c<T, D>) {
				// assign pointer
				_data = ptr._data;
				// return self reference
				return *this;
			}

			/* shared pointer assignment */
			template <class D>
			Self& assign(const Xf::SharedPointer<D>& ptr) noexcept
			requires (Xf::is_base_of_c<T, D>) {
				// assign pointer
				_data = ptr._data;
				// return self reference
				return *this;
			}


			// -- P U B L I C  A S S I G N M E N T  O P E R A T O R S ---------

			/* nullptr assignment operator */
			Self& operator=(Xf::Nullptr) noexcept {
				// return nullptr assignment
				return assign(nullptr);
			}

			/* pointer assignment operator */
			Self& operator=(Pointer ptr) noexcept {
				// return pointer assignment
				return assign(ptr);
			}

			/* copy assignment operator */
			Self& operator=(const Self& other) noexcept {
				// return copy assignment
				return assign(other);
			}

			/* derived copy assignment operator */
			template <class D>
			Self& operator=(const WeakPointer<D>& other) noexcept
			requires (Xf::is_base_of_c<T, D>) {
				// return derived copy assignment
				return assign(other);
			}

			/* move assignment operator */
			Self& operator=(Self&& other) noexcept {
				// return move assignment
				return assign(Xf::move(other));
			}

			/* derived move assignment operator */
			template <class D>
			Self& operator=(WeakPointer<D>&& other) noexcept
			requires (Xf::is_base_of_c<T, D>) {
				// return derived move assignment
				return assign(Xf::move(other));
			}

			/* unique pointer assignment operator */
			template <class D>
			Self& operator=(const Xf::UniquePointer<D>& ptr) noexcept
			requires (Xf::is_base_of_c<T, D>) {
				// return unique pointer assignment
				return assign(ptr);
			}

			/* shared pointer assignment operator */
			template <class D>
			Self& operator=(const Xf::SharedPointer<D>& ptr) noexcept
			requires (Xf::is_base_of_c<T, D>) {
				// return shared pointer assignment
				return assign(ptr);
			}


			// -- P U B L I C  A C C E S S O R S  O P E R A T O R S -----------

			/* dereference operator */
			Reference operator*(void) noexcept {
				// return reference
				return *_data;
			}

			/* const dereference operator */
			ConstRef operator*(void) const noexcept {
				// return const reference
				return *_data;
			}

			/* arrow operator */
			Pointer operator->(void) noexcept {
				// return pointer
				return _data;
			}

			/* const arrow operator */
			ConstPtr operator->(void) const noexcept {
				// return const pointer
				return _data;
			}


			// -- P U B L I C  B O O L E A N S  O P E R A T O R S -------------

			/* boolean operator */
			operator Bool(void) const noexcept {
				// return pointer validity
				return _data != nullptr;
			}

			/* not operator */
			Bool operator!(void) const noexcept {
				// return pointer invalidity
				return _data == nullptr;
			}


			// -- P U B L I C  C O M P A R I S O N  O P E R A T O R S ---------

			/* equality operator */
			Bool operator==(const Self& other) const noexcept {
				// return pointer equality
				return _data == other._data;
			}

			/* inequality operator */
			Bool operator!=(const Self& other) const noexcept {
				// return pointer inequality
				return _data != other._data;
			}

			/* null equality operator */
			Bool operator==(Xf::Nullptr) const noexcept {
				// return pointer invalidity
				return _data == nullptr;
			}

			/* null inequality operator */
			Bool operator!=(Xf::Nullptr) const noexcept {
				// return pointer validity
				return _data != nullptr;
			}


		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			/* pointer */
			Pointer _data;



	};


};

#endif
