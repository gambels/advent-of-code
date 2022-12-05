#include "lib/part2.h"

#include <iostream>

int main (int argc, char** argv)
{
  std::cout << "Adven of code: day " << AOE_DAY << " / part 2" << std::endl;
  std::cout << "Answer: " << Part2{argv[1]}.handle_input(std::cin) << std::endl;
  return 0;
}
