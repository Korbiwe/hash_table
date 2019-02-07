//
// Created by korbiwe on 2019-02-05.
//

#include "util.h"

extern size_t round_up_to_power_of_two(size_t num) {
  num--;
  num |= num >> 1;
  num |= num >> 2;
  num |= num >> 4;
  num |= num >> 8;
  num |= num >> 16;
  num++;
  return num;
}

