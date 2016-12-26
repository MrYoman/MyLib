/*
 * @Author: Igor Tymchyshyn
 *			Taras Shevchenko National University of Kyiv
 *          Kyiv, Ukraine
 */


#pragma once

#ifndef _DS_STACK_MIN_FIXED_N_
#define _DS_STACK_MIN_FIXED_N_


#include "../typedefs/typedefgeneral.h"

#include "IStack.h"
#include "StackFixedN.h"


namespace ds
{

    template <class T, size_t n>
    class StackMinFixedN : public IStack<T>
    {
    private:
        StackFixedN<T, n> data;
        StackFixedN<T, n> data_min;

    public:
        StackMinFixedN();
        StackMinFixedN(const T& val);
        StackMinFixedN(const StackMinFixedN& stackMinFixedN);

        StackMinFixedN& operator=(const StackMinFixedN& stackMinFixedN);

        ~StackMinFixedN();

        template <class S, size_t m>
        friend void swap(const StackMinFixedN<S, m> stack_first, const StackMinFixedN<S, m> stack_second);

        void push(const T& val);
        void push(T&& val);
        T pop();
        T top() const;
        T pop_min() const;
        T min() const;
        size_t size() const;
        bool empty() const;
        bool full() const;
        void clear();
    };

    template <class T, size_t n>
    StackMinFixedN<T, n>::StackMinFixedN()
    {
    }

    template <class T, size_t n>
    StackMinFixedN<T, n>::StackMinFixedN(const T& val) : data(val), data_min(val)
    {
    }

    template <class T, size_t n>
    StackMinFixedN<T, n>::StackMinFixedN(const StackMinFixedN<T, n>& stackMinFixedN)
    {
        data = stackMinFixedN.data;
        data_min = stackMinFixedN.data_min;
    }

    template <class T, size_t n>
    StackMinFixedN<T, n>& StackMinFixedN<T, n>::operator=(const StackMinFixedN<T, n>& stackMinFixedN)
    {
        data = stackMinFixedN.data;
        data_min = stackMinFixedN.data_min;

        return *this;
    }

    template <class T, size_t n>
    StackMinFixedN<T, n>::~StackMinFixedN()
    {
    }

    template <class S, size_t m>
    void swap(const StackMinFixedN<S, m> stack_first, const StackMinFixedN<S, m> stack_second)
    {
        StackFixedN<S, m> tmp = stack_first.data;
        stack_first.data = stack_second.data;
        stack_second.data = tmp;

        tmp = stack_first.data_min;
        stack_first.data_min = stack_second.data_min;
        stack_second.data_min = tmp;
    }

    template <class T, size_t n>
    void StackMinFixedN<T, n>::push(const T& val)
    {
        if (!data.full())
        {
            data.push(val);
            if (data_min.top() < val)
            {
                data_min.push(data_min.top());
            }
            else
            {
                data_min.push(val);
            }
        }
    }

    template <class T, size_t n>
    void StackMinFixedN<T, n>::push(T&& val)
    {
        if (!data.full())
        {
            data.push(val);
            if (data_min.top() < val)
            {
                data_min.push(data_min.top());
            }
            else
            {
                data_min.push(val);
            }
        }
    }

    template <class T, size_t n>
    inline T StackMinFixedN<T, n>::pop()
    {
        data_min.pop();
        return data.pop();
    }

    template <class T, size_t n>
    inline T StackMinFixedN<T, n>::top() const
    {
        return data.top();
    }

    template <class T, size_t n>
    inline T StackMinFixedN<T, n>::pop_min() const
    {
        data.pop();
        return data_min.pop();
    }

    template <class T, size_t n>
    inline T StackMinFixedN<T, n>::min() const
    {
        return data_min.top();
    }

    template <class T, size_t n>
    inline size_t StackMinFixedN<T, n>::size() const
    {
        return data.size();
    }

    template <class T, size_t n>
    inline bool StackMinFixedN<T, n>::empty() const
    {
        return data.empty();
    }

    template <class T, size_t n>
    void StackMinFixedN<T, n>::clear()
    {
        data.clear();
        data_min.clear();
    }
}

#endif  // !_DS_STACK_MIN_FIXED_N_
