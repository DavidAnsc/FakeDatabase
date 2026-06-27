#include <string>
#include <iostream>
#include "Kits/CommandParser.h"


std::array<std::string, 4> CommandParser::parseToArgs(const std::string& command) {
  if (command.at(0) != 'k' && command.at(1) != ' ') {
    return {};
  }
  std::array<std::string, 4> commandParts {};
  int iS = 0;
  int lastIndex = 0;
  for (size_t i = 1; i < command.size(); ++i) {
    if (command.at(i) != ' ' && command.at(i - 1) == ' ') {
      lastIndex = i;
    }
    if (i == command.size()-1) {
      commandParts.at(iS) = command.substr(lastIndex, i-lastIndex+1);
      ++iS;
      break;
    } else if (command.at(i) == ' ' && i != 1) {
      commandParts.at(iS) = command.substr(lastIndex, i-lastIndex);
      ++iS;
      continue;
    }
  }
  return commandParts;
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