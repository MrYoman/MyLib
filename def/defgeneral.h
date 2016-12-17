#pragma once

#ifndef DEFGENERAL_H
#define DEFGENERAL_H


#if !defined(__GNUC__ ) && !defined(_MSC_VER)
#error GNU or MSVC compiler required
#endif  // !defined(__GNUC__ ) && !defined(_MSC_VER)


#include <limits.h>
#include <stdint.h>


#if !defined(MODE_x64) && !defined(MODE_x86)


#if defined(WIN64) || defined(_WIN64)
#define MODE_x64
#else   // defined(WIN64) || defined(_WIN64)
#if defined(WIN32) || defined(_WIN32)
#define MODE_x86
#endif  // defined(WIN32) || defined(_WIN32)
#endif  // defined(WIN64) || defined(_WIN64)


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


#ifndef UINT
#define UINT unsigned int
#endif  // UINT

#if !defined(UINT8)

#if __GNUC__
#define UINT8 uint8_t
#endif  // __GNUC__

#ifdef _MSC_VER
#define UINT8 unsigned __int8
#endif  // _MSC_VER

#endif  // !defined(UINT8)

#ifndef UINT8
#error UINT8 was not defined
#endif  // UINT8

#if !defined(INT8)

#if __GNUC__
#define INT8 int8_t
#endif  // __GNUC__

#ifdef _MSC_VER
#define UINT8 signed __int8
#endif  // _MSC_VER

#endif  // !defined(INT8)

#ifndef INT8
#error INT8 was not defined
#endif  // INT8

#if !defined(UINT16)

#if __GNUC__
#define UINT16 uint16_t
#endif  // __GNUC__

#ifdef _MSC_VER
#define UINT16 unsigned __int16
#endif  // _MSC_VER

#endif  // !defined(UINT16)

#ifndef UINT16
#error UINT16 was not defined
#endif  // UINT16

#if !defined(INT16)

#if __GNUC__
#define INT16 int16_t
#endif  // __GNUC__

#ifdef _MSC_VER
#define INT16 signed __int16
#endif  // _MSC_VER

#endif  // !defined(INT16)

#ifndef INT16
#error INT16 was not defined
#endif  // INT16

#if !defined(UINT32)

#if __GNUC__
#define UINT32 uint32_t
#endif  // __GNUC__

#ifdef _MSC_VER
#define UINT32 unsigned __int32
#endif  // _MSC_VER

#endif  // !defined(UINT32)

#ifndef UINT32
#error UINT32 was not defined
#endif  // UINT32

#if !defined(INT32)

#if __GNUC__
#define INT32 int32_t
#endif  // __GNUC__

#ifdef _MSC_VER
#define INT32 signed __int32
#endif  // _MSC_VER

#endif  // !defined(INT32)

#ifndef INT32
#error INT32 was not defined
#endif  // INT32

#if !defined(UINT64)

#if __GNUC__
#define UINT64 uint64_t
#endif  // __GNUC__

#ifdef _MSC_VER
#define UINT64 unsigned __int64
#endif  // _MSC_VER

#endif  // !defined(UINT64)

#ifndef UINT64
#error UINT64 was not defined
#endif  // UINT64

#if !defined(INT64)

#if __GNUC__
#define INT64 int64_t
#endif  // __GNUC__

#ifdef _MSC_VER
#define INT64 signed __int64
#endif  // _MSC_VER

#endif  // !defined(INT64)

#ifndef INT64
#error INT64 was not defined
#endif  // INT64


#ifdef MODE_x64

#ifndef SIZE_T
#define SIZE_T UINT64
#endif  // size_t

#ifndef S_SIZE_T
#define S_SIZE_T INT64
#endif  // sign_size_t

#endif  // MODE_x64


#ifdef MODE_x86

#ifndef SIZE_T
#define SIZE_T UINT32
#endif  // size_t

#ifndef S_SIZE_T
#define S_SIZE_T INT32
#endif  // sign_size_t

#endif  // MODE_x86


#endif  // !DEFGENERAL_H
