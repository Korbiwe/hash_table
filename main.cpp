#include <iostream>
#include "lib/HashMap.hpp"

int main() {
    HashMap<std::string, std::string> map;
    for (int i = 0; i < 5000; i++) {
        map.insert({ std::to_string(i), std::to_string(i + 1) });
    }
    std::cout << map.at("3000") << std::endl;
    map["3000"] = "wow";
    std::cout << map["3000"] << std::endl;
    std::cout << map["6000"] << " <<< should be empty" << std::endl;
    map.erase("6000");
    //map.at("6000"); throws
    return 0;
}