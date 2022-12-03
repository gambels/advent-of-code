#pragma once

#include <iostream>
#include <sstream>
#include <array>
#include <vector>

class Part2
{
  public:
    using group_t = std::array<std::string, 3>;
    using groups_t = std::vector<group_t>;

    struct Input
    {
      Input() {}
      group_t _group;

      operator std::string()
      {
        auto ss = std::stringstream{};

        for (auto& elem : _group)
        {
          ss << elem << " ";
        }
        return ss.str();
      }
    };

    Part2();

    [[nodiscard]] auto handle_input(std::istream& in) -> size_t;

  protected:

  private:
};

inline
std::istream& operator>>(std::istream& in, Part2::Input& input)
{
  for (auto n = 0; n < 3; ++n)
  {
    auto str = std::string{};
    in >> str;
    input._group[n] = str;
  }

  return in;
}
