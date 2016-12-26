/*
 * @Author: Igor Tymchyshyn
 *			Taras Shevchenko National University of Kyiv
 *          Kyiv, Ukraine
 */


#pragma once

#ifndef _DS_QUEUE_MIN_FIXED_N_
#define _DS_QUEUE_MIN_FIXED_N_

#include "../typedefs/typedefgeneral.h"

#include "IQueue.h"
#include "StackMinFixedN.h"


namespace ds
{

    template <class T, size_t n>
    class QueueMinFixedN : public IQueue<T>
    {
    private:
        StackMinFixedN<T, n> stack_for_pushing;
        StackMinFixedN<T, n> stack_for_poping;

        void stacks_move_elements();

    public:
        QueueMinFixedN();
        QueueMinFixedN(const T& val);
        QueueMinFixedN(const QueueMinFixedN& queueMinFixedN);

        QueueMinFixedN& operator=(const QueueMinFixedN& queueMinFixedN);

        ~QueueMinFixedN();

        template <class S, size_t m>
        friend void swap(const QueueMinFixedN<S, m> queue_first, const QueueMinFixedN<S, m> queue_second);

        void push(const T& val);
        void push(T&& val);
        T pop();
        T front() const;
        T min() const;
        T pop_min() const;
        size_t size() const;
        bool empty() const;
        bool full() const;
        void clear();
    };

    template <class S, size_t m>
    void swap(const QueueMinFixedN<S, m> queue_first, const QueueMinFixedN<S, m> queue_second)
    {
        swap(queue_first.stack_for_pushing, queue_second.stack_for_pushing);
        swap(queue_first.stack_for_poping, queue_second.stack_for_poping);
    }

    template <class T, size_t n>
    QueueMinFixedN<T, n>::QueueMinFixedN()
    {
    }

    template <class T, size_t n>
    QueueMinFixedN<T, n>::QueueMinFixedN(const T& val) : stack_for_poping(val)
    {
    }

    template <class T, size_t n>
    QueueMinFixedN<T, n>::QueueMinFixedN(const QueueMinFixedN<T, n>& queueMinFixedN) :
        stack_for_pushing(queueMinFixedN.stack_for_pushing),
        stack_for_poping(queueMinFixedN.stack_for_poping)
    {
    }

    template <class T, size_t n>
    QueueMinFixedN<T, n>& QueueMinFixedN<T, n>::operator=(const QueueMinFixedN<T, n>& queueMinFixedN)
    {
        stack_for_pushing = queueMinFixedN.stack_for_pushing;
        stack_for_poping = queueMinFixedN.stack_for_poping;
    }

    template <class T, size_t n>
    QueueMinFixedN<T, n>::~QueueMinFixedN()
    {
    }

    template <class T, size_t n>
    void QueueMinFixedN<T, n>::stacks_move_elements()
    {
#ifdef DEBUG_MODE
        if (!stack_for_poping.empty())
        {
            throw "error: [QueueMinFixedN] Stack for poping is not empty\n";
        }
#endif  // DEBUG_MODE

        for (size_t i = stack_for_pushing.size(); i; --i)
        {
            stack_for_poping.push(stack_for_pushing.pop());
        }
    }

    template <class T, size_t n>
    void QueueMinFixedN<T, n>::push(const T& val)
    {
        if (stack_for_pushing.full())
        {
            stacks_move_elements();
        }

        stack_for_pushing.push(val);
    }

    template <class T, size_t n>
    void QueueMinFixedN<T, n>::push(T&& val)
    {
        if (stack_for_pushing.full())
        {
            stacks_move_elements();
        }

        stack_for_pushing.push(val);
    }

    template <class T, size_t n>
    T QueueMinFixedN<T, n>::pop()
    {
#ifdef DEBUG_MODE
        if (stack_for_poping.empty() && stack_for_pushing.empty())
        {
            throw "error: [QueueMinFixedN] Stack for poping is not empty\n";
        }
#endif  // DEBUG_MODE

        if (stack_for_poping.empty())
        {
            stacks_move_elements();
        }

        return stack_for_poping.pop();
    }

    template <class T, size_t n>
    T QueueMinFixedN<T, n>::front() const
    {
#ifdef DEBUG_MODE
        if (stack_for_poping.empty() && stack_for_pushing.empty())
        {
            throw "error: [QueueMinFixedN] Stack for poping is not empty\n";
        }
#endif  // DEBUG_MODE

        if (stack_for_poping.empty())
        {
            stacks_move_elements();
        }

        return stack_for_poping.top();
    }

    template <class T, size_t n>
    T QueueMinFixedN<T, n>::min() const
    {
        T min_val_pushin_stack = stack_for_pushing.min();
        T min_val_poping_stack = stack_for_poping.min();

        if (min_val_poping_stack < min_val_pushin_stack)
        {
            return min_val_poping_stack;
        }

        return min_val_pushin_stack;
    }

    template <class T, size_t n>
    T QueueMinFixedN<T, n>::pop_min() const
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

    template <class T, size_t n>
    size_t QueueMinFixedN<T, n>::size() const
    {
        return stack_for_pushing.size() + stack_for_poping.size();
    }

    template <class T, size_t n>
    bool QueueMinFixedN<T, n>::empty() const
    {
        return stack_for_pushing.empty() && stack_for_poping.empty();
    }

    template <class T, size_t n>
    bool QueueMinFixedN<T, n>::full() const
    {
        return !(size() - n);
    }

    template <class T, size_t n>
    void QueueMinFixedN<T, n>::clear()
    {
        stack_for_pushing.clear();
        stack_for_poping.clear();
    }

}

#endif  // !_DS_QUEUE_MIN_FIXED_N_
