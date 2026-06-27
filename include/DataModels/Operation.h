#pragma once
#include <string>
#include <functional>


class Operation {
  private:
  std::string name {};
  std::function<void()> action {};

  public:
  Operation() = default;
  Operation(const std::string& opName, const std::function<void()>& opAction);
  const std::string& getName() const;
  void setName(const std::string& name);
  void setAction(const std::function<void()>& action);
  void execute();
};