#include "part2.h"

#include <list>
#include <numeric>

Part2::Part2()
{}

auto Part2::handle_input(std::istream& in) -> size_t
{
  auto n = size_t{0};
  auto list = std::list<size_t>{};
  for (auto line = std::string{}; getline(in, line, '\n'); )
  {
    if (line.empty())
    {
      list.push_back(n);
      n = 0;
    }
    else
    {
      n += std::stoi(line);
    }
  }
  list.sort();

  return std::reduce(list.rbegin(), std::next(list.rbegin(), 3));
}

