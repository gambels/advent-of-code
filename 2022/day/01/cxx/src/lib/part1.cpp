#include "part1.h"

Part1::Part1()
{}

auto Part1::handle_input(std::istream& in) -> size_t
{
  auto count = size_t{0};
  auto max = count;
  for (auto line = std::string{}; getline(in, line, '\n'); )
  {
    if (line.empty())
    {
      if (count > max)
      {
        max = count;
      }
      count = 0;
    }
    else
    {
      count += std::stoi(line);
    }
  }

  return max;
}
