#include <iostream>
#include "Kits/CommandParser.h"
#include "DataModels/DatabaseRelated/Commands.h"
#include "DataModels/DatabaseRelated/DBOperations.h"

void sayHello(const std::array<std::string, 4>& args) {
  std::cout << "Hello, " << args.at(1) << "!" << std::endl;
}
void sayGoodbye(const std::array<std::string, 4>& args) {
  std::cout << "James An!" << std::endl;
}

int main() {
  
  std::array<OperationArray, 8> prefilledCommands {
    {
      OperationArray {DBOperations::displayTable, {"table", "display", "${ARG}", ""}},
      OperationArray {DBOperations::createTable, {"table", "create", "${ARG}", ""}},
      OperationArray {DBOperations::dropTable, {"table", "drop", "${ARG}", ""}},
      OperationArray {DBOperations::createColumn, {"column", "create", "${ARG}", "${ARG}"}},
      OperationArray {DBOperations::dropColumn, {"column", "drop", "${ARG}", "${ARG}"}},
      OperationArray {DBOperations::insertRow, {"row", "insert", "${ARG}", "${ARG}"}},
      OperationArray {DBOperations::updateRow, {"update", "${ARG}", "${ARG}", "${ARG}"}},
      OperationArray {DBOperations::deleteRow, {"delete", "${ARG}", "${ARG}", ""}}
    }
  };
  
  CommandParser::setCommands(prefilledCommands);
  
  while (true) {
    std::string input {""};
    std::getline(std::cin, input);
    auto args = CommandParser::parseToArgs(input);
    CommandParser::executeCommands(args);
    std::cout << std::endl;
  }
  
  return 0;
}

// int main() {

//   std::cout << Commands::createTable("Users") << std::endl;

//   int tableId {};

//   for (auto& table : Commands::query.getTables()) {
//     if (table.getName() == "Users") {
//       tableId = table.getId();
//       break;
//     }
//   }


//   std::cout << Commands::createColumn(tableId, "Name") << std::endl;
//   std::cout << Commands::createColumn(tableId, "Email") << std::endl;
//   std::cout << Commands::createColumn(tableId, "Age") << std::endl;
//   std::cout << Commands::createColumn(tableId, "City") << std::endl;
//   std::cout << Commands::createColumn(tableId, "Country") << std::endl;
//   std::cout << Commands::insertRow(tableId, {"John Doe", "john.doe@example.com", 30, "New York", "USA"}) << std::endl;
//   std::cout << Commands::insertRow(tableId, {"Jane Smith", "jane.smith@example.com", 25, "Los Angeles", "USA"}) << std::endl;
//   std::cout << Commands::displayTable(tableId) << std::endl;
//   return 0;
// }