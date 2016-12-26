/*
 * @Author: Igor Tymchyshyn
 *			Taras Shevchenko National University of Kyiv
 *          Kyiv, Ukraine
 */


#pragma once

#ifndef _DS_STACK_FIXED_N_
#define _DS_STACK_FIXED_N_

#include "../typedefs/typedefgeneral.h"

#include "IStack.h"


namespace ds
{

    template <class T, size_t n>
    class StackFixedN : public IStack<T>
    {
    private:
        T data[n];
        size_t data_size;
        size_t top_index;

    public:
        StackFixedN();
        StackFixedN(const T& val);
        StackFixedN(const StackFixedN& stackFixedN);

        StackFixedN& operator=(const StackFixedN& stackFixedN);

        ~StackFixedN();

        template <class S, size_t m>
        friend void swap(const StackFixedN<S, m> stack_first, const StackFixedN<S, m> stack_second);

        void push(const T& val);
        void push(T&& val);
        T pop();
        T top() const;
        size_t size() const;
        bool empty() const;
        bool full() const;
        void clear();
    };

    template <class S, size_t m>
    void swap(const StackFixedN<S, m> stack_first, const StackFixedN<S, m> stack_second)
    {
        S tmp_el;

        for (size_t i = 0; i < m; ++i)
        {
            tmp_el = stack_first.data[i];
            stack_first.data[i] = stack_second.data[i];
            stack_second.data[i] = tmp_el;
        }

        size_t tmp = stack_first.data_size;
        stack_first.data_size = stack_second.data_size;
        stack_second.data_size = tmp;

        tmp = stack_first.top_index;
        stack_first.top_index = stack_second.top_index;
        stack_second.top_index = tmp;
    }

    template <class T, size_t n>
    StackFixedN<T, n>::StackFixedN()
    {
        data_size = 0;
        top_index = 0;
    }

    template <class T, size_t n>
    StackFixedN<T, n>::StackFixedN(const T& val)
    {
        data_size = n;
        for (top_index = 0; top_index < n; ++top_index)
        {
            data[top_index] = val;
        }
    }

    template <class T, size_t n>
    StackFixedN<T, n>::StackFixedN(const StackFixedN<T, n>& stackFixedN)
    {
        data_size = stackFixedN.data_size;
        top_index = stackFixedN.top_index;
        for (size_t i = 0; i < n; ++i)
        {
            data[i] = stackFixedN.data[i];
        }
    }

    template <class T, size_t n>
    StackFixedN<T, n>& StackFixedN<T, n>::operator=(const StackFixedN<T, n>& stackFixedN)
    {
        data_size = stackFixedN.data_size;
        top_index = stackFixedN.top_index;
        for (size_t i = 0; i < n; ++i)
        {
            data[i] = stackFixedN.data[i];
        }

        return *this;
    }

    template <class T, size_t n>
    StackFixedN<T, n>::~StackFixedN()
    {
    }

    template <class T, size_t n>
    void StackFixedN<T, n>::push(const T& val)
    {
        if (!(n - top_index))
        {
            top_index = 0;
        }

        data[top_index] = val;
        ++top_index;

        if (n - data_size)
        {
            ++data_size;
        }
    }

    template <class T, size_t n>
    void StackFixedN<T, n>::push(T&& val)
    {
        if (!(n - top_index))
        {
            top_index = 0;
        }

        data[top_index] = val;
        ++top_index;

        if (n - data_size)
        {
            ++data_size;
        }
    }

    template <class T, size_t n>
    T StackFixedN<T, n>::pop()
    {
        if (data_size)
        {
            --data_size;

            if (top_index)
            {
                return data[--top_index];
            }
            else
            {
                top_index = n - 1;
                return data[top_index];
            }
        }

        return data[0];
    }

    template <class T, size_t n>
    inline T StackFixedN<T, n>::top() const
    {
        if (!top_index)
        {
            return data[data_size - 1];
        }

        return data[top_index - 1];
    }

    template <class T, size_t n>
    inline size_t StackFixedN<T, n>::size() const
    {
        return data_size;
    }

    template <class T, size_t n>
    inline bool StackFixedN<T, n>::empty() const
    {
        return !data_size;
    }

    template <class T, size_t n>
    inline bool StackFixedN<T, n>::full() const
    {
        return !(n - data_size);
    }

    template <class T, size_t n>
    inline void StackFixedN<T, n>::clear()
    {
        data_size = 0;
        top_index = 0;
    }

}

#endif  // !_DS_STACK_FIXED_N_
