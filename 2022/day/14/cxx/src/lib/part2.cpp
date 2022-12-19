#include "part2.h"
#include "common.hpp"

using Part2 = aoc::Part2;

Part2::Part2()
{}

auto Part2::handle_input(std::istream& in) -> size_t
{
  auto grid = make_grid_with_floor(in);
  auto sand_units = 0;
  auto point = START_POINT;
  while (!is_sand(grid, START_POINT))
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
      grid[point.row][point.col] = 'o';
      ++sand_units;
      point = START_POINT;
    }
  }
  //print_grid(grid);

  return sand_units;
}
