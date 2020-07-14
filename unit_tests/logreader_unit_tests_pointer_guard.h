/**
* \file logreader_unit_tests_pointer_guard.h
*/

#pragma once
#ifndef LOGREADER_UNIT_TESTS_POINTER_GUARD_H_INCLUDED
#define LOGREADER_UNIT_TESTS_POINTER_GUARD_H_INCLUDED

#include <stddef.h>

template<typename T>
class pointer_guard
{
public:
  inline explicit pointer_guard(T* ptr) : ptr_(ptr) {}
  inline ~pointer_guard() {delete ptr_;}
  inline operator T*() const {return ptr_;}
  inline operator bool() const {return (NULL !=ptr_);}
  inline T* operator->() const {return ptr_;}
private:
  T* ptr_;
};

#endif // !LOGREADER_UNIT_TESTS_POINTER_GUARD_H_INCLUDED
