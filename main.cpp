#include <iostream>
#include "lib/HashTable.hpp"

#define DEBUG

int main() {
  lib::HashTable<int, int> map;
  for (int i = 0; i < 5000; i++) {
    map.insert({i, i + 1});
  }
  std::cout << map.at(3000) << " <<< should be 3001" << std::endl;
  map[3000] = 4999;
  std::cout << map[3000] << " <<< should be 4999" << std::endl;
  std::cout << map[6000] << " <<< should be default constructed" << std::endl;
  map.erase(6000);
  std::cout << "Next statement will throw" << std::endl;
  try {
    map.at(6000);
  } catch (std::out_of_range& e) {
    std::cout << "Caught std::out_of_range. It says: " << e.what() << std::endl;
  }
  return 0;
}