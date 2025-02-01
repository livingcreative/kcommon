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
    template <typename T>
    struct StringStaticData
    {
        static T s_null;
    };

    template <typename T>
    T StringStaticData<T>::s_null = 0;


    struct StringIncludeNull
    {
        enum {
            NULL_LEN = 1
        };
    };

    struct StringExcludeNull
    {
        enum {
            NULL_LEN = 0
        };
    };


    // TODO add allocator parametrization
    template <typename T, typename M, typename N>
    class StringStore : public StringViewBase<T, M>
    {
    protected:
#if _DEBUG
        StringStore() noexcept
        {
            ++dbg_instances;
        }
#endif

        ~StringStore() noexcept
        {
            CleanUp();
#if _DEBUG
            --dbg_instances;
#endif
        }

        void SetEmptyWithNull() noexcept
        {
            if constexpr (N::NULL_LEN != 0) {
                this->p_data = &StringStaticData<typename M::storage_type>::s_null;
            }
        }

        void EnsureNull() noexcept
        {
            if constexpr (N::NULL_LEN != 0) {
                this->p_data[this->p_size] = 0;
            }
        }

        void CopyFromSource(const T *source) noexcept
        {
            if (this->p_size == 0) {
                return;
            }

            memcpy(this->p_data, source, this->p_size * sizeof(T));

            EnsureNull();
        }

        void CleanUp() noexcept
        {
            if constexpr (N::NULL_LEN != 0) {
                if (this->p_data == &StringStaticData<typename M::storage_type>::s_null) {
                    return;
                }
            }
            delete[] this->p_data;
        }

        static constexpr size_t actualsize(size_t size) noexcept
        {
            return size + N::NULL_LEN;
        }

#if _DEBUG
        static size_t dbg_instances;
        static size_t dbg_allocated;
#endif
    };

#if _DEBUG
    template <typename T, typename M, typename N>
    size_t StringStore<T, M, N>::dbg_instances = 0;

    template <typename T, typename M, typename N>
    size_t StringStore<T, M, N>::dbg_allocated = 0;
