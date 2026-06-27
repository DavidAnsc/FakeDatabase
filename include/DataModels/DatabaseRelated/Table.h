#pragma once
#include <array>
#include <string>
#include <optional>
#include "Row.h"

class Table {
  private:
  long id {};
  std::string name {};
  std::optional<std::string> primaryKey {};
  std::array<std::string, 5> columns {{}};
  std::array<Row, 10> rows {{}};
  
  public:
  Table() = default;
  Table(long id, const std::string& name, std::optional<std::string> primaryKey, std::array<std::string, 5> columns, std::array<Row, 10> rows);

  const long& getId() const;
  const std::string& getName() const;
  const std::optional<std::string>& getPrimaryKey() const;
  const std::array<std::string, 5>& getColumns() const;
  const std::array<Row, 10>& getRows() const;

  void setId(const long& id);
  void setName(const std::string& name);
  void setPrimaryKey(const std::optional<std::string>& primaryKey);
  void setColumns(const std::array<std::string, 5>& columns);
  void setRows(const std::array<Row, 10>& rows);

  const std::optional<std::string> convertToStr(const std::any& data) const;
};