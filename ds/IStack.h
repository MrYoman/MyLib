/*
 * @Author: Igor Tymchyshyn
 *			Taras Shevchenko National University of Kyiv
 *          Kyiv, Ukraine
 */


#pragma once

#ifndef _DS_ISTACK_
#define _DS_ISTACK_

#include "../typedefs/typedefgeneral.h"

namespace ds
{

    template <class T>
    class IStack
    {
    public:
        void push(const T& val);
        void push(T&& val);
        T pop();
        T top() const;
        size_t size() const;
        bool empty() const;
        void clear();
    };

}

#endif  // !_DS_ISTACK_
