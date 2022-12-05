#pragma once

#include "common.hpp"

#include <iostream>

class Part1
{
  public:
    Part1(std::filesystem::path stacks);

    [[nodiscard]] auto handle_input(std::istream& in) -> std::string;

  protected:

  private:
    stacks_t m_stacks = stacks_t{};
};
