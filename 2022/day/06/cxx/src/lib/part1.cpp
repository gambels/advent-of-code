#include "part1.h"
#include "common.hpp"

#include <ranges>
#include <algorithm>

Part1::Part1()
{}

auto Part1::handle_input(std::istream& in) -> std::size_t
{
  auto parser = Parser{4};
  std::ranges::for_each(std::ranges::istream_view<std::string>(in), std::ref(parser));
  return parser.msg_start();
}
