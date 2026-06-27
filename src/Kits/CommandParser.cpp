#include <string>
#include <sstream>
#include <iostream>
#include <any>
#include "Kits/CommandParser.h"


std::array<std::string, 4> CommandParser::parseToArgs(const std::string& cmd) {
  if (cmd.at(0) != 'k' && cmd.at(1) != ' ') {
    return {};
  }

  const std::string& command {cmd.substr(2)};

  std::array<std::string, 4> commandParts {};
  std::stringstream ss(command);
  std::string token;
  std::array<std::string, 4> result;
  
  int i = 0;
  while (std::getline(ss, token, ' ')) {
    result[i] = token;
    ++i;
    if (i >= result.size()) {
      break;
    }
  }
  return result;
}

void CommandParser::setCommands(const std::array<OperationArray, 8>& commands) {
  CommandParser::commands = commands;
}

void CommandParser::executeCommands(const std::array<std::string, 4>& args) {
  if (args.at(0).empty()) {
    return;
  }
  for (size_t i = 0; i < sizeof(commands) / sizeof(commands.at(0)); ++i) {
    size_t matchingArgs = 0;
    size_t argSize = sizeof(commands.at(i).getOperationSymbolArray()) / sizeof(commands.at(i).getOperationSymbolArray().at(0));
    for (size_t j = 0; j < argSize; ++j) {
      if ( commands.at(i).getOperationSymbolArray().at(j) == args.at(j)
        || commands.at(i).getOperationSymbolArray().at(j) == "${ARG}") {
        matchingArgs++;
      }
    }
    if (matchingArgs == argSize) {
      commands.at(i).executeOperation(args);
      return;
    }
  }
}