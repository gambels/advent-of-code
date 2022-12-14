#include "part1.h"

#include <algorithm>
#include <iterator>

Part1::Part1()
{}

auto Part1::handle_input(std::istream& in) -> std::size_t
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
