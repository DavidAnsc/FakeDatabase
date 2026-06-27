#pragma once
#include <any>
#include <array>

class Row {
  private:
  long id {-1};
  std::array<std::any, 5> data {{}};
  
  public:
  Row() = default;
  Row(long id, std::array<std::any, 5> data);

  const long& getId() const;
  const std::array<std::any, 5>& getData() const;
  void setId(const long& id);
  void setData(const std::array<std::any, 5>& data);
};