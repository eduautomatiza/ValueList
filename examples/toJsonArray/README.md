# valueList

Code example:

```CPP
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

  temperature.toJsonArray(doc.createNestedArray("TEMPERATURE"));
  humidity.toJsonArray(doc.createNestedArray("HUMIDITY"));

  serializeJsonPretty(doc, Serial);
  Serial.println();

  delay(1000);
}

```

Terminal output:

```JSON
{
  "TEMPERATURE": [
    {
      "ID": "id_1",
      "VALUE": 52
    },
    {
      "ID": "id_2",
      "VALUE": 20.12
    },
    {
      "ID": "id_3",
      "VALUE": "text 123"
    }
  ],
  "HUMIDITY": [
    {
      "ID": "id_4",
      "VALUE": 32
    }
  ]
}
```
