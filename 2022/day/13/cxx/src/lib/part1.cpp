#include "part1.h"
#include "common.hpp"

using Part1 = aoc::Part1;

Part1::Part1()
{}

auto Part1::handle_input(std::istream& in) -> std::size_t
{
  auto sum = 0;
  auto do_compare = [&, idx = 1] (auto& pair) mutable {
    sum += pair.first < pair.second ? idx : 0;
    ++idx;
  };
  std::ranges::for_each(make_pair_list(in), do_compare);
  
  return sum;
}
