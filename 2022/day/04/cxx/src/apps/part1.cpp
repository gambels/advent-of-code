#include "lib/part1.h"

#include <iostream>

int main ()
{
  auto part1 = Part1{};

  std::cout << "Adven of code: day " << std::string{AOE_DAY} << " / part 1" << std::endl;
  std::cout << "Answer: " << Part1().handle_input(std::cin) << std::endl;
  return 0;
}
