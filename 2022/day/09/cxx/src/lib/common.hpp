#pragma once

#include <algorithm>
#include <ranges>
#include <istream>
#include <sstream>
#include <map>
#include <set>
#include <vector>

using point_t = std::pair<int, int>;
using point_map_t = std::set<point_t>;
using point_list_t = std::vector<point_t>;

struct Input
{
  Input() {};

  operator std::string()
  {
    auto ss = std::stringstream{};
    ss << "direction: " << direction << ", steps: " << steps;
    return ss.str();
  }

  char direction = '.';
  size_t steps = 0;
};

inline
std::istream& operator>>(std::istream& in, Input& input)
{
  in >> input.direction >> input.steps;
  return in;
}

struct IsAdjacent
{
  IsAdjacent(size_t max_span) :
    m_max_span{max_span}
  {}

  auto operator() (point_t a, point_t b) 
  {
    auto [a_x, a_y] = a;
    auto [b_x, b_y] = b;

    auto x_abs = std::abs(a_x - b_x);
    auto y_abs = std::abs(a_y - b_y);

    return x_abs <= m_max_span && y_abs <= m_max_span;
  }

  const size_t m_max_span = 0;
};

struct MoveHead
{
  MoveHead() {}

  auto operator() (Input input, point_t head)
  {
    auto next_head = point_t{head};
    auto& [head_x, head_y] = next_head;

    switch (input.direction)
    {
      case 'R': head_x += 1; break;
      case 'L': head_x -= 1; break;
      case 'U': head_y += 1; break;
      case 'D': head_y -= 1; break;
    }

    return next_head;
  }
};

struct NextTail
{
  NextTail() {}

  auto operator() (point_t head, point_t tail)
  {
    auto next_tail = point_t{tail};
    auto& [head_x, head_y] = head;
    auto& [tail_x, tail_y] = next_tail;
    
    auto y = (head_y - tail_y);
    if ( y >  1 ) y = 1;
    if ( y < -1 ) y = -1;

    auto x = (head_x - tail_x);
    if ( x >  1 ) x = 1;
    if ( x < -1 ) x = -1;

    if (head_y == tail_y)
    {
      tail_x += x;
    }
    else if (head_x == tail_x)
    {
      tail_y += y;
    }
    else
    {
      tail_x += x;
      tail_y += y;
    }

    return next_tail;
  }
};
