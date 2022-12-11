#pragma once

#include <istream>
#include <sstream>
#include <ranges>
#include <algorithm>

#include <vector>
#include <list>
#include <map>
#include <set>

namespace aoc
{

  struct Input
  {
    Input() {}
  };

  inline
  std::istream& operator>>(std::istream& in, Input& input)
  {
    return in;
  }

} // namespace aoc
