/*
 * @Author: Igor Tymchyshyn
 *			Taras Shevchenko National University of Kyiv
 *          Kyiv, Ukraine
 */


#pragma once

#ifndef _DS_STACK_MIN_
#define _DS_STACK_MIN_


#include "../typedefs/typedefgeneral.h"

#include "IStack.h"
#include <stack>


namespace ds
{

    template <class T>
    class StackMin : public IStack<T>
    {
    private:
        std::stack<T> data;
        std::stack<T> data_min;

    public:
        StackMin();
        StackMin(const StackMin& stackMin);
        StackMin(StackMin&& stackMin);

        StackMin& operator=(const StackMin& stackMin);
        StackMin& operator=(StackMin&& stackMin);

        ~StackMin();

        template <class S>
        friend void swap(const StackMin<S> stack_first, const StackMin<S> stack_second);

        void push(const T& val);
        void push(T&& val);
        T pop();
        T top() const;
        T pop_min();
        T min() const;
        size_t size() const;
        bool empty() const;
        bool full() const;
        void clear();
    };

    template <class T>
    StackMin<T>::StackMin()
    {
    }

    template <class T>
    StackMin<T>::StackMin(const StackMin<T>& stackMin)
    {
        data = stackMin.data;
        data_min = stackMin.data_min;
    }

    template <class T>
    StackMin<T>::StackMin(StackMin<T>&& stackMin)
    {
        data = static_cast< std::stack<T>&& >(stackMin.data);
        data_min = static_cast< std::stack<T>&& >(stackMin.data_min);
    }

    template <class T>
    StackMin<T>& StackMin<T>::operator=(const StackMin<T>& stackMin)
    {
        data = stackMin.data;
        data_min = stackMin.data_min;

        return *this;
    }

    template <class T>
    StackMin<T>& StackMin<T>::operator=(StackMin<T>&& stackMin)
    {
        data = static_cast< std::stack<T>&& >(stackMin.data);
        data_min = static_cast< std::stack<T>&& >(stackMin.data_min);

        return *this;
    }

    template <class T>
    StackMin<T>::~StackMin()
    {
    }

    template <class S>
    void swap(const StackMin<S> stack_first, const StackMin<S> stack_second)
    {
        swap(stack_first.data, stack_second.data);
        swap(stack_first.data_min, stack_second.data_min);
    }

    template <class T>
    void StackMin<T>::push(const T& val)
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

    template <class T>
    void StackMin<T>::push(T&& val)
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

    template <class T>
    inline T StackMin<T>::pop()
    {
        data_min.pop();
        return data.pop();
    }

    template <class T>
    inline T StackMin<T>::top() const
    {
        return data.top();
    }

    template <class T>
    inline T StackMin<T>::pop_min()
    {
        data.pop();
        return data_min.pop();
    }

    template <class T>
    inline T StackMin<T>::min() const
    {
        return data_min.top();
    }

    template <class T>
    inline size_t StackMin<T>::size() const
    {
        return data.size();
    }

    template <class T>
    inline bool StackMin<T>::empty() const
    {
        return data.empty();
    }

    template <class T>
    void StackMin<T>::clear()
    {
        data.clear();
        data_min.clear();
    }
}

#endif  // !_DS_STACK_MIN_FIXED_N_
