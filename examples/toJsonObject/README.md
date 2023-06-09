# valueList

Code example:

```CPP
#include <Arduino.h>
#include <ArduinoJson.h>

#include "valueList.h"

void setup() { Serial.begin(115200); }

void loop() {
  DynamicJsonDocument doc(4096);
  ValueList temperature();
  ValueList humidity();

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

```

Terminal output:

```JSON
{
  "TEMPERATURE": {
    "id_1": 52,
    "id_2": 20.12,
    "id_3": "text 123"
  },
  "HUMIDITY": {
    "id_4": 32
  }
}
```
