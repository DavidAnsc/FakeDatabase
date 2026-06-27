#include "Kits/CommandParser.h"
#include <sstream>
#include <iostream>
#include <any>
#include <chrono>

std::array<std::string, 4> quickParse(const std::string& command);

int main() {
  std::string original {"1 fjaisofjofjiqowjfoawjfifjawoifjaiwofjiqwjf jwqifojwqoifjwiqofbwqffasiofjqwoijfqwjfiowqjfio21859791287519825 218957192857189257fbwqiufbqiwbiofqw"};

  auto start_time1 = std::chrono::steady_clock::now();
  for (int i = 0; i < 122550; ++i) {
    // std::array<std::string, 4> result1 {};
    // std::cout << 
    quickParse(original).at(0);
    // << std::endl;
  }
  auto end_time1 = std::chrono::steady_clock::now();
  auto elapsed_time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time1 - start_time1);

  
  auto start_time2 = std::chrono::steady_clock::now();
  for (int i = 0; i < 122550; ++i) {
    // std::array<std::string, 4> result2 {};
    // std::cout << 
    CommandParser::parseToArgs(original).at(0);
    // << std::endl;
  }
  auto end_time2 = std::chrono::steady_clock::now();
  auto elapsed_time2 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time2 - start_time2);


  std::cout << "time taken by quickParse: " << elapsed_time1.count() << " milliseconds" << std::endl;
  std::cout << "time taken by CommandParser::parseToArgs: " << elapsed_time2.count() << " milliseconds" << std::endl;
  
  return 0;
}

std::array<std::string, 4> quickParse(const std::string& command) {
  std::stringstream ss(command);
  std::string token;
  std::array<std::string, 4> result;
  
  int i = 0;
  while (std::getline(ss, token, ',')) {
    result[i] = token;
    ++i;
    if (i >= result.size()) {
      break;
    }
  }

  return result;
}

