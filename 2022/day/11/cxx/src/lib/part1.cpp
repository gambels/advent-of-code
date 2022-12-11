#include "part1.h"
#include "common.hpp"

using Part1 = aoc::Part1;

Part1::Part1()
{}

auto Part1::handle_input(std::istream& in) -> size_t
{
  auto monkeys = make_monkey_list(in);
  std::ranges::for_each(std::views::iota(1, 21), [&monkeys, worry_level_div = 3] (auto round) { do_monkey_round(monkeys, round, worry_level_div); });
  
  return make_monkey_business(monkeys);
}
