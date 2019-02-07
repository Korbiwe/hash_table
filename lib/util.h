//
// Created by korbiwe on 2019-02-05.
//

#ifndef HASH_TABLE_UTIL_H
#define HASH_TABLE_UTIL_H


#include <cstddef>
#include <functional>

extern size_t round_up_to_power_of_two(size_t num);

template <typename TFunction>
class TimerWrapper {
public:
  TimerWrapper(TFunction function, clock_t& elapsed_time):
      call(function),
      _start_time(::clock()),
      _elapsed_time(elapsed_time)
  {
  }

  ~TimerWrapper()
  {
    const clock_t _end_time = ::clock();
    const clock_t diff = (_end_time - _start_time);
    _elapsed_time += diff;
  }

  TFunction call;
private:
  const clock_t _start_time;
  clock_t& _elapsed_time;
};


template <typename TFunction>
TimerWrapper<TFunction> test_time(TFunction function, clock_t& timer)
{
  return TimerWrapper<TFunction>(function, timer);
}

#endif //HASH_TABLE_UTIL_H
