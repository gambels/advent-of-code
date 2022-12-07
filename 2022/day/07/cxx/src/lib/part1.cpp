#include "part1.h"
#include "common.hpp"

#include <numeric>

Part1::Part1()
{}

auto Part1::handle_input(std::istream& in) -> std::size_t
{
  auto is_at_most = [most = 100000] (auto& pair) {
    auto [dir, size] = pair;
    return size <= most;
  };
  auto fs = made_fs(in);
  auto values = fs | std::views::filter(is_at_most) | std::views::values;
  
  return std::accumulate(values.begin(), values.end(), 0);
}
