/*
        common utility types and funcs.

    (c) livingcreative, 2025

    https://github.com/livingcreative/kcommon

    feel free to use and modify
*/

#pragma once

#include "c_string.h"


namespace c_common
{
    template <typename T>
    class StringBuilderStaticReallocator
    {
    public:
        static void Resize(T* &buffer, size_t &capacity, size_t size) {}
    };

    template <typename T, typename N = StringExcludeNull, typename R = StringBuilderStaticReallocator<T>>
    class StringBuilderBase
    {
    protected:
        constexpr StringBuilderBase(T *buffer, size_t capacity = 0) noexcept :
            p_buffer(buffer),
            p_size(0),
            p_capacity(capacity)
        {
            // assert capacity > 0
            if constexpr (N::NULL_LEN) {
                *p_buffer = 0;
            }
        }

    public:
        constexpr const T *data() const noexcept { return p_buffer; }
        constexpr size_t size() const noexcept { return p_size; }
        constexpr size_t capacity() const noexcept { return p_capacity; }

        StringViewBase<T> text() const { return StringViewBase<T>(p_buffer, p_size); }

        void Write(const StringViewBase<T> &text)
        {
            Write(text.data(), text.size());
        }

        void Write(const T *data, size_t size)
        {
            auto reqsize = size;
            if (p_width != -1 && p_width > reqsize) {
                reqsize = p_width;
            }

            R::Resize(p_buffer, p_capacity, p_size + reqsize);

            if (p_size >= (p_capacity - N::NULL_LEN)) {
                return;
            }
            if ((p_size + reqsize + N::NULL_LEN) > p_capacity) {
                reqsize = p_capacity - p_size - N::NULL_LEN;
            }
            if (reqsize < size) {
                size = reqsize;
            }

            if (size < reqsize) {
                auto p = p_buffer + p_size;
                for (auto n = size; n < reqsize; ++n) {
                    *p++ = p_textfill;
                }
                p_size += reqsize - size;
            }

            memcpy(p_buffer + p_size, data, size * sizeof(T));
            p_size += size;

            if constexpr (N::NULL_LEN) {
                *(p_buffer + p_size) = 0;
            }

            p_precision = -1;
            p_width = -1;
        }

        void Write(long long int value)
        {
            T buffer[24];
            auto size = size_t(0);
            auto negative = value < 0;
            if (negative) {
                value = -value;
            }
            ToString(buffer, 24, size, (long long unsigned)value);
            if (negative) {
                *(buffer + 23 - size) = '-';
                ++size;
            }
            Write(buffer + 24 - size, size);
        }

        void Write(long long unsigned value)
        {
            T buffer[24];
            auto size = size_t(0);
            ToString(buffer, 24, size, value);
            Write(buffer + 24 - size, size);
        }

        void Write(double value)
        {
            T buffer[512];
            auto size = size_t(0);
            ToString(buffer, 512, size, value);
            Write(buffer, size);
        }

        void Revert(size_t count = 1)
        {
            if (count > p_size) {
                count = p_size;
            }
            p_size -= count;
        }

        void Clear()
        {
            p_size = 0;

            if constexpr (N::NULL_LEN) {
                *p_buffer = 0;
            }
        }

        void precision(unsigned p)
        {
            p_precision = p;
        }

        void width(unsigned w)
        {
            p_width = w;
        }

    protected:
        void ToString(T *buffer, size_t capacity, size_t &size, long long unsigned value)
        {
            auto n = capacity;

            if (value == 0) {
                buffer[--n] = '0';
                ++size;
            }

            while (value > 0 && n > 0) {
                auto d = value % 10;
                buffer[--n] = T(d) + '0';
                ++size;
                value /= 10;
            }

            if (p_width != -1 && size < p_width) {
                while (n > 0 && size < p_width) {
                    buffer[--n] = p_numberfill;
                    ++size;
                }
            }
        }

