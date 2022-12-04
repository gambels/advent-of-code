#include "part2.h"
#include "common.hpp"

#include <algorithm>
#include <ranges>

#define DEBUG 0

Part2::Part2()
{}

auto Part2::handle_input(std::istream& in) -> std::size_t
{
  auto n = 0;
  auto do_line = [&n] (auto& input) {
#if DEBUG
    std::cout << input._a.first << "-" << input._a.second << " " << input._b.first << "-" << input._b.second << std::endl;
#endif
    n += Input::is_part_of(input._a, input._b) ? 1 : 0;
  };
  std::ranges::for_each(std::ranges::istream_view<Input>(in), do_line);

  return n;
}
