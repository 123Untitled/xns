#ifndef XNS_MEMCPY_HEADER
#define XNS_MEMCPY_HEADER

// local headers
#include "os.hpp"
#include "types.hpp"


// check architecture
# if defined(XNS_ARM64)
// check neon
#  if defined(__ARM_NEON) || defined(__ARM_NEON__)
#   include <arm_neon.h>
#   define XNS_SIMD_ARM64
#  endif

# elif defined(XNS_X86_64)
// check sse
#  if defined(__SSE__)
#   include <emmintrin.h>
#   define XNS_SIMD_X86_64
#  endif

# endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- detail --------------------------------------------------------------

	namespace impl {

		/* memcpy base */
		inline auto memcpy_base(xns::ubyte* dst, const xns::ubyte* src, const xns::size_t size) -> void {
			// loop over bytes
			for (xns::size_t i = 0; i < size; ++i)
				// copy byte
				dst[i] = src[i];
		}

		// /* memcpy simd 16 */
		// inline auto memcpy_simd(xns::ubyte* dst, const xns::ubyte* src, const xns::size_t size) -> void {
		// 	// std::cout << "memcpy_simd: " << size << std::endl;
		// 	// loop over bytes
		// 	for (xns::size_t i = 0; i < size; i += 16) {
		// 		// load 16 bytes
		// 		const auto data = vld1q_u8(src + i);
		// 		// store 16 bytes
		// 		vst1q_u8(dst + i, data);
		// 	}
		// }


	}


//
//#if not defined(XNS_SIMD_ARM64) && not defined(XNS_SIMD_X86_64)
//	/* memcpy */
//	inline auto memcpy_impl(xns::ubyte* dst, const xns::ubyte* src, const xns::size_t size) -> void {
//
//		// xns::println("memcpy: generic");
//		// xns::out::render();
//
//		for (xns::size_t i = 0; i < size; ++i) {
//			*(dst + i) = *(src + i);
//		}
//	}
//
//
//	template <decltype(sizeof(0)) N>
//	bool is_aligned(const void* ptr) {
//		return (reinterpret_cast<xns::uptr_t>(ptr) % N) == 0;
//	}
//
//
//#elif defined(XNS_SIMD_ARM64)
//	/* memcpy */
//	inline auto memcpy_impl(xns::ubyte* dst, const xns::ubyte* src, const xns::size_t size) -> void {
//
//		enum : xns::size_t {
//			ALIGNMENT = 16
//		};
//
//
//		// compute number of bytes before correct alignment
//		const auto unaligned_bytes = (ALIGNMENT - (reinterpret_cast<xns::uptr_t>(dst) & (ALIGNMENT - 1))) & (ALIGNMENT - 1);
//		const auto simd_size = (size - unaligned_bytes) / ALIGNMENT;
//		const auto remainder = (size - unaligned_bytes) % ALIGNMENT;
//
//		// std::cout << "size: " << size << std::endl;
//		// std::cout << "simd_size: " << simd_size << std::endl;
//		// std::cout << "remainder: " << remainder << std::endl;
//
//		// copy unaligned bytes
//		impl::memcpy_base(dst, src, unaligned_bytes);
//
//		dst += unaligned_bytes;
//		src += unaligned_bytes;
//
//		// simd copy
//		impl::memcpy_simd(dst, src, simd_size * ALIGNMENT);
//
//		dst += simd_size * ALIGNMENT;
//		src += simd_size * ALIGNMENT;
//
//		// copy remainder
//		impl::memcpy_base(dst, src, remainder);
//
//	}
//
//#elif defined(XNS_SIMD_X86_64)
//	/* memcpy */
//	inline auto memcpy_impl(void* dst, const void* src, const xns::size_t size) -> void {
//	}
//#endif


	// -- M E M C P Y ---------------------------------------------------------

	template <typename D, typename S>
	inline auto memcpy(D* dst, const S* src, const xns::size_t size) -> void {
		// check if types have the same size
		static_assert(sizeof(D) == sizeof(S), "): MEMCPY: TYPES HAVE DIFFERENT SIZE :(");
		// call implementation with ubyte pointers and size in bytes
		impl::memcpy_base(static_cast<xns::ubyte*>      (static_cast<void*>      (dst)),
						  static_cast<const xns::ubyte*>(static_cast<const void*>(src)),
						  size * sizeof(D));
	}

}



#endif // MEMCPY_HEADER











