#Arduino GetTimes Library
GetTimes is a library for getting the sunrise and sunset times, as well as if it is 
daylight savings or not for a specified location, or for your location. Also is able to 
find your position when using internet.

A primary goal was to enable the user to easily get sunset and sunrise times without
doing the calculations his/her self.

##Functions

-sunrise();               // the sunrise hour and minute
-sunset();                // the minute now (0-59)          
-daylightSavings();       // the second now (0-59) 
-getLon();                // the day now (1-31)
-getLat();                // day of the week, Sunday is day 0 
-convertToTime();         // takes the float from sunrise() or 
                         // sunset() and converts it to a string 
  
Functions for managing the location services are:  
GetTimes();             // set the system location to current location (only use when connected to internet)
GetTimes(lat, lon);     // alternative to above, lat and lon are string of the latitude and longitude of the position

##How to use
To use the library, while in the Arduino IDE add a library and navigate to GetTimes.h

##Contains
The GetTimes directory contains the GetTimes and Time library and some example sketches:

- sunsetsunrise.ino shows an example of retrieving the sunset and sunrise time for a certain location and 
  printing them to the console

- springorfall.ino shows an example of how to see wether or not you are in daylight savings or not

 
##Contributors:
RPBruiser
