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
  ValueList(size_t size_list, String keyId, String keyValeu);
  ~ValueList(void);
  bool insert(const String &id, valueType_t valueType, const String &value);
  void clear(void);
  void toJsonObject(JsonObject jsonObject) const;
  void toJsonArray(JsonArray jsonArray) const;
  const value_t &operator[](size_t index) const;

  const size_t &length = length_;

 private:
  size_t size_;
  size_t length_;
  value_t *item_;
  const String keyId_;
  const String keyValue_;
  const StaticJsonDocument<0> value(size_t index) const;
  const char *id(size_t index) const;
};
