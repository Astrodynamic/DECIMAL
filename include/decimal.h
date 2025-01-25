#pragma once

#include <iostream>
#include <optional>
#include <regex>
#include <cmath>
#include <bitset>
#include <string_view>

namespace utils::finantial {
template <std::size_t mantissa = 96> class Decimal final {
public:
  enum class Codes {
    kError_000 = 0,
    kError_001,
    kError_002
  };

  explicit Decimal(const std::string_view& value = {});
  explicit Decimal(const Decimal&) = default;
  explicit Decimal(Decimal&&) noexcept = default;
  ~Decimal() = default;

  auto operator=(const std::string_view& value) -> Decimal&;
  auto operator=(const Decimal&) -> Decimal& = default;
  auto operator=(Decimal&&) noexcept -> Decimal& = default;

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

  template <std::size_t M>
  friend auto operator<<(std::ostream& os, const Decimal<M>& decimal) -> std::ostream&;

  // explicit operator std::string() const noexcept;
  // explicit operator bool() const noexcept;

  // [[nodiscard]] auto trunc() const noexcept -> Decimal;
  // [[nodiscard]] auto round() const noexcept -> Decimal;
  // [[nodiscard]] auto floor() const noexcept -> Decimal;
  // [[nodiscard]] auto ceil() const noexcept -> Decimal;

private:
  static inline const std::regex m_mask{R"(^([+-]?)(?:0*)(\d*)(?:\.(\d*))?$)"};

  static constexpr std::size_t m_sign_bit = 1;
  static constexpr std::size_t m_min_exponent{};
  static constexpr std::size_t m_max_exponent = mantissa * 0.30102999566398119521373889472449 + 1;

  Codes m_code{Codes::kError_000};

  std::size_t m_exponent{};
  std::bitset<m_sign_bit + mantissa> m_mantissa{};

  [[nodiscard]] auto parse(const std::string_view& value) const -> std::optional<std::cmatch>;
  auto conversion(const std::cmatch& match) -> void;
};

template <std::size_t mantissa> auto operator<<(std::ostream& os, const utils::finantial::Decimal<mantissa>& decimal) -> std::ostream&;
} // namespace utils::finantial

#include "decimal.tpp"