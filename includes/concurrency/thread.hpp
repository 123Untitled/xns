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

#ifndef XNS_THREAD_HPP
#define XNS_THREAD_HPP

// local headers
#include "macros.hpp"
#include "tuple.hpp"
#include "apply.hpp"

#include "is_function.hpp"
#include "integer_sequence.hpp"
#include "unique_ptr.hpp"
#include "invoke.hpp"

// operating system headers
#include <pthread.h>
#include <unistd.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- T H R E A D ---------------------------------------------------------

	class thread final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::thread;

			/* thread type */
			using thread_type = ::pthread_t;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			thread(void) noexcept;

			/* function constructor */
			template <typename F, typename... A>
			explicit thread(F&& func, A&&... args)
			: _thread{} {

				// declare tuple type
				using tuple_type = xns::tuple<std::decay_t<F>,
											  std::decay_t<A>...>;

				// allocate tuple
				auto unique = xns::make_unique<tuple_type>(xns::forward<F>(func),
														   xns::forward<A>(args)...);
				// create thread
				if (::pthread_create(&_thread,
									 nullptr,
									 thread_proxy<tuple_type>,
									 unique.get()) != 0) {
					; // handle error
					return;
				}
				unique.release();
			}

			/* deleted copy constructor */
			thread(const self&) = delete;

			/* move constructor */
			thread(self&&) noexcept;

			/* destructor */
			~thread(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public methods ----------------------------------------------

			/* join */
			auto join(void) noexcept -> void;

			/* detach */
			auto detach(void) noexcept -> void;

			/* swap */
			auto swap(self&) noexcept -> void;

			// -- public accessors --------------------------------------------

			/* joinable */
			auto joinable(void) const noexcept -> bool;

			/* native handle */
			auto native_handle(void) const noexcept -> const thread_type&;


			// -- public static methods ---------------------------------------

			/* hardware_concurrency */
			static auto hardware_concurrency(void) noexcept -> unsigned int;


		private:

			// -- private static methods --------------------------------------

			template <typename F, typename... A, auto... I>
			static inline auto thread_execute(xns::tuple<F, A...>& tuple,
									   xns::index_sequence<I...>) -> void {
				xns::invoke(std::move(xns::get<0>(tuple)),
							std::move(xns::get<I>(tuple))...);
			}

			/* thread proxy */
			template <typename T>
			static auto thread_proxy(void* arg) -> void* {
				// reconstruct unique pointer
				xns::unique_ptr<T> unique{static_cast<T*>(arg)};
				// execute thread
				self::thread_execute(*unique,
									// make index sequence
									xns::make_index_range<1, xns::tuple_size<T>>{});
				return nullptr;
			}


			// -- private members ---------------------------------------------

			/* thread */
			thread_type _thread;

	}; // class thread



	class thread_pool final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::thread_pool;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			thread_pool(void) noexcept;


		private:




	}; // class thread_pool



} // namespace xns

#endif // XNS_THREAD_HPP











