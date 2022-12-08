#pragma once

#include <algorithm>
#include <ranges>
#include <istream>
#include <sstream>
#include <map>
#include <vector>

using grid_t = std::map<int, std::vector<char>>;

struct Input : public std::string
{
};

inline
std::istream& operator>>(std::istream& in, Input& input)
{
  getline(in, input);
  return in;
}

inline
auto print_grid(auto& grid)
{
  std::ranges::for_each(grid | std::views::values, [] (auto v) { for(auto i : v) std::cout << i; std::cout << std::endl;}); 
}

inline
auto made_grid(std::istream& in)
{
  auto grid_rows = grid_t{};
  auto grid_cols = grid_t{};
  auto row = 0;

  auto do_line = [&] (auto& input) {
    auto ss = std::stringstream{input};
    auto c = char{};
    for (auto col = 0; ss >> c; ++col)
    {
      grid_rows[row].push_back(c);
      grid_cols[col].push_back(c);
    }
    ++row;
  };
  std::ranges::for_each(std::ranges::istream_view<Input>(in), do_line);

  return std::make_pair(grid_rows, grid_cols);
}

inline
auto left_view(auto& v, auto pos)
{
  return v | std::ranges::views::take(pos);
}

inline
auto reverse_left_view(auto& v, auto pos)
{
  return left_view(v, pos) | std::ranges::views::reverse;
}

inline
auto right_view(auto& v, auto pos)
{
  return v | std::ranges::views::drop(pos + 1);
};

inline
auto reverse_right_view(auto& v, auto pos)
{
  return right_view(v, pos) | std::ranges::views::reverse;
};
