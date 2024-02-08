/*****************************************************************************/
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*****************************************************************************/

#pragma once

#ifndef XNS_UNIQUE_PTR_HPP
#define XNS_UNIQUE_PTR_HPP

#include "types.hpp"
#include "allocator.hpp"
#include "inheritance.hpp"
#include "is_same.hpp"
#include "memory.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- U N I Q U E  P T R --------------------------------------------------

	template <typename T>
	class unique_ptr final {


		// -- friends ---------------------------------------------------------

		/* weak pointer as friend */
		template <typename>
		friend class weak_ptr;

		/* derived types as friend */
		template <typename>
		friend class unique_ptr;

		/* make unique as friend */
		template <typename U, typename... A>
		friend auto make_unique(A&&...) -> xns::unique_ptr<U>;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self       = xns::unique_ptr<T>;

			/* value type */
			using type       = T;

			/* reference type */
			using mut_ref    = type&;

			/* move reference type */
			using move_ref   = type&&;

			/* const reference type */
			using const_ref  = const type&;

			/* pointer type */
			using mut_ptr    = type*;

			/* const pointer type */
			using const_ptr  = const type*;

			/* allocator type */
			using allocator  = xns::allocator<type>;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline unique_ptr(void) noexcept
			: _data{nullptr} {
			}

			/* nullptr constructor */
			inline unique_ptr(xns::null) noexcept
			: _data{nullptr} {
			}

			/* pointer constructor */
			inline unique_ptr(mut_ptr ptr) noexcept
			: _data{ptr} {
			}

			/* non-copyable class */
			non_copyable(unique_ptr);

			/* self move constructor */
			inline unique_ptr(self&& other) noexcept
			: _data(other._data) {
				other._data = nullptr;
			}

			/* derived move constructor */
			template <typename D> requires (xns::is_derived_from<D, type>)
			inline unique_ptr(xns::unique_ptr<D>&& other) noexcept
			: _data(other._data) {
				// invalidate other
				other._data = nullptr;
			}

			/* destructor */
			inline ~unique_ptr(void) noexcept {
				// deallocate memory
				free();
			}


			// -- public assignments ------------------------------------------

			/* nullptr assignment */
			inline auto assign(xns::null) noexcept -> void {
				// clean up
				reset();
			}

			/* self move assignment */
			auto assign(self&& other) noexcept -> void {
				// check for self assignment
				if (this != &other) {
					// deallocate memory
					free();
					// move other
					_data = other._data;
					// invalidate other
					other._data = nullptr; }
			}

			/* derived move assignment */
			template <class D> requires (xns::is_derived_from<D, type>)
			auto assign(unique_ptr<D>&& other) noexcept -> void {
				// check for self assignment
				if (this != reinterpret_cast<self*>(&other)) {
					// deallocate memory
					free();
					// move other
					_data = other._data;
					// invalidate other
					other._data = nullptr; }
			}


			// -- public assignment operators ---------------------------------

			/* nullptr assignment operator */
			inline auto operator=(xns::null) noexcept -> self& {
				// call nullptr assignment
				assign(nullptr);
				return *this;
			}

			/* self move assignment operator */
			inline auto operator=(self&& other) noexcept -> self& {
				// call self move assignment
				assign(xns::move(other));
				return *this;
			}

			/* derived move assignment operator */
			template <typename D> requires (xns::is_derived_from<D, type>)
			inline auto operator=(xns::unique_ptr<D>&& other) noexcept -> self& {
				// call derived move assignment
				assign(xns::move(other));
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* dereference operator */
			inline auto operator*(void) noexcept -> mut_ref {
				return *_data;
			}

			/* const dereference operator */
			inline auto operator*(void) const noexcept -> const_ref {
				return *_data;
			}

			/* arrow operator */
			inline auto operator->(void) noexcept -> mut_ptr {
				return _data;
			}

			/* const arrow operator */
			inline auto operator->(void) const noexcept -> const_ptr {
				return _data;
			}

			/* get */
			inline auto get(void) noexcept -> mut_ptr {
				return _data;
			}

			/* const get */
			inline auto get(void) const noexcept -> const_ptr {
				return _data;
			}



			// -- public boolean operators ------------------------------------

			/* boolean operator */
			inline explicit operator bool(void) const noexcept {
				return _data != nullptr;
			}

			/* not operator */
			inline auto operator!(void) const noexcept -> bool {
				return _data == nullptr;
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			inline auto operator==(const self& other) const noexcept -> bool {
				return _data == other._data;
			}

			/* inequality operator */
			inline auto operator!=(const self& other) const noexcept -> bool {
				return _data != other._data;
			}

			/* nullptr equality operator */
			inline auto operator==(xns::null) const noexcept -> bool {
				return _data == nullptr;
			}

			/* nullptr inequality operator */
			inline auto operator!=(xns::null) const noexcept -> bool {
				return _data != nullptr;
			}


			// -- public modifiers --------------------------------------------

			/* reset */
			inline auto reset(void) noexcept -> void {
				free(); init();
			}

			/* release */
			inline auto release(void) noexcept -> mut_ptr {
				// get pointer
				mut_ptr ptr = _data;
				// invalidate pointer
				_data = nullptr;
				// return pointer
				return ptr;
			}


			// -- public conversion -------------------------------------------

			/* base reference cast */
			template <typename B>
			inline auto as(void) noexcept -> xns::unique_ptr<B>& {
				static_assert(xns::is_base_of<B, type>, "WOOO, THIS CAST IS NOT ALLOWED");
				// return casted reference
				return reinterpret_cast<unique_ptr<B>&>(*this);
			}

			/* base const reference cast */
			template <typename B>
			inline auto as(void) const noexcept -> const unique_ptr<B>& {
				static_assert(xns::is_base_of<B, type>, "WOOO, THIS CAST IS NOT ALLOWED");
				// return casted const reference
				return reinterpret_cast<const unique_ptr<B>&>(*this);
			}


		private:


			// -- private methods ---------------------------------------------

			/* init */
			inline auto init(void) noexcept -> void {
				_data = nullptr;
			}

			/* deallocate memory */
			inline auto free(void) noexcept -> void {
				// check pointer validity
				if (_data == nullptr)
					return;
				// destroy object
				allocator::destroy(_data);
				// deallocate memory
				allocator::deallocate(_data);
			}


			// -- private members ---------------------------------------------

			/* data */
			self::mut_ptr _data;


	};


	// -- non-member functions ------------------------------------------------

	/* make unique */
	template <typename T, typename... A>
	auto make_unique(A&&... args) -> xns::unique_ptr<T> {
		// instantiate unique pointer
		unique_ptr<T> ptr;
		// allocate memory
		ptr._data = unique_ptr<T>::allocator::allocate();
		// construct object by forwarding arguments
		unique_ptr<T>::allocator::construct(ptr._data, xns::forward<A>(args)...);
		// return unique pointer
		return ptr;
	}

} // namespace xns

#endif // XNS_UNIQUE_PTR_HPP


#include "is_function.hpp"
#include "enable_if.hpp"
#include "is_convertible.hpp"
#include "is_void.hpp"

//namespace xns {
//
//	template <typename T>
//	class default_delete {
//
//		public:
//
//			// -- public types ------------------------------------------------
//
//			/* self type */
//			using self = xns::default_delete<T>;
//
//			static_assert(not xns::is_function<T>,
//						"default_delete cannot be instantiated for function types");
//
//
//			template <typename U> requires (xns::is_convertible<U*, T*>)
//			inline constexpr default_delete(const default_delete<U>&) noexcept {
//			}
//
//			inline constexpr auto operator()(T* ptr) const noexcept -> void {
//				static_assert(sizeof(T) >= 0, "cannot delete an incomplete type");
//				static_assert(not xns::is_void<T>, "cannot delete an incomplete type");
//				delete ptr;
//			}
//		};
//
//#endif


	/*

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS default_delete<_Tp[]> {
private:
  template <class _Up>
  struct _EnableIfConvertible
      : enable_if<is_convertible<_Up(*)[], _Tp(*)[]>::value> {};

public:
#ifndef _LIBCPP_CXX03_LANG
  _LIBCPP_INLINE_VISIBILITY constexpr default_delete() _NOEXCEPT = default;
#else
  _LIBCPP_INLINE_VISIBILITY default_delete() {}
#endif

  template <class _Up>
  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23
  default_delete(const default_delete<_Up[]>&, typename _EnableIfConvertible<_Up>::type* = 0) _NOEXCEPT {}

  template <class _Up>
  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 typename _EnableIfConvertible<_Up>::type
  operator()(_Up* __ptr) const _NOEXCEPT {
    static_assert(sizeof(_Up) >= 0, "cannot delete an incomplete type");
    delete[] __ptr;
  }
};





template <class _Deleter>
struct __unique_ptr_deleter_sfinae {
  static_assert(!is_reference<_Deleter>::value, "incorrect specialization");
  typedef const _Deleter& __lval_ref_type;
  typedef _Deleter&& __good_rval_ref_type;
  typedef true_type __enable_rval_overload;
};

template <class _Deleter>
struct __unique_ptr_deleter_sfinae<_Deleter const&> {
  typedef const _Deleter& __lval_ref_type;
  typedef const _Deleter&& __bad_rval_ref_type;
  typedef false_type __enable_rval_overload;
};

template <class _Deleter>
struct __unique_ptr_deleter_sfinae<_Deleter&> {
  typedef _Deleter& __lval_ref_type;
  typedef _Deleter&& __bad_rval_ref_type;
  typedef false_type __enable_rval_overload;
};


template <typename T, typename D = xns::default_delete<T>>
class unique_ptr2 {

	public:

		typedef _Tp element_type;
		typedef _Dp deleter_type;
		typedef _LIBCPP_NODEBUG typename __pointer<_Tp, deleter_type>::type pointer;


		static_assert(!is_rvalue_reference<deleter_type>::value,
				"the specified deleter type cannot be an rvalue reference");

private:
  __compressed_pair<pointer, deleter_type> __ptr_;

  struct __nat { int __for_bool_; };

  typedef _LIBCPP_NODEBUG __unique_ptr_deleter_sfinae<_Dp> _DeleterSFINAE;

  template <bool _Dummy>
  using _LValRefType _LIBCPP_NODEBUG =
      typename __dependent_type<_DeleterSFINAE, _Dummy>::__lval_ref_type;

  template <bool _Dummy>
  using _GoodRValRefType _LIBCPP_NODEBUG =
      typename __dependent_type<_DeleterSFINAE, _Dummy>::__good_rval_ref_type;

  template <bool _Dummy>
  using _BadRValRefType _LIBCPP_NODEBUG =
      typename __dependent_type<_DeleterSFINAE, _Dummy>::__bad_rval_ref_type;

  template <bool _Dummy, class _Deleter = typename __dependent_type<
                             __type_identity<deleter_type>, _Dummy>::type>
  using _EnableIfDeleterDefaultConstructible _LIBCPP_NODEBUG =
      typename enable_if<is_default_constructible<_Deleter>::value &&
                         !is_pointer<_Deleter>::value>::type;

  template <class _ArgType>
  using _EnableIfDeleterConstructible _LIBCPP_NODEBUG =
      typename enable_if<is_constructible<deleter_type, _ArgType>::value>::type;

  template <class _UPtr, class _Up>
  using _EnableIfMoveConvertible _LIBCPP_NODEBUG = typename enable_if<
      is_convertible<typename _UPtr::pointer, pointer>::value &&
      !is_array<_Up>::value
  >::type;

  template <class _UDel>
  using _EnableIfDeleterConvertible _LIBCPP_NODEBUG = typename enable_if<
      (is_reference<_Dp>::value && is_same<_Dp, _UDel>::value) ||
      (!is_reference<_Dp>::value && is_convertible<_UDel, _Dp>::value)
    >::type;

  template <class _UDel>
  using _EnableIfDeleterAssignable = typename enable_if<
      is_assignable<_Dp&, _UDel&&>::value
    >::type;

public:
  template <bool _Dummy = true,
            class = _EnableIfDeleterDefaultConstructible<_Dummy> >
  _LIBCPP_INLINE_VISIBILITY
  _LIBCPP_CONSTEXPR unique_ptr() _NOEXCEPT : __ptr_(__value_init_tag(), __value_init_tag()) {}

  template <bool _Dummy = true,
            class = _EnableIfDeleterDefaultConstructible<_Dummy> >
  _LIBCPP_INLINE_VISIBILITY
  _LIBCPP_CONSTEXPR unique_ptr(nullptr_t) _NOEXCEPT : __ptr_(__value_init_tag(), __value_init_tag()) {}

  template <bool _Dummy = true, class = _EnableIfDeleterDefaultConstructible<_Dummy> >
  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 explicit unique_ptr(pointer __p) _NOEXCEPT
      : __ptr_(__p, __value_init_tag()) {}

  template <bool _Dummy = true, class = _EnableIfDeleterConstructible<_LValRefType<_Dummy> > >
  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 unique_ptr(pointer __p, _LValRefType<_Dummy> __d) _NOEXCEPT
      : __ptr_(__p, __d) {}

  template <bool _Dummy = true, class = _EnableIfDeleterConstructible<_GoodRValRefType<_Dummy> > >
  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23
  unique_ptr(pointer __p, _GoodRValRefType<_Dummy> __d) _NOEXCEPT : __ptr_(__p, _VSTD::move(__d)) {
    static_assert(!is_reference<deleter_type>::value,
                  "rvalue deleter bound to reference");
  }

  template <bool _Dummy = true,
            class = _EnableIfDeleterConstructible<_BadRValRefType<_Dummy> > >
  _LIBCPP_INLINE_VISIBILITY
  unique_ptr(pointer __p, _BadRValRefType<_Dummy> __d) = delete;

  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 unique_ptr(unique_ptr&& __u) _NOEXCEPT
      : __ptr_(__u.release(), _VSTD::forward<deleter_type>(__u.get_deleter())) {}

  template <class _Up,
            class _Ep,
            class = _EnableIfMoveConvertible<unique_ptr<_Up, _Ep>, _Up>,
            class = _EnableIfDeleterConvertible<_Ep> >
  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 unique_ptr(unique_ptr<_Up, _Ep>&& __u) _NOEXCEPT
      : __ptr_(__u.release(), _VSTD::forward<_Ep>(__u.get_deleter())) {}

#if _LIBCPP_STD_VER <= 14 || defined(_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR)
  template <class _Up>
  _LIBCPP_INLINE_VISIBILITY
  unique_ptr(auto_ptr<_Up>&& __p,
             typename enable_if<is_convertible<_Up*, _Tp*>::value &&
                                    is_same<_Dp, default_delete<_Tp> >::value,
                                __nat>::type = __nat()) _NOEXCEPT
      : __ptr_(__p.release(), __value_init_tag()) {}
#endif

  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 unique_ptr& operator=(unique_ptr&& __u) _NOEXCEPT {
    reset(__u.release());
    __ptr_.second() = _VSTD::forward<deleter_type>(__u.get_deleter());
    return *this;
  }

  template <class _Up,
            class _Ep,
            class = _EnableIfMoveConvertible<unique_ptr<_Up, _Ep>, _Up>,
            class = _EnableIfDeleterAssignable<_Ep> >
  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 unique_ptr& operator=(unique_ptr<_Up, _Ep>&& __u) _NOEXCEPT {
    reset(__u.release());
    __ptr_.second() = _VSTD::forward<_Ep>(__u.get_deleter());
    return *this;
  }

#if _LIBCPP_STD_VER <= 14 || defined(_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR)
  template <class _Up>
  _LIBCPP_INLINE_VISIBILITY
      typename enable_if<is_convertible<_Up*, _Tp*>::value &&
                             is_same<_Dp, default_delete<_Tp> >::value,
                         unique_ptr&>::type
      operator=(auto_ptr<_Up> __p) {
    reset(__p.release());
    return *this;
  }
#endif

#ifdef _LIBCPP_CXX03_LANG
  unique_ptr(unique_ptr const&) = delete;
  unique_ptr& operator=(unique_ptr const&) = delete;
#endif

  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 ~unique_ptr() { reset(); }

  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 unique_ptr& operator=(nullptr_t) _NOEXCEPT {
    reset();
    return *this;
  }

  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 __add_lvalue_reference_t<_Tp> operator*() const {
    return *__ptr_.first();
  }
  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 pointer operator->() const _NOEXCEPT {
    return __ptr_.first();
  }
  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 pointer get() const _NOEXCEPT { return __ptr_.first(); }
  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 deleter_type& get_deleter() _NOEXCEPT {
    return __ptr_.second();
  }
  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 const deleter_type& get_deleter() const _NOEXCEPT {
    return __ptr_.second();
  }
  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 explicit operator bool() const _NOEXCEPT {
    return __ptr_.first() != nullptr;
  }

  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 pointer release() _NOEXCEPT {
    pointer __t = __ptr_.first();
    __ptr_.first() = pointer();
    return __t;
  }

  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 void reset(pointer __p = pointer()) _NOEXCEPT {
    pointer __tmp = __ptr_.first();
    __ptr_.first() = __p;
    if (__tmp)
      __ptr_.second()(__tmp);
  }

  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 void swap(unique_ptr& __u) _NOEXCEPT {
    __ptr_.swap(__u.__ptr_);
  }
};



// specializations for array types

//template <class _Tp, class _Dp>
//class _LIBCPP_UNIQUE_PTR_TRIVIAL_ABI _LIBCPP_TEMPLATE_VIS unique_ptr<_Tp[], _Dp> {
//public:
//  typedef _Tp element_type;
//  typedef _Dp deleter_type;
//  typedef typename __pointer<_Tp, deleter_type>::type pointer;
//
//private:
//  __compressed_pair<pointer, deleter_type> __ptr_;
//
//  template <class _From>
//  struct _CheckArrayPointerConversion : is_same<_From, pointer> {};
//
//  template <class _FromElem>
//  struct _CheckArrayPointerConversion<_FromElem*>
//      : integral_constant<bool,
//          is_same<_FromElem*, pointer>::value ||
//            (is_same<pointer, element_type*>::value &&
//             is_convertible<_FromElem(*)[], element_type(*)[]>::value)
//      >
//  {};
//
//  typedef __unique_ptr_deleter_sfinae<_Dp> _DeleterSFINAE;
//
//  template <bool _Dummy>
//  using _LValRefType _LIBCPP_NODEBUG =
//      typename __dependent_type<_DeleterSFINAE, _Dummy>::__lval_ref_type;
//
//  template <bool _Dummy>
//  using _GoodRValRefType _LIBCPP_NODEBUG =
//      typename __dependent_type<_DeleterSFINAE, _Dummy>::__good_rval_ref_type;
//
//  template <bool _Dummy>
//  using _BadRValRefType _LIBCPP_NODEBUG =
//      typename __dependent_type<_DeleterSFINAE, _Dummy>::__bad_rval_ref_type;
//
//  template <bool _Dummy, class _Deleter = typename __dependent_type<
//                             __type_identity<deleter_type>, _Dummy>::type>
//  using _EnableIfDeleterDefaultConstructible _LIBCPP_NODEBUG =
//      typename enable_if<is_default_constructible<_Deleter>::value &&
//                         !is_pointer<_Deleter>::value>::type;
//
//  template <class _ArgType>
//  using _EnableIfDeleterConstructible _LIBCPP_NODEBUG =
//      typename enable_if<is_constructible<deleter_type, _ArgType>::value>::type;
//
//  template <class _Pp>
//  using _EnableIfPointerConvertible _LIBCPP_NODEBUG = typename enable_if<
//      _CheckArrayPointerConversion<_Pp>::value
//  >::type;
//
//  template <class _UPtr, class _Up,
//        class _ElemT = typename _UPtr::element_type>
//  using _EnableIfMoveConvertible _LIBCPP_NODEBUG = typename enable_if<
//      is_array<_Up>::value &&
//      is_same<pointer, element_type*>::value &&
//      is_same<typename _UPtr::pointer, _ElemT*>::value &&
//      is_convertible<_ElemT(*)[], element_type(*)[]>::value
//    >::type;
//
//  template <class _UDel>
//  using _EnableIfDeleterConvertible _LIBCPP_NODEBUG = typename enable_if<
//      (is_reference<_Dp>::value && is_same<_Dp, _UDel>::value) ||
//      (!is_reference<_Dp>::value && is_convertible<_UDel, _Dp>::value)
//    >::type;
//
//  template <class _UDel>
//  using _EnableIfDeleterAssignable _LIBCPP_NODEBUG = typename enable_if<
//      is_assignable<_Dp&, _UDel&&>::value
//    >::type;
//
//public:
//  template <bool _Dummy = true,
//            class = _EnableIfDeleterDefaultConstructible<_Dummy> >
//  _LIBCPP_INLINE_VISIBILITY
//  _LIBCPP_CONSTEXPR unique_ptr() _NOEXCEPT : __ptr_(__value_init_tag(), __value_init_tag()) {}
//
//  template <bool _Dummy = true,
//            class = _EnableIfDeleterDefaultConstructible<_Dummy> >
//  _LIBCPP_INLINE_VISIBILITY
//  _LIBCPP_CONSTEXPR unique_ptr(nullptr_t) _NOEXCEPT : __ptr_(__value_init_tag(), __value_init_tag()) {}
//
//  template <class _Pp,
//            bool _Dummy = true,
//            class       = _EnableIfDeleterDefaultConstructible<_Dummy>,
//            class       = _EnableIfPointerConvertible<_Pp> >
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 explicit unique_ptr(_Pp __p) _NOEXCEPT
//      : __ptr_(__p, __value_init_tag()) {}
//
//  template <class _Pp,
//            bool _Dummy = true,
//            class       = _EnableIfDeleterConstructible<_LValRefType<_Dummy> >,
//            class       = _EnableIfPointerConvertible<_Pp> >
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 unique_ptr(_Pp __p, _LValRefType<_Dummy> __d) _NOEXCEPT
//      : __ptr_(__p, __d) {}
//
//  template <bool _Dummy = true, class = _EnableIfDeleterConstructible<_LValRefType<_Dummy> > >
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 unique_ptr(nullptr_t, _LValRefType<_Dummy> __d) _NOEXCEPT
//      : __ptr_(nullptr, __d) {}
//
//  template <class _Pp,
//            bool _Dummy = true,
//            class       = _EnableIfDeleterConstructible<_GoodRValRefType<_Dummy> >,
//            class       = _EnableIfPointerConvertible<_Pp> >
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 unique_ptr(_Pp __p, _GoodRValRefType<_Dummy> __d) _NOEXCEPT
//      : __ptr_(__p, _VSTD::move(__d)) {
//    static_assert(!is_reference<deleter_type>::value,
//                  "rvalue deleter bound to reference");
//  }
//
//  template <bool _Dummy = true, class = _EnableIfDeleterConstructible<_GoodRValRefType<_Dummy> > >
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 unique_ptr(nullptr_t, _GoodRValRefType<_Dummy> __d) _NOEXCEPT
//      : __ptr_(nullptr, _VSTD::move(__d)) {
//    static_assert(!is_reference<deleter_type>::value,
//                  "rvalue deleter bound to reference");
//  }
//
//  template <class _Pp, bool _Dummy = true,
//            class = _EnableIfDeleterConstructible<_BadRValRefType<_Dummy> >,
//            class = _EnableIfPointerConvertible<_Pp> >
//  _LIBCPP_INLINE_VISIBILITY
//  unique_ptr(_Pp __p, _BadRValRefType<_Dummy> __d) = delete;
//
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 unique_ptr(unique_ptr&& __u) _NOEXCEPT
//      : __ptr_(__u.release(), _VSTD::forward<deleter_type>(__u.get_deleter())) {}
//
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 unique_ptr& operator=(unique_ptr&& __u) _NOEXCEPT {
//    reset(__u.release());
//    __ptr_.second() = _VSTD::forward<deleter_type>(__u.get_deleter());
//    return *this;
//  }
//
//  template <class _Up,
//            class _Ep,
//            class = _EnableIfMoveConvertible<unique_ptr<_Up, _Ep>, _Up>,
//            class = _EnableIfDeleterConvertible<_Ep> >
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 unique_ptr(unique_ptr<_Up, _Ep>&& __u) _NOEXCEPT
//      : __ptr_(__u.release(), _VSTD::forward<_Ep>(__u.get_deleter())) {}
//
//  template <class _Up,
//            class _Ep,
//            class = _EnableIfMoveConvertible<unique_ptr<_Up, _Ep>, _Up>,
//            class = _EnableIfDeleterAssignable<_Ep> >
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 unique_ptr& operator=(unique_ptr<_Up, _Ep>&& __u) _NOEXCEPT {
//    reset(__u.release());
//    __ptr_.second() = _VSTD::forward<_Ep>(__u.get_deleter());
//    return *this;
//  }
//
//#ifdef _LIBCPP_CXX03_LANG
//  unique_ptr(unique_ptr const&) = delete;
//  unique_ptr& operator=(unique_ptr const&) = delete;
//#endif
//public:
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 ~unique_ptr() { reset(); }
//
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 unique_ptr& operator=(nullptr_t) _NOEXCEPT {
//    reset();
//    return *this;
//  }
//
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 __add_lvalue_reference_t<_Tp>
//  operator[](size_t __i) const {
//    return __ptr_.first()[__i];
//  }
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 pointer get() const _NOEXCEPT { return __ptr_.first(); }
//
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 deleter_type& get_deleter() _NOEXCEPT {
//    return __ptr_.second();
//  }
//
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 const deleter_type& get_deleter() const _NOEXCEPT {
//    return __ptr_.second();
//  }
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 explicit operator bool() const _NOEXCEPT {
//    return __ptr_.first() != nullptr;
//  }
//
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 pointer release() _NOEXCEPT {
//    pointer __t = __ptr_.first();
//    __ptr_.first() = pointer();
//    return __t;
//  }
//
//  template <class _Pp>
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23
//      typename enable_if< _CheckArrayPointerConversion<_Pp>::value >::type
//      reset(_Pp __p) _NOEXCEPT {
//    pointer __tmp = __ptr_.first();
//    __ptr_.first() = __p;
//    if (__tmp)
//      __ptr_.second()(__tmp);
//  }
//
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 void reset(nullptr_t = nullptr) _NOEXCEPT {
//    pointer __tmp = __ptr_.first();
//    __ptr_.first() = nullptr;
//    if (__tmp)
//      __ptr_.second()(__tmp);
//  }
//
//  _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX23 void swap(unique_ptr& __u) _NOEXCEPT {
//    __ptr_.swap(__u.__ptr_);
//  }
//};



template <typename T, typename D> requires (xns::is_swappable<D>)
inline constexpr swap(unique_ptr<T, D>& __x, unique_ptr<T, D>& __y) noexcept {
  __x.swap(__y);
}



template <typename T>
struct unique_if final {
	using unique_single = xns::unique_ptr<T>;
};

template <typename T>
struct unique_if<T[]> final { {
	using unique_array_unknown_bound = xns::unique_ptr<T[]>;
};

template <typename T, decltype(sizeof(0)) N>
struct unique_if <T[N]> final {
	using unique_array_known_bound = void;
};


template <typename T, typename... A>
inline constexpr auto make_unique(A&&... args) -> typename unique_if<T>unique_single {
	return xns::unique_ptr<T>(new T(xns::forward<A>(args)...));
}

template <typename T>
inline constexpr auto make_unique(const decltype(sizeof(0)) size) -> typename unique_if<T>::unique_array_unknown_bound {

	using up = __remove_extent_t<T>;
	return xns::unique_ptr<T>(new up[size]{});
}

template <typename T, typename... A>
auto make_unique(A&&...) -> typename unique_if<T>::unique_array_known_bound = delete;



template <typename T>
inline constexpr auto make_unique_for_overwrite(void) -> typename unique_if<T>::unique_single {
	return xns::unique_ptr<T>(new T);
}

template <typename T>
inline constexpr auto
make_unique_for_overwrite(const decltype(sizeof(0)) size) -> typename unique_if<T>::unique_array_unknown_bound {
  return xns::unique_ptr<T>(new __remove_extent_t<T>[size]);
}

template <typename T, typename... A>
auto make_unique_for_overwrite(A&&...) -> typename unique_if<T>::unique_array_known_bound = delete;



template <typename T>
struct hash;

template <typename T, typename D>
struct hash<xns::unique_ptr<T, D>> {

	inline size_t operator()(const xns::unique_ptr<T, D>& ptr) const {
		using pointer = xns::unique_ptr<T, D>::pointer;
		return xns::hash<pointer>{}(ptr.get());
	}
};



#endif // _LIBCPP___MEMORY_UNIQUE_PTR_H
*/

