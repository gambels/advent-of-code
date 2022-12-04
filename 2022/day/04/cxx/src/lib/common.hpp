#pragma once

#include <utility>
#include <istream>

struct Input
{
    Input() {}

    [[nodiscard]] static auto is_all_of(auto a, auto b) -> bool
    {
      if (b.first <= a.first && a.second <= b.second )
      {
        return true;
      }
      return false;
    }

    [[nodiscard]] static auto is_part_of(auto a, auto b) -> bool
    {
      if (b.first <= a.second && a.first <= b.second)
      {
        return true;
      }
      return false;
    }

    std::pair<int, int> _a;
    std::pair<int, int> _b;
};

inline
std::istream& operator>>(std::istream& in, Input& input)
{
  auto c = char{};
  in >> input._a.first >> c >> input._a.second >> c >> input._b.first >> c >> input._b.second;
  return in;
}
