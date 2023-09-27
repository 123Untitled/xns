# types

#### term_size
```cpp
/* terminal size type */
using term_size = decltype(std::declval<struct winsize>().ws_row);
```

#### null
```cpp
/* null pointer type */
using null = decltype(nullptr);
```

#### unsign
```cpp
/* unsigned integer types */
template <decltype(sizeof(void*)) N>
using unsign =  xns::conditional<(sizeof(unsigned char)      == N), unsigned char,
      xns::conditional<(sizeof(unsigned short)     == N), unsigned short,
      xns::conditional<(sizeof(unsigned int)       == N), unsigned int,
      xns::conditional<(sizeof(unsigned long)      == N), unsigned long,
      xns::conditional<(sizeof(unsigned long long) == N), unsigned long long,
      void > > > > >;
```

#### sign
```cpp
/* signed integer types */
template <decltype(sizeof(void*)) N>
using sign =    xns::conditional<(sizeof(signed char)        == N), signed char,
      xns::conditional<(sizeof(signed short)       == N), signed short,
      xns::conditional<(sizeof(signed int)         == N), signed int,
      xns::conditional<(sizeof(signed long)        == N), signed long,
      xns::conditional<(sizeof(signed long long)   == N), signed long long,
      void > > > > >;
```
