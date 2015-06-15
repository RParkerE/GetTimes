/*
  GetTimes.h - Library for getting the sunrise and
  sunset times, as well as if it is daylight savings
  or not for a specified location, or for your location.
  Also is able to find your position when using internet.
  Created by Robert P. Ellwanger, June 14, 2015.
  Licensed under Apache License v2.0.
*/

#ifndef GetTimes_h
#define GetTimes_h

#include "Arduino.h"

class GetTimes
{
  public:
    GetTimes();
    GetTimes(String lat, String lon);
    float sunrise();
    float sunset();
    boolean daylightSavings();
    String getLon();
    String getLat();
	String convertToTime(float n)
  private:
    int _lon;
    int _lat;
};

#endif
