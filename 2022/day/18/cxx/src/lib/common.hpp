#pragma once

#include <algorithm>
#include <cassert>
#include <istream>
#include <list>
#include <map>
#include <ranges>
#include <set>
#include <unordered_set>
#include <sstream>
#include <vector>
#include <queue>
#include <numeric>

namespace aoc {

struct Point {
  auto operator<=>(const Point&) const = default;

  auto neighbours()
  {
    return std::vector<Point>{
      {x - 1, y, z},
      {x + 1, y, z},
      {x, y - 1, z},
      {x, y + 1, z},
      {x, y, z - 1},
      {x, y, z + 1}};
  }

  auto is_bounded(Point min, Point max)
  {
    if (x < min.x || max.x < x ||
        y < min.y || max.y < y ||
        z < min.z || max.z < z)
    {
      return false;
    }
    return true;
  }

  int x = 0;
  int y = 0;
  int z = 0;
};

struct Side {
  Side(Point p1, Point p2, Point p3, Point p4)
  {
    points_ = std::vector<Point>{p1, p2, p3, p4};
    std::ranges::sort(points_);
  }

  auto is_adjacent(const Side& rhs) const
  {
    auto set = std::set<Point>{};

    std::ranges::for_each(points_, [&set] (auto& point) {set.insert(point);});
    std::ranges::for_each(rhs.points_, [&set] (auto& point) {set.insert(point);});

    return set.size() == 6;
  }

  auto operator<=>(const Side&) const = default;

  std::vector<Point> points_;
};
using Sides = std::list<Side>;

struct Cube {
  Cube(Point point) : point_{point} {}

  auto get_bottom_side() const
  {
    auto [x, y, z] = point_;

    auto p1 = Point{.x = x, .y = y, .z = z};
    ++y;
    auto p2 = Point{.x = x, .y = y, .z = z};
    ++x;
    auto p3 = Point{.x = x, .y = y, .z = z};
    --y;
    auto p4 = Point{.x = x, .y = y, .z = z};

    return Side(p1, p2, p3, p4);
  }

  auto get_up_side() const
  {
    auto [x, y, z] = point_;

    ++z;
    auto p1 = Point{.x = x, .y = y, .z = z};
    ++y;
    auto p2 = Point{.x = x, .y = y, .z = z};
    ++x;
    auto p3 = Point{.x = x, .y = y, .z = z};
    --y;
    auto p4 = Point{.x = x, .y = y, .z = z};

    return Side(p1, p2, p3, p4);
  }

  auto get_left_side() const
  {
    auto [x, y, z] = point_;

    auto p1 = Point{.x = x, .y = y, .z = z};
    ++x;
    auto p2 = Point{.x = x, .y = y, .z = z};
    ++z;
    auto p3 = Point{.x = x, .y = y, .z = z};
    --x;
    auto p4 = Point{.x = x, .y = y, .z = z};

    return Side(p1, p2, p3, p4);
  }

  auto get_right_side() const
  {
    auto [x, y, z] = point_;

    ++y;
    auto p1 = Point{.x = x, .y = y, .z = z};
    ++x;
    auto p2 = Point{.x = x, .y = y, .z = z};
    ++z;
    auto p3 = Point{.x = x, .y = y, .z = z};
    --x;
    auto p4 = Point{.x = x, .y = y, .z = z};

    return Side(p1, p2, p3, p4);
  }

  auto get_front_side() const
  {
    auto [x, y, z] = point_;

    auto p1 = Point{.x = x, .y = y, .z = z};
    ++z;
    auto p2 = Point{.x = x, .y = y, .z = z};
    ++y;
    auto p3 = Point{.x = x, .y = y, .z = z};
    --z;
    auto p4 = Point{.x = x, .y = y, .z = z};

    return Side(p1, p2, p3, p4);
  }

