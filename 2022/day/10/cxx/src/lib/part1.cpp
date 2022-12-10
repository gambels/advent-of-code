#include "part1.h"
#include "common.hpp"

#include <vector>

using namespace aoc;

Part1::Part1()
{}

auto Part1::handle_input(std::istream& in) -> std::size_t
{
  auto sum = 0;
  auto do_signal_strenght = [&sum, xreg = make_register(in)] (auto cycle) 
  {
    sum += cycle * xreg[cycle - 1];
  };
  std::ranges::for_each(std::vector<int>{20, 60, 100, 140, 180, 220}, do_signal_strenght);
  
  return sum;
}
