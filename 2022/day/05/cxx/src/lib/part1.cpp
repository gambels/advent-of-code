/**
 * 
    [D]
[N] [C]
[Z] [M] [P]
 1   2   3

*/

#include "part1.h"

#include <algorithm>
#include <ranges>

Part1::Part1(std::filesystem::path stacks) :
  m_stacks{made_stacks(stacks)}
{}

auto Part1::handle_input(std::istream& in) -> std::string
{
  auto do_line = [this] (auto& input) {
#if DEBUG
    std::cout << input.m_count << " " << input.m_from << " " << input.m_to << std::endl;
#endif
    auto& from = this->m_stacks[input.from];
    auto& to = this->m_stacks[input.to];

    for (auto i = 0; i < input.count; ++i)
    {
      to.push_back(from.back());
      from.pop_back();
    }
  };
  std::ranges::for_each(std::ranges::istream_view<Input>(in), do_line);
  
  return get_code(m_stacks);
}
