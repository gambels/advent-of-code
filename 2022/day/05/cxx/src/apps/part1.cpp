#include "lib/part1.h"

#include <iostream>

int main (int argc, char** argv)
{
  std::cout << "Adven of code: day " << AOE_DAY << " / part 1" << std::endl;
  std::cout << "Answer: " << Part1{argv[1]}.handle_input(std::cin) << std::endl;
  return 0;
}
