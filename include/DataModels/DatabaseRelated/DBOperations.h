#pragma once
#include <string>
#include <iostream>
#include <any>

namespace DBOperations {
  void displayTable(const std::array<std::string, 4>& args);
  void createTable(const std::array<std::string, 4>& args);
  void dropTable(const std::array<std::string, 4>& args);
  void createColumn(const std::array<std::string, 4>& args);
  void dropColumn(const std::array<std::string, 4>& args);
  void insertRow(const std::array<std::string, 4>& args);
  void updateRow(const std::array<std::string, 4>& args);
  void deleteRow(const std::array<std::string, 4>& args);
}