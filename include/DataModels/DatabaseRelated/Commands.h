#pragma once
#include <string>
#include <array>
#include "Query.h"


class Commands {
  public:
  static Query query;

  static std::string displayTable(const long& tableId);
  static std::string createTable(const std::string& tableName);
  static std::string dropTable(const long& tableId);
  static std::string createColumn(const long& tableId, const std::string& columnName);
  static std::string dropColumn(const long& tableId, const long& columnId);
  static std::string insertRow(const long& tableId, const std::array<std::any, 5>& rowData);
  static std::string updateRow(const long& tableId, const long& rowId, const std::array<std::any, 5>& rowData);
  static std::string deleteRow(const long& tableId, const long& rowId);
  static int stringToInt(const std::string& str);
  
};