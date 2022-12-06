#include "part2.h"

#include <ranges>
#include <algorithm>
#include <list>

Part2::Part2()
{}

auto Part2::handle_input(std::istream& in) -> size_t
{
  auto n = 0;
  auto do_line = [&n] (auto& line)
  {
    auto is_unique = [] (auto win) {
        auto n = win.size();
        win.sort();
        win.unique();
      return (win.size() == n);
    };
    auto it = std::next(line.begin(), 14);
    auto win = std::list<char>{line.begin(), it};

    if(!is_unique(win))
    {
      do
      {
        win.pop_front();
        win.push_back(*(it++));
        if (is_unique(win))
        {
          break;
        }
      } while (it != line.end());
    }
    n = std::distance(line.begin(), it);
  };
  std::ranges::for_each(std::ranges::istream_view<std::string>(in), do_line);

  return n;
}