#endif


    template <typename T, typename N>
    class MutableStringBase;

    template <typename T, typename N>
    class FixedStringBuilderBase;

    template <typename T, typename N>
    class DynamicStringBuilderBase;


    template <typename T>
    struct ImmutableStringData final
    {
        using interface_type = typename const T;
        using storage_type = typename T;
    };

    template <typename T, typename N = StringExcludeNull>
    class StringBase : public StringStore<T, ImmutableStringData<T>, N>
    {
        friend class MutableStringBase<T, N>;
        friend class FixedStringBuilderBase<T, N>;
        friend class DynamicStringBuilderBase<T, N>;

    public:
        StringBase() noexcept
        {
            this->SetEmptyWithNull();
        }

        template <size_t length>
        StringBase(const T(&text)[length])
        {
            Allocate(length - 1);
            this->CopyFromSource(text);
        }

        StringBase(const T *begin, const T *end)
        {
            Allocate(end - begin);
            this->CopyFromSource(begin);
        }

        StringBase(const StringBase<T, N> &other)
        {
            Allocate(other.size());
            this->CopyFromSource(other.data());
        }

        template <typename M>
        StringBase(const StringViewBase<T, M> &other)
        {
            Allocate(other.size());
            this->CopyFromSource(other.data());
        }

        StringBase(StringBase<T, N> &&other) noexcept
        {
            this->p_data = other.p_data;
            this->p_size = other.p_size;

            other.p_data = nullptr;
            other.p_size = 0;
        }

        StringBase(MutableStringBase<T, N> &&other) noexcept
        {
            this->p_data = other.p_data;
            this->p_size = other.p_size;

            other.p_data = nullptr;
            other.p_size = 0;
            other.p_capacity = 0;
        }


        StringBase<T, N> &operator=(const StringBase<T, N> &other)
        {
            ReallocateDiscard(other.size());
            this->CopyFromSource(other.data());
            return *this;
        }

        template <typename NN>
        StringBase<T, N> &operator=(const StringBase<T, NN> &other)
        {
            ReallocateDiscard(other.size());
            this->CopyFromSource(other.data());
            return *this;
        }
        
        template <typename NN>
        StringBase<T, N> &operator=(const MutableStringBase<T, NN> &other)
        {
            ReallocateDiscard(other.size());
            this->CopyFromSource(other.size());
            return *this;
        }

        template <size_t length>
        StringBase<T, N> &operator=(const T(&text)[length])
        {
            ReallocateDiscard(length - 1);
            this->CopyFromSource(text);
            return *this;
        }

        StringBase<T, N> &operator=(T ch)
        {
            ReallocateDiscard(1);
            this->CopyFromSource(&ch);
            return *this;
        }


        template <typename M>
        StringBase<T, N> &operator=(const StringViewBase<T, M> &other)
        {
            ReallocateDiscard(other.size());
            this->CopyFromSource(other.data());
            return *this;
        }

        StringBase<T, N> &operator=(StringBase<T, N> &&other)
        {
            this->CleanUp();

            this->p_data = other.p_data;
            this->p_size = other.p_size;

            other.p_data = nullptr;
            other.p_size = 0;

            return *this;
        }

        StringBase<T, N> &operator=(MutableStringBase<T, N> &&other)
        {
            this->CleanUp();

            this->p_data = other.p_data;
            this->p_size = other.p_size;

            other.p_data = nullptr;
            other.p_size = 0;
            other.p_capacity = 0;

            return *this;
        }

    protected:
        void Allocate(size_t size)
        {
            assert(this->p_data == nullptr);

            if (size == 0) {
                this->SetEmptyWithNull();
                return;
            }

            this->p_data = new T[calcalloc(this->actualsize(size))];
            this->p_size = size;
        }

        void ReallocateDiscard(size_t size)
        {
            if (size == 0) {
                this->CleanUp();
                this->SetEmptyWithNull();
                this->p_size = 0;
                return;
            }

            if (this->p_size >= this->actualsize(size)) {
                // TODO reallocate if diff is too large
                this->p_size = size;
                return;
            }

            this->CleanUp();
#if _DEBUG
            this->p_data = nullptr;
#endif
            Allocate(size);
        }

        constexpr static size_t calcalloc(size_t newsize) noexcept
        {
            return ((newsize + sizeof(size_t) - 1) / sizeof(size_t)) * sizeof(size_t);
        }

        StringBase(T *data, size_t size)
        {
            this->p_data = data;
            this->p_size = size;
        }
    };

    using String = StringBase<char>;
    using StringW = StringBase<wchar_t>;
    using String32 = StringBase<uint32_t>;
    using StringNT = StringBase<char, StringIncludeNull>;
    using StringWNT = StringBase<wchar_t, StringIncludeNull>;
    using String32NT = StringBase<uint32_t, StringIncludeNull>;


    template <typename T, typename N = StringExcludeNull>
    class MutableStringBase : public StringStore<T, MutableSpanData<T>, N>
    {
        friend class StringBase<T, N>;
        friend class DynamicStringBuilderBase<T, N>;

    public:
        constexpr MutableStringBase() noexcept :
            p_capacity(0)
        {
            this->SetEmptyWithNull();
        }

        template <size_t length>
        MutableStringBase(const T(&text)[length]) :
            p_capacity(calccapacity(this->actualsize(length - 1)))
        {
            Allocate(length - 1);
            this->CopyFromSource(text);
        }

        MutableStringBase(const T *begin, const T *end) :
            p_capacity(calccapacity(this->actualsize(end - begin)))
        {
            Allocate(end - begin);
            this->CopyFromSource(begin);
        }

        MutableStringBase(const MutableStringBase<T, N> &other) :
            p_capacity(calccapacity(this->actualsize(other.size())))
        {
            Allocate(other.size());
            this->CopyFromSource(other.data());
        }

        template <typename M>
        MutableStringBase(const StringViewBase<T, M> &other) :
            p_capacity(calccapacity(this->actualsize(other.size())))
        {
            Allocate(other.size());
            this->CopyFromSource(other.data());
        }

        MutableStringBase(StringBase<T, N> &&other) :
            // NOTE - can't align capacity as String does not have aligned storage
            p_capacity(this->actualsize(other.p_size))
        {
            this->p_data = other.p_data;
            this->p_size = other.p_size;

            other.p_data = nullptr;
            other.p_size = 0;
        }

        MutableStringBase(MutableStringBase<T, N> &&other) :
            p_capacity(other.p_capacity)
        {
            this->p_data = other.p_data;
            this->p_size = other.p_size;

            other.p_data = nullptr;
            other.p_size = 0;
            other.p_capacity = 0;
        }

        template <size_t length>
        MutableStringBase<T, N> &operator=(const T(&text)[length])
        {
            Reserve(this->actualsize(length - 1), false);
            this->p_size = length - 1;
            this->CopyFromSource(text);
            return *this;
        }

        template <typename M>
        MutableStringBase<T, N> &operator=(const StringViewBase<T, M> &other)
        {
            Reserve(other.size(), false);
            this->p_size = other.size();
            this->CopyFromSource(other.data());
            return *this;
        }

        MutableStringBase<T, N> &operator=(MutableStringBase<T, N> &&other)
        {
            this->CleanUp();

            this->p_data = other.p_data;
            this->p_size = other.p_size;
            this->p_capacity = other.p_capacity;

            other.p_data = nullptr;
            other.p_size = 0;
            other.p_capacity = 0;

            return *this;
        }

        MutableStringBase<T, N> &operator=(StringBase<T, N> &&other)
        {
            this->CleanUp();

            this->p_data = other.p_data;
            this->p_size = other.p_size;
            this->p_capacity = this->actualsize(other.p_size);

            other.p_data = nullptr;
            other.p_size = 0;

            return *this;
        }


        const T *data() const { return this->p_data; }
        T *data() { return this->p_data; }


        MutableStringBase<T, N> &operator+=(T ch)
        {
            reserve(this->actualsize(this->p_size + 1));
            this->p_data[this->p_size++] = ch;
            this->EnsureNull();
            return *this;
        }

        template <typename M>
        MutableStringBase<T, N> &operator+=(const StringViewBase<T, M> &str)
        {
            reserve(this->actualsize(this->p_size + 1));

            memcpy(
                this->p_data + this->p_size, str.data(),
                str.size() * sizeof(T)
            );

            this->p_size += str.size();
            this->EnsureNull();

            return *this;
        }

        template <size_t length>
        MutableStringBase<T, N> &operator+=(const T(&text)[length])
        {
            reserve(this->actualsize(this->p_size + length - 1));

            memcpy(
                this->p_data + this->p_size, text,
                (length - 1) * sizeof(T)
            );

            this->p_size += length - 1;
            this->EnsureNull();

            return *this;
        }


        void reserve(size_t capacity)
        {
            Reserve(capacity, true);
        }

        void resize(size_t newsize)
        {
            auto actualnewsize = this->actualsize(newsize);
            if (actualnewsize > p_capacity) {
                reserve(calccapacity(actualnewsize));
            }
            this->p_size = newsize;
        }

        void append(T val)
        {
            reserve(this->p_size + 1);
            this->p_data[this->p_size++] = val;
            this->EnsureNull();
        }

        template <size_t length>
        void append(const T(&val)[length])
        {
            append(StringViewBase<T>(val));
        }

        template <typename MM>
        void append(const StringViewBase<T, MM> &val)
        {
            reserve(this->p_size + val.size());
            memcpy(this->p_data + this->p_size, val.data(), val.size() * sizeof(T));
            this->p_size += val.size();
            this->EnsureNull();
        }

        void insert(const T *at, T val)
        {
            insert(at - this->p_data, val);
        }

        template <size_t length>
        void insert(const T *at, const T(&val)[length])
        {
            insert(at, StringViewBase<T>(val));
        }

        template <typename MM>
        void insert(const T *at, const StringViewBase<T, MM> &val)
        {
            insert(at - this->p_data, val);
        }

        void insert(size_t at, T val)
        {
            assert(at <= this->p_size);

            // TODO avoid memmove if reserve did copy realloc and
            //      create insertion hole via realloc copy
            reserve(this->p_size + 1);
            memmove(
                this->p_data + at + 1, this->p_data + at,
                this->actualsize(this->p_size - at) * sizeof(T)
            );
            this->p_data[at] = val;
            this->p_size++;
        }

        template <size_t length>
        void insert(size_t at, const T(&val)[length])
        {
            insert(at, StringViewBase<T>(val));
        }

        template <typename MM>
        void insert(size_t at, const StringViewBase<T, MM> &val)
        {
            assert(at <= this->p_size);

            reserve(this->p_size + val.size());
            memmove(
                this->p_data + at + val.size(), this->p_data + at,
                this->actualsize(this->p_size - at) * sizeof(T)
            );
            memcpy(
                this->p_data + at, val.data(),
                val.size() * sizeof(T)
            );
            this->p_size += val.size();
        }

        void erase(const T *at)
        {
            erase(at - this->p_data);
        }

        void erase(T *from, T *to)
        {
            erase(from - this->p_data, to - from);
        }

        void erase(size_t at)
        {
            assert(at < this->p_size);

            memmove(
                this->p_data + at, this->p_data + at + 1,
                this->actualsize(this->p_size - at - 1) * sizeof(T)
            );
            this->p_size--;
        }

        void erase(size_t from, size_t count)
        {
            assert(from + count <= this->p_size);

            memmove(
                this->p_data + from, this->p_data + from + count,
                this->actualsize(this->p_size - from - count) * sizeof(T)
            );
            this->p_size -= count;
        }

        void clear() noexcept
        {
            this->p_size = 0;
            this->EnsureNull();
        }

        // std compatibility slop
        void push_back(T ch) { append(ch); }

    private:
        void Allocate(size_t size)
        {
            assert(this->p_data == nullptr);

            if (p_capacity == 0) {
                this->SetEmptyWithNull();
                return;
            }

            this->p_data = new T[p_capacity];
            this->p_size = size;

            if (size == 0) {
                this->EnsureNull();
            }
        }

        void Reserve(size_t capacity, bool preservesource)
        {
            if (capacity > p_capacity) {
                auto newcapacity = calccapacity(capacity);
                auto newdata = new T[newcapacity];

                if (preservesource) {
                    auto minsize = this->p_size;
                    if (newcapacity < minsize) {
                        minsize = newcapacity;
                    }
                    memcpy(newdata, this->p_data, minsize * sizeof(T));
                }

                this->CleanUp();

                this->p_data = newdata;
                p_capacity = newcapacity;
            }
        }

        constexpr static size_t calccapacity(size_t newsize) noexcept
        {
            return ((newsize + 1023) / 1024) * 1024;
        }

    private:
        size_t p_capacity;
    };

    using MutableString = MutableStringBase<char>;
    using MutableStringW = MutableStringBase<wchar_t>;
    using MutableString32 = MutableStringBase<uint32_t>;
    using MutableStringNT = MutableStringBase<char, StringIncludeNull>;
    using MutableStringWNT = MutableStringBase<wchar_t, StringIncludeNull>;
    using MutableString32NT = MutableStringBase<uint32_t, StringIncludeNull>;
}
