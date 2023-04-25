#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

#include <vector>

class ValueList {
 public:
  typedef enum {
    typeUndefined = 0,
    typeString = 1,
    typeNumber = 2
  } valueType_t;

  struct value_t {
    String id;
    valueType_t valueType;
    String value;
  };

  ValueList(void);
  ValueList(String keyId, String keyValeu);
  ~ValueList();
  void insert(const String &id, valueType_t valueType, const String &value);
  void clear(void);
  size_t size(void);
  const value_t &operator[](size_t index) const;
  void toJsonObject(JsonObject jsonObject) const;
  void toJsonArray(JsonArray jsonArray) const;

  const String keyId_;
  const String keyValue_;

 private:
  std::vector<const value_t *> items_;
};