//namespace this_thread
//{
//
//_LIBCPP_EXPORTED_FROM_ABI void sleep_for(const chrono::nanoseconds& __ns);
//
//template <class _Rep, class _Period>
//_LIBCPP_HIDE_FROM_ABI void
//sleep_for(const chrono::duration<_Rep, _Period>& __d)
//{
//    if (__d > chrono::duration<_Rep, _Period>::zero())
//    {
//        // The standard guarantees a 64bit signed integer resolution for nanoseconds,
//        // so use INT64_MAX / 1e9 as cut-off point. Use a constant to avoid <climits>
//        // and issues with long double folding on PowerPC with GCC.
//        _LIBCPP_CONSTEXPR chrono::duration<long double> __max =
//            chrono::duration<long double>(9223372036.0L);
//        chrono::nanoseconds __ns;
//        if (__d < __max)
//        {
//            __ns = chrono::duration_cast<chrono::nanoseconds>(__d);
//            if (__ns < __d)
//                ++__ns;
//        }
//        else
//            __ns = chrono::nanoseconds::max();
//        this_thread::sleep_for(__ns);
//    }
//}
//
//template <class _Clock, class _Duration>
//_LIBCPP_HIDE_FROM_ABI void
//sleep_until(const chrono::time_point<_Clock, _Duration>& __t)
//{
//    mutex __mut;
//    condition_variable __cv;
//    unique_lock<mutex> __lk(__mut);
//    while (_Clock::now() < __t)
//        __cv.wait_until(__lk, __t);
//}
//
//template <class _Duration>
//inline _LIBCPP_INLINE_VISIBILITY
//void
//sleep_until(const chrono::time_point<chrono::steady_clock, _Duration>& __t)
//{
//    this_thread::sleep_for(__t - chrono::steady_clock::now());
//}
//
//inline _LIBCPP_INLINE_VISIBILITY
//void yield() _NOEXCEPT {__libcpp_thread_yield();}
//
//} // namespace this_thread
//
//_LIBCPP_END_NAMESPACE_STD
//
//_LIBCPP_POP_MACROS
//
//#endif // _LIBCPP___THREAD_THIS_THREAD_H
//
//
//
//
//// -*- C++ -*-
////===----------------------------------------------------------------------===//
////
//// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
//// See https://llvm.org/LICENSE.txt for license information.
//// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
////
////===----------------------------------------------------------------------===//
//
//_LIBCPP_BEGIN_NAMESPACE_STD
//
//#ifndef _LIBCPP_HAS_NO_THREADS
//
//template <__fmt_char_type _CharT>
//struct _LIBCPP_TEMPLATE_VIS formatter<__thread_id, _CharT> {
//  public:
//    template <class _ParseContext>
//    _LIBCPP_HIDE_FROM_ABI constexpr typename _ParseContext::iterator parse(_ParseContext& __ctx) {
//        return __parser_.__parse(__ctx, __format_spec::__fields_fill_align_width);
//    }
//
//    template <class _FormatContext>
//    _LIBCPP_HIDE_FROM_ABI typename _FormatContext::iterator format(__thread_id __id, _FormatContext& __ctx) const {
//        // In __threading_support __libcpp_thread_id is either a
//        // unsigned long long or a pthread_t.
//        //
//        // The type of pthread_t is left unspecified in POSIX so it can be any
//        // type. The most logical types are an integral or pointer.
//        // On Linux systems pthread_t is an unsigned long long.
//        // On Apple systems pthread_t is a pointer type.
//        //
//        // Note the output should match what the stream operator does. Since
//        // the ostream operator has been shipped years before this formatter
//        // was added to the Standard, this formatter does what the stream
//        // operator does. This may require platform specific changes.
//
//        using _Tp = decltype(__get_underlying_id(__id));
//        using _Cp = conditional_t<integral<_Tp>, _Tp, conditional_t<is_pointer_v<_Tp>, uintptr_t, void>>;
//        static_assert(!is_same_v<_Cp, void>, "unsupported thread::id type, please file a bug report");
//
//        __format_spec::__parsed_specifications<_CharT> __specs = __parser_.__get_parsed_std_specifications(__ctx);
//        if constexpr (is_pointer_v<_Tp>) {
//          __specs.__std_.__alternate_form_ = true;
//          __specs.__std_.__type_           = __format_spec::__type::__hexadecimal_lower_case;
//        }
//        return __formatter::__format_integer(reinterpret_cast<_Cp>(__get_underlying_id(__id)), __ctx, __specs);
//    }
//
//    __format_spec::__parser<_CharT> __parser_{.__alignment_ = __format_spec::__alignment::__right};
//};
//
//#endif // !_LIBCPP_HAS_NO_THREADS
//
//_LIBCPP_END_NAMESPACE_STD
//
//#endif // _LIBCPP_STD_VER >= 23
//
//#endif // _LIBCPP___THREAD_FORMATTER_H
//
//
//
//
//
//
//
//
//
//
//
//
//
//_LIBCPP_BEGIN_NAMESPACE_STD
//
//
//template <class _Tp> class
//__thread_specific_ptr;
//
//class __thread_struct;
//class __thread_struct_imp;
//class __assoc_sub_state;
//
//_LIBCPP_EXPORTED_FROM_ABI __thread_specific_ptr<__thread_struct>& __thread_local_data();
//
//class _LIBCPP_EXPORTED_FROM_ABI __thread_struct {
//
//    __thread_struct_imp* __p_;
//
//    __thread_struct(const __thread_struct&);
//    __thread_struct& operator=(const __thread_struct&);
//public:
//    __thread_struct();
//    ~__thread_struct();
//
//    void notify_all_at_thread_exit(condition_variable*, mutex*);
//    void __make_ready_at_thread_exit(__assoc_sub_state*);
//};
//
//template <class _Tp>
//class __thread_specific_ptr
//{
//    __libcpp_tls_key __key_;
//
//     // Only __thread_local_data() may construct a __thread_specific_ptr
//     // and only with _Tp == __thread_struct.
//    static_assert((is_same<_Tp, __thread_struct>::value), "");
//    __thread_specific_ptr();
//    friend _LIBCPP_EXPORTED_FROM_ABI __thread_specific_ptr<__thread_struct>& __thread_local_data();
//
//    __thread_specific_ptr(const __thread_specific_ptr&);
//    __thread_specific_ptr& operator=(const __thread_specific_ptr&);
//
//    _LIBCPP_HIDDEN static void _LIBCPP_TLS_DESTRUCTOR_CC __at_thread_exit(void*);
//
//public:
//    typedef _Tp* pointer;
//
//    ~__thread_specific_ptr();
//
//    _LIBCPP_INLINE_VISIBILITY
//    pointer get() const {return static_cast<_Tp*>(__libcpp_tls_get(__key_));}
//    _LIBCPP_INLINE_VISIBILITY
//    pointer operator*() const {return *get();}
//    _LIBCPP_INLINE_VISIBILITY
//    pointer operator->() const {return get();}
//    void set_pointer(pointer __p);
//};
//
//template <class _Tp>
//void _LIBCPP_TLS_DESTRUCTOR_CC
//__thread_specific_ptr<_Tp>::__at_thread_exit(void* __p)
//{
//    delete static_cast<pointer>(__p);
//}
//
//template <class _Tp>
//__thread_specific_ptr<_Tp>::__thread_specific_ptr()
//{
//  int __ec =
//      __libcpp_tls_create(&__key_, &__thread_specific_ptr::__at_thread_exit);
//  if (__ec)
//    __throw_system_error(__ec, "__thread_specific_ptr construction failed");
//}
//
//template <class _Tp>
//__thread_specific_ptr<_Tp>::~__thread_specific_ptr()
//{
//    // __thread_specific_ptr is only created with a static storage duration
//    // so this destructor is only invoked during program termination. Invoking
//    // pthread_key_delete(__key_) may prevent other threads from deleting their
//    // thread local data. For this reason we leak the key.
//}
//
//template <class _Tp>
//void
//__thread_specific_ptr<_Tp>::set_pointer(pointer __p)
//{
//    _LIBCPP_ASSERT_UNCATEGORIZED(get() == nullptr,
//                   "Attempting to overwrite thread local data");
//    std::__libcpp_tls_set(__key_, __p);
//}
//
//template<>
//struct _LIBCPP_TEMPLATE_VIS hash<__thread_id>
//    : public __unary_function<__thread_id, size_t>
//{
//    _LIBCPP_INLINE_VISIBILITY
//    size_t operator()(__thread_id __v) const _NOEXCEPT
//    {
//        return hash<__libcpp_thread_id>()(__v.__id_);
//    }
//};
//
//#ifndef _LIBCPP_HAS_NO_LOCALIZATION
//template <class _CharT, class _Traits>
//_LIBCPP_INLINE_VISIBILITY basic_ostream<_CharT, _Traits>&
//operator<<(basic_ostream<_CharT, _Traits>& __os, __thread_id __id) {
//    // [thread.thread.id]/9
//    //   Effects: Inserts the text representation for charT of id into out.
//    //
//    // [thread.thread.id]/2
//    //   The text representation for the character type charT of an
//    //   object of type thread::id is an unspecified sequence of charT
//    //   such that, for two objects of type thread::id x and y, if
//    //   x == y is true, the thread::id objects have the same text
//    //   representation, and if x != y is true, the thread::id objects
//    //   have distinct text representations.
//    //
//    // Since various flags in the output stream can affect how the
//    // thread id is represented (e.g. numpunct or showbase), we
//    // use a temporary stream instead and just output the thread
//    // id representation as a string.
//
//    basic_ostringstream<_CharT, _Traits> __sstr;
//    __sstr.imbue(locale::classic());
//    __sstr << __id.__id_;
//    return __os << __sstr.str();
//}
//#endif // _LIBCPP_HAS_NO_LOCALIZATION



