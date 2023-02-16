#pragma once

#include <string_view>


namespace c_common
{
    template <typename T = char>
    class StringBreaker
    {
    public:
        StringBreaker(const std::string_view &text, T breaker = ' ') :
            p_current(text.data()),
            p_currentlen(0),
            p_end(text.data() + text.length()),
            p_breaker(breaker)
        {}

        bool next()
        {
            p_current += p_currentlen;
            p_currentlen = 0;

            while (p_current != p_end && *p_current == p_breaker) {
                ++p_current;
            }

            auto result = p_current != p_end;

            auto p = p_current;
            while (p != p_end && *p != p_breaker) {
                ++p;
                ++p_currentlen;
            }

            return result;
        }

        std::string_view current() const
        {
            return std::string_view(p_current, p_currentlen);
        }

    private:
        const char  *p_current;
        size_t       p_currentlen;
        const char  *p_end;
        T            p_breaker;
    };
}
