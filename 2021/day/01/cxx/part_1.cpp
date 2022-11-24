#include <iostream>
#include <algorithm>
#include <iterator>
#include <limits>

int main ()
{

  std::cout << "Advent of code: day 01" << std::endl;

  auto is_greater = [prev = std::numeric_limits<int>::max()] (auto input) mutable {
    auto cur = std::atoi(input.c_str());
    return std::exchange(prev, cur) < cur;
  };

  auto n = count_if(std::istream_iterator<std::string>{std::cin}, std::istream_iterator<std::string>{}, is_greater);

  std::cout << "Answer: " << n << std::endl;

  return 0;
}
