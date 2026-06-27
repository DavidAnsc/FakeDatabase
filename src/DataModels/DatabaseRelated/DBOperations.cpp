#include "DataModels/DatabaseRelated/DBOperations.h"
#include "DataModels/DatabaseRelated/Commands.h"
#include <iostream>
#include <sstream>

int getTableIdByName(std::string tableName);
int getColumnIdByName(int tableId, std::string columnName);

// k table display <tableName>
void DBOperations::displayTable(const std::array<std::string, 4>& args) {
  int tableId = getTableIdByName(args.at(2));
  if (tableId == -1) {
    return;
  }
  std::cout << Commands::displayTable(tableId) << std::endl;
}

// k table create <tableName>
void DBOperations::createTable(const std::array<std::string, 4>& args) {
  std::cout << Commands::createTable(args.at(2)) << std::endl;
}

// k table drop <tableName>
void DBOperations::dropTable(const std::array<std::string, 4>& args) {
  int tableId = getTableIdByName(args.at(2));
  if (tableId == -1) {
    return;
  }
  std::cout << Commands::dropTable(tableId) << std::endl;
}

// k column create <tableName> <columnName>
void DBOperations::createColumn(const std::array<std::string, 4>& args) {
  int tableId = getTableIdByName(args.at(2));
  if (tableId == -1) {
    return;
  }
  std::cout << Commands::createColumn(tableId, args.at(3)) << std::endl;
}

// k column drop <tableName> <columnName>
void DBOperations::dropColumn(const std::array<std::string, 4>& args) {
  int tableId = getTableIdByName(args.at(2));
  if (tableId == -1) {
    return;
  }
  int columnId = getColumnIdByName(tableId, args.at(3));
  if (columnId == -1) {
    return;
  }
  std::cout << Commands::dropColumn(tableId, getColumnIdByName(tableId, args.at(3))) << std::endl;
}

// k row insert <tableName> <rowData>
void DBOperations::insertRow(const std::array<std::string, 4>& args) {
  int tableId = getTableIdByName(args.at(2));
  if (tableId == -1) {
    return;
  }
  std::stringstream ss(args.at(3));
  std::string token;
  std::array<std::any, 5> result;

  int i = 0;
  while (std::getline(ss, token, ',')) {
    result[i] = token;
    ++i;
    if (i >= result.size()) {
      break;
    }
  }
  std::cout << Commands::insertRow(tableId, result) << std::endl;
}

// k update <tableName> <rowId> <rowData>
void DBOperations::updateRow(const std::array<std::string, 4>& args) {
  int tableId = getTableIdByName(args.at(1));
  if (tableId == -1) {
    return;
  }
  int rowId = Commands::stringToInt(args.at(2));
  if (rowId == -999999) {
    std::cout << "invalid row ID: '" << args.at(2) << "'" << std::endl;
    return;
  }
  std::stringstream ss(args.at(3));
  std::string token;
  std::array<std::any, 5> result;

  int i = 0;
  while (std::getline(ss, token, ',')) {
    result[i] = token;
    ++i;
    if (i >= result.size()) {
      break;
    }
  }
  std::cout << Commands::updateRow(tableId, rowId, result) << std::endl;
}

// k delete <tableName> <rowId>
void DBOperations::deleteRow(const std::array<std::string, 4>& args) {
  int tableId = getTableIdByName(args.at(1));
  if (tableId == -1) {
    return;
  }
  int rowId = Commands::stringToInt(args.at(2));
  if (rowId == -999999) {
    std::cout << "invalid row ID: '" << args.at(2) << "'" << std::endl;
    return;
  }
  std::cout << Commands::deleteRow(tableId, rowId) << std::endl;
}


int getTableIdByName(std::string tableName) {
  int tableId = Commands::query.getTableByName(tableName).has_value() ? Commands::query.getTableByName(tableName).value().getId() : -1;
  if (tableId == -1) {
    std::cout << "table with name '" << tableName << "' not found" << std::endl;
    return -1;
  }
  return tableId;
}
int getColumnIdByName(int tableId, std::string columnName) {
  auto table = Commands::query.getTableById(tableId);
  if (!table.has_value()) {
    std::cout << "table with ID " << tableId << " not found" << std::endl;
    return -1;
  }

  auto columns = table.value().getColumns();
  for (size_t i = 0; i < columns.size(); ++i) {
    if (columns.at(i) == columnName) {
      return static_cast<int>(i);
    }
  }

  std::cout << "column with name '" << columnName << "' not found in table named: '" << table.value().getName() << "'" << std::endl;
  return -1;
}