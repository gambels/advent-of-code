#include "part2.h"
#include "common.hpp"

Part2::Part2()
{}

auto Part2::handle_input(std::istream& in) -> size_t
{
  auto [grid_rows, grid_cols] = made_grid(in);
  auto tree_scenic_score_max = 0;

  auto do_scenic_score = [&] (auto row, auto col)
  {
    auto  distance = [tree = grid_rows[row][col]] (auto view) {
      auto it = std::ranges::find_if(view, [tree] (auto i) {return i >= tree;}) ;
      auto n = std::ranges::distance(view.begin(), it);
      return (it == view.end() ? n : n + 1);
    };

    auto max_tree_left = distance(reverse_left_view(grid_rows[row], col));
    auto max_tree_right = distance(right_view(grid_rows[row], col));
    auto max_tree_up = distance(reverse_left_view(grid_cols[col], row));
    auto max_tree_down = distance(right_view(grid_cols[col], row));
    
    auto tree_scenic_score = (max_tree_left * max_tree_right * max_tree_up * max_tree_down);
    if (tree_scenic_score > tree_scenic_score_max)
    {
      tree_scenic_score_max = tree_scenic_score;
    }
  };

  for (auto it = std::next(grid_rows.begin(), 1); it != std::prev(grid_rows.end(), 1); ++it)
  {
    auto& [row, vec] = *it;
    for (auto it = std::next(vec.begin(), 1); it != std::prev(vec.end(), 1); ++it)
    {
      auto col = std::distance(vec.begin(), it);
      do_scenic_score(row, col);
    }
  }
  return tree_scenic_score_max;
}
