#pragma once

#include <istream>
#include <sstream>
#include <ranges>
#include <algorithm>
#include <optional>
#include <numeric>

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>


namespace aoc
{

  using map_t = std::vector<std::string>;

  struct Point
  {
    auto left()
    {
      return Point{row, col - 1, cost + 1};
    }
    auto right()
    {
      return Point{row, col + 1, cost + 1};
    }
    auto down() 
    { 
      return Point{row + 1, col, cost + 1};
    }
    auto up()
    {
      return Point{row - 1, col, cost + 1};
    }

    auto is_bound(auto min_row, auto max_row, auto min_col, auto max_col)
    {
      if (row < min_row || max_row < row)
      {
        return false;
      }
      if (col < min_col || max_col < col)
      {
        return false;
      }
      return true;
    }

    int row = 0;
    int col = 0;
    int cost = 0;
  };

  struct Input
  {
    Input() {}

    std::string line;
    std::optional<int> col_start;
    std::optional<int> col_end;
  };

  inline
  std::istream& operator>>(std::istream& in, Input& input)
  {
    getline(in, input.line);

    auto do_find = [&input] (auto c)
    {
      auto rv = std::optional<int>{std::nullopt};
      if (auto n = input.line.find(c); n != std::string::npos)
      {
        rv = n;
      }
      return rv;
    };
    input.col_start = do_find('S');
    input.col_end = do_find('E');

    return in;
  }

  inline 
  auto make_map(std::istream& in)
  {
    auto map = map_t{};
    auto start = Point{};
    auto end = Point{};

    auto do_input = [&] (auto& input)
    {
      if (input.col_start)
      {
        start = Point{static_cast<int>(map.size()), input.col_start.value()};
      }
      if (input.col_end)
      {
        end = Point{static_cast<int>(map.size()), input.col_end.value()};
      }
      map.push_back(input.line);
    };
    std::ranges::for_each(std::ranges::istream_view<Input>(in), do_input);

    return std::make_pair(map, std::make_pair(start, end));
  }

  inline    
  auto is_elevation_ok(char from, char to, bool backwards)
  {
    // If backwards, exchange points (from -> to).
    if (backwards)
    {
      to = std::exchange(from, to);
    }

    // Normalize points.
    from = (from == 'S') ? 'a' : from;
    to = (to == 'E') ? 'z' : to;

    return (from >= to) || (from + 1 == to);
  }

  inline
  auto do_hill_climb(const map_t& map, Point start, Point end)
  {
    auto max_cost = std::numeric_limits<int>::max();
    auto path_map = std::vector<std::vector<int>>(map.size(), std::vector<int>(map[0].length(), max_cost));

    auto can_step = [&] (Point from, Point to)
    {
      // Check bounds,
      if (!to.is_bound(0, map.size() -1 , 0, map[0].size() -1))
      {
        return false;
      }
      // Check shortest path.
      if (to.cost >= path_map[to.row][to.col])
      {
        return false;
      }
      return is_elevation_ok(map[from.row][from.col], map[to.row][to.col], false);
    };
    
    auto queue = std::queue<Point>{};
    auto enqueue = [&] (auto p)
    {
      queue.push(p);
      path_map[p.row][p.col] = p.cost;
    };
    auto dequeue = [&] ()
    {
      auto p = queue.front();
      queue.pop();
      return p;
    };

    enqueue(start);
    while (!queue.empty())
    {
      auto from = dequeue();
      if (map[from.row][from.col] == 'E')
      {
        continue;
      }
      for (auto dir : {&Point::left, &Point::right, &Point::up, &Point::down})
      {
        auto to = (from.*dir)();
        if (can_step(from, to))
        {
         queue.push(to);
         path_map[to.row][to.col] = to.cost;
        }
      }
    }
    return path_map[end.row][end.col];
  }

  inline
  auto do_hill_climb_backwards(const map_t& map, Point end)
  {
    auto max_cost = std::numeric_limits<int>::max();
    auto path_map = std::vector<std::vector<int>>(map.size(), std::vector<int>(map[0].length(), max_cost));

    auto can_step = [&] (Point from, Point to)
    {
      const auto backwards = true;

      // Check bounds,
      if (!to.is_bound(0, map.size() -1 , 0, map[0].size() -1))
      {
        return false;
      }
      // Check shortest path.
      if (to.cost >= path_map[to.row][to.col])
      {
        return false;
      }
      return is_elevation_ok(map[from.row][from.col], map[to.row][to.col], backwards);
    };
    
    auto best_cost = max_cost; 
    auto queue = std::queue<Point>{};

    auto enqueue = [&] (auto p)
    {
      queue.push(p);
      path_map[p.row][p.col] = p.cost;
    };
    auto dequeue = [&] ()
    {
      auto p = queue.front();
      queue.pop();
      return p;
    };
    
    enqueue(end);
    while (!queue.empty())
    {
      auto from = dequeue();
      if (map[from.row][from.col] == 'S' || map[from.row][from.col] == 'a')
      {
        best_cost = from.cost < best_cost ? from.cost : best_cost;
        continue;
      }
      for (auto dir : {&Point::left, &Point::right, &Point::up, &Point::down})
      {
        auto to = (from.*dir)();
        if (can_step(from, to))
        {
          enqueue(to);
        }
      }
    }
    return best_cost;
  }
  
} // namespace aoc
