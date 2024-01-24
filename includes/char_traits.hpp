#ifndef XNS_CHAR_TRAITS_HEADER
#define XNS_CHAR_TRAITS_HEADER


//#include "is_char.hpp"
#include "config.hpp"
#include "macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- C H A R  T R A I T S ------------------------------------------------

	/* char traits */
	template <typename T>
	struct char_traits;


	// -- C H A R  T R A I T S  S P E C I A L I Z A T I O N -------------------

	template <>
	struct char_traits<char> {


		// -- types -----------------------------------------------------------

		/* self type */
		using _self      = xns::char_traits<char>;

		/* char type */
		using _char      = char;

		/* size type */
		using _size      = decltype(sizeof(0));

		/* mutable pointer type */
		using _mut_ptr   = _char*;

		/* const pointer type */
		using _const_ptr = const _char*;

		/* mutable reference type */
		using _mut_ref   = _char&;

		/* const reference type */
		using _const_ref = const _char&;

		/* signed int type */
		using _signed    = signed int;


		//using char_type           = char;
		//using int_type            = int;
		//using off_type            = streamoff;
		//using pos_type            = streampos;
		//using state_type          = mbstate_t;
		#if XNS_CPP_VERSION >= 20
		//using comparison_category = strong_ordering;
		#endif


		// -- non instanciable ------------------------------------------------

		/* non instanciable */
		non_instanciable(char_traits<_char>);



		// -- static methods --------------------------------------------------

		/* assign */
		static inline constexpr auto assign(_mut_ref dst, _const_ref src) noexcept -> void {
			dst = src;
		}

		/* eq */
		static inline constexpr auto eq(_char lhs, _char rhs) noexcept -> bool {
			return lhs == rhs;
		}

		/* lt */
		static inline constexpr auto lt(_char lhs, _char rhs) noexcept -> bool {
			return static_cast<unsigned char>(lhs) < static_cast<unsigned char>(rhs);
		}

		// done.




		/* compare */
		static inline constexpr auto compare(_const_ptr lhs, _const_ptr rhs, _size size) noexcept -> _signed {
			return __builtin_memcmp(lhs, rhs, size);
		}

		/* length */
		static inline constexpr auto length(_const_ptr str) noexcept -> _size {
			return __builtin_strlen(str);
		}

		/* find */
		static inline constexpr auto find(_const_ptr str, _size size, _const_ref ch) noexcept -> _const_ptr {
			return static_cast<_const_ptr>(__builtin_memchr(str, ch, size));
		}

		/* move */
		static constexpr auto move(_mut_ptr dst, _const_ptr src, _size size) noexcept -> void {
			__builtin_memmove(dst, src, size);
		}

		/* copy */
		static inline constexpr auto copy(_mut_ptr dst, _const_ptr src, _size size) noexcept -> void {
			__builtin_memcpy(dst, src, size);
		}

		/* assign */
		static inline /* constexpr */ auto assign(_mut_ptr dst, _size size, _const_ref ch) noexcept -> _mut_ptr {
			return static_cast<_mut_ptr>(__builtin_memset(dst, ch, size));
		}

	};

}

template <typename T>
auto test(T&& t) -> xns::char_traits<T>::_char {
	return xns::char_traits<T>::assign(t, t);
}

namespace xns {

	// -- C H A R  T R A I T S  S P E C I A L I Z A T I O N -------------------

	template <>
	struct char_traits<wchar_t> {
		/* self type */
		using _self      = xns::char_traits<char>;

		/* char type */
		using _char      = char;

		/* size type */
		using _size      = decltype(sizeof(0));

		/* mutable pointer type */
		using _mut_ptr   = _char*;

		/* const pointer type */
		using _const_ptr = const _char*;

		/* mutable reference type */
		using _mut_ref   = _char&;

		/* const reference type */
		using _const_ref = const _char&;

		/* signed int type */
		using _signed    = signed int;

	};

	template <>
	struct char_traits<char16_t> {
		/* self type */
		using _self      = xns::char_traits<char>;

		/* char type */
		using _char      = char;

		/* size type */
		using _size      = decltype(sizeof(0));

		/* mutable pointer type */
		using _mut_ptr   = _char*;

		/* const pointer type */
		using _const_ptr = const _char*;

		/* mutable reference type */
		using _mut_ref   = _char&;

		/* const reference type */
		using _const_ref = const _char&;

		/* signed int type */
		using _signed    = signed int;

	};

