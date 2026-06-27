#include "DataModels/OperationArray.h"
#include <array>

OperationArray::OperationArray(const std::function<void(std::array<std::string, 4>)>& op, const std::array<std::string, 4>& symbols) {
  operation = op;
  operationSymbol = symbols;
}

const std::function<void(std::array<std::string, 4>)>& OperationArray::getOperation() const {
  return operation;
}
void OperationArray::executeOperation(const std::array<std::string, 4>& args) const {
  operation(args);
}
const std::array<std::string, 4>& OperationArray::getOperationSymbolArray() const {
  return operationSymbol;
}

void OperationArray::setOperation(const std::function<void(std::array<std::string, 4>)>& ops) {
  operation = ops;
}
void OperationArray::setOperationSymbolArray(const std::array<std::string, 4>& symbols) {
  operationSymbol = symbols;
}