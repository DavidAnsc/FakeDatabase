#include <iostream>
#include "DataModels/DatabaseRelated/Query.h"

Query::Query(const std::array<Table, 3>& tables) : tables(tables) {}

const std::array<Table, 3>& Query::getTables() const {
  return tables;
}
const Table* Query::getTableById(const long& tableId) const {
  for (const auto& table : tables) {
    if (table.getId() == tableId) {
      return &table;
    }
  }
  return nullptr;
}

const Table* Query::getTableByName(const std::string& tableName) const {
  for (const auto& table : tables) {
    if (table.getName() == tableName) {
      return &table;
    }
  }
  return nullptr;
}

void Query::setTables(const std::array<Table, 3>& tables) {
  this->tables = tables;
}

void Query::addTable(const Table& table) {
  for (auto& t : tables) {
    if (t.getId() == 0) {
      t = table;
      return;
    }
  }
  std::cerr << "No space to add new table" << std::endl;
}
void Query::removeTableById(const long& tableId) {
  for (auto& table : tables) {
    if (table.getId() == tableId) {
      table = Table(); // Reset the table to default
      return;
    }
  }
  std::cerr << "Table with ID " << tableId << " not found" << std::endl;
}