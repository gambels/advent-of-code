#include "part2.h"
#include "common.hpp"

using Part2 = aoc::Part2;

Part2::Part2()
{}

auto Part2::handle_input(std::istream& in) -> size_t
{
  const auto div_pkg_1 = List{List{2}};
  const auto div_pkg_2 = List{List{6}};
  auto list = std::vector<List>{div_pkg_1, div_pkg_2};

  auto do_transform = [&] (auto& pair) {
    list.push_back(pair.first);
    list.push_back(pair.second);
  };
  std::ranges::for_each(make_pair_list(in), do_transform);

  auto is_less = [] (auto& a, auto& b) {
    return a < b;
  };
  std::ranges::sort(list, is_less);

  auto n1 = std::distance(std::begin(list), std::next(std::find(std::begin(list), std::end(list), div_pkg_1)));
  auto n2 = std::distance(std::begin(list), std::next(std::find(std::begin(list), std::end(list), div_pkg_2)));
  
  return n1 * n2 ;
}
