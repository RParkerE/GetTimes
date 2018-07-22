#include GetTimes.h

void setup() {
  GetTimes();
}

void loop() {
  if(daylightSavings()) {
    Serial.println("Spring forward!");
  }
  else {
    Serial.println("Fall back!");
  }
}
