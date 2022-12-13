#include "part1.h"
#include "common.hpp"

using Part1 = aoc::Part1;

Part1::Part1()
{}

auto Part1::handle_input(std::istream& in) -> std::size_t
{
  auto [map, points] = make_map(in);
  auto [start, end] = points;

  return do_hill_climb(map, start, end);
}
