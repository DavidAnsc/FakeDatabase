#include "DataModels/DatabaseRelated/Table.h"
#include <optional>
#include <array>
#include <string>

Table::Table(long id, const std::string& name, std::optional<std::string> primaryKey, std::array<std::string, 5> columns, std::array<Row, 10> rows) 
  : id(id), 
  name(name),
  primaryKey(primaryKey), 
  columns(columns), 
  rows(rows) {}

const long& Table::getId() const {
  return id;
}
const std::string& Table::getName() const {
  return name;
}
const std::optional<std::string>& Table::getPrimaryKey() const {
  return primaryKey;
}
const std::array<std::string, 5>& Table::getColumns() const {
  return columns;
}
const std::array<Row, 10>& Table::getRows() const {
  return rows;
}

void Table::setId(const long& id) {
  this->id = id;
}
void Table::setName(const std::string& name) {
  this->name = name;
}
void Table::setPrimaryKey(const std::optional<std::string>& primaryKey) {
  this->primaryKey = primaryKey;
}
void Table::setColumns(const std::array<std::string, 5>& columns) {
  this->columns = columns;
}
void Table::setRows(const std::array<Row, 10>& rows) {
  this->rows = rows;
}

const std::optional<std::string> Table::convertToStr(const std::any& data) const {
  if (data.type() == typeid(std::string)) {
    return std::any_cast<std::string>(data);
  } else if (data.type() == typeid(const char*)) {
    return std::any_cast<const char*>(data);
  } else if (data.type() == typeid(int)) {
    return std::to_string(std::any_cast<int>(data));
  } else {
    return std::nullopt;
  }
}
