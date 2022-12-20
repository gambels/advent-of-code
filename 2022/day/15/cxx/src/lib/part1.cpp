#include "part1.h"
#include "common.hpp"

using Part1 = aoc::Part1;

Part1::Part1()
{}

auto Part1::handle_input(std::istream& in) -> std::size_t
{
  auto row = 2000000;
  auto intervals = dissect(make_scan(in), row);
  
  auto count = 0;
  auto do_count = [&] (auto& interval) {
    count += interval.max - interval.min;
  };
  std::ranges::for_each(intervals, do_count);

  return count;
}
