#pragma once
#include <array>
#include <string>
#include "Table.h"

class Query {
  private:
  std::array<Table, 3> tables {{}};
  
  public:
  Query() = default;
  Query(const std::array<Table, 3>& tables);

  const std::array<Table, 3>& getTables() const;
  const Table* getTableById(const long& tableId) const;
  const Table* getTableByName(const std::string& tableName) const;
  
  void setTables(const std::array<Table, 3>& tables);
  
  void addTable(const Table& table);
  void removeTableById(const long& tableId);

};