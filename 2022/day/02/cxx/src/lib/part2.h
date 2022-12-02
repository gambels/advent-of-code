#pragma once

#include "common.hpp"

#include <iostream>

class Part2
{
  public:
    struct Input                                                                                                       
    {
      Input() {}

      auto lhs() -> HandShape
      {
        return input2shape[lhs_];
      }

      auto rhs() -> HandShape
      {
        auto lose_rule_set = std::map<HandShape, HandShape> {
            {HandShape::ROCK, HandShape::SCISSORS},
            {HandShape::PAPER, HandShape::ROCK},
            {HandShape::SCISSORS, HandShape::PAPER}
          };

        auto win_rule_set = std::map<HandShape, HandShape> {
            {HandShape::ROCK, HandShape::PAPER},
            {HandShape::PAPER, HandShape::SCISSORS},
            {HandShape::SCISSORS, HandShape::ROCK}
          };
  
        auto rv = HandShape{};    
        switch(auto game_result = input2result[rhs_])
        {
          case GameResult::LOST:
            rv = lose_rule_set[lhs()];
            break;

          case GameResult::DRAW:
            rv = lhs();
            break;

          case GameResult::WON:
            rv = win_rule_set[lhs()];
            break;
        }
        return rv;
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
        {'C', HandShape::SCISSORS}};

      std::map<char, GameResult> input2result = { 
        {'X', GameResult::LOST},
        {'Y', GameResult::DRAW},
        {'Z', GameResult::WON}};
      };

    Part2();

    [[nodiscard]] auto handle_input(std::istream& in) -> size_t;

  protected:

  private:
};

inline
std::istream& operator>>(std::istream& in, Part2::Input& input)
{
  in >> input.lhs_ >> input.rhs_;
  return in;
}