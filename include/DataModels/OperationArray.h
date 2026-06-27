#include <array>
#include <string>
#include <functional>

class OperationArray {
  private:
  std::function<void(std::array<std::string, 4>)> operation;
  std::array<std::string, 4> operationSymbol;

  public:
  OperationArray() = default;
  OperationArray(const std::function<void(std::array<std::string, 4>)>& op, const std::array<std::string, 4>& symbols);
  
  const std::function<void(std::array<std::string, 4>)>& getOperation() const;
  void executeOperation(const std::array<std::string, 4>& args) const;
  const std::array<std::string, 4>& getOperationSymbolArray() const;

  void setOperation(const std::function<void(std::array<std::string, 4>)>& op);
  void setOperationSymbolArray(const std::array<std::string, 4>& symbols);
};