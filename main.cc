#include <iostream>

#include "decimal.h"

int main(int argc, char* argv[]) {

  utils::finantial::Decimal a("-20");
  // a = -a;
  // std::cout << a << "\n";

  utils::finantial::Decimal b("-6");
  // b = -b;
  std::cout << (a % b) << "\n";

  std::cout << -20 % -6;
  // std::cout << b << std::endl;
// // a = a + b;
//   a += b;
  // std::cout << -a << "\n";

//   std::cout << (utils::finantial::Decimal("171") /= utils::finantial::Decimal("10")) << "\n";
  return 0;
}