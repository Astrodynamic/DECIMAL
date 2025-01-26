#include <iostream>

#include "decimal.h"

int main(int argc, char* argv[]) {

  utils::finantial::Decimal a("-15.1");
  // a = -a;
  std::cout << a << "\n";

  utils::finantial::Decimal b("-15.1");
  // b = -b;
  std::cout << -b << "\n";
// a = a + b;
  a += b;
  std::cout << -a << "\n";
  return 0;
}