#pragma once

#include <iostream>
#include <utility>

class Part1
{
  public:
    struct Input
    {
      Input() {}

      [[nodiscard]] auto a()
      {

      }

      [[nodiscard]] auto b()
      {

      }

      [[nodiscard]] auto transform(auto first, auto last)
      {
        
      }

      std::pair<int, int> _a;
      std::pair<int, int> _b;
    };
    Part1();

    [[nodiscard]] auto handle_input(std::istream& in) -> size_t;

  protected:

  private:
};

inline 
std::istream& operator>>(std::istream& in, Part1::Input& input)
{
  auto c = char{};
  in >> input._a.first >> c >> input._a.second >> c >> input._b.first >> c >> input._b.second;

  return in;
}
