# Decimal

Decimal is a high-precision arithmetic library for financial calculations. It supports bank (round-half-even) rounding and mimics the behavior of C#'s decimal type.

## Dependencies

- **C++17** compliant compiler
- **CMake** (>= 3.28.3)
- **GoogleTest** (for running tests)

## Build

```sh
# build
cmake -S . -B build
cmake --build build

# run tests
./build/tests/TEST
```

## Usage

```cpp
#include <iostream>
#include "decimal.h"

int main() {
    using utils::finantial::Decimal;

    Decimal a{"123.456"};
    Decimal b{"78.9"};

    std::cout << "add: " << a + b << '\n';
    std::cout << "sub: " << a - b << '\n';
    std::cout << "mul: " << a * b << '\n';
    std::cout << "div: " << a / b << '\n';
    std::cout << "mod: " << a % b << '\n';
    return 0;
}
```

## Interface

```cpp
namespace utils::finantial {
template <std::size_t bits = 96>
class Decimal final {
public:
  Decimal(const std::string_view& value = {});
  
  // Assignment
  auto operator=(const std::string_view& value) -> Decimal&;

  // Comparison operators
  [[nodiscard]] auto operator<(const Decimal& other) const noexcept -> bool;
  [[nodiscard]] auto operator>(const Decimal& other) const noexcept -> bool;
  [[nodiscard]] auto operator>=(const Decimal& other) const noexcept -> bool;
  [[nodiscard]] auto operator<=(const Decimal& other) const noexcept -> bool;
  [[nodiscard]] auto operator==(const Decimal& other) const noexcept -> bool;
  [[nodiscard]] auto operator!=(const Decimal& other) const noexcept -> bool;

  // Arithmetic operators
  [[nodiscard]] auto operator-() const noexcept -> Decimal;
  [[nodiscard]] auto operator+(const Decimal& other) const noexcept -> Decimal;
  [[nodiscard]] auto operator-(const Decimal& other) const noexcept -> Decimal;
  [[nodiscard]] auto operator*(const Decimal& other) const noexcept -> Decimal;
  [[nodiscard]] auto operator/(const Decimal& other) const noexcept -> Decimal;
  [[nodiscard]] auto operator%(const Decimal& other) const noexcept -> Decimal;
  
  auto operator+=(const Decimal& other) noexcept -> Decimal&;
  auto operator-=(const Decimal& other) noexcept -> Decimal&;
  auto operator*=(const Decimal& other) noexcept -> Decimal&;
  auto operator/=(const Decimal& other) noexcept -> Decimal&;
  auto operator%=(const Decimal& other) noexcept -> Decimal&;

  // Stream output
  template <std::size_t M>
  friend auto operator<<(std::ostream& os, Decimal<M> decimal) -> std::ostream&;

  // Conversion to string
  explicit operator std::string() const noexcept;

  // Rounding and truncation
  [[nodiscard]] auto trunc() const noexcept -> Decimal;
  [[nodiscard]] auto round() const noexcept -> Decimal;
  [[nodiscard]] auto floor() const noexcept -> Decimal;
  [[nodiscard]] auto ceil() const noexcept -> Decimal;
};
} // namespace utils::finantial
```

## Improving Algorithms  

The library currently uses basic algorithms for computations. If you have experience with more efficient methods, especially those utilizing bitwise operations, you are welcome to contribute your improvements. This will not only enhance the library's performance but also help the author gain knowledge of these techniques.

## License

This project is licensed under the [MIT License](LICENSE).
