#include "part2.h"
#include "common.hpp"

Part2::Part2()
{}

auto Part2::handle_input(std::istream& in) -> size_t
{
  auto point_map = point_map_t{point_t{0, 0}};
  auto point_list = point_list_t{}; 
  point_list.resize(10); // [0]: head, [9]: tail
  
  auto do_line = [&] (auto& input) 
  {
    for (auto s = 0; s < input.steps; ++s)
    {
      for (auto it = point_list.begin(); it < std::prev(point_list.end()); ++it)
      {
        auto& head = *it;
        auto& tail = *std::next(it);

        // Move only first head.
        if (it == point_list.begin())
        {
          head = MoveHead{}(input, head);
        }
        if (!IsAdjacent{1}(head, tail))
        {  
          tail = NextTail{}(head, tail);
        }
      }
      point_map.insert(point_list.back());
    }
  };
  std::ranges::for_each(std::ranges::istream_view<Input>(in), do_line);

  return point_map.size();
}