	template <>
	struct char_traits<char32_t> {
		/* self type */
		using _self      = xns::char_traits<char>;

		/* char type */
		using _char      = char;

		/* size type */
		using _size      = decltype(sizeof(0));

		/* mutable pointer type */
		using _mut_ptr   = _char*;

		/* const pointer type */
		using _const_ptr = const _char*;

		/* mutable reference type */
		using _mut_ref   = _char&;

		/* const reference type */
		using _const_ref = const _char&;

		/* signed int type */
		using _signed    = signed int;

	};

	template <>
	struct char_traits<char8_t> {
		/* self type */
		using _self      = xns::char_traits<char>;

		/* char type */
		using _char      = char;

		/* size type */
		using _size      = decltype(sizeof(0));

		/* mutable pointer type */
		using _mut_ptr   = _char*;

		/* const pointer type */
		using _const_ptr = const _char*;

		/* mutable reference type */
		using _mut_ref   = _char&;

		/* const reference type */
		using _const_ref = const _char&;

		/* signed int type */
		using _signed    = signed int;

	};

}



#endif


//    // __constexpr_memcmp requires a trivially lexicographically comparable type, but char is not when char is a signed type
//    static  _LIBCPP_CONSTEXPR_SINCE_CXX17 int
//    compare(const char_type* __lhs, const char_type* __rhs, size_t __count) _NOEXCEPT {
//      if (__libcpp_is_constant_evaluated()) {
//#ifdef _LIBCPP_COMPILER_CLANG_BASED
//        return __builtin_memcmp(__lhs, __rhs, __count);
//#else
//        while (__count != 0) {
//          if (lt(*__lhs, *__rhs))
//            return -1;
//          if (lt(*__rhs, *__lhs))
//            return 1;
//
//          __count -= sizeof(char_type);
//          ++__lhs;
//          ++__rhs;
//        }
//        return 0;
//#endif // _LIBCPP_COMPILER_CLANG_BASED
//      } else {
//        return __builtin_memcmp(__lhs, __rhs, __count);
//      }
//    }
//
//    static inline  size_t _LIBCPP_CONSTEXPR_SINCE_CXX17 length(const char_type* __s)  _NOEXCEPT {
//      return std::__constexpr_strlen(__s);
//    }
//
//    static  _LIBCPP_CONSTEXPR_SINCE_CXX17
//    const char_type* find(const char_type* __s, size_t __n, const char_type& __a) _NOEXCEPT {
//      if (__n == 0)
//          return nullptr;
//      return std::__constexpr_memchr(__s, __a, __n);
//    }
//
//    static inline  _LIBCPP_CONSTEXPR_SINCE_CXX20
//    char_type* move(char_type* __s1, const char_type* __s2, size_t __n) _NOEXCEPT {
//        return std::__constexpr_memmove(__s1, __s2, __element_count(__n));
//    }
//
//    static inline  _LIBCPP_CONSTEXPR_SINCE_CXX20
//    char_type* copy(char_type* __s1, const char_type* __s2, size_t __n) _NOEXCEPT {
//        if (!__libcpp_is_constant_evaluated())
//            _LIBCPP_ASSERT_NON_OVERLAPPING_RANGES(
//                __s2 < __s1 || __s2 >= __s1 + __n, "char_traits::copy overlapped range");
//        std::copy_n(__s2, __n, __s1);
//        return __s1;
//    }
//
//    static inline  _LIBCPP_CONSTEXPR_SINCE_CXX20
//    char_type* assign(char_type* __s, size_t __n, char_type __a) _NOEXCEPT {
//        std::fill_n(__s, __n, __a);
//        return __s;
//    }
//
//    static inline  _LIBCPP_CONSTEXPR int_type  not_eof(int_type __c) _NOEXCEPT
//        {return eq_int_type(__c, eof()) ? ~eof() : __c;}
//    static inline  _LIBCPP_CONSTEXPR char_type to_char_type(int_type __c) _NOEXCEPT
//        {return char_type(__c);}
//    static inline  _LIBCPP_CONSTEXPR int_type to_int_type(char_type __c) _NOEXCEPT
//        {return int_type((unsigned char)__c);}
//    static inline  _LIBCPP_CONSTEXPR bool eq_int_type(int_type __c1, int_type __c2) _NOEXCEPT
//        {return __c1 == __c2;}
//    static inline  _LIBCPP_CONSTEXPR int_type  eof() _NOEXCEPT
//        {return int_type(EOF);}
//};
