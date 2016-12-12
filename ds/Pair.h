
#pragma once

#ifndef _DS_PAIR_
#define _DS_PAIR_

namespace ds {

    template <class T, class S = T>
    struct Pair
    {
        T x;
        S y;
    };

}

#endif // !_DS_PAIR_
