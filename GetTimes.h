/*
 GetTimes.h - Library for getting the sunrise and
 sunset times, as well as if it is daylight savings
 or not for a specified location, or for your location.
 Also is able to find your position when using internet.
 Created by Robert P. Ellwanger, June 14, 2015.
 Licensed under LGPL v3.0.
 */

#ifndef GetTimes_h
  #define GetTimes_h
  
  #include "Arduino.h"
  
  class GetTimes
{
  public:
    GetTimes(int utcOffset);
    GetTimes(String lat, String lon, int utcOffset);
    float sunrise();
    float sunset();
    boolean daylightSavings();
    String getLon();
    String getLat();
    String convertToTime(float n)
  private:
    String _lon;
    String _lat;
    int _utcOffset;
};

#endif
