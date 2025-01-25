#include "decimal.h"
#include <cstddef>
#include <string_view>

namespace utils::finantial {
template <std::size_t mantissa> Decimal<mantissa>::Decimal(const std::string_view& value) {
  *this = value;
}

template <std::size_t mantissa> auto Decimal<mantissa>::operator=(const std::string_view& value) -> Decimal<mantissa>& {
  auto match = parse(value);
  if (match) {
    conversion(*match);
  }
  return *this;
}

template <std::size_t mantissa> auto Decimal<mantissa>::operator-() noexcept -> Decimal& {
  m_mantissa.flip(mantissa);
  return *this;
}

template <std::size_t mantissa> auto Decimal<mantissa>::parse(const std::string_view& value) const -> std::optional<std::cmatch> {
  std::cmatch match;
  if (std::regex_match(value.begin(), value.end(), match, m_mask)) {
    if (match[2].length() <= m_max_exponent) {
      return match;
    }
  }
  return {};
}

template <std::size_t mantissa> auto Decimal<mantissa>::conversion(const std::cmatch& match) -> void {
  m_mantissa.set(mantissa, match[1] == "-");
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
}

template <std::size_t mantissa> auto operator<<(std::ostream& os, const Decimal<mantissa>& decimal) -> std::ostream& {
  return os << decimal.m_mantissa.to_string();
}
} // namespace utils::finantial