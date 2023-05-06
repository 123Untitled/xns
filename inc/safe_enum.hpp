#ifndef SAFE_ENUM_HEADER
#define SAFE_ENUM_HEADER

#include "types.hpp"

class Enum {

	public:

		/* integral type */
		using Integer = UInt;

		/* enum type */
		enum : Integer { ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN };


	private:

		using Type = decltype(ONE);


	public:

		/* enum constructor */
		explicit Enum(const Type value)
		: _value(value) {
			// code here...
		}


	private:

		Integer _value;

};

template <class T, class P, typename T::Type N>
class SafeEnum : public T {

	public:

		/* integral type */
		using Integer = decltype(N);

		/* enum type */
		//enum : Integer { ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN };

	private:

		using Type = P;


	public:

		/* enum constructor */
		constexpr explicit SafeEnum(const Type value) : _value(value) {
			// code here...
		}

		constexpr Integer size(void) const { return N; }



	private:

		Integer _value;

};

struct Color_def {
	using Type = UInt;
	enum : Type {
		BLACK, RED, GREEN
	};
};


#endif
