#include "part1.h"
#include "common.hpp"

Part1::Part1()
{}

auto Part1::handle_input(std::istream& in) -> std::size_t
{
  auto head = point_t{0, 0};
  auto tail = point_t{0, 0};
  auto point_map = point_map_t{tail};

  auto do_line = [&] (auto& input) 
  {
    for (auto i = 0; i < input.steps; ++i)
    {
      head = MoveHead{}(input, head);
      if (!IsAdjacent{1}(head, tail))
      {  
        tail = NextTail{}(head, tail);
        point_map.insert(tail);
      }
    }
  };
  std::ranges::for_each(std::ranges::istream_view<Input>(in), do_line);

  return point_map.size();
}
