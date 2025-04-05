/*
        common utility types and funcs.

    (c) livingcreative, 2025

    https://github.com/livingcreative/kcommon

    feel free to use and modify
*/

#pragma once

#include "c_stringview.h"


namespace c_common
{
    template <typename T = char>
    class StringBreaker
    {
    public:
        template <typename M = ImmutableSpanData<T>>
        StringBreaker(const StringViewBase<T, M> &text, T breaker = ' ') :
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

        StringViewBase<T> current() const
        {
            return { p_current, p_currentlen };
        }

    private:
        const T  *p_current;
        size_t    p_currentlen;
        const T  *p_end;
        T         p_breaker;
    };


    template <typename T>
    bool ParseIntT(const StringViewBase<T> &text, int &result, int defaultval = 0) noexcept
    {
        auto resultval = defaultval;
        auto p = text.begin();
        auto e = text.end();

        if (p == e) {
            result = defaultval;
            return false;
        }

        auto neg = false;
        switch (*p) {
            case '+': p++; break;
            case '-': p++; neg = true; break;
        }

        while (p != e) {
            if (*p < '0' || *p > '9') {
                result = defaultval;
                return false;
            }
            resultval = resultval * 10 + (*p - '0');
            p++;
        }

        if (neg) {
            resultval = -resultval;
        }

        result = resultval;
        return true;
    }

    // c++ committee eat shit

    inline bool ParseInt(const StringView &text, int &result, int defaultval = 0) noexcept
    {
        return ParseIntT(text, result, defaultval);
    }

    inline bool ParseInt(const StringViewW &text, int &result, int defaultval = 0) noexcept
    {
        return ParseIntT(text, result, defaultval);
    }

    inline bool ParseInt(const StringView32 &text, int &result, int defaultval = 0) noexcept
    {
        return ParseIntT(text, result, defaultval);
    }

    template <typename T>
    bool ParseFloat(const StringViewBase<T> &text, float &result, float defaultval = 0) noexcept
    {
        auto dresult = 0.0;
        auto ret = ParseDouble(text, dresult, defaultval);
        if (ret) {
            result = float(dresult);
        } else {
            result = defaultval;
        }
        return ret;
    }

    template <typename T>
    bool ParseDouble(const StringViewBase<T> &text, double &result, double defaultval = 0) noexcept
    {
        auto resultval = 0.0;
        auto p = text.begin();
        auto e = text.end();

        if (p == e) {
            result = defaultval;
            return false;
        }

        auto neg = false;
        switch (*p) {
            case '+': p++; break;
            case '-': p++; neg = true; break;
        }

        // int part
        while (p != e) {
            if (*p == '.' || *p == 'e' || *p == 'E') {
                break;
            }

            if (*p < '0' || *p > '9') {
                result = defaultval;
                return false;
            }
            resultval = resultval * 10 + (*p - '0');
            p++;
        }

        // frac part
        if (p != e && *p == '.') {
            p++;

            auto frac = 0.0;
            auto scale = 0.1;
            while (p != e) {
                if (*p == 'e' || *p == 'E') {
                    break;
                }

                if (*p < '0' || *p > '9') {
                    result = defaultval;
                    return false;
                }
                frac += scale * (*p - '0');
                scale *= 0.1;
                p++;
            }

            resultval += frac;
        }

        // exp part
        if (p != e && (*p == 'e' || *p == 'E')) {
            p++;

            if (p == e) {
                result = defaultval;
                return false;
            }

            auto neg = false;
            switch (*p) {
                case '+': p++; break;
                case '-': p++; neg = true; break;
            }

            auto exp = 0.0;
            while (p != e) {
                if (*p < '0' || *p > '9') {
                    result = defaultval;
                    return false;
                }
                exp = exp * 10 + (*p - '0');
                p++;
            }

            if (neg) {
                exp = -exp;
            }

            resultval = pow(result, exp);
        }

        if (neg) {
            resultval = -resultval;
        }

        result = resultval;
        return true;
    }
}
