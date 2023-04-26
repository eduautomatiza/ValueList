#include "valueList.h"

static const StaticJsonDocument<0> value(const ValueList::value_t *item);
static const char *id(const ValueList::value_t *item);

ValueList::ValueList(void) : keyId_("ID"), keyValue_("VALUE") {}

ValueList::ValueList(String keyId, String keyValue)
    : keyId_(keyId), keyValue_(keyValue) {}

ValueList::~ValueList() { clear(); }

void ValueList::insert(const String &id, valueType_t valueType,
                       const String &value) {
  items_.push_back(
      new value_t({.id = id, .valueType = valueType, .value = value}));
}

void ValueList::clear(void) {
  for (auto item : items_) {
    delete item;
  }
  items_.clear();
}

void ValueList::toJsonObject(JsonObject jsonObject) const {
  for (auto item : items_) {
    jsonObject[id(item)] = value(item);
  }
}

void ValueList::toJsonArray(JsonArray jsonArray) const {
  for (auto item : items_) {
    JsonObject jsonObject = jsonArray.createNestedObject();
    jsonObject[keyId_.c_str()] = id(item);
    jsonObject[keyValue_.c_str()] = value(item);
  }
}

const ValueList::value_t *ValueList::operator[](size_t index) const {
  if (index < items_.size()) {
    return items_[index];
  } else {
    return nullptr;
  }
}

size_t ValueList::size(void) { return items_.size(); }

static const StaticJsonDocument<0> value(const ValueList::value_t *item) {
  StaticJsonDocument<0> jsonValue;
  if (item->valueType == ValueList::typeString) {
    jsonValue = item->value.c_str();
  } else {
    deserializeJson(jsonValue, item->value.c_str());
  }
  return jsonValue;
}

static const char *id(const ValueList::value_t *item) {
  return item->id.c_str();
}
