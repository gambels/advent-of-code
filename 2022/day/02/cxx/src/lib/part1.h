#pragma once

#include "common.hpp"

#include <iostream>

class Part1
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
    
    Part1();

    [[nodiscard]] auto handle_input(std::istream& in) -> size_t;

  protected:

  private:
};

inline
std::istream& operator>>(std::istream& in, Part1::Input& input)
{
  in >> input.lhs_ >> input.rhs_;
  return in;
}
