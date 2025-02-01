/*
        common utility types and funcs.

    (c) livingcreative, 2025

    https://github.com/livingcreative/kcommon

    feel free to use and modify
*/

#pragma once

#include "c_span.h"
#include <memory>


namespace c_common
{
    template <typename T>
    class StringViewReverseIterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

    public:
        StringViewReverseIterator() :
            p_it(nullptr)
        {}

        StringViewReverseIterator(T *it) :
            p_it(it)
        {}

        T &operator*() const { return *p_it; }
        T &operator->() const { return *p_it; }

        StringViewReverseIterator<T> &operator++() { --p_it; return *this; }
        bool operator==(const StringViewReverseIterator<T> &other) const { return p_it == other.p_it; }
        bool operator!=(const StringViewReverseIterator<T> &other) const { return p_it != other.p_it; }

        size_t operator-(const StringViewReverseIterator<T> &other) const { return other.p_it - p_it; }

    private:
        T *p_it;
    };

    template <typename T, typename M = ImmutableSpanData<T>>
    class StringViewBase : public Span<T, M>
    {
    public:
        constexpr StringViewBase() noexcept :
            Span<T, M>()
        {}

        constexpr StringViewBase(typename M::storage_type *data, size_t size) noexcept :
            Span<T, M>(data, size)
        {}

        template <size_t length>
        constexpr StringViewBase(typename M::storage_type(&text)[length]) noexcept :
            Span<T, M>(text, length - 1)
        {}

        constexpr StringViewBase(const StringViewBase<T, M> &source) noexcept :
            Span<T, M>(source.data(), source.size())
        {}

        template <typename MM>
        constexpr StringViewBase(const StringViewBase<T, MM> &source) noexcept :
            Span<T, M>(source.data(), source.size())
        {}

        constexpr StringViewBase<T, M> &operator=(const StringViewBase<T, M> &source) noexcept
        {
            this->p_data = source.p_data;
            this->p_size = source.p_size;
            return *this;
        }

        size_t length() const { return this->p_size; }

        StringViewReverseIterator<typename M::interface_type> rbegin() const noexcept
        {
            return { end() - 1 };
        }

        StringViewReverseIterator<typename M::interface_type> rend() const noexcept
        {
            return { begin() - 1 };
        }

        constexpr StringViewBase<T, M> substr(size_t start) const noexcept
        {
            return substr(start, this->p_size - start);
        }

        constexpr StringViewBase<T, M> substr(size_t start, size_t size) const noexcept
        {
            auto sliced = Span<T, M>::slice(start, size);
            return StringViewBase<T, M>(sliced.data(), sliced.size());
        }

        constexpr size_t find(T ch, size_t start = 0) const noexcept
        {
            if (start >= this->p_size) {
                return -1;
            }

            auto c = this->p_data + start;
            for (auto n = start; n < this->p_size; ++n, ++c) {
                if (*c == ch) {
                    return n;
                }
            }

            return -1;
        }

        constexpr size_t find(const StringViewBase<T, M> &substr, size_t start = 0) const noexcept
        {
            if ((start + substr.size()) >= this->p_size) {
                return -1;
            }

            auto end = this->p_size - substr.size();
            for (auto n = start; n < end; ++n) {
                if (substr == slice(n, substr.size())) {
                    return n;
                }
            }

            return -1;
        }

        constexpr bool contains(T rangestart, T rangeend) const noexcept
        {
            for (auto c : *this) {
                if (c >= rangestart && c <= rangeend) {
                    return true;
                }
            }

            return false;
        }

        constexpr bool contains(const StringViewBase<T, M> &substr, size_t start = 0) const noexcept
        {
            return find(substr) != -1;
        }

        constexpr size_t rfind(T ch) const noexcept { return rfind(ch, this->p_size); }
        constexpr size_t rfind(T ch, size_t end) const noexcept
        {
            if (end > this->p_size || end == 0) {
                return -1;
            }

            auto c = this->end();
            for (auto n = end; n > 0;) {
                --c;
                --n;
                if (*c == ch) {
                    return n;
                }
            }

            return -1;
        }

        constexpr size_t rfind(const StringViewBase<T, M> &substr) const noexcept { return rfind(substr, this->p_size); }
        constexpr size_t rfind(const StringViewBase<T, M> &substr, size_t end) const noexcept
        {
            return -1;
        }

        constexpr StringViewBase<T, M> trim(size_t size) const noexcept { return slice(0, size); }
        constexpr StringViewBase<T, M> rtrim(size_t size) const noexcept { return slice(this->p_size - size, size); }

        constexpr StringViewBase<T, M> trim() const noexcept
        {
            auto f = firstnonspace();
            auto l = lastnonspace();
            return slice(f, l - f + 1);
        }

        constexpr StringViewBase<T, M> ltrim() const noexcept
        {
            return slice(firstnonspace());
        }

        constexpr StringViewBase<T, M> rtrim() const noexcept
        {
            return slice(0, lastnonspace() + 1);
        }

        constexpr size_t firstnonspace() const noexcept
        {
            // TODO make consistent returns and figure out if -1 result is needed
            //if (this->p_size == 0) {
            //    return -1;
            //}

            auto n = size_t(0);
            auto c = this->p_data;
            while (n < this->p_size && *c >= 0 && *c <= ' ') {
                ++n;
                ++c;
            }
            return n;
        }

        // TODO consider returning +1 so it points to one char after?
        constexpr size_t lastnonspace() const noexcept
        {
            //if (this->p_size == 0) {
            //    return -1;
            //}

            auto n = this->p_size;
            auto c = this->p_data + n - 1;
            while (n > 0 && *c >= 0 && *c <= ' ') {
                --n;
                --c;
            }

            return n;
        }

        constexpr bool startswith(const StringViewBase<T, M> &other) const noexcept
        {
            return slice(0, other.size()) == other;
        }

        constexpr bool endswith(const StringViewBase<T, M> &other) const noexcept
        {
            return slice(this->p_size - other.size(), other.size()) == other;
        }

        constexpr void remove_prefix(size_t count) noexcept { this->ChopStart(count); }
        constexpr void remove_suffix(size_t count) noexcept { this->ChopEnd(count); }

        template <typename MM>
        bool operator==(const StringViewBase<T, MM> &other) const noexcept
        {
            if (this->p_size != other.size()) {
                return false;
            }
            return memcmp(this->p_data, other.data(), this->p_size * sizeof(T)) == 0;
        }

        template <typename MM>
        bool operator!=(const StringViewBase<T, MM> &other) const noexcept
        {
            if (this->p_size != other.size()) {
                return true;
            }
            return memcmp(this->p_data, other.data(), this->p_size * sizeof(T)) != 0;
        }

        template <size_t length>
        constexpr bool operator==(const T(&text)[length]) const noexcept
        {
            return *this == StringViewBase<T>(text);
        }

        template <typename MM>
        bool operator<(const StringViewBase<T, MM> &other) const noexcept
        {
            auto minsize = this->p_size;
            if (other.size() < minsize) {
                minsize = other.size();
            }

            auto res = memcmp(this->p_data, other.data(), minsize * sizeof(T));

            if (res < 0) {
                return true;
            }

            if (res == 0) {
                return this->p_size < other.size();
            }

            return false;
        }
    };

    using StringView = StringViewBase<char>;
    using StringViewW = StringViewBase<wchar_t>;
    using StringView32 = StringViewBase<char32_t>;


    constexpr StringView operator "" _sv(const char *text, size_t length) noexcept
    {
        return StringView(text, length);
    }

    constexpr StringViewW operator "" _sv(const wchar_t *text, size_t length) noexcept
    {
        return StringViewW(text, length);
    }

    constexpr StringView32 operator "" _sv(const char32_t *text, size_t length) noexcept
    {
        return StringView32(text, length);
    }
}


