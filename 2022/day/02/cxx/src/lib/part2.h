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
          auto do_win = [] (auto shape) {
          auto rv = HandShape{};
          switch (shape)
          {
            case HandShape::ROCK:
              rv = HandShape::PAPER;
              break;
            case HandShape::PAPER:
              rv = HandShape::SCISSORS;
              break;
            case HandShape::SCISSORS:
              rv = HandShape::ROCK;
              break;            
          }
          return rv;
        };
        auto do_loose = [] (auto shape) {
          auto rv = HandShape{};
          switch (shape)
          {
            case HandShape::PAPER:
              rv = HandShape::ROCK;
              break;
            case HandShape::SCISSORS:
              rv = HandShape::PAPER;
              break;
            case HandShape::ROCK:
              rv = HandShape::SCISSORS;
              break;            
          }
          return rv;
        };

        auto rv = HandShape{};    
        switch(auto game_result = input2result[rhs_])
        {
          case GameResult::LOST:
            rv = do_loose(lhs());
            break;

          case GameResult::DRAW:
            rv = lhs();
            break;

          case GameResult::WON:
            rv = do_win(lhs());
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