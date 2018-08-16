#include GetTimes.h

String lat;
String lon;

void setup() {
  GetTimes();
}

void loop() {
  lat = getLat();
  lon = getLon();
  Serial.println("Your Location is:");
  Serial.println("Lat: " + lat);
  Serial.println("Lon: " + lon);
}
  
