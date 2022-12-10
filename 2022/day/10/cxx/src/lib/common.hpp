#pragma once

#include <iostream>
#include <istream>
#include <ranges>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cassert>

static constexpr int XREG_INIT = 1;

namespace aoc
{
  using register_t = std::vector<int>;
  using sprite_t = std::string;

  struct Input
  {
    enum class Opcode
    {
      NOOP, ADDX
    };

    Input() {}

    operator std::string()
    {
      auto ss = std::stringstream{};
      switch (opcode)
      {
        case Opcode::NOOP:
          ss << "noop";
          break;

        case Opcode::ADDX:
          ss << "addx" << " " << xval;
          break;
      }
      return ss.str();
    }

    Opcode opcode = Opcode::NOOP;
    int xval = 0;
  };

  inline
  std::istream& operator>>(std::istream& in, Input::Opcode &code)
  {
    auto str = std::string{};
    in >> str;
    if (str== "addx") code = Input::Opcode::ADDX;
    else if (str == "noop") code = Input::Opcode::NOOP;

    return in;
  }

  inline
  std::istream& operator>>(std::istream& in, Input& input)
  {
    in >> input.opcode;
    switch(input.opcode)
    {
      case Input::Opcode::ADDX:
        in >> input.xval;
        break;
    }
    return in;
  }

  inline
  auto make_register(std::istream& in, int init = XREG_INIT)
  {
    auto reg = register_t{init};
    auto do_line = [&reg] (auto& input)
    {
      switch (input.opcode)
      {
        case Input::Opcode::NOOP:
          reg.push_back(reg.back());
          break;

        case Input::Opcode::ADDX:
          reg.push_back(reg.back());
          reg.push_back(reg.back() + input.xval);
          break;
      }
    };
    std::ranges::for_each(std::ranges::istream_view<Input>(in), do_line);

    return reg;
  }

  inline
  auto make_sprite(int pos, size_t wide)
  {
    auto sprite = sprite_t(wide, '.');
    auto begin = (pos - 1) >= 0 ? (pos - 1) : 0;
    auto end = (pos + 2) >= 0 ? (pos + 2) : 0;
    std::ranges::fill(std::next(sprite.begin(), begin), std::next(sprite.begin(), end), '#');
    
    return sprite;
  }
} // namespace aoc