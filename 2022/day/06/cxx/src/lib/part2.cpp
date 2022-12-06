#include "part2.h"
#include "common.hpp"

#include <ranges>
#include <algorithm>

Part2::Part2()
{}

auto Part2::handle_input(std::istream& in) -> size_t
{
  auto parser = Parser{14};
  std::ranges::for_each(std::ranges::istream_view<std::string>(in), std::ref(parser));
  return parser.msg_start();
}
