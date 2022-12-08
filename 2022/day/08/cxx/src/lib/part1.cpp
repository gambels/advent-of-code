#include "part1.h"
#include "common.hpp"

#include <algorithm>
#include <ranges>

Part1::Part1()
{}

auto Part1::handle_input(std::istream& in) -> std::size_t
{
  auto [grid_rows, grid_cols] = made_grid(in);
  auto is_visible = [&] (auto row, auto col)
  {
    auto tree = grid_rows[row][col];

    auto max_tree_left = std::ranges::max(left_view(grid_rows[row], col));
    auto max_tree_right = std::ranges::max(right_view(grid_rows[row], col));
    auto max_tree_up = std::ranges::max(left_view(grid_cols[col], row));
    auto max_tree_down = std::ranges::max(right_view(grid_cols[col], row));
    
    return (max_tree_left < tree || tree > max_tree_right) || (max_tree_up < tree || tree > max_tree_down);
  };

  auto interior_count = 0;
  for (auto it = std::next(grid_rows.begin(), 1); it != std::prev(grid_rows.end(), 1); ++it)
  {
    auto& [row, vec] = *it;
    for (auto it = std::next(vec.begin(), 1); it != std::prev(vec.end(), 1); ++it)
    {
      auto col = std::distance(vec.begin(), it);
      interior_count += is_visible(row, col) ? 1 : 0;
    }
  }
  return (interior_count + 2 * grid_rows.size() + 2 * (grid_cols.size() - 2));
}
