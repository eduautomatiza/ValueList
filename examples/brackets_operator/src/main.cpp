#include <Arduino.h>
#include <ArduinoJson.h>

#include "valueList.h"

void setup() { Serial.begin(115200); }

void loop() {
  DynamicJsonDocument doc(4096);
  ValueList temperature(3);

  temperature.insert("id_1", ValueList::typeNumber, "52");
  temperature.insert("id_2", ValueList::typeNumber, "20.12");
  temperature.insert("id_3", ValueList::typeString, "text 123");

  Serial.println("TEMPERATURE");
  for (size_t i = 0; i < temperature.length; i++) {
    const ValueList::value_t &item = temperature[i];
    Serial.printf("id: %s, value: %s\n", item.id, item.value);
  }

  delay(1000);
}
