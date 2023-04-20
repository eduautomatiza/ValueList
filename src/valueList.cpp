#include "valueList.h"

ValueList::ValueList(size_t size_list)
    : size_(0),
      length_(0),
      item_(new value_t[size_list]),
      keyId_("ID"),
      keyValue_("VALUE") {
  if (item_) size_ = size_list;
}

ValueList::ValueList(size_t size_list, String keyId, String keyValue)
    : size_(0),
      length_(0),
      item_(new value_t[size_list]),
      keyId_(keyId),
      keyValue_(keyValue) {
  if (item_) size_ = size_list;
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

void ValueList::toJsonObject(JsonObject jsonObject) const {
  for (size_t i = 0; i < length_; i++) {
    jsonObject[id(i)] = value(i);
  }
}

void ValueList::toJsonArray(JsonArray jsonArray) const {
  for (size_t i = 0; i < length_; i++) {
    JsonObject jsonObject = jsonArray.createNestedObject();
    jsonObject[keyId_.c_str()] = id(i);
    jsonObject[keyValue_.c_str()] = value(i);
  }
}

const ValueList::value_t &ValueList::operator[](size_t index) const {
  static const value_t invalidResult = {"", typeUndefined, ""};
  if (index < length_) {
    return item_[index];
  } else {
    return invalidResult;
  }
}

const StaticJsonDocument<0> ValueList::value(size_t index) const {
  StaticJsonDocument<0> jsonValue;
  if (item_[index].valueType == typeString) {
    jsonValue = item_[index].value.c_str();
  } else {
    deserializeJson(jsonValue, item_[index].value.c_str());
  }
  return jsonValue;
}

const char *ValueList::id(size_t index) const {
  return item_[index].id.c_str();
}
