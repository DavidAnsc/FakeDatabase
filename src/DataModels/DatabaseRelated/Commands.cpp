#include "DataModels/DatabaseRelated/Commands.h"
#include "DataModels/DatabaseRelated/Query.h"
#include <string>
#include <cmath>
#include <iostream>
#include <charconv>

Query Commands::query {};

int countDigits(int number);

std::string Commands::displayTable(const long& tableId) {
  if (query.getTableById(tableId) == nullptr) {
    return "table with ID " + std::to_string(tableId) + " not found";
  }
  const Table& table = *query.getTableById(tableId);
  auto columns = table.getColumns();
  std::array<int, 5> columnWidths {};
  int idColumnWidth {};
  for (int i = -1; i < static_cast<int>(sizeof(columns) / sizeof(columns[0])); ++i) {

    if (i == -1) {
      int biggestIdLength {2}; // two is the length of 'id'
      for (const auto& row : table.getRows()) {
        if (row.getId() == -1) {
          continue;
        }
        std::cout << "comparing: " << row.getId() << " and " << biggestIdLength << std::endl;
        biggestIdLength = std::max(biggestIdLength, countDigits(row.getId()));
        std::cout << biggestIdLength << " is the winner" << std::endl;
      }
      idColumnWidth = biggestIdLength;
      continue;
    }

    int biggestColumnLength = 0;
    std::string columnNameValue = columns.at(i);
    int maxColumnLength {};
    for (const auto& row : table.getRows()) {
      if (row.getId() != -1) {
        auto columnValue = table.convertToStr(row.getData().at(i));
        if (columnValue.has_value()) {
          maxColumnLength = std::max(maxColumnLength, static_cast<int>(columnValue.value().length()));
        }
      }
    }
    biggestColumnLength = std::max(maxColumnLength, static_cast<int>(columnNameValue.length()));
    columnWidths.at(i) = biggestColumnLength;
  }
  std::cout << idColumnWidth << std::endl;

  std::string result = "Table: " + table.getName() + "\n";
  // printing the id
  result += ("\033[1m" + std::string("id") + "\033[0m");
  for (int j = 0; j < idColumnWidth-2; ++j) { // not 2 because ...
    result += " ";
  }
  result += " | ";
  // printing the actual column info
  for (size_t i = 0; i < sizeof(columns) / sizeof(columns[0]); ++i) {
    std::string column = columns.at(i);
    if (!column.empty()) {
      result += "\033[1m" + column + "\033[0m";
      for (int j = 0; j < columnWidths.at(i) - column.length(); ++j) {
        result += " ";
      }
      result += " | ";
    }
  }
  result += "\n";

  // printing the rows
  for (const auto& row : table.getRows()) {
    if (row.getId() == -1) {
      continue;
    }

    result += std::to_string(row.getId());
    for (int i = 0; i < idColumnWidth - countDigits(row.getId()); ++i) {
      result += " ";
    }
    result += " | ";

    for (int j = 0; j < row.getData().size(); ++j) {
      const auto& data = row.getData().at(j);
      if (!data.has_value()) {
        for (int i = 0; i < columnWidths.at(j); ++i) {
          result += " ";
        }
        result += " | ";
        continue;
      }

      table.convertToStr(data).has_value() ? result += table.convertToStr(data).value() : result += "NULL";
      for (int i = 0; i < columnWidths.at(j) - table.convertToStr(data).value().length(); ++i) {
        result += " ";
      }
      result += " | ";

    }
    result += "\n";
  }
  return result;
}

std::string Commands::createTable(const std::string& tableName) {
  Table newTable {
    static_cast<long>(query.getTables().size()) + 1,
    tableName,
    std::nullopt,
    {{}},
    {{}}
  };
  
  std::cout << newTable.getName() << std::endl;
  
  query.addTable(newTable);
  return "created table named: '" + tableName + "'";
  
}

std::string Commands::dropTable(const long& tableId) {
  const Table* tablePtr = query.getTableById(tableId);
  if (tablePtr == nullptr) {
    return "table with ID " + std::to_string(tableId) + " not found";
  }
  const Table& table = *tablePtr;
  query.removeTableById(tableId);
  return "dropped table named: '" + table.getName() + "'";
}

