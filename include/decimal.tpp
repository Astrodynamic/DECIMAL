#include "decimal.h"
#include <bitset>
#include <cstddef>
#include <string_view>

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
  Decimal a(*this), b(other);
  normalize(a, b);
  this->m_mantissa = a.m_mantissa + b.m_mantissa;
  return *this;
}

template <std::size_t bits> auto Decimal<bits>::operator-=(const Decimal& other) noexcept -> Decimal& {
  Decimal a(*this), b(other);
  normalize(a, b);
  this->m_mantissa = a.m_mantissa - b.m_mantissa;
  return *this;
}

template <std::size_t bits> auto Decimal<bits>::operator*=(const Decimal& other) noexcept -> Decimal& {
  Decimal a(*this), b(other);
  normalize(a, b);
  return *this;
}

template <std::size_t bits> auto Decimal<bits>::operator/=(const Decimal& other) noexcept -> Decimal& {
  Decimal a(*this), b(other);
  normalize(a, b);
  return *this;
}

template <std::size_t bits> auto Decimal<bits>::operator%=(const Decimal& other) noexcept -> Decimal& {
  Decimal a(*this), b(other);
  normalize(a, b);
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

template <std::size_t bits> auto Decimal<bits>::normalize(Decimal& a, Decimal& b) -> void {
  if (a.m_exponent > b.m_exponent) {
    for (std::size_t i{}; i < a.m_exponent - b.m_exponent; ++i) {
      b.m_mantissa = b.m_mantissa * std::bitset<m_bits>(0b1010);
    }
    b.m_exponent = a.m_exponent;
  } else if (a.m_exponent < b.m_exponent) {
    for (std::size_t i{}; i < b.m_exponent - a.m_exponent; ++i) {
      a.m_mantissa = a.m_mantissa * std::bitset<m_bits>(0b1010);
    }
    a.m_exponent = b.m_exponent;
  }
}


template <std::size_t bits> auto operator<<(std::ostream& os, const Decimal<bits>& decimal) -> std::ostream& {
  return os << decimal.m_mantissa.to_string();
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
} // namespace utils::finantial