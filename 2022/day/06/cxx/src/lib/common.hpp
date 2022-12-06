#pragma once

#include <string>
#include <list>

class Parser
{
    public:
        Parser(size_t marker_len) :
          m_marker_len{marker_len}
         {}

        [[nodiscard]] auto msg_start() -> size_t;

        auto operator() (std::string& input) -> void;

    protected:

    private:
        const size_t m_marker_len = 0;
        size_t m_msg_start = 0;
};

inline 
auto Parser::msg_start() -> size_t
{
    return m_msg_start;
}

inline
auto Parser::operator() (std::string& input) -> void
{
    auto it = std::next(input.begin(), m_marker_len);
    auto win = std::list<char>{input.begin(), it};

    auto is_unique = [] (auto win) {
        win.sort();
        return std::adjacent_find(std::begin(win), std::end(win)) == std::end(win);
    };
    
    if(!is_unique(win))
    {
      for (; it != input.end(); ++it)
      {
        win.pop_front();
        win.push_back(*it);
        if (is_unique(win))
        {
          ++it;
          break;
        }
      }
    }
    m_msg_start = std::distance(input.begin(), it);
}
