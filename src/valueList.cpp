#include "valueList.h"

ValueList::ValueList(size_t size_list) : size_(0), length_(0), item_(nullptr) {
  item_ = new value_t[size_list];
  if (item_) {
    size_ = size_list;
  }
}

ValueList::~ValueList(void) {
  if (item_) {
    delete[] item_;
  }
}

bool ValueList::insert(const String &id, valueType_t valueType,
                       const String &value) {
  if (item_ && length_ < size_) {
    item_[length_++] = {.id = id, .valueType = valueType, .value = value};
    return true;
  } else {
    return false;
  }
}

void ValueList::clear(void) { length_ = 0; }

void ValueList::toJsonObject(JsonObject jsonObject, const value_t &item) {
  jsonObject["ID"] = item.id;
  if (item.valueType == typeString) {
    jsonObject["VALUE"] = item.value.c_str();
  } else {
    StaticJsonDocument<0> jsonValue;
    deserializeJson(jsonValue, item.value.c_str());
    jsonObject["VALUE"] = jsonValue;
  }
}

void ValueList::toJsonArray(JsonArray jsonArray) {
  for (size_t i = 0; i < length_; i++) {
    toJsonObject(jsonArray.createNestedObject(), item_[i]);
  }
}

const ValueList::value_t &ValueList::operator[](size_t index) const {
  static value_t invalidResult = {"", typeUndefined, ""};
  if (index < length_) {
    return item_[index];
  } else {
    return invalidResult;
  }
}
