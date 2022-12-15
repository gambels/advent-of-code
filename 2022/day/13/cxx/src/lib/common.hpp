#pragma once

#include <istream>
#include <sstream>
#include <ranges>
#include <algorithm>

#include <initializer_list>
#include <vector>
#include <variant>
#include <cassert>

namespace aoc
{
  struct List
  {
    using elem_t = std::variant<int, List>;
    using pair_t = std::pair<List, List>;
    using pair_list_t = std::vector<pair_t>;

    List() = default;

    List(std::initializer_list<elem_t> l) :
      _list(l)
    {}

    List(std::string line)
    {
      std::function<List(std::stringstream&)> to_list;
      to_list = [&to_list] (std::stringstream& ss) {
        auto c = char{};
        ss >> c;
        assert(c == '[');

        auto list = List{};
        while (true)
        {
          auto i = int{};
          if (ss >> i)
          {
            list._list.push_back(i);
          }
          else
          {
            ss.clear();
            ss >> c;
            if (c == ',') continue;
            if (c == ']') break;
            if (c == '[') 
            {
              ss.putback(c);
              list._list.push_back(to_list(ss));
            }
          }
        }
        return list;
      };
      auto ss = std::stringstream{std::move(line)};
      _list = std::move(to_list(ss)._list);
    }

    auto operator<(const List& rhs)
    {
      return (compare(*this, rhs) == -1);
    }

    auto operator==(const List& rhs)
    {
      return (compare(*this, rhs) == 0);
    }

    auto operator>(const List& rhs)
    {
      return (compare(*this, rhs) > 0);
    }
    
    auto compare(const List& lhs, const List& rhs) -> int
    {
      auto lhs_size = lhs._list.size();
      auto rhs_size = rhs._list.size();
      auto rv = lhs_size < rhs_size ? -1 : lhs_size == rhs_size ? 0 : 1;

      for (auto i = 0; i < std::min(lhs_size, rhs_size); ++i)
      {
        if (std::holds_alternative<List>(lhs._list[i]) || std::holds_alternative<List>(rhs._list[i]))
        {
          auto to_list = [] (const List::elem_t& elem) -> List{
            if (std::holds_alternative<int>(elem))
            {
              return List{std::get<int>(elem)};
            }
            return std::get<List>(elem);
          };
          auto res = compare(to_list(lhs._list[i]), to_list(rhs._list[i]));
          if (res != 0)
          {
            rv = res;
            break;
          }
        }
        else
        {
          auto lhs_val = std::get<int>(lhs._list[i]);
          auto rhs_val = std::get<int>(rhs._list[i]);
          auto res = lhs_val < rhs_val ? -1 : lhs_val == rhs_val ? 0 : 1;
          if (res != 0)
          {
            rv = res;
            break;
          }
        }
      }
      return rv;
    }

    explicit operator std::string() const
    {
      auto ss = std::stringstream{};
      ss << '[';
      auto separator = std::string{""};
      auto do_stream = [&] (const elem_t& elem) mutable {
        if (std::holds_alternative<int>(elem))
        {
          ss << separator << std::get<int>(elem);
        }
        else
        {
          ss << separator << std::string{std::get<List>(elem)};
        }
        separator = ",";
      };
      std::ranges::for_each(_list, do_stream);
      ss << ']';
      return ss.str();
    }

    std::vector<elem_t> _list;
  };

  struct Input
  {
    Input() {}
    List::pair_t pair;
  };

  inline
  std::istream& operator>>(std::istream& in, Input& input)
  {
    auto line = std::string{};
    for (auto i = 1; getline(in, line); )
    {
      if (line.empty())
      {
        continue;
      }
      if (i == 1)
      {
        input.pair.first = List{line};
      }
      if (i == 2)
      {
        input.pair.second = List{line};
        break;
      }
      ++i;
    }
    return in;
  }

  inline
  auto make_pair_list(std::istream& in)
  {
    auto pair_list = List::pair_list_t{};
    auto do_input = [&] (auto&& input) {
      pair_list.push_back(std::move(input.pair));
    };
    std::ranges::for_each(std::ranges::istream_view<Input>(in), do_input);

    return pair_list;
  }

} // namespace aoc
