
# XNS Integral Types

XNS provides a suite of integral types (xns::sint / xns::uint) designed for compile-time type selection based on specified bit-width.
This approach ensures optimal type selection adapted to the architecture, enabling precise control over data size and performance without runtime overhead.
Importantly, it achieves this independence from traditional standard library dependencies, offering a more flexible and self-contained solution for handling integral data types.

## Usage

### Signed Integral Types
```cpp
xns::sint<32> num;
```

### Unsigned Integral Types
```cpp
xns::uint<64> num;
```
