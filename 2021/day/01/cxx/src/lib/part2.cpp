#include "part2.h"

#include <algorithm>
#include <numeric>
#include <iterator>
#include <limits>
#include <list>

#define WINDOW_SIZE 3

using window_t = std::list<int>;

Part2::Part2()
{}

auto Part2::handle_input(std::istream& in) -> size_t
{
  auto list = std::list<int>{};
  for_each(std::istream_iterator<int>{in}, std::istream_iterator<int>{}, [&list, window = window_t{}] (auto cur) mutable
     {
        window.push_back(cur);
        if (window.size() == 3)
        {
          list.push_back(std::accumulate(std::begin(window), std::end(window), 0));
          window.pop_front();
        }
     }
  );

  auto is_greater = [prev = std::numeric_limits<int>::max()] (auto cur) mutable {
    return std::exchange(prev, cur) < cur;
  };
  return count_if(list.begin(), list.end(), is_greater);
}

