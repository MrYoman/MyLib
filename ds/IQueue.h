/*
 * @Author: Igor Tymchyshyn
 *			Taras Shevchenko National University of Kyiv
 *          Kyiv, Ukraine
 */


#pragma once

#ifndef _DS_IQUEUE_
#define _DS_IQUEUE_

#include "../typedefs/typedefgeneral.h"

namespace ds
{

    template <class T>
    class IQueue
    {
    public:
        void push(const T& val);
        void push(T&& val);
        T pop();
        T front() const;
        size_t size() const;
        bool empty() const;
        void clear();
    };

}

#endif  // !_DS_IQUEUE_
