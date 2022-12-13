#pragma once

#include <istream>
#include <ranges>
#include <algorithm>
#include <optional>
#include <numeric>

#include <vector>
#include <queue>


namespace aoc
{
  using height_map_t = std::vector<std::string>;

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
    
    auto neighbors()
    {
      return std::vector{left(), right(), down(), up()};
    }

    auto is_bound(const height_map_t& map)
    {
      auto min_row = 0;
      auto max_row = map.size() -1;
      if (row < min_row || max_row < row)
      {
        return false;
      }
      auto min_col = 0;
      auto max_col = map[0].size() -1;
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

  struct Queue
  {
    using queue_t = std::queue<Point>;
    using path_map_t = std::vector<std::vector<int>>;

    Queue(const height_map_t& map) :
      path_map(map.size(), std::vector<int>(map[0].length(), -1))
    {}

    Queue(const height_map_t& path_map, Point init) :
      Queue{path_map}
    {
      enqueue(init);
    }

    auto enqueue (Point p) -> bool
    {
      queue.push(p);
      path_map[p.row][p.col] = p.cost;
      return true;
    }
    
    auto dequeue()
    {
      auto p = queue.front();
      queue.pop();
      return p;
    };

    auto empty()
    {
      return queue.empty();
    }

    auto visited(Point p)
    {
      return (path_map[p.row][p.col] != -1);
    }

    auto operator() (Point p)
    {
      return path_map[p.row][p.col];
    }

    queue_t queue;
    path_map_t path_map;
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
  auto make_height_map(std::istream& in)
  {
    auto map = height_map_t{};
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
  auto do_hill_climb(const height_map_t& height_map, Point start, Point end)
  {
    auto queue = Queue{height_map, start};
    while (!queue.empty())
    {
      auto from = queue.dequeue();
      if (height_map[from.row][from.col] == 'E')
      {
        continue;
      }
      auto is_stepable = [&] (Point from, Point to)
      {
        if (!to.is_bound(height_map) || queue.visited(to))
        {
          return false;
        }
        return is_elevation_ok(height_map[from.row][from.col], height_map[to.row][to.col], false);
      };
      std::ranges::for_each(from.neighbors(), [&] (auto to) {
        is_stepable(from, to) && queue.enqueue(to);
      });
    }
    return queue(end);
  }

  inline
  auto do_hill_climb_backwards(const height_map_t& height_map, Point end)
  {
    auto queue = Queue{height_map, end};
    auto best_cost = std::numeric_limits<int>::max();   
    
    while (!queue.empty())
    {
      auto from = queue.dequeue();
      if (height_map[from.row][from.col] == 'S' || height_map[from.row][from.col] == 'a')
      {
        best_cost = from.cost < best_cost ? from.cost : best_cost;
        continue;
      }
      auto is_stepable = [&] (Point from, Point to)
      {
        const auto backwards = true;
        if (!to.is_bound(height_map) || queue.visited(to))
        {
          return false;
        }
        return is_elevation_ok(height_map[from.row][from.col], height_map[to.row][to.col], backwards);
      };
      std::ranges::for_each(from.neighbors(), [&] (auto to) {
        is_stepable(from, to) && queue.enqueue(to);
      });
    }
    return best_cost;
  }
  
} // namespace aoc
