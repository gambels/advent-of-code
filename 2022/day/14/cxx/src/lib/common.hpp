#pragma once

#include <istream>
#include <sstream>
#include <ranges>
#include <algorithm>
#include <regex>
#include <numeric>

#include <vector>
#include <list>
#include <map>
#include <set>

namespace aoc
{
  using grid_t = std::vector<std::string>;

  static constexpr int MAX_COL = 1000;
  static constexpr int MAX_ROW = 250;

  static constexpr char STONE = '#';
  static constexpr char AIR = '.';
  static constexpr char SAND = 'o';
  static constexpr char START = '+';
  
  struct Point
  {
    auto down() { return Point{.row = row + 1, .col = col}; }
    auto down_left() { return Point{.row = row + 1, .col = col - 1}; }
    auto down_right() { return Point{.row = row + 1, .col = col + 1}; }

    int row;
    int col;
  };
  static constexpr Point START_POINT = Point{.row = 0, .col = 500};
  
  struct Input
  {
    Input() {}
    std::vector<Point> points;
  };

  inline
  std::istream& operator>>(std::istream& in, Input& input)
  {
    auto line = std::string{};
    getline(in, line);
    input.points.clear();

    auto rgx = std::regex("([0-9]+),([0-9]+)");
    auto do_scan = [&input] (auto& match) {
      auto point = Point{};
      std::stringstream{match.str(1)} >> point.col;
      std::stringstream{match.str(2)} >> point.row;
      input.points.push_back(point);
    };
    std::ranges::for_each(std::sregex_iterator{line.begin(), line.end(), rgx}, std::sregex_iterator{}, do_scan);

    return in;
  }

  inline 
  auto make_row(char c)
  {
    return std::string(MAX_COL, c);
  }

  inline
  auto make_grid(std::istream& in)
  {
    auto grid = grid_t{make_row(AIR)};
    grid[0][500] = START;

    auto do_input = [&] (auto& input) {
      auto prev = input.points.front();
      for (auto& point : input.points)
      {
        auto row_start = prev.row < point.row ? prev.row : point.row;
        auto row_end  = prev.row > point.row ? prev.row : point.row;
        
        auto col_start = prev.col < point.col ? prev.col : point.col;
        auto col_end  = prev.col > point.col ? prev.col : point.col;

        for (auto row = row_start; row <= row_end; ++row)
        {
          for (auto col = col_start; col <= col_end; ++col)
          {
            if (row >= grid.size())
            {
              while (row >= grid.size())
              {
                grid.push_back(make_row(AIR));
              }
            }
            grid[row][col] = STONE;
          }
        }
        prev = Point{.row = point.row, .col = point.col};
      }
    };
    std::ranges::for_each(std::ranges::istream_view<Input>(in), do_input);
   
    return grid;
  }

  inline
  auto make_grid_with_floor(std::istream& in)
  {
    auto grid = make_grid(in);
    grid.push_back(make_row(AIR));
    grid.push_back(make_row(STONE));    
    return grid;
  }

  inline
  auto print_grid(auto& grid)
  {
    std::cout << std::endl;
    auto do_row = [] (auto& row) {
      std::cout << row.substr(MAX_COL / 2 - 50, 100) << std::endl;
    };
    std::ranges::for_each(grid, do_row);
  }

  inline
  auto is_stepable(const auto& grid, const auto& point)
  {
    auto row = point.row;
    auto col = point.col;

    if (row < 0 || row > grid.size() -1 || col < 0 || col > grid[0].size() - 1)
    {
      throw std::runtime_error("sand flows out the bottom");
    }

    if (grid[row][col] == '.')
    {
      return true;
    }
    return false;
  }
  
  inline
  auto is_sand(const auto& grid, const auto& point)
  {
    if (grid[point.row][point.col] == SAND)
    {
      return true;
    }
    return false;
  }

} // namespace aoc