namespace std
{
    template <typename T, typename M>
    struct hash<c_common::StringViewBase<T, M>>
    {
        constexpr size_t operator()(const c_common::StringViewBase<T, M> &key) const noexcept
        {
            auto result = size_t(0);

            auto totalbytes = key.size() * sizeof(T);
            auto blocks = totalbytes / sizeof(size_t); // NOTE div is expected to be replaced by shift
            auto p = reinterpret_cast<const size_t*>(key.data());
            for (auto n = 0u; n < blocks; ++n) {
                if constexpr (sizeof(size_t) == 8) {
                    result += *p++ ^ 0x6211CC036211CC03u;
                } else {
                    result += *p++ ^ 0x6211CC03u;
                }
            }

            auto evenbytes = blocks * sizeof(size_t);
            if (evenbytes < totalbytes) {
                auto reminder = size_t(0);
                auto s = reinterpret_cast<const unsigned char*>(p);
                auto e = reinterpret_cast<const unsigned char*>(key.end());
                auto d = reinterpret_cast<unsigned char*>(&reminder);
                while (s != e) {
                    *d++ = *s++;
                }

                if constexpr (sizeof(size_t) == 8) {
                    result += reminder ^ 0x6211CC036211CC03u;
                } else {
                    result += reminder ^ 0x6211CC03u;
                }
            }

            return result;
        }
    };
}