        void ToString(T *buffer, size_t capacity, size_t &size, double value)
        {
            auto p = buffer;
            auto negative = value < 0;
            if (negative) {
                value = -value;
                *p++ = '-';
                ++size;
            }

            auto integer = floor(value);
            auto fraction = value - integer;

            if (p_precision != -1) {
                if (p_precision == 0) {
                    integer += round(fraction);
                    fraction = 0;
                } else {
                    auto pp = pow(10, p_precision);
                    fraction = round(fraction * pp) / pp;
                }
            }

            // removing trailing zeroes from integer part
            auto zeroes = 0u;
            while (integer > 0xFFFFFFFFFFFFull) {
                integer *= .1;
                zeroes++;
            }

            auto digits = size_t(0);
            ToString(p, 16, digits, (unsigned long long)integer);
            memmove(p, p + 16 - digits, digits * sizeof(T));
            p += digits;
            size += digits;

            for (auto n = 0u; n < zeroes; ++n) {
                *p++ = '0';
                size++;
            }

            if (p_precision == 0) {
                return;
            }

            *p++ = '.';
            size++;

            // removing "leading" zeroes from a fractional part
            zeroes = 0u;
            if (fraction > 0) {
                while (fraction < 0.0000000000000001) {
                    fraction *= 10;
                    zeroes++;
                }
            }

            for (auto n = 0u; n < zeroes; ++n) {
                *p++ = '0';
                size++;
            }

            digits = size_t(0);
            ToString(p, 16, digits, (unsigned long long)(fraction * 10e15));

            // fill leading fractional zeroes up to 16 digits
            for (auto n = 0u; n < (16 - digits); ++n) {
                *p++ = '0';
            }

            if (p_precision != -1) {
                if (p_precision < 16) {
                    digits = p_precision;
                } else {
                    digits = 16;
                    p += digits;
                    while (digits < p_precision) {
                        *p++ = '0';
                        digits++;
                    }
                }
            }

            size += digits;
        }

    protected:
        T        *p_buffer;
        size_t    p_size;
        size_t    p_capacity;
        unsigned  p_width = -1;       // next write width
        unsigned  p_precision = -1;   // next number write precision
        T         p_textfill = ' ';   // width fill for text writes
        T         p_numberfill = '0'; // numbers leading fill
    };


    template <typename T, typename N, typename R>
    StringBuilderBase<T, N, R> &operator<<(StringBuilderBase<T, N, R> &sb, int value)
    {
        sb.Write((long long int)value);
        return sb;
    }

    template <typename T, typename N, typename R>
    StringBuilderBase<T, N, R> &operator<<(StringBuilderBase<T, N, R> &sb, long int value)
    {
        sb.Write((long long int)value);
        return sb;
    }

    template <typename T, typename N, typename R>
    StringBuilderBase<T, N, R> &operator<<(StringBuilderBase<T, N, R> &sb, long long int value)
    {
        sb.Write((long long int)value);
        return sb;
    }

    template <typename T, typename N, typename R>
    StringBuilderBase<T, N, R> &operator<<(StringBuilderBase<T, N, R> &sb, unsigned value)
    {
        sb.Write((long long unsigned)value);
        return sb;
    }

    template <typename T, typename N, typename R>
    StringBuilderBase<T, N, R> &operator<<(StringBuilderBase<T, N, R> &sb, long unsigned value)
    {
        sb.Write((long long unsigned)value);
        return sb;
    }

    template <typename T, typename N, typename R>
    StringBuilderBase<T, N, R> &operator<<(StringBuilderBase<T, N, R> &sb, long long unsigned value)
    {
        sb.Write(value);
        return sb;
    }

    template <typename T, typename N, typename R>
    StringBuilderBase<T, N, R> &operator<<(StringBuilderBase<T, N, R> &sb, float value)
    {
        sb.Write(value);
        return sb;
    }

    template <typename T, typename N, typename R>
    StringBuilderBase<T, N, R> &operator<<(StringBuilderBase<T, N, R> &sb, double value)
    {
        sb.Write(value);
        return sb;
    }

    template <typename T, typename N, typename R>
    StringBuilderBase<T, N, R> &operator<<(StringBuilderBase<T, N, R> &sb, T value)
    {
        sb.Write({ &value, 1 });
        return sb;
    }

    template <typename T, typename N, typename R>
    StringBuilderBase<T, N, R> &operator<<(StringBuilderBase<T, N, R> &sb, const StringViewBase<T> &value)
    {
        sb.Write(value);
        return sb;
    }

    template <typename T, typename N, typename R, typename NN>
    StringBuilderBase<T, N, R> &operator<<(StringBuilderBase<T, N, R> &sb, const StringBase<T, NN> &value)
    {
        sb.Write(value);
        return sb;
    }

    template <typename T, typename N, typename R, typename NN>
    StringBuilderBase<T, N, R> &operator<<(StringBuilderBase<T, N, R> &sb, const MutableStringBase<T, NN> &value)
    {
        sb.Write(value);
        return sb;
    }

    template <typename T, typename N, typename R, size_t length>
    StringBuilderBase<T, N, R> &operator<<(StringBuilderBase<T, N, R> &sb, const T(&value)[length])
    {
        sb.Write(value, length - 1);
        return sb;
    }


