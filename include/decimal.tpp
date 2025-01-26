#include "decimal.h"
#include <bitset>
#include <cstddef>
#include <string_view>
#include <cstdint>

namespace utils::finantial {
template <std::size_t bits> Decimal<bits>::Decimal(const std::string_view& value) {
  *this = value;
}

template <std::size_t bits> auto Decimal<bits>::operator=(const std::string_view& value) -> Decimal<bits>& {
  if (auto match = parse(value); match) {
    conversion(*match);
  }
  return *this;
}

template <std::size_t bits> auto Decimal<bits>::operator<(const Decimal& other) const noexcept -> bool {
  return true;
}

template <std::size_t bits> auto Decimal<bits>::operator>(const Decimal& other) const noexcept -> bool {
  return other < *this;
}

template <std::size_t bits> auto Decimal<bits>::operator>=(const Decimal& other) const noexcept -> bool {
  return !(*this < other);
}

template <std::size_t bits> auto Decimal<bits>::operator<=(const Decimal& other) const noexcept -> bool {
  return !(other < *this);
}

template <std::size_t bits> auto Decimal<bits>::operator==(const Decimal& other) const noexcept -> bool {
  return !(*this != other);
}

template <std::size_t bits> auto Decimal<bits>::operator!=(const Decimal& other) const noexcept -> bool {
  return true;
}

template <std::size_t bits> auto Decimal<bits>::operator-() const noexcept -> Decimal {
  Decimal<bits> result(*this);
  result.m_mantissa = -result.m_mantissa;
  return result;
}

template <std::size_t bits> auto Decimal<bits>::operator+(const Decimal& other) const noexcept -> Decimal {
  return Decimal(*this) += other;
}

template <std::size_t bits> auto Decimal<bits>::operator-(const Decimal& other) const noexcept -> Decimal {
  return Decimal(*this) -= other;
}

template <std::size_t bits> auto Decimal<bits>::operator*(const Decimal& other) const noexcept -> Decimal {
  return Decimal(*this) *= other;
}

template <std::size_t bits> auto Decimal<bits>::operator/(const Decimal& other) const noexcept -> Decimal {
  return Decimal(*this) /= other;
}

template <std::size_t bits> auto Decimal<bits>::operator%(const Decimal& other) const noexcept -> Decimal {
  return Decimal(*this) %= other;
}

template <std::size_t bits> auto Decimal<bits>::operator+=(const Decimal& other) noexcept -> Decimal& {
  Decimal temp(other);
  normalize(temp);
  this->m_mantissa = this->m_mantissa + temp.m_mantissa;
  fit();
  return *this;
}

template <std::size_t bits> auto Decimal<bits>::operator-=(const Decimal& other) noexcept -> Decimal& {
  Decimal temp(other);
  normalize(temp);
  this->m_mantissa = this->m_mantissa - temp.m_mantissa;
  fit();
  return *this;
}

template <std::size_t bits> auto Decimal<bits>::operator*=(const Decimal& other) noexcept -> Decimal& {
  Decimal a(*this), b(other);
  normalize(b);
  return *this;
}

template <std::size_t bits> auto Decimal<bits>::operator/=(const Decimal& other) noexcept -> Decimal& {
  Decimal temp(other);
  normalize(temp);
  this->m_mantissa = this->m_mantissa / temp.m_mantissa;
  return *this;
}

template <std::size_t bits> auto Decimal<bits>::operator%=(const Decimal& other) noexcept -> Decimal& {
  Decimal a(*this), b(other);
  normalize(b);
  return *this;
}

template <std::size_t bits> auto Decimal<bits>::parse(const std::string_view& value) const -> std::optional<std::cmatch> {
  std::cmatch match;
  if (std::regex_match(value.begin(), value.end(), match, m_mask)) {
    if (match[2].length() <= m_max_exponent) {
      return match;
    }
  }
  return {};
}

template <std::size_t bits> auto Decimal<bits>::conversion(const std::cmatch& match) -> void {
  m_exponent = std::min<std::size_t>(m_max_exponent - match[2].length(), match[3].length());

  std::size_t bit{}, value{}, carry{};
  std::string temp, number = match[2].str() + match[3].str().substr(0, m_exponent);
  while (!number.empty()) {
    m_mantissa.set(bit++, (number.back() - '0') & 1);

    carry = {};
    for (char digit : number) {
      value = carry * 10 + (digit - '0');
      temp += value / 2 + '0';
      carry = value % 2;
    }
    temp.erase(0, temp.find_first_not_of('0'));
    number = temp;
    temp.clear();
  }

  if (match[1] == "-") {
    *this = -(*this);
  }
}

template <std::size_t bits> auto Decimal<bits>::normalize(Decimal& other) -> void {
  if (this->m_exponent > other.m_exponent) {
    for (std::size_t i{}; i < this->m_exponent - other.m_exponent; ++i) {
      other.m_mantissa = other.m_mantissa * std::bitset<m_bits>(0b1010);
    }
    other.m_exponent = this->m_exponent;
  } else if (this->m_exponent < other.m_exponent) {
    for (std::size_t i{}; i < other.m_exponent - this->m_exponent; ++i) {
      this->m_mantissa = this->m_mantissa * std::bitset<m_bits>(0b1010);
    }
    this->m_exponent = other.m_exponent;
  }
}

template <std::size_t bits> auto Decimal<bits>::fit() -> void {
  for (std::size_t i = m_bits - 2; i <= m_bits / 2 && m_exponent; --i, --m_exponent) {
    m_mantissa = m_mantissa / std::bitset<m_bits>(0b1010);
  }
}

template <std::size_t bits> auto operator<<(std::ostream& os, const Decimal<bits>& decimal) -> std::ostream& {
  return os << decimal.m_mantissa.to_string();
}

template <std::size_t bits> auto operator<(std::bitset<bits> a, std::bitset<bits> b) -> bool {
  std::bitset<bits> result = b - a;
  return !result[bits - 1] && result.any();
}

template <std::size_t bits> auto operator<=(std::bitset<bits> a, std::bitset<bits> b) -> bool {
  return !(b < a);
}

template <std::size_t bits> auto operator-(std::bitset<bits> a) -> std::bitset<bits> {
  return ~a + std::bitset<bits>(0b1);
}

template <std::size_t bits> auto operator+(std::bitset<bits> a, std::bitset<bits> b) -> std::bitset<bits> {
  std::bitset<bits> carry;
  while (b.any()) {
    carry = a & b;
    a = a ^ b;
    b = carry << 1;
  }
  return a;
}

template <std::size_t bits> auto operator-(std::bitset<bits> a, std::bitset<bits> b) -> std::bitset<bits> {
  return a + (-b);
}

template <std::size_t bits> auto operator*(std::bitset<bits> a, std::bitset<bits> b) -> std::bitset<bits> {
  std::bitset<bits> result, one(0b1);
  while (b.any()) {
    if ((result & one)[0]) {
      result = result + a;
    }
    a <<= 1;
    b >>= 1;
  }
  return result;
}

template <std::size_t bits> auto operator/(std::bitset<bits> a, std::bitset<bits> b) -> std::bitset<bits> {
  std::size_t bit{bits - 1};
  std::bitset<bits> rest, result;
  do {
    rest <<= 1;
    rest.set(0, a[bit]);
    if (b <= rest) {
      result.set(bit);
      rest = rest - b;
    }
  } while (bit--);
  return result;
}

template <std::size_t bits> auto operator%(std::bitset<bits> a, std::bitset<bits> b) -> std::bitset<bits> {
  return a - (a / b) * b;
}
} // namespace utils::finantial