#ifndef XNS_XORSHIFT_HEADER
#define XNS_XORSHIFT_HEADER

#include "types.hpp"

#include <unistd.h>
#include <ctime>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- X O R S H I F T -----------------------------------------------------

	class xorshift final {

		public:

			// -- public static methods ---------------------------------------

			/* xorshift 32 next */
			inline static xns::u32 next32(void) {

				_xrshft32 ^= _xrshft32 << 13;
				_xrshft32 ^= _xrshft32 >> 17;
				_xrshft32 ^= _xrshft32 << 5;

				return _xrshft32;
			}

			/* xorshift 64 next */
			inline static xns::u64 next64(void) {

				_xrshft64 ^= _xrshft64 << 13;
				_xrshft64 ^= _xrshft64 >> 7;
				_xrshft64 ^= _xrshft64 << 17;

				return _xrshft64;
			}


		private:

			// -- private static members --------------------------------------

			/* 32 bit state */
			inline static xns::u32 _xrshft32 =
				(unsigned)std::time(nullptr) ^ (unsigned)getpid();

			/* 64 bit state */
			inline static xns::u64 _xrshft64 = (xns::u64)(((unsigned)std::time(nullptr) / (unsigned)getpid())) << 32 |
				((unsigned)std::time(nullptr) / (unsigned)getpid());


	};


}




#endif









/* This is the jump function for the generator. It is equivalent
   to 2^128 calls to next(); it can be used to generate 2^128
   non-overlapping subsequences for parallel computations. */

//void jump(void) {
//	static const uint64_t JUMP[] = { 0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c };
//
//	uint64_t s0 = 0;
//	uint64_t s1 = 0;
//	uint64_t s2 = 0;
//	uint64_t s3 = 0;
//	for(int i = 0; i < sizeof JUMP / sizeof *JUMP; i++)
//		for(int b = 0; b < 64; b++) {
//			if (JUMP[i] & UINT64_C(1) << b) {
//				s0 ^= s[0];
//				s1 ^= s[1];
//				s2 ^= s[2];
//				s3 ^= s[3];
//			}
//			next();
//		}
//
//	s[0] = s0;
//	s[1] = s1;
//	s[2] = s2;
//	s[3] = s3;
//}
//
//
//
///* This is the long-jump function for the generator. It is equivalent to
//   2^192 calls to next(); it can be used to generate 2^64 starting points,
//   from each of which jump() will generate 2^64 non-overlapping
//   subsequences for parallel distributed computations. */
//
//void long_jump(void) {
//	static const uint64_t LONG_JUMP[] = { 0x76e15d3efefdcbbf, 0xc5004e441c522fb3, 0x77710069854ee241, 0x39109bb02acbe635 };
//
//	uint64_t s0 = 0;
//	uint64_t s1 = 0;
//	uint64_t s2 = 0;
//	uint64_t s3 = 0;
//	for(int i = 0; i < sizeof LONG_JUMP / sizeof *LONG_JUMP; i++)
//		for(int b = 0; b < 64; b++) {
//			if (LONG_JUMP[i] & UINT64_C(1) << b) {
//				s0 ^= s[0];
//				s1 ^= s[1];
//				s2 ^= s[2];
//				s3 ^= s[3];
//			}
//			next();
//		}
//
//	s[0] = s0;
//	s[1] = s1;
//	s[2] = s2;
//	s[3] = s3;
//}
