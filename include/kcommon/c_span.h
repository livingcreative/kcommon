/*
        common utility types and funcs.

    (c) livingcreative, 2025

    https://github.com/livingcreative/kcommon

    feel free to use and modify
*/

#pragma once

#include <cassert>


namespace c_common
{
    template <typename T>
    struct ImmutableSpanData final
    {
        using interface_type = typename const T;
        using storage_type = typename const T;
    };

    template <typename T>
    struct MutableSpanData final
    {
        using interface_type = typename T;
        using storage_type = typename T;
    };


    template <typename T, typename M = ImmutableSpanData<T>>
    class Span
    {
    public:
        using value_type = T;
        using data_type = typename M::interface_type;

    public:
        constexpr Span() noexcept :
            p_data(nullptr),
            p_size(0)
        {}

        constexpr Span(typename M::storage_type *data, size_t size) noexcept :
            p_data(data),
            p_size(size)
        {}

        template <size_t length>
        constexpr Span(typename M::storage_type(&data)[length]) noexcept :
            p_data(data),
            p_size(length)
        {}

        constexpr Span(const std::initializer_list<T> &source) noexcept :
            p_data(std::data(source)),
            p_size(source.size())
        {}

        constexpr Span(const Span<T, M> &other) noexcept :
            p_data(other.p_data),
            p_size(other.p_size)
        {}

        constexpr Span<T, M> &operator=(const Span<T, M> &other) noexcept
        {
            this->p_data = other.p_data;
            this->p_size = other.p_size;
            return *this;
        }

        constexpr data_type *begin() const noexcept { return p_data; }
        constexpr data_type *end() const noexcept { return p_data + p_size; }

        constexpr bool empty() const noexcept { return p_size == 0; }

        constexpr data_type *data() const noexcept { return p_data; }
        constexpr size_t size() const noexcept { return p_size; }

        constexpr Span<T, M> slice(size_t start) const noexcept
        {
            return slice(start, p_size - start);
        }

        constexpr Span<T, M> slice(size_t start, size_t size) const noexcept
        {
            if (start >= p_size) {
                return {};
            }

            if ((start + size) > p_size) {
                size = p_size - start;
            }

            return Span<T, M>(p_data + start, size);
        }

        data_type &at(size_t index) const { assert(index < p_size); return p_data[index]; }
        data_type &operator[](size_t index) const { assert(index < p_size); return p_data[index]; }
        data_type &front() const { assert(p_size); return *p_data; }
        data_type &back() const { assert(p_size); return *(p_data + p_size - 1); }

        void ChopStart(size_t count)
        {
            if (count < p_size) {
                p_data += count;
                p_size -= count;
            }
        }

        void ChopEnd(size_t count)
        {
            if (count < p_size) {
                p_size -= count;
            }
        }

    protected:
        typename M::storage_type *p_data;
        size_t                    p_size;
    };
}
