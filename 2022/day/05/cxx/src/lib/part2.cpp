#include "part2.h"

#include <algorithm>
#include <ranges>

Part2::Part2(std::filesystem::path stacks) :
  m_stacks{made_stacks(stacks)}
{}

auto Part2::handle_input(std::istream& in) -> std::string
{
    auto do_line = [this] (auto& input) {
#if DEBUG
    std::cout << input.m_count << " " << input.m_from << " " << input.m_to << std::endl;
#endif
    auto& from = this->m_stacks[input.from];
    auto& to = this->m_stacks[input.to];

    auto tmp = std::decay_t<decltype(from)>{};
    for (auto i = 0; i < input.count; ++i)
    {
      tmp.push_back(from.back());
      from.pop_back();
    }
    for (auto elem : tmp | std::views::reverse)
    {
      to.push_back(elem);
    }
  };
  std::ranges::for_each(std::ranges::istream_view<Input>(in), do_line);
  
  return get_code(m_stacks);
}
