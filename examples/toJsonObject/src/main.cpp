#include <Arduino.h>
#include <ArduinoJson.h>

#include "valueList.h"

void setup() { Serial.begin(115200); }

void loop() {
  DynamicJsonDocument doc(4096);
  ValueList temperature(3);
  ValueList humidity(1);

  temperature.insert("id_1", ValueList::typeNumber, "52");
  temperature.insert("id_2", ValueList::typeNumber, "20.12");
  temperature.insert("id_3", ValueList::typeString, "text 123");
  humidity.insert("id_4", ValueList::typeNumber, "32");

  temperature.toJsonObject(doc.createNestedObject("TEMPERATURE"));
  humidity.toJsonObject(doc.createNestedObject("HUMIDITY"));

  serializeJsonPretty(doc, Serial);
  Serial.println();

  delay(1000);
}
