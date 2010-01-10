//
// coroutine.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef COROUTINE_HPP
#define COROUTINE_HPP

class coroutine
{
public:
  coroutine() : value_(0) {}
  bool is_child() const { return value_ < 0; }
  bool is_parent() const { return !is_child(); }
private:
  friend class coroutine_ref;
  int value_;
};

class coroutine_ref
{
public:
  coroutine_ref(coroutine& c) : value_(c.value_) {}
  coroutine_ref(coroutine* c) : value_(c->value_) {}
  operator int() const { return value_; }
  int& operator=(int v) { return value_ = v; }
private:
  void operator=(const coroutine_ref&);
  int& value_;
};

#define CORO_REENTER(c) \
  switch (coroutine_ref _coro_value = c) \
    if (_coro_value) \
    { \
      goto bail_out_of_coroutine; \
      bail_out_of_coroutine: \
      break; \
    } \
    else case 0:

#define CORO_YIELD \
  for (_coro_value = __LINE__;;) \
    if (_coro_value == 0) \
    { \
      case __LINE__: ; \
      break; \
    } \
    else \
      switch (_coro_value ? 0 : 1) \
        for (;;) \
          if (_coro_value) \
            goto bail_out_of_coroutine; \
          else case 0:

#define CORO_FORK \
  for (_coro_value = -__LINE__;; _coro_value = __LINE__) \
    if (_coro_value == __LINE__) \
    { \
      case -__LINE__: ; \
      break; \
    } \
    else

#endif // COROUTINE_HPP