    template <typename T, size_t capacity, typename N = StringExcludeNull>
    class StaticStringBuilderBase : public StringBuilderBase<T, N>
    {
    public:
        StaticStringBuilderBase() :
            StringBuilderBase<T, N>(p_staticbuffer, capacity)
        {}

    private:
        T p_staticbuffer[capacity];
    };

    template <size_t capacity>
    using StaticStringBuilder = StaticStringBuilderBase<char, capacity>;

    template <size_t capacity>
    using StaticStringBuilderW = StaticStringBuilderBase<wchar_t, capacity>;

    template <size_t capacity>
    using StaticStringBuilder32 = StaticStringBuilderBase<char32_t, capacity>;


    template <typename T, typename N = StringExcludeNull>
    class FixedStringBuilderBase : public StringBuilderBase<T, N>
    {
    public:
        FixedStringBuilderBase(size_t capacity) :
            StringBuilderBase<T, N>(new T[capacity], capacity)
        {}

        ~FixedStringBuilderBase()
        {
            delete[] this->p_buffer;
        }

        StringBase<T, N> MoveToString()
        {
            StringBase<T, N> result(this->p_buffer, this->p_size);

            this->p_buffer = nullptr;
            this->p_size = 0;

            return result;
        }

        MutableStringBase<T, N> MoveToMutableString()
        {
            MutableStringBase<T, N> result;

            result.p_data = this->p_buffer;
            result.p_size = this->p_size;
            result.p_capacity = this->p_size + N::NULL_LEN;

            this->p_buffer = nullptr;
            this->p_size = 0;

            return result;
        }
    };

    using FixedStringBuilder = FixedStringBuilderBase<char>;
    using FixedStringBuilderW = FixedStringBuilderBase<wchar_t>;
    using FixedStringBuilder32 = FixedStringBuilderBase<char32_t>;
    using FixedStringBuilderNT = FixedStringBuilderBase<char, StringIncludeNull>;
    using FixedStringBuilderWNT = FixedStringBuilderBase<wchar_t, StringIncludeNull>;
    using FixedStringBuilder32NT = FixedStringBuilderBase<char32_t, StringIncludeNull>;


    template <typename T>
    class StringBuilderDefaultReallocator
    {
    public:
        static void Resize(T* &buffer, size_t &capacity, size_t size)
        {
            if (size > capacity) {
                auto newcapacity = capacity + 1024;
                auto newbuffer = new T[newcapacity];

                memcpy(newbuffer, buffer, capacity * sizeof(T));

                delete[] buffer;

                buffer = newbuffer;
                capacity = newcapacity;
            }
        }
    };


    template <typename T, typename N = StringExcludeNull>
    class DynamicStringBuilderBase : public StringBuilderBase<T, N, StringBuilderDefaultReallocator<T>>
    {
    public:
        DynamicStringBuilderBase(size_t initialcapacity = 1024) :
            StringBuilderBase<T, N, StringBuilderDefaultReallocator<T>>(new T[initialcapacity], initialcapacity)
        {}

        ~DynamicStringBuilderBase()
        {
            delete[] this->p_buffer;
        }

        StringBase<T, N> MoveToString()
        {
            StringBase<T, N> result;

            result.p_data = this->p_buffer;
            result.p_size = this->p_size;

            this->p_buffer = nullptr;
            this->p_size = 0;
            this->p_capacity = 0;

            return result;
        }

        MutableStringBase<T, N> MoveToMutableString()
        {
            MutableStringBase<T, N> result;

            result.p_data = this->p_buffer;
            result.p_size = this->p_size;
            result.p_capacity = this->p_capacity;

            this->p_buffer = nullptr;
            this->p_size = 0;
            this->p_capacity = 0;

            return result;
        }
    };

    using StringBuilder = DynamicStringBuilderBase<char>;
    using StringBuilderW = DynamicStringBuilderBase<wchar_t>;
    using StringBuilder32 = DynamicStringBuilderBase<char32_t>;
    using StringBuilderNT = DynamicStringBuilderBase<char, StringIncludeNull>;
    using StringBuilderWNT = DynamicStringBuilderBase<wchar_t, StringIncludeNull>;
    using StringBuilder32NT = DynamicStringBuilderBase<char32_t, StringIncludeNull>;


    template <typename T, typename N = StringExcludeNull>
    class BakedStringBuilderBase : public StringBuilderBase<T, N, StringBuilderDefaultReallocator<T>>
    {
    public:
        // TODO
    };
}
