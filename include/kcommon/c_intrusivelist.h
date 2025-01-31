#pragma once

namespace c_common
{
    template <typename T>
    class IntrusiveListDefaultAdapter
    {
    public:
        static T * &prev(T *item) { return item->prevsibling; }
        static T * &next(T *item) { return item->nextsibling; }
    };


    // NOTE: does not maintain ownership of the contained items, nor handle any kind of allocation
    template <typename T, typename intrusiveT = IntrusiveListDefaultAdapter<T>>
    class IntrusiveList
    {
    public:
        class IteratorBase
        {
        public:
            IteratorBase() noexcept :
                p_current(nullptr)
            {}

            IteratorBase(T *item) noexcept :
                p_current(item)
            {}

            T *operator*() const noexcept { return p_current; }
            T *operator->() const noexcept { return p_current; }

            bool operator==(const IteratorBase &other) const noexcept { return p_current == other.p_current; }
            bool operator!=(const IteratorBase &other) const noexcept { return p_current != other.p_current; }

        protected:
            T *p_current;
        };

        class ForwardIterator : public IteratorBase
        {
        public:
            ForwardIterator() noexcept :
                IteratorBase()
            {}

            ForwardIterator(T *item) noexcept :
                IteratorBase(item)
            {}

            ForwardIterator &operator++()
            {
                p_current = intrusiveT::next(p_current);
                return *this;
            }
        };

        class BackwardIterator : public IteratorBase
        {
        public:
            BackwardIterator() noexcept :
                IteratorBase()
            {}

            BackwardIterator(T *item) noexcept :
                IteratorBase(item)
            {}

            BackwardIterator &operator++()
            {
                p_current = intrusiveT::prev(p_current);
                return *this;
            }
        };

    public:
        IntrusiveList() :
            p_firstchild(nullptr),
            p_lastchild(nullptr),
            p_count(0)
        {}

        IntrusiveList(const IntrusiveList &source) = delete;
        IntrusiveList &operator=(const IntrusiveList &source) = delete;

        IntrusiveList(const IntrusiveList &&source) :
            p_firstchild(source.p_firstchild),
            p_lastchild(source.p_lastchild),
            p_count(source.p_count)
        {
            source.p_firstchild = nullptr;
            source.p_lastchild = nullptr;
            source.p_count = 0;
        }

        IntrusiveList &operator=(IntrusiveList &&source)
        {
            p_firstchild = source.p_firstchild;
            p_lastchild = source.p_lastchild;
            p_count = source.p_count;

            source.p_firstchild = nullptr;
            source.p_lastchild = nullptr;
            source.p_count = 0;

            return *this;
        }

        ForwardIterator begin() const noexcept { return ForwardIterator(p_firstchild); }
        ForwardIterator end() const noexcept { return ForwardIterator(); }

        BackwardIterator rbegin() const noexcept { return BackwardIterator(p_lastchild); }
        BackwardIterator rend() const noexcept { return BackwardIterator(); }

        T *front() const noexcept { return p_firstchild; }
        T *back() const noexcept { return p_lastchild; }
        size_t size() const noexcept { return p_count; }

        void Add(T *item)
        {
#if _DEBUG && defined(_CrtDbgBreak)
            if (intrusiveT::prev(item) != nullptr || intrusiveT::next(item) != nullptr) {
                _CrtDbgBreak();
            }
#endif

            if (p_lastchild == nullptr) {
                p_firstchild = item;
                p_lastchild = item;
            } else {
                intrusiveT::next(p_lastchild) = item;
                intrusiveT::prev(item) = p_lastchild;
                p_lastchild = item;
            }

            ++p_count;
        }

        void Remove(T *item)
        {
            // TODO: assert item is not in other list

            auto prev = intrusiveT::prev(item);
            auto next = intrusiveT::next(item);

            intrusiveT::prev(item) = nullptr;
            intrusiveT::next(item) = nullptr;

            if (prev) {
                intrusiveT::next(prev) = next;
            } else {
#if _DEBUG && defined(_CrtDbgBreak)
                if (p_firstchild != item) {
                    _CrtDbgBreak();
                }
#endif
                p_firstchild = next;
            }

            if (next) {
                intrusiveT::prev(next) = prev;
            } else {
#if _DEBUG && defined(_CrtDbgBreak)
                if (p_lastchild != item) {
                    _CrtDbgBreak();
                }
#endif
                p_lastchild = prev;
            }

            --p_count;

#if _DEBUG && defined(_CrtDbgBreak)
            if (p_count == 0 && (p_firstchild || p_lastchild)) {
                _CrtDbgBreak();
            }
#endif
        }

    public:
        struct Links
        {
            Links() :
                prevsibling(nullptr),
                nextsibling(nullptr)
            {}

            T *prevsibling;
            T *nextsibling;
        };

    private:
        T      *p_firstchild;
        T      *p_lastchild;
        size_t  p_count;
    };
}
