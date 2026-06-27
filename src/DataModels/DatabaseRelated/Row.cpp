#include "DataModels/DatabaseRelated/Row.h"
#include <any>
#include <array>

Row::Row(long id, std::array<std::any, 5> data) : id(id), data(data) {}

const long& Row::getId() const {
  return id;
}
const std::array<std::any, 5>& Row::getData() const {
  return data;
}

void Row::setId(const long& id) {
  this->id = id;
}
void Row::setData(const std::array<std::any, 5>& data) {
  this->data = data;
}