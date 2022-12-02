/*
  Column 1     Column 2       Points
  A: Rock      X: Rock        1
  B: Paper     Y: Paper       2
  C: Scissors  Z: Scissors    3

  Points
  Lost: 0
  Draw: 3
  Won : 6

  For example, suppose you were given the following strategy guide:

  A Y : Rock Paper (2)        : Lost (6) : 8
  B X : Paper Rock (1)        : Lost (0) : 1
  C Z : Scissors Scissors (3) : Draw (3) : 6

  Paper    > Rock
  Rock     > Scissors
  Scissors > Paper

  Total: 15
*/

#include "part1.h"
#include "common.hpp"

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
