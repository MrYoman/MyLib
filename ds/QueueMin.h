/*
 * @Author: Igor Tymchyshyn
 *			Taras Shevchenko National University of Kyiv
 *          Kyiv, Ukraine
 */


#pragma once

#ifndef _DS_QUEUE_MIN_
#define _DS_QUEUE_MIN_

#include "../typedefs/typedefgeneral.h"

#include "IQueue.h"
#include "StackMin.h"


namespace ds
{

    template <class T>
    class QueueMin : public IQueue<T>
    {
    private:
        StackMin<T> stack_for_pushing;
        StackMin<T> stack_for_poping;

        void stacks_move_elements();

    public:
        QueueMin();
        QueueMin(const T& val);
        QueueMin(const QueueMin<T>& QueueMin);

        QueueMin<T>& operator=(const QueueMin<T>& QueueMin);

        ~QueueMin();

        template <class S>
        friend void swap(const QueueMin<S> queue_first, const QueueMin<S> queue_second);

        void push(const T& val);
        void push(T&& val);
        T pop();
        T front() const;
        T min() const;
        T pop_min();
        size_t size() const;
        bool empty() const;
        void clear();
    };

    template <class S>
    void swap(const QueueMin<S> queue_first, const QueueMin<S> queue_second)
    {
        swap(queue_first.stack_for_pushing, queue_second.stack_for_pushing);
        swap(queue_first.stack_for_poping, queue_second.stack_for_poping);
    }

    template <class T>
    QueueMin<T>::QueueMin()
    {
    }

    template <class T>
    QueueMin<T>::QueueMin(const T& val) : stack_for_poping(val)
    {
    }

    template <class T>
    QueueMin<T>::QueueMin(const QueueMin<T>& QueueMin) :
        stack_for_pushing(QueueMin.stack_for_pushing),
        stack_for_poping(QueueMin.stack_for_poping)
    {
    }

    template <class T>
    QueueMin<T>& QueueMin<T>::operator=(const QueueMin<T>& QueueMin)
    {
        stack_for_pushing = QueueMin.stack_for_pushing;
        stack_for_poping = QueueMin.stack_for_poping;
    }

    template <class T>
    QueueMin<T>::~QueueMin()
    {
    }

    template <class T>
    void QueueMin<T>::stacks_move_elements()
    {
#ifdef DEBUG_MODE
        if (!stack_for_poping.empty())
        {
            throw "error: [QueueMin] Stack for poping is not empty\n";
        }
#endif  // DEBUG_MODE

        for (size_t i = stack_for_pushing.size(); i; --i)
        {
            stack_for_poping.push(stack_for_pushing.pop());
        }
    }

    template <class T>
    void QueueMin<T>::push(const T& val)
    {
        stack_for_pushing.push(val);
    }

    template <class T>
    void QueueMin<T>::push(T&& val)
    {
        stack_for_pushing.push(val);
    }

    template <class T>
    T QueueMin<T>::pop()
    {
#ifdef DEBUG_MODE
        if (stack_for_poping.empty() && stack_for_pushing.empty())
        {
            throw "error: [QueueMin] Stack for poping is not empty\n";
        }
#endif  // DEBUG_MODE

        if (stack_for_poping.empty())
        {
            stacks_move_elements();
        }

        return stack_for_poping.pop();
    }

    template <class T>
    T QueueMin<T>::front() const
    {
#ifdef DEBUG_MODE
        if (stack_for_poping.empty() && stack_for_pushing.empty())
        {
            throw "error: [QueueMin] Stack for poping is not empty\n";
        }
#endif  // DEBUG_MODE

        if (stack_for_poping.empty())
        {
            stacks_move_elements();
        }

        return stack_for_poping.top();
    }

    template <class T>
    T QueueMin<T>::min() const
    {
        T min_val_pushin_stack = stack_for_pushing.min();
        T min_val_poping_stack = stack_for_poping.min();

        if (min_val_poping_stack < min_val_pushin_stack)
        {
            return min_val_poping_stack;
        }

        return min_val_pushin_stack;
    }

    template <class T>
    T QueueMin<T>::pop_min()
    {
        T min_val_pushin_stack = stack_for_pushing.min();
        T min_val_poping_stack = stack_for_poping.min();

        pop();

        if (min_val_poping_stack < min_val_pushin_stack)
        {
            return min_val_poping_stack;
        }

        return min_val_pushin_stack;
    }

    template <class T>
    size_t QueueMin<T>::size() const
    {
        return stack_for_pushing.size() + stack_for_poping.size();
    }

    template <class T>
    bool QueueMin<T>::empty() const
    {
        return stack_for_pushing.empty() && stack_for_poping.empty();
    }

    template <class T>
    void QueueMin<T>::clear()
    {
        stack_for_pushing.clear();
        stack_for_poping.clear();
    }

}

#endif  // !_DS_QUEUE_MIN_
