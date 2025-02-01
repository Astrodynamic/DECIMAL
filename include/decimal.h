#pragma once

#include <bitset>
#include <cstddef>
#include <optional>
#include <regex>
#include <string_view>

namespace utils::finantial {
template <std::size_t bits = 96> class Decimal final {
public:
  Decimal(const std::string_view& value = {});
  Decimal(const Decimal&) noexcept = default;
  Decimal(Decimal&&) noexcept = default;
  ~Decimal() = default;

  auto operator=(const std::string_view& value) -> Decimal&;
  auto operator=(const Decimal&) noexcept -> Decimal& = default;
  auto operator=(Decimal&&) noexcept -> Decimal& = default;

  [[nodiscard]] auto operator<(const Decimal& other) const noexcept -> bool;
  [[nodiscard]] auto operator>(const Decimal& other) const noexcept -> bool;
  [[nodiscard]] auto operator>=(const Decimal& other) const noexcept -> bool;
  [[nodiscard]] auto operator<=(const Decimal& other) const noexcept -> bool;
  [[nodiscard]] auto operator==(const Decimal& other) const noexcept -> bool;
  [[nodiscard]] auto operator!=(const Decimal& other) const noexcept -> bool;

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

  template <std::size_t M>
  friend auto operator<<(std::ostream& os, Decimal<M> decimal) -> std::ostream&;

  explicit operator std::string() const noexcept;

  [[nodiscard]] auto trunc() const noexcept -> Decimal;
  [[nodiscard]] auto round() const noexcept -> Decimal;
  [[nodiscard]] auto floor() const noexcept -> Decimal;
  [[nodiscard]] auto ceil() const noexcept -> Decimal;

private:
  static inline const std::regex m_mask{R"(^([+-]?)(?:0*)(\d*)(?:\.(\d*))?$)"};

  static constexpr std::size_t m_bits = bits * 2 + 1;
  static constexpr std::size_t m_max_exponent = bits * 0.30102999566398119521373889472449 + 1;
  static constexpr std::bitset<m_bits> m_bit_one{0b1};
  static constexpr std::bitset<m_bits> m_bit_ten{0b1010};

  std::size_t m_exponent{};
  std::bitset<m_bits> m_mantissa{};

  [[nodiscard]] auto parse(const std::string_view& value) const -> std::optional<std::cmatch>;
  [[nodiscard]] auto sign() const noexcept -> bool;
  auto conversion(const std::cmatch& match) -> void;
  auto normalize(Decimal& other) -> void;
  auto fit() noexcept -> void;
  auto abs() noexcept -> Decimal&;
};
} // namespace utils::finantial

#include "decimal.tpp"
