#include "decimal.h"
#include <algorithm>
#include <bitset>
#include <cstddef>
#include <string_view>
#include <cstdint>

namespace utils::finantial {
template <std::size_t bits> Decimal<bits>::Decimal(const std::string_view& value) {
  *this = value;
}

template <std::size_t bits> auto Decimal<bits>::operator=(const std::string_view& value) -> Decimal<bits>& {
  if (const auto& match = parse(value); match) {
    conversion(*match);
  }
  return *this;
}

template <std::size_t bits> auto Decimal<bits>::operator<(const Decimal& other) const noexcept -> bool {
  Decimal a(*this), b(other);
  a.normalize(b);
  return a.m_mantissa < b.m_mantissa;
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
  Decimal a(*this), b(other);
  a.normalize(b);
  return a.m_mantissa == b.m_mantissa;
}

template <std::size_t bits> auto Decimal<bits>::operator!=(const Decimal& other) const noexcept -> bool {
  return !(*this == other);
}

template <std::size_t bits> auto Decimal<bits>::operator-() const noexcept -> Decimal {
  Decimal result(*this);
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
  m_mantissa = m_mantissa + temp.m_mantissa;
  fit();
  return *this;
}

template <std::size_t bits> auto Decimal<bits>::operator-=(const Decimal& other) noexcept -> Decimal& {
  Decimal temp(other);
  normalize(temp);
  m_mantissa = m_mantissa - temp.m_mantissa;
  fit();
  return *this;
}

template <std::size_t bits> auto Decimal<bits>::operator*=(const Decimal& other) noexcept -> Decimal& {
  m_exponent = m_exponent + other.m_exponent;
  m_mantissa = m_mantissa * other.m_mantissa;
  fit();
  return *this;
}

template <std::size_t bits> auto Decimal<bits>::operator/=(const Decimal& other) noexcept -> Decimal& {
  Decimal temp(other);
  normalize(temp);

  bool negative = sign() ^ temp.sign();
  abs();
  temp.abs();

  std::bitset<m_bits> div = m_mantissa % temp.m_mantissa;
  m_mantissa = m_mantissa / temp.m_mantissa;

  for (m_exponent = {}; div.any() && m_exponent < m_max_exponent - 1; ++m_exponent) {
    m_mantissa = m_mantissa * std::bitset<m_bits>(0b1010);
    div = div * std::bitset<m_bits>(0b1010);
    m_mantissa = m_mantissa + div / temp.m_mantissa;
    div = div % temp.m_mantissa;
  }
  fit();
  if (negative) m_mantissa = -m_mantissa;
  return *this;
}

template <std::size_t bits> auto Decimal<bits>::operator%=(const Decimal& other) noexcept -> Decimal& {
  Decimal temp(other);
  normalize(temp);
  m_mantissa = m_mantissa % temp.m_mantissa;
  fit();
  return *this;
}

template <std::size_t bits> Decimal<bits>::operator std::string() const noexcept {
  std::bitset<m_bits> mantissa(sign() ? -this->m_mantissa : this->m_mantissa);

  std::string result;
  while (mantissa.any()) {
    result += (mantissa % std::bitset<m_bits>(0b1010)).to_ulong() + '0';
    mantissa = mantissa / std::bitset<m_bits>(0b1010);
  }

  while (result.size() <= m_exponent) {
    result += '0';
  }

  if (m_exponent) {
    result.insert(m_exponent, ".");
  }

  result += (sign() ? '-' : '+');

  std::reverse(result.begin(), result.end());
  return result;
}

template <std::size_t bits> auto Decimal<bits>::trunc() const noexcept -> Decimal {
  Decimal result(*this);
  while (result.m_exponent) {
    result.m_mantissa = result.m_mantissa / std::bitset<m_bits>(0b1010);
    --result.m_exponent;
  }
  return result;
}

template <std::size_t bits> auto Decimal<bits>::round() const noexcept -> Decimal {
  Decimal result(*this);
  bool negative = result.m_mantissa[m_bits - 1];
  if (negative) result.m_mantissa = -result.m_mantissa;

  if (result % Decimal("1") >= Decimal("0.5")) {
    result = result + Decimal("1");
    return negative ? -result.trunc() : result.trunc();
  } else {
    return negative ? -result.trunc() : result.trunc();
  }
}

template <std::size_t bits> auto Decimal<bits>::floor() const noexcept -> Decimal {
  Decimal result(*this);
  if (!result.m_mantissa[result.m_bits - 1]) {
    return result.trunc();
  }
  result = result - Decimal("1");
  return result.trunc();
}

template <std::size_t bits> auto Decimal<bits>::ceil() const noexcept -> Decimal {
  Decimal result(*this);
  if (result.m_mantissa[result.m_bits - 1]) {
    return result.trunc();
  }
  result = result + Decimal("1");
  return result.trunc();
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

template <std::size_t bits> auto Decimal<bits>::sign() const noexcept -> bool {
  return m_mantissa[m_bits - 1];
}

template <std::size_t bits> auto Decimal<bits>::conversion(const std::cmatch& match) -> void {
  m_exponent = std::min<std::size_t>(m_max_exponent - match[2].length(), match[3].length());

  std::string number = match[2].str() + match[3].str().substr(0, m_exponent);

  std::vector<int> digits(number.size());
  for (const char& digit : number) {
    digits.push_back(digit - '0');
  }

  std::size_t bit{}, value{}, carry{};
  while(!digits.empty()) {
    m_mantissa.set(bit++, digits.back() & 1);

    carry = {};
    for (int & digit : digits) {
      value = carry * 10 + digit;
      digit = value / 2;
      carry = value % 2;
    };

    digits.erase(digits.begin(), std::find_if(digits.begin(), digits.end(), [](const int& digit) { return digit != 0; }));
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

template <std::size_t bits> auto Decimal<bits>::fit() noexcept -> void {
  bool negative = sign();
  abs();
  for (std::size_t i = m_bits - 2; (i >= m_bits / 2) && m_exponent; --i) {
    if (m_mantissa[i] && m_exponent--) {
      m_mantissa = m_mantissa / std::bitset<m_bits>(0b1010);
    }
  }
  if (negative) m_mantissa = -m_mantissa;
}

template <std::size_t bits> auto Decimal<bits>::abs() noexcept -> Decimal<bits>& {
  if (sign()) {
    m_mantissa = -m_mantissa;
  }
  return *this;
}

template <std::size_t bits> auto operator<<(std::ostream& os, Decimal<bits> decimal) -> std::ostream& {
  return os << static_cast<std::string>(decimal);
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
    a ^= b;
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
    if ((b & one)[0]) {
      result = result + a;
    }
    a <<= 1;
    b >>= 1;
  }
  return result;
}

template <std::size_t bits> auto operator/(std::bitset<bits> a, std::bitset<bits> b) -> std::bitset<bits> {
  bool negative = a[bits - 1] ^ b[bits - 1];
  if (a[bits - 1]) a = -a;
  if (b[bits - 1]) b = -b;
  if (a.none() || b.none()) {
    return {};
  }

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

  return negative ? -result : result;
}

template <std::size_t bits> auto operator%(std::bitset<bits> a, std::bitset<bits> b) -> std::bitset<bits> {
  bool negative = a[bits - 1];
  if (a[bits - 1]) a = -a;
  if (b[bits - 1]) b = -b;
  if (a.none()) {
    return a;
  }
  if (b.none()) {
    return b;
  }

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

  return negative ? -rest : rest;
}
} // namespace utils::finantial