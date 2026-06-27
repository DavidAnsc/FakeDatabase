#pragma once
#include <array>
#include <string>
#include "DataModels/OperationArray.h"

namespace CommandParser {
  inline std::array<OperationArray, 8> commands {{}};
  std::array<std::string, 4> parseToArgs(const std::string& command);
  void setCommands(const std::array<OperationArray, 8>& commands);
  void executeCommands(const std::array<std::string, 4>& args);
}