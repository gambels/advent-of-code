#include "part2.h"
#include "common.hpp"

using Part2 = aoc::Part2;

Part2::Part2()
{}

auto Part2::handle_input(std::istream& in) -> size_t
{
  auto [map, points] = make_height_map(in);
  auto [start, end] = points;

  return do_hill_climb_backwards(map, end);
}
