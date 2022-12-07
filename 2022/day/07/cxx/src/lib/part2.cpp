#include "part2.h"
#include "common.hpp"

Part2::Part2()
{}

auto Part2::handle_input(std::istream& in) -> size_t
{
  auto fs = made_fs(in);

  const auto total = 70000000;
  const auto update = 30000000;
  auto free = total - fs["/"];

  auto is_at_least = [least = (update - free)] (auto& pair) {
    auto [dir, size] = pair;
    return size >= least;
  };
  
  return std::ranges::min(fs | std::views::filter(is_at_least) | std::views::values);
}
