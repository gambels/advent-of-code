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
 
inline
auto handshape2points(HandShape shape)
{
  auto points = std::map<HandShape, int>{ {HandShape::ROCK,1}, {HandShape::PAPER,2}, {HandShape::SCISSORS,3} };
  return points[shape];
}

inline
auto gameresult2points(GameResult result)
{
  auto points = std::map<GameResult, int>{ {GameResult::LOST, 0}, {GameResult::DRAW, 3}, {GameResult::WON, 6} };
  return points[result];
}

inline
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
