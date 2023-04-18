#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

class ValueList {
 public:
  typedef enum {
    typeUndefined = 0,
    typeString = 1,
    typeNumber = 2
  } valueType_t;

  typedef struct {
    String id;
    valueType_t valueType;
    String value;
  } value_t;

  explicit ValueList(size_t size_list);
  ~ValueList(void);
  bool insert(const String &id, valueType_t valueType, const String &value);
  void clear(void);
  void toJsonObject(JsonObject jsonObject, const value_t &item);
  void toJsonArray(JsonArray jsonArray);
  const value_t &operator[](size_t index) const;

  const size_t &length = length_;

 private:
  size_t size_;
  size_t length_;
  value_t *item_;
};