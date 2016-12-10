#pragma once

#ifndef DEFGENERAL_H
#define DEFGENERAL_H


#if !defined(__GNUC__ ) && !defined(_MSC_VER)
#error GNU or MSVC compiler required
#endif  // !defined(__GNUC__ ) && !defined(_MSC_VER)


#include <limits.h>


#if !defined(MODE_x64) && !defined(MODE_x86)


#ifdef WIN64
#define MODE_x64
#else   //  WIN_64
#ifdef WIN32
#define MODE_x86
#endif  // WIN_32
#endif  // WIN_64


#if __GNUC__

#if __x86_64__ || __ppc64__
#define MODE_x64
#else   // __x86_64__ || __ppc64__
#define MODE_x86
#endif  // __x86_64__ || __ppc64__

#endif  // __GNUC__

#endif  // !defined(MODE_x64) && !defined(MODE_x86)


#if defined(MODE_x64) && defined(MODE_x86)
#error There was defined both MODE_x64 and MODE_x86
#endif  // defined(MODE_x64) && defined(MODE_x86)


#ifdef _MSC_VER

#if _DEBUG
#define DEBUG_MODE
#else   // _DEBUG
#undef DEBUG_MODE
#endif  // _DEBUG

#endif  // _MSC_VER


#ifdef QT_VERSION

#ifdef QT_DEBUG
#define DEBUG_MODE
#else   // QT_DEBUG
#undef DEBUG_MODE
#endif  // QT_DEBUG

#endif  // QT_VERSION


#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))


#ifdef MODE_x64

#ifndef SIZE_T
#define SIZE_T unsigned long long
#endif  // size_t
#ifndef S_SIZE_T
#define S_SIZE_T long long
#endif  // sign_size_t

#endif  // MODE_x64


#ifdef MODE_x86

#ifndef SIZE_T
#define SIZE_T unsigned int
#endif  // size_t
#ifndef S_SIZE_T
#define S_SIZE_T int
#endif  // sign_size_t

#endif  // MODE_x86


#ifndef UINT
#define UINT unsigned int
#endif  // UINT

#if !defined(UINT8) && defined(__UINT8_TYPE__)
#define UINT8 __UINT8_TYPE__
#endif  // !defined(UINT8) && defined(__UINT8_TYPE__)

#if !defined(UINT8) && (UCHAR_MAX == 0xff)
#define UINT8 unsigned char
#endif  // !defined(UINT8) && (UCHAR_MAX == 0xff)

#if !defined(INT8) && defined(__INT8_TYPE__)
#define INT8 __INT8_TYPE__
#endif  // !defined(INT8) && defined(__INT8_TYPE__)

#if !defined(INT8) && (SCHAR_MAX == 127)
#define INT8 signed char
#endif  // !defined(INT8) && (SCHAR_MAX == 127)

#ifndef UINT8
#error UINT8 was not defined
#endif  // UINT8

#ifndef INT8
#error INT8 was not defined
#endif  // INT8

#if !defined(UINT16) && defined(__UINT16_TYPE__)
#define UINT16 __UINT16_TYPE__
#endif  // !defined(UINT16) && defined(__UINT16_TYPE__)

#if !defined(UINT16) && (USHRT_MAX == 0xffff)
#define UINT16 unsigned short
#endif  // !defined(UINT16) && (USHRT_MAX == 0xffff)

#if !defined(INT16) && defined(__INT16_TYPE__)
#define INT16 __INT16_TYPE__
#endif  // !defined(INT16) && defined(__INT16_TYPE__)

#if !defined(INT16) && (SHRT_MAX == 32767)
#define INT16 short
#endif  // !defined(INT16) && (SHRT_MAX == 32767)

#ifndef UINT16
#error UINT16 was not defined
#endif  // UINT16

#ifndef INT16
#error INT16 was not defined
#endif  // INT16

#if !defined(UINT32) && defined(__UINT32_TYPE__)
#define UINT32 __UINT32_TYPE__
#endif  // !defined(UINT32) && defined(__UINT32_TYPE__)

#if !defined(UINT32) && (USHRT_MAX == 0xffffffffUL)
#define UINT32 unsigned short
#endif  // !defined(UINT32) && (USHRT_MAX == 0xffffffffUL)

#if !defined(UINT32) && (UINT_MAX == 0xffffffffUL)
#define UINT32 unsigned int
#endif  // !defined(UINT32) && (UINT_MAX == 0xffffffffUL)

#if !defined(UINT32) && (ULONG_MAX == 0xffffffffUL)
#define UINT32 unsigned long
#endif  // !defined(UINT32) && (ULONG_MAX == 0xffffffffUL)

#if !defined(INT32) && defined(__INT32_TYPE__)
#define INT32 __INT32_TYPE__
#endif  // !defined(INT32) && defined(__INT32_TYPE__)

#if !defined(INT32) && (SHRT_MAX == 2147483647L)
#define INT32 short
#endif  // !defined(INT32) && (SHRT_MAX == 2147483647L)

#if !defined(INT32) && (INT_MAX == 2147483647L)
#define INT32 int
#endif  // !defined(INT32) && (INT_MAX == 2147483647L)

#if !defined(INT32) && (LONG_MAX == 2147483647L)
#define INT32 long
#endif  // !defined(INT32) && (LONG_MAX == 2147483647L)

#ifndef UINT32
#error UINT32 was not defined
#endif  // UINT32

#ifndef INT32
#error INT32 was not defined
#endif  // INT32

#if !defined(UINT64) && defined(__UINT64_TYPE__)
#define UINT64 __UINT64_TYPE__
#endif  // !defined(UINT64) && defined(__UINT64_TYPE__)

#if !defined(UINT64) && (UINT_MAX == 0xffffffffffffffffULL)
#define UINT64 unsigned int
#endif  // !defined(UINT64) && (UINT_MAX == 0xffffffffffffffffULL)

#if !defined(UINT64) && (ULONG_MAX == 0xffffffffffffffffULL)
#define UINT64 unsigned long
#endif  // !defined(UINT64) && (ULONG_MAX == 0xffffffffffffffffULL)

#if !defined(UINT64) && (ULLONG_MAX == 0xffffffffffffffffULL)
#define UINT64 unsigned long long
#endif  // !defined(UINT64) && (ULLONG_MAX == 0xffffffffffffffffULL)

#if !defined(INT64) && defined(__INT64_TYPE__)
#define INT64 __INT64_TYPE__
#endif  // !defined(INT64) && defined(__INT64_TYPE__)

#if !defined(INT64) && (INT_MAX == 9223372036854775807LL)
#define INT64 int
#endif  // !defined(INT64) && (INT_MAX == 9223372036854775807LL)

#if !defined(INT64) && (LONG_MAX == 9223372036854775807ULL)
#define INT64 long
#endif  // !defined(INT64) && (LONG_MAX == 9223372036854775807LL)

#if !defined(INT64) && (LLONG_MAX == 9223372036854775807ULL)
#define INT64 long long
#endif  // !defined(INT64) && (LLONG_MAX == 9223372036854775807LL)

#ifndef UINT64
#error UINT64 was not defined
#endif  // UINT32

#ifndef INT64
#error INT64 was not defined
#endif  // INT32


#endif  // !DEFGENERAL_H