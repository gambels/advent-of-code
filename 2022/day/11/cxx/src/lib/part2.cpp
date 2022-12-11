#include "part2.h"
#include "common.hpp"

using Part2 = aoc::Part2;

Part2::Part2()
{}

auto Part2::handle_input(std::istream& in) -> size_t
{
  auto monkeys = make_monkey_list(in);
  std::ranges::for_each(std::views::iota(1, 10001), [&monkeys, worry_level_div = make_monkey_lcm(monkeys)] (auto round) { do_monkey_worried_round(monkeys, round, worry_level_div); });
  
  return make_monkey_business(monkeys);
}
