/*
 * @Author: Igor Tymchyshyn
 *			Taras Shevchenko National University of Kyiv
 *          Kyiv, Ukraine
 */


#pragma once

#ifndef TYPEDEFGENERAL_H
#define TYPEDEFGENERAL_H

#include "../def/defgeneral.h"

typedef SIZE_T size_t;

typedef UINT uint;
typedef UINT8 uint8;
typedef UINT16 uint16;
typedef UINT32 uint32;
typedef UINT64 uint64;

typedef INT8 int8;
typedef INT16 int16;
typedef INT32 int32;
typedef INT64 int64;

template <size_t bytes_count>
class UInt_N
{
};

template <>
class UInt_N<8>
{
public:
    typedef uint64 type;
};

template <>
class UInt_N<7>
{
public:
    typedef uint64 type;
};

template <>
class UInt_N<6>
{
public:
    typedef uint64 type;
};

template <>
class UInt_N<5>
{
public:
    typedef uint64 type;
};

template <>
class UInt_N<4>
{
public:
    typedef uint32 type;
};

template <>
class UInt_N<3>
{
public:
    typedef uint32 type;
};

template <>
class UInt_N<2>
{
public:
    typedef uint16 type;
};

template <>
class UInt_N<1>
{
public:
    typedef uint8 type;
};

#endif  // TYPEDEFGENERAL_H
