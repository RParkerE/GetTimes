/*
  GetTimes.cpp - Library for getting the sunrise and
  sunset times, as well as if it is daylight savings
  or not for a specified location, or for your location.
  Created by Robert P. Ellwanger, June 14, 2015.
  Licensed under Apache License v2.0.
*/

#include <Bridge.h>
#include <HttpClient.h>
#include <Process.h>
#include <Wire.h>
#include <Time.h>
#include "Arduino.h"
#include "GetTimes.h"

GetTimes::GetTimes()
{
  _lon = getLon();
  _lat = getLat();
}

GetTimes::GetTimes(String lat, String lon)
{
  _lat = lat;
  _lon = lon;
}

float GetTimes::sunrise()
{
   daylightSavings();
  
   char longitude[20];
   char latitude[20];
   float longi, lati, A, B, C, E, F, JD, JC, longSun, anomSun, eOrbit, sunEqCtr, trueLongSun, trueAnomSun, sunRadVector, sunAppLong, obliqEcliptic, obliqCorr;
   float sunAscen, sunDeclin, varY, eqTime, haSunrise, solarNoon; 
   float D2R = PI / 180;
   float R2D = 180 / PI;
    
   lat.toCharArray(latitude, 20);
   lati = atof(latitude);
    
   lon.toCharArray(longitude, 20);
   longi = atof(longitude);
   
   A = year() / 100;
   B = A / 4;
   C = 2 - A + B;
   E = 365.25 * (year() + 4716);
   F = 30.6001 * (month() + 1);
   JD = C + day() + E + F - 1524.5;
   JC = (JD - 2451545) / 36525;
   longSun = int(280.46646 + JC * (36000.76983 + JC * 0.0003032)) % 360; //TODO: Non integer modulo
   anomSun = 357.52911 + JC * (35999.05029 - 0.0001537 * JC);
   eOrbit = 0.016708634 - JC * (0.000042037 + 0.0000001267 * JC);
   sunEqCtr = sin(D2R * (anomSun)) * (1.914602 - JC * (0.004817 + 0.000014 * JC)) + sin(D2R * (2 * anomSun)) * (0.019993 - 0.000101 * JC) + sin(D2R * (3 * anomSun)) * 0.000289;
   trueLongSun = longSun + sunEqCtr;
   trueAnomSun = anomSun + sunEqCtr;
   sunRadVector = (1.000001018 * (1 - eOrbit * eOrbit)) / (1 + eOrbit * cos(D2R * (trueAnomSun)));
   sunAppLong = trueLongSun - 0.00569 - 0.00478 * sin(D2R * (125.04 - 1934.136 * JC));
   obliqEcliptic = 23 + (26 + ((21.448 - JC * (46.815 + JC * (0.00059 - JC * 0.001813)))) / 60) / 60;
   obliqCorr = obliqEcliptic + 0.00256 * cos(D2R * (125.04 - 1934.136 * JC));
   sunAscen = R2D * (atan2(cos(D2R * (sunAppLong)), cos(D2R * (obliqCorr)) * sin(D2R * (sunAppLong))));
   sunDeclin = R2D * (asin(sin(D2R * (obliqCorr)) * sin(D2R * (sunAppLong))));
   varY = tan(D2R * (obliqCorr / 2)) * tan(D2R * (obliqCorr / 2));
   eqTime = 4 * R2D * (varY * sin(2 * D2R * (longSun)) - 2 * eOrbit * sin(D2R * (anomSun)) + 4 * eOrbit * varY * sin(D2R * (anomSun)) * cos(2 * D2R * (longSun)) - 0.5 * varY * varY * 
     sin(4 * D2R * (longSun)) - 1.25 * eOrbit * eOrbit * sin(2 * D2R * (anomSun)));
   haSunrise = R2D * (acos(cos(D2R * (90.833)) / (cos(D2R * (lati)) * cos(D2R * (sunDeclin))) - tan(D2R * (lati)) * tan(D2R * (sunDeclin))));
   if (daylight == true) {
     solarNoon = (720 - 4 * longi - eqTime + -5 * 60) / 1440; //TODO: Change -5 to a method for finding timezone
     solarNoon = solarNoon + .041667;
   }
   else {
     solarNoon = (720 - 4 * longi - eqTime + -5 * 60) / 1440; //TODO: Change -5 to a method for finding timezone
   }
   localRiseTime = (solarNoon * 1440 - haSunrise * 4) / 1440;
   
   return localRiseTime;
}