std::string Commands::createColumn(const long& tableId, const std::string& columnName) {
  const Table* tablePtr = query.getTableById(tableId);
  if (tablePtr == nullptr) {
    return "table with ID " + std::to_string(tableId) + " not found";
  }
  Table table = *tablePtr;
  auto columnBefore = table.getColumns();
  for (size_t i = 0; i < columnBefore.size(); ++i) {
    if (columnBefore.at(i).empty()) {
      columnBefore.at(i) = columnName;
      break;
    }
    if (i == columnBefore.size() - 1) {
      return "table named: '" + table.getName() + "' has no more space for new columns";
    }
  }
  table.setColumns(columnBefore);

  query.removeTableById(tableId);
  query.addTable(table);
  std::string tableName = table.getName();
  return "created column named: '" + columnName + "' in table named: '" + tableName + "'";
}

std::string Commands::dropColumn(const long& tableId, const long& columnId) {
  const Table* tablePtr = query.getTableById(tableId);
  if (tablePtr == nullptr) {
    return "table with ID " + std::to_string(tableId) + " not found";
  }
  Table table = *tablePtr;

  std::array<std::string, 5> columns = table.getColumns();

  if (columnId < 0 || columnId >= columns.size() || columns.at(columnId).empty()) {
    return "column with ID " + std::to_string(columnId) + " not found in table named: '" + table.getName() + "'";
  }

  std::string columnName = columns.at(columnId);
  columns.at(columnId) = "";
  table.setColumns(columns);
  query.removeTableById(tableId);
  query.addTable(table);

  return "dropped column named: '" + columnName + "' from table named: '" + table.getName() + "'";
}

std::string Commands::insertRow(const long& tableId, const std::array<std::any, 5>& rowData) {
  const Table* tablePtr = query.getTableById(tableId);
  if (tablePtr == nullptr) {
    return "table with ID " + std::to_string(tableId) + " not found";
  }
  Table table = *tablePtr;
  std::array<Row, 10> rows = table.getRows();
  for (size_t i = 0; i < rows.size(); ++i) {
    Row& row = rows.at(i);
    if (row.getId() == -1) { // the default empty id for row is -1
      Row newRow {
        static_cast<long>(i),
        {rowData[0], rowData[1], rowData[2], rowData[3], rowData[4]}
      };

      rows.at(i) = newRow;
      table.setRows(rows);
      query.removeTableById(tableId);
      query.addTable(table);
      return "inserted row with ID " + std::to_string(newRow.getId()) + " into table named: '" + table.getName() + "'";
    }
    if (i == rows.size() - 1) {
      return "table named: '" + table.getName() + "' has no more space for new rows";
    }
  }
  return "failed to insert row into table named: '" + table.getName() + "'";
}

std::string Commands::updateRow(const long& tableId, const long& rowId, const std::array<std::any, 5>& rowData) {
  const Table* tablePtr = query.getTableById(tableId);
  if (tablePtr == nullptr) {
    return "table with ID " + std::to_string(tableId) + " not found";
  }
  Table table = *tablePtr;

  auto rows = table.getRows();
  if (rowId < 0 || rowId >= rows.size() || rows.at(rowId).getId() == -1) {
    return "row with ID " + std::to_string(rowId) + " not found in table named: '" + table.getName() + "'";
  }

  Row updatedRow {
    rowId,
    {rowData[0], rowData[1], rowData[2], rowData[3], rowData[4]}
  };

  rows.at(rowId) = updatedRow;
  table.setRows(rows);

  query.removeTableById(tableId);
  query.addTable(table);

  return "updated row with ID " + std::to_string(rowId) + " in table named: '" + table.getName() + "'";
}

std::string Commands::deleteRow(const long& tableId, const long& rowId) {
  const Table* tablePtr = query.getTableById(tableId);
  if (tablePtr == nullptr) {
    return "table with ID " + std::to_string(tableId) + " not found";
  }
  Table table = *tablePtr;

  std::array<Row, 10> rows = table.getRows();
  if (rowId < 0 || rowId >= rows.size() || rows.at(rowId).getId() == -1) {
    return "row with ID " + std::to_string(rowId) + " not found in table named: '" + table.getName() + "'";
  }

  rows.at(rowId) = Row(); // Reset the row to default (id -1)
  table.setRows(rows);

  query.removeTableById(tableId);
  query.addTable(table);

  return "deleted row with ID " + std::to_string(rowId) + " from table named: '" + table.getName() + "'";
}

int Commands::stringToInt(const std::string& str) {
    int out_value {};
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), out_value);

    if (ec == std::errc{}) {
        // Optional: Check if there are leftover unparsed trailing characters
        if (ptr == str.data() + str.size()) {
            return out_value; // Complete success
        }
        return -999999; // Trailing garbage characters present
    }
    
    return -999999; 
}

int countDigits(int number) {
    int count = 0;
    // Handled using a do-while loop to ensure 0 counts as 1 digit
    do {
        count++;
        number /= 10;
    } while (number != 0);
    
    return count;
}