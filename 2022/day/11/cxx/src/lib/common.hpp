#pragma once

#include <iostream>
#include <istream>
#include <sstream>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <regex>
#include <vector>
#include <list>

namespace aoc
{
  static constexpr auto STREAM_SIZE_MAX = std::numeric_limits<std::streamsize>::max();

  struct Operation
  {
    enum class Instruction
    {
      ADD, MUL, NOOP
    };

    Operation() =default;

    Operation(Instruction ins) :
      _ins{ins}
    {}

    Operation(Instruction ins, int val) :
      _ins{ins},
      _val{val},
      _with_val{true}
    {}

    auto operator() (int64_t old)
    {
      auto val = _with_val ? _val : old;
      switch (_ins)
      {
        case Instruction::ADD : old += val; break;
        case Instruction::MUL : old *= val; break;
      }
      ++_items_inspected;
      return old;  
    }

    operator std::string()
    {
      auto ss = std::stringstream{};
      ss << "( old" << " " << (_ins == Instruction::ADD ? "+ " : "* ") << (_with_val ? std::to_string(_val) : "old") << ", inspects= " << _items_inspected << " )";
      return ss.str();
    }

    Instruction _ins = Instruction::NOOP;
    int64_t _val = 0;
    bool _with_val = false;
    size_t _items_inspected = 0;
  };

  struct Test
  {
    Test() =default;

    operator std::string()
    {
      auto ss = std::stringstream{};
      ss << "( div=" << _div << ", if_true=" << _if_true << ", if_false=" << _if_false << " )";
      return ss.str();
    }

    int _div = -1;
    int _if_true = -1;
    int _if_false = -1;
  };

  struct Monkey
  {
    using list_t = std::vector<Monkey>;
    using items_t = std::vector<int64_t>;

    Monkey() =default;

    operator std::string()
    {
      auto ss = std::stringstream{};
      ss << "Monkey: id=" << _id << ", items=( ";
      std::ranges::for_each(_items, [&ss] (auto item) {ss << item << " ";});
      ss << "), operation=" << std::string{_operation} << ", test=" << std::string{_test};
      return ss.str();
    }

    size_t _id = 0;
    items_t _items = items_t{};
    Operation _operation = Operation{};
    Test _test = Test{};
  };

  inline
  std::istream& operator>>(std::istream& in, Monkey& monkey)
  {
    auto do_str2int = [] (auto& line) 
    {
      auto v = std::vector<int64_t>{};
      auto do_add = [&v] (auto& it)
      {
        auto i = std::stoi(it.str()); 
        v.push_back(i);
      };
      auto regx = std::regex{"[0-9]+"};
      std::ranges::for_each(std::sregex_iterator(std::begin(line), std::end(line), regx), std::sregex_iterator(), do_add);
      return v;
    };

    auto do_str2operation = [] (auto& line)
    {
      auto lhs = std::string{};
      auto ins = char{};
      auto rhs = std::string{};
      
      auto ss = std::stringstream{line};
      ss.ignore(STREAM_SIZE_MAX, '=');
      ss >> lhs >> ins >> rhs;

      auto oper_ins = Operation::Instruction{};
      
      switch (ins)
      {
        case '+': oper_ins = Operation::Instruction::ADD; break; 
        case '*': oper_ins = Operation::Instruction::MUL; break;
      }
      return (rhs == "old") ? Operation{oper_ins} : Operation{oper_ins, std::stoi(rhs)};
    };

    auto line = std::string{};
    while (getline(in, line))
    {
      if (line.find("Monkey") != std::string::npos)
      {  
        monkey._id = do_str2int(line).front();
      }
      else if (line.find("Starting items") != std::string::npos)
      { 
        monkey._items = do_str2int(line);
      }
      else if (line.find("Operation") != std::string::npos)
      {
        monkey._operation = do_str2operation(line);
      }
      else if (line.find("Test") != std::string::npos)
      {
        monkey._test._div = do_str2int(line).front();
        if (getline(in, line); line.find("If true") != std::string::npos)
        {
          monkey._test._if_true = do_str2int(line).front();
        }
        if (getline(in, line); line.find("If false") != std::string::npos)
        {
          monkey._test._if_false = do_str2int(line).front();
          break;
        }
      }
    } 
    return in;
  }

  inline
  auto make_monkey_list(std::istream& in)
  {
    auto monkeys = Monkey::list_t{};
    auto do_read_monkey = [&] (auto& monkey)
    {
      monkeys.push_back(std::move(monkey));
    };
    std::ranges::for_each(std::ranges::istream_view<Monkey>(in), do_read_monkey);
    return monkeys;
  }

  inline
  auto make_monkey_business(auto& monkeys)
  {
    auto inspections = std::list<size_t>{};
    std::ranges::for_each(monkeys, [&inspections] (auto& monkey) { inspections.push_back(monkey._operation._items_inspected);});
    inspections.sort(std::greater<size_t>());
  
    return (*inspections.begin()) * (*std::next(inspections.begin()));
  }

  inline
  auto make_monkey_lcm(auto& monkeys)
  {
    auto lcm = 1;
    auto do_lcm = [&lcm] (auto& monkey) 
    {
      lcm = std::lcm(lcm, monkey._test._div);
    };
    std::ranges::for_each(monkeys, do_lcm);
    return lcm;
  }

  inline
  auto do_monkey_round(auto& monkeys, auto round, auto worry_level_div)
  {
    auto do_inspect = [&monkeys, worry_level_div] (auto& monkey)
    {
      for (auto item = std::begin(monkey._items); item != std::end(monkey._items); )
      {
        auto worry_level = monkey._operation(*item) / worry_level_div;
        auto next_monkey_id = (worry_level % monkey._test._div == 0) ? monkey._test._if_true : monkey._test._if_false;

        monkeys[next_monkey_id]._items.push_back(worry_level);
        monkey._items.erase(item);
      }
    };
    std::ranges::for_each(monkeys, do_inspect);

#if 0
    if (true)
    {
      std::cout << "After round " << round << std::endl;
      std::ranges::for_each(monkeys, [] (auto& monkey) { std::cout << std::string{monkey} << std::endl;});
      std::cout << std::endl;
    }
#endif
  }

  inline
  auto do_monkey_worried_round(auto& monkeys, auto round, auto worry_level_div)
  {
    auto do_inspect = [&monkeys, worry_level_div] (auto& monkey)
    {
      for (auto item = std::begin(monkey._items); item != std::end(monkey._items); )
      {
        auto worry_level = monkey._operation(*item) % worry_level_div;
        auto next_monkey_id = (worry_level % monkey._test._div == 0) ? monkey._test._if_true : monkey._test._if_false;

        monkeys[next_monkey_id]._items.push_back(worry_level);
        monkey._items.erase(item);
      }
    };
    std::ranges::for_each(monkeys, do_inspect);

#if 0
    if (true)
    {
      std::cout << "After round " << round << std::endl;
      std::ranges::for_each(monkeys, [] (auto& monkey) { std::cout << std::string{monkey} << std::endl;});
      std::cout << std::endl;
    }
#endif
  }

} // namespace aoc
