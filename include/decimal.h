#pragma once

#include <bitset>

namespace utils::finantial {
template <std::size_t mantissa = 96> class Decimal final {
public:
  explicit Decimal(const std::string_view& value = {});
  // explicit Decimal(const Decimal&) = default;
  // explicit Decimal(Decimal&&) noexcept = default;
  // ~Decimal() = default;

  // auto operator=(const Decimal&) -> Decimal& = default;
  // auto operator=(Decimal&&) noexcept -> Decimal& = default;

  // [[nodiscard]] auto operator<(const Decimal& other) const noexcept -> bool;
  // [[nodiscard]] auto operator>(const Decimal& other) const noexcept -> bool;
  // [[nodiscard]] auto operator>=(const Decimal& other) const noexcept -> bool;
  // [[nodiscard]] auto operator<=(const Decimal& other) const noexcept -> bool;
  // [[nodiscard]] auto operator==(const Decimal& other) const noexcept -> bool;
  // [[nodiscard]] auto operator!=(const Decimal& other) const noexcept -> bool;

  // [[nodiscard]] auto operator+(const Decimal& other) const noexcept -> Decimal;
  // [[nodiscard]] auto operator-(const Decimal& other) const noexcept -> Decimal;
  // [[nodiscard]] auto operator*(const Decimal& other) const noexcept -> Decimal;
  // [[nodiscard]] auto operator/(const Decimal& other) const noexcept -> Decimal;
  // [[nodiscard]] auto operator%(const Decimal& other) const noexcept -> Decimal;

  // auto operator-() const noexcept -> Decimal;
  // auto operator+=(const Decimal& other) noexcept -> Decimal&;
  // auto operator-=(const Decimal& other) noexcept -> Decimal&;
  // auto operator*=(const Decimal& other) noexcept -> Decimal&;
  // auto operator/=(const Decimal& other) noexcept -> Decimal&;
  // auto operator%=(const Decimal& other) noexcept -> Decimal&;

  // [[nodiscard]] auto trunc() const noexcept -> Decimal;
  // [[nodiscard]] auto round() const noexcept -> Decimal;
  // [[nodiscard]] auto floor() const noexcept -> Decimal;
  // [[nodiscard]] auto ceil() const noexcept -> Decimal;

private:
  static constexpr std::size_t m_bit_sign = 1;
  static constexpr std::size_t m_min_exponent{};
  static constexpr std::size_t m_max_exponent{28};

  std::size_t m_exponent{};
  std::bitset<m_bit_sign + mantissa> m_mantissa{};
};
} // namespace utils::finantial

#include "decimal.tpp"