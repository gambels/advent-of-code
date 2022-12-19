#include "part1.h"
#include "common.hpp"

using Part1 = aoc::Part1;

Part1::Part1()
{}

auto Part1::handle_input(std::istream& in) -> std::size_t
{
  auto grid = make_grid(in);
  auto sand_units = 0;
  auto point = START_POINT;
  while (true)
  {
    try
    {
      if (is_stepable(grid, point.down()))
      {
        point = point.down();
      }
      else if (is_stepable(grid, point.down_left()))
      {
        point = point.down_left();
      }
      else if (is_stepable(grid, point.down_right()))
      {
        point = point.down_right();
      }
      else
      {
        grid[point.row][point.col] = SAND;
        ++sand_units;
        point = START_POINT;
      }
    }
    catch (const std::exception& e)
    {
      break;
    }
  }
  //print_grid(grid);

  return sand_units;
}
