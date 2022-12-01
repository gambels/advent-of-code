#include "part1.h"

#include <algorithm>
#include <iterator>
#include <limits>

Part1::Part1()
{}

auto Part1::handle_input(std::istream& in) -> size_t
{
  auto is_greater = [prev = std::numeric_limits<int>::max()] (auto cur) mutable {
    return std::exchange(prev, cur) < cur;
  };
  return count_if(std::istream_iterator<int>{in}, std::istream_iterator<int>{}, is_greater);
}

