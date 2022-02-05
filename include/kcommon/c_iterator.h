/*
        iterator helper types

    (c) livingcreative, 2021

    https://github.com/livingcreative/kcommon

    feel free to use and modify
*/

#pragma once

#include <memory>


namespace c_util
{
    /*
     -------------------------------------------------------------------------------
     unique_ptr_iterator_adapter
     -------------------------------------------------------------------------------
         Adapter around unique_ptr for ptr_iterator
    */

    class unique_ptr_iterator_adapter
    {
    public:
        template<typename T>
        static T *get(const std::unique_ptr<T> *ptr)
        {
            return ptr->get();
        }
    };


    /*
     -------------------------------------------------------------------------------
     ptr_iterator_base<T, ptrT>
     -------------------------------------------------------------------------------
         Base class template for iterator of pointers to T
    */

    template<typename T, typename ptrT = std::unique_ptr<T>>
    class ptr_iterator_base
    {
    public:
        ptr_iterator_base(const ptrT *current) :
            p_current(current)
        {}

        bool operator!=(const ptr_iterator_base<T, ptrT> &other) const { return p_current != other.p_current; }
        ptr_iterator_base<T, ptrT> &operator++() { ++p_current; return *this; }

    protected:
        const ptrT *p_current;
    };


    /*
     -------------------------------------------------------------------------------
     ptr_iterator<T, ptrT, adapterT>
     -------------------------------------------------------------------------------
         Class template for iterator of pointers to T
         dereferences iterable pointers directly to item of type T*
    */

    template<typename T, typename ptrT = std::unique_ptr<T>, typename adapterT = unique_ptr_iterator_adapter>
    class ptr_iterator : public ptr_iterator_base<T, ptrT>
    {
    public:
        ptr_iterator(const ptrT *current) :
            ptr_iterator_base(current)
        {}

        T *operator*() const { return adapterT::get(p_current); }
        T *operator->() const { return adapterT::get(p_current); }
    };

    template<typename T, typename ptrT = std::unique_ptr<T>, typename adapterT = unique_ptr_iterator_adapter>
    class ptr_const_iterator : public ptr_iterator_base<T, ptrT>
    {
    public:
        ptr_const_iterator(const ptrT *current) :
            ptr_iterator_base(current)
        {}

        const T *operator*() const { return adapterT::get(p_current); }
        const T *operator->() const { return adapterT::get(p_current); }
    };


    /*
     -------------------------------------------------------------------------------
     index_iterator<T>
     -------------------------------------------------------------------------------
         Template wrapper around iterator
         adds index() property to get index of the current iteration
    */

    template<typename T>
    class index_iterator
    {
    public:
        // initialize wrapper iterator around existing iterator of type T
        //      initial index - value from which indexing starts
        index_iterator(T iterator, size_t initialindex = 0) :
            p_iterator(iterator),
            p_index(initialindex)
        {}

        // regular iterator operators
        bool operator!=(const index_iterator<T> &other) const { return p_iterator != other.p_iterator; }
        index_iterator<T> &operator++() { ++p_iterator; ++p_index return *this; }

        // item retrieval operators
        T *operator*() const { return *p_iterator; }
        T *operator->() const { return *p_iterator; }

        // return current index
        size_t index() const { return p_index; }

    private:
        T      p_iterator;
        size_t p_index;
    };


    /*
     -------------------------------------------------------------------------------
     index_enumerator<T>
     -------------------------------------------------------------------------------
         Template wrapper around enumerable type to access indexed iteration
         
         typical use:
         for (auto &item : index_enumerator(container)) {
            
         }
    */
    template<typename T>
    class index_enumerator
    {
    public:
        index_enumerator(T &enumerable) :
            p_enumerable(enumerable)
        {}

        index_iterator<typename T::iterator> begin() { return index_iterator(p_enumerable.begin()); }
        index_iterator<typename T::iterator> end() { return index_iterator(p_enumerable.end()); }

    private:
        T &p_enumerable;
    };

}