  auto get_back_side() const
  {
    auto [x, y, z] = point_;

    ++x;
    auto p1 = Point{.x = x, .y = y, .z = z};
    ++z;
    auto p2 = Point{.x = x, .y = y, .z = z};
    ++y;
    auto p3 = Point{.x = x, .y = y, .z = z};
    --z;
    auto p4 = Point{.x = x, .y = y, .z = z};

    return Side(p1, p2, p3, p4);
  }

  auto get_sides() const
  {
    return Sides{get_bottom_side(), get_up_side(),    get_left_side(),
                 get_right_side(),  get_front_side(), get_back_side()};
  }

  const Point point_;
};
using Cubes = std::list<Cube>;

struct Input {
  Input() {}

  int x;
  int y;
  int z;
};

inline std::istream& operator>>(std::istream& in, Input& input)
{
  auto delim = char{};
  in >> input.x >> delim >> input.y >> delim >> input.z;
  return in;
}

inline auto make_cubes(std::istream& in)
{
  auto cubes = Cubes{};
  auto do_input = [&](auto& input) {
    auto [x, y, z] = input;
    cubes.emplace_back(Point{x, y, z});
  };
  std::ranges::for_each(std::ranges::istream_view<Input>(in), do_input);

  return cubes;
}

inline auto make_sides(const auto& cubes)
{
  auto all_sides = Sides{};
  auto do_side = [&](const auto& cube) {
    auto sides = cube.get_sides();
    std::copy(std::begin(sides), std::end(sides), std::back_inserter(all_sides));
  };
  std::ranges::for_each(cubes, do_side);

  return all_sides;
}

inline auto make_grid(const auto& cubes)
{
  using Grid = std::unordered_map<int,std::unordered_map<int, std::set<int>>>;

  auto min = std::numeric_limits<int>::min();
  auto max_boundary = Point{min, min, min};
  auto update_max_boundary = [&max_boundary] (const Point& point) {
    max_boundary.x = std::max(max_boundary.x, point.x + 1);
    max_boundary.y = std::max(max_boundary.y, point.y + 1);
    max_boundary.z = std::max(max_boundary.z, point.z + 1);
  };

  auto max = std::numeric_limits<int>::max();
  auto min_boundary = Point{max, max, max};
  auto update_min_boundary = [&min_boundary] (const Point& point) {
    min_boundary.x = std::min(min_boundary.x, point.x - 1);
    min_boundary.y = std::min(min_boundary.y, point.y - 1);
    min_boundary.z = std::min(min_boundary.z, point.z - 1);
  };
  
  auto grid = Grid{};
  for (auto &cube : cubes)
  {
    grid[cube.point_.x][cube.point_.y].insert(cube.point_.z);
    update_max_boundary(cube.point_);
    update_min_boundary(cube.point_);
  }

  return std::make_tuple(grid, min_boundary, max_boundary);
}

inline auto surface(const auto& cubes)
{
  auto sides = make_sides(cubes);
  sides.sort();

  auto it = std::adjacent_find(std::begin(sides), std::end(sides));
  while (it != std::end(sides))
  {
    it = sides.erase(it, std::next(it, 2));
    it = std::adjacent_find(it, std::end(sides));
  }
  return sides.size();
}


inline auto exterior_surface(const auto& cubes)
{
  auto [cubes_grid, min, max] = make_grid(cubes);

  auto visited_grid = decltype(cubes_grid){};
  visited_grid[min.x][min.y].insert(min.z);

  auto queue = std::queue<Point>{};
  queue.push(min);
  
  int total_sides = 0;
  while (queue.size())
  {
    Point curr = queue.front();
    queue.pop();

    auto is_cube = [&] (auto& n) {
      if (!n.is_bounded(min, max) || visited_grid[n.x][n.y].contains(n.z))
      {
        return;
      }
      if (cubes_grid[n.x][n.y].contains(n.z))
      {
        total_sides++;
        return;
      }
      visited_grid[n.x][n.y].insert(n.z);
      queue.push(n);
    };
    std::ranges::for_each(curr.neighbours(), is_cube);
  }
  return total_sides;
}

}  // namespace aoc
