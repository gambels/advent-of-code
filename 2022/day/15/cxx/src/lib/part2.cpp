#include "part2.h"
#include "common.hpp"

using Part2 = aoc::Part2;

Part2::Part2()
{}

auto Part2::handle_input(std::istream& in) -> uint64_t
{
  auto scan = make_scan(in);
  auto min_row = 0;
  auto max_row = 4000000;

  for (auto row = min_row; row <= max_row; ++row)
  {
    auto intervals = dissect(scan, row); 
    if (intervals.size() > 1)
    {
      return (intervals.front().max + 1) * 4000000 + row;
    }
  }
  return 0;
}
