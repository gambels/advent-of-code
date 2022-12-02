#include "part2.h"
#include "common.hpp"

#include <algorithm>
#include <iterator>

Part2::Part2()
{}

auto Part2::handle_input(std::istream& in) -> std::size_t
{
  auto points = 0;
  auto handle_round = [&] (auto input) mutable {
    //std::cout << std::string{input} << std::endl;
    auto enemy = input.lhs();
    auto player = input.rhs();
    points += gameresult2points(do_play(player, enemy)) + handshape2points(player);
  };
  std::for_each(std::istream_iterator<Input>{in}, std::istream_iterator<Input>{}, handle_round); 

  return points;
}