float GetTimes::sunset()
{
   daylightSavings();
  
   char longitude[20];
   char latitude[20];
   float longi, lati, A, B, C, E, F, JD, JC, longSun, anomSun, eOrbit, sunEqCtr, trueLongSun, trueAnomSun, sunRadVector, sunAppLong, obliqEcliptic, obliqCorr;
   float sunAscen, sunDeclin, varY, eqTime, haSunrise, solarNoon; 
   float D2R = PI / 180;
   float R2D = 180 / PI;
    
   lat.toCharArray(latitude, 20);
   lati = atof(latitude);
    
   lon.toCharArray(longitude, 20);
   longi = atof(longitude);
   
   A = year() / 100;
   B = A / 4;
   C = 2 - A + B;
   E = 365.25 * (year() + 4716);
   F = 30.6001 * (month() + 1);
   JD = C + day() + E + F - 1524.5;
   JC = (JD - 2451545) / 36525;
   longSun = int(280.46646 + JC * (36000.76983 + JC * 0.0003032)) % 360; //TODO: Non integer modulo
   anomSun = 357.52911 + JC * (35999.05029 - 0.0001537 * JC);
   eOrbit = 0.016708634 - JC * (0.000042037 + 0.0000001267 * JC);
   sunEqCtr = sin(D2R * (anomSun)) * (1.914602 - JC * (0.004817 + 0.000014 * JC)) + sin(D2R * (2 * anomSun)) * (0.019993 - 0.000101 * JC) + sin(D2R * (3 * anomSun)) * 0.000289;
   trueLongSun = longSun + sunEqCtr;
   trueAnomSun = anomSun + sunEqCtr;
   sunRadVector = (1.000001018 * (1 - eOrbit * eOrbit)) / (1 + eOrbit * cos(D2R * (trueAnomSun)));
   sunAppLong = trueLongSun - 0.00569 - 0.00478 * sin(D2R * (125.04 - 1934.136 * JC));
   obliqEcliptic = 23 + (26 + ((21.448 - JC * (46.815 + JC * (0.00059 - JC * 0.001813)))) / 60) / 60;
   obliqCorr = obliqEcliptic + 0.00256 * cos(D2R * (125.04 - 1934.136 * JC));
   sunAscen = R2D * (atan2(cos(D2R * (sunAppLong)), cos(D2R * (obliqCorr)) * sin(D2R * (sunAppLong))));
   sunDeclin = R2D * (asin(sin(D2R * (obliqCorr)) * sin(D2R * (sunAppLong))));
   varY = tan(D2R * (obliqCorr / 2)) * tan(D2R * (obliqCorr / 2));
   eqTime = 4 * R2D * (varY * sin(2 * D2R * (longSun)) - 2 * eOrbit * sin(D2R * (anomSun)) + 4 * eOrbit * varY * sin(D2R * (anomSun)) * cos(2 * D2R * (longSun)) - 0.5 * varY * varY * 
     sin(4 * D2R * (longSun)) - 1.25 * eOrbit * eOrbit * sin(2 * D2R * (anomSun)));
   haSunrise = R2D * (acos(cos(D2R * (90.833)) / (cos(D2R * (lati)) * cos(D2R * (sunDeclin))) - tan(D2R * (lati)) * tan(D2R * (sunDeclin))));
   if (daylight == true) {
     solarNoon = (720 - 4 * longi - eqTime + -5 * 60) / 1440; //TODO: Change -5 to a method for finding timezone
     solarNoon = solarNoon + .041667;
   }
   else {
     solarNoon = (720 - 4 * longi - eqTime + -5 * 60) / 1440; //TODO: Change -5 to a method for finding timezone
   }
   localSetTime = (solarNoon * 1440 + haSunrise * 4) / 1440;
   
   return localSetTime;
}

boolean Morse::daylightSavings()
{
  int marchSecondSunday, novFirstSunday, cent, i, n;
  
  cent = floor(year() / 100);
  
  for (i = 8; i <= 14; i++) { 
    if (marchSecondSunday != 0) {
      marchSecondSunday = int((i + floor(2.6 * 3 - 0.2) - 2 * cent + year() + floor(year() / 4) + floor(cent / 4))) % 7;
    }
    break;
  } 
  for (n = 1; n <= 7; n++) { 
    if (novFirstSunday != 0) {
      novFirstSunday = int((i + floor(2.6 * 11 - 0.2) - 2 * cent + year() + floor(year() / 4) + floor(cent / 4))) % 7;
    }
    break;
  } 
  
  if (month() == 3) {
   if (day() >= i) {
     daylight = true;
    }
  }
  else if (month() == 11) {
   if (day() <= n) {
    daylight = true;
   } 
  }
  else if (month() > 3) {
   daylight = true; 
  }
  else if (month() < 11) {
   daylight = true; 
  }
  else {
   daylight = false; 
  }
  
  return daylight;
}

String GetTimes::getLon() {
    HttpClient clientLon;
    clientLon.get("http://ip-api.com/csv/?fields=lon");
    
    while (clientLon.available()) {
       lon = clientLon.readString();
    }
    
    return lon;
}

String GetTimes::getLat() {
    HttpClient clientLat;
    clientLat.get("http://ip-api.com/csv/?fields=lat");
    
    while (clientLat.available()) {
       lat = clientLat.readString();
    }
    
    return lat;
}

String GetTimes::convertToTime(float n) {
  float tmp;
  int newHour, newMinute, newSecond;
  String convertedTime;
  
  tmp = n * 24;
  newHour = floor(tmp);
  tmp = tmp - newHour;
  tmp = tmp * 60;
  newMinute = floor(tmp);
  if (newMinute < 10) {
    convertedTime = String(newHour) + ":0" + String(newMinute);
  }
  else {
    convertedTime = String(newHour) + ":" + String(newMinute);
  }
  
  return convertedTime;
}
