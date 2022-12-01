#include "lib/part1.h"

#include <iostream>

int main ()
{
  auto part1 = Part1{};

  std::cout << "Adven of code: day xx" << std::endl;
  std::cout << "Answer: " << Part1().handle_input(std::cin) << std::endl;
  return 0;
}
