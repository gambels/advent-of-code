#include <iostream>
#include <algorithm>
#include <iterator>
#include <limits>

int main ()
{

  std::cout << "Advent of code: day 01" << std::endl;

  auto is_greater = [prev = std::numeric_limits<int>::max()] (auto cur) mutable {
    return std::exchange(prev, cur) < cur;
  };
  auto n = count_if(std::istream_iterator<int>{std::cin}, std::istream_iterator<int>{}, is_greater);

  std::cout << "Answer: " << n << std::endl;

  return 0;
}
