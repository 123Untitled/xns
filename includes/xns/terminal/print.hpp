#ifndef XNS_PRINT_HEADER
#define XNS_PRINT_HEADER

#include "xns/type_traits/other/string_literal.hpp"

#include "xns/type_traits/types.hpp"

#include <iostream>


namespace xns {


	template <xns::basic_string_literal __format>
	class format final {

		public:

			using size_type = xns::size_t;

			enum __state : size_type {
				START, IN_STRING, OPEN_BRACE, IN_VALUE, CLOSE_BRACE, END
			};


			static consteval auto _vcount(void) -> size_type {

				size_type count = 0;
				bool      brace = false;

				for (size_type i = 0; i < __format.size(); ++i) {


					if (brace == false
					 && __format[i]     == '{'
					 && __format[i + 1] != '{') {
						brace = true;
					}

					else if (brace == true
					 && __format[i]     == '}'
					 && __format[i + 1] != '}') {
						brace = false;
						++count;
					}

				}

				return count;
			}

			static consteval auto _bcount(void) -> size_type {

				size_type count = 0;
				bool      brace = false;
				bool      block = false;

				for (size_type i = 0; i < __format.size(); ++i) {

					if (brace == false
					 && __format[i]     == '{'
					 && __format[i + 1] != '{') {
						brace = true;
						block = false;
					}

					else if (brace == true
					 && __format[i]     == '}'
					 && __format[i + 1] != '}') {
						brace = false;
					}

					else if (block == false) {
						block = true;
						++count;
					}

				}

				return count;
			}

			char _blocks[_bcount()];



	};

	template <xns::size_t N>
	consteval auto test(const char (&str)[N]) -> xns::size_t {

		xns::size_t count = 0;
		bool        brace = false;

		for (xns::size_t i = 0; i < N; ++i) {

			if (brace == false)
				brace = str[i] == '{' && str[i + 1] != '{';

			if (brace == true) {
				brace = str[i] == '}' && str[i + 1] != '}';
				count += brace == false;
			}
		}

		return count;
	}



	template <xns::basic_string_literal __format, typename... __params>
	auto println(__params&&... __args) -> void {

		//constexpr auto vcount = format<__format>::_vcount();
		//constexpr auto bcount = format<__format>::_bcount();

		constexpr auto bcount = test("hello {world} my name is {john}.");


		//std::cout << "size: " << __format.size() << std::endl;
		//std::cout << "vcount: " << vcount << std::endl;
		std::cout << "bcount: " << bcount << std::endl;


	}

}

#endif // XNS_PRINT_HEADER
