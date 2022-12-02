#pragma once

#include <map>
#include <sstream>

enum class HandShape
{
  ROCK, PAPER, SCISSORS
};

enum class GameResult
{
  LOST, DRAW, WON
};
 
auto handshape2points(HandShape shape)
{
  auto points = std::map<HandShape, int>{ {HandShape::ROCK,1}, {HandShape::PAPER,2}, {HandShape::SCISSORS,3} };
  return points[shape];
}

auto gameresult2points(GameResult result)
{
  auto points = std::map<GameResult, int>{ {GameResult::LOST, 0}, {GameResult::DRAW, 3}, {GameResult::WON, 6} };
  return points[result];
}

auto do_play (HandShape player, HandShape enemy)
{
  auto rv = GameResult{GameResult::DRAW};

  switch (player)
  {
    case HandShape::ROCK:
      switch (enemy)
      {
        case HandShape::PAPER:
          rv = GameResult::LOST;
          break;
        case HandShape::SCISSORS:
          rv = GameResult::WON;
          break;
      }
      break;

    case HandShape::PAPER:
      switch (enemy)
      {
        case HandShape::SCISSORS:
          rv = GameResult::LOST;
          break;
        case HandShape::ROCK:
          rv = GameResult::WON;
          break;
      }
      break;

    case HandShape::SCISSORS:
      switch (enemy)
      {
        case HandShape::ROCK:
          rv = GameResult::LOST;
          break;
        case HandShape::PAPER:
          rv = GameResult::WON;
          break;
      }
      break;
  }

 return rv;
}

struct Input                                                                                                                       
{
  Input() {}

  auto lhs() -> HandShape
  {
    return input2shape[lhs_];
  }

  auto rhs() -> HandShape
  {
    return input2shape[rhs_];
  }

  explicit operator std::string() const
  {
    auto ss = std::stringstream{};
    ss << lhs_ << " " << rhs_;
    return ss.str();
  }

  char lhs_;
  char rhs_;

  std::map<char, HandShape> input2shape = { 
    {'A', HandShape::ROCK},
    {'B', HandShape::PAPER},
    {'C', HandShape::SCISSORS},
    {'X', HandShape::ROCK},
    {'Y', HandShape::PAPER},
    {'Z', HandShape::SCISSORS}};
};

std::istream& operator>>(std::istream& in, Input& input)
{
  in >> input.lhs_ >> input.rhs_;
  return in;
}
