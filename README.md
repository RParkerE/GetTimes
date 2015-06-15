#Arduino GetTimes Library
GetTimes is a library for getting the sunrise and sunset times, as well as if it is 
daylight savings or not for a specified location, or for your location. Also is able to 
find your position when using internet.

A primary goal was to enable the user to easily get sunset and sunrise times without
doing the calculations his/her self.

##CONTENTS

- [Functions](#functions)
- [Usage](#how-to-get-and-use)
- [What Is In It?](#contains)
- [Contributors](#contributors)

##Functions

- sunrise();
  - the sunrise hour and minute in a float
- sunset();
  - the sunset hour and minute        
- daylightSavings();
  - whether or not it is currently daylight savings time or not 
- getLon();
  - get your current longitude (only with internet)
- getLat();
  - get your current latitude (only with internet)
- convertToTime();
  - takes the float from sunrise() or sunset() and converts it to a string 
  
Functions for managing the location services are:  
- GetTimes();
  - set the system location to current location (only use when connected to internet)
- GetTimes(lat, lon);
  - alternative to above, lat and lon are string of the latitude and longitude of the position

##How to get and use
###Windows

- Download the .zip file
- Click on "My Computer".
- Click on "Downloads"
- Click on the .zip file you just downloaded
- `Extract All`
- Open the Arduino IDE
- Add a library
- Add GetTimes.h

###Macintosh

- Download the .zip file
- Go to "Downloads"
- - Click on the .zip file you just downloaded
- `Extract All`
- Open the Arduino IDE
- Add a library
- Add GetTimes.h

###Unix

- `sudo apt-get install git-core`
- `git clone https://github.com/RPBruiser/MagicLamp.git`
- Open the Arduino IDE
- Add a library
- Add GetTimes.h

##Contains
The GetTimes directory contains the GetTimes and Time library and some example sketches:

- sunsetsunrise.ino shows an example of retrieving the sunset and sunrise time for a certain location and 
  printing them to the console

- springorfall.ino shows an example of how to see wether or not you are in daylight savings or not

 
##Contributors:
RPBruiser
