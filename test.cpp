//
// Created by korbiwe on 2019-02-07.
//

#include <cassert>
#include <iostream>
#include "lib/HashMap.hpp"

void test_initially_empty() {
  lib::HashMap<std::string, std::string> hm;

  assert(hm.empty() && "HashMap must be initially empty");
  assert(hm.size() == 0 && "HashMap must have initial size of 0"); // NOLINT(readability-container-size-empty)
}

void test_throws_when_empty() {
  lib::HashMap<std::string, std::string> hm;

  try {
    hm.at("smth");
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCSimplifyInspection"
    assert(false && "Expected HashMap to throw std::out_of_range when calling HashMap::at with an invalid key");
#pragma clang diagnostic pop
  } catch (std::out_of_range& e) {}
}

void test_no_value_mismatch() {
  lib::HashMap<std::string, std::string> hm;

  for (size_t i = 0; i < 10000; i++) {
    std::string key(i, char(i % 254));
    std::string value(i, char(i % 254 + 1));
    hm.insert({ key, value });
    assert(hm.at(key) == value && "Value mismatch");
  }

}

void test_bracket_default() {
  lib::HashMap<std::string, std::string> hm;

  assert(hm["test"].empty() && "Expecting bracket operator to use the default constructor of T");

  try {
    hm.at("test");
  } catch (std::out_of_range& e) {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCSimplifyInspection"
    assert(false && "Expected to not throw");
#pragma clang diagnostic pop
  }
}

void test_erase() {
  lib::HashMap<std::string, std::string> hm;

  hm.insert({ "test", "test" });

  hm.erase("test");

  try {
    hm.at("test");
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCSimplifyInspection"
    assert(false && "Expected to throw std::out_of_range for an erased element");
#pragma clang diagnostic pop
  } catch (std::out_of_range& e) {}

}

void test_string_string_map() {
  clock_t timer = 0;
  std::cout << "Starting test_initially_empty" << std::endl << "..." << std::endl;
  test_time(test_initially_empty, timer).call();
  std::cout << "Passed in " << timer << " ticks (" << std::fixed << ((double) (timer) / CLOCKS_PER_SEC) << " seconds)" << std::endl << std::endl;

  timer = 0;
  std::cout << "Starting test_throws_when_empty" << std::endl << "..." << std::endl;
  test_time(test_throws_when_empty, timer).call();
  std::cout << "Passed in " << timer << " ticks (" << std::fixed << ((double) (timer) / CLOCKS_PER_SEC) << " seconds)" << std::endl << std::endl;

  timer = 0;
  std::cout << "Starting test_no_value_mismatch" << std::endl << "..." << std::endl;
  test_time(test_no_value_mismatch, timer).call();
  std::cout << "Passed in " << timer << " ticks (" << std::fixed << ((double) (timer) / CLOCKS_PER_SEC) << " seconds)" << std::endl << std::endl;

  timer = 0;
  std::cout << "Starting test_bracket_default" << std::endl << "..." << std::endl;
  test_time(test_bracket_default, timer).call();
  std::cout << "Passed in " << timer << " ticks (" << std::fixed << ((double) (timer) / CLOCKS_PER_SEC) << " seconds)" << std::endl << std::endl;

  timer = 0;
  std::cout << "Starting test_erase" << std::endl << "..." << std::endl;
  test_time(test_erase, timer).call();
  std::cout << "Passed in " << timer << " ticks (" << std::fixed << ((double) (timer) / CLOCKS_PER_SEC) << " seconds)" << std::endl << std::endl;
}

int main() {
  test_string_string_map();
  std::cout << "All tests passed!" << std::endl;
  return 0;
}
