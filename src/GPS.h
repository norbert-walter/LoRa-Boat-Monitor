#ifndef GPS_h
#define GPS_h

// Parse hour  
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
int getRMC_hour(String s) {
  int k = s.indexOf( ',',1);
  return s.substring(k+1, k+3).toInt();
}

// Parse minute
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
int getRMC_min(String s) {
  int k = s.indexOf( ',',1);
  return s.substring(k+3, k+5).toInt();;
}

// Parse secound
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
int getRMC_sec(String s) {
  int k = s.indexOf( ',',1);
  return s.substring(k+5, k+7).toInt();;
}

// Parse status [A valid data| V invalid data]
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
String getRMC_status(String s) {
  int k = s.indexOf( ',',1);
  k = s.indexOf( ',',k+1);
  return s.substring(k+1, k+2);
}

// Parse latitude in degree
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65

int getRMC_LatDeg(String s) {
  int k = s.indexOf( ',',1);
  k = s.indexOf( ',',k+1);
  k = s.indexOf( ',',k+1);
  return s.substring(k+1, k+3).toInt();;
}

// Parse latitude in minute as integer
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
int getRMC_LatMinInt(String s) {
  int k = s.indexOf( ',',1);
  k = s.indexOf( ',',k+1);
  k = s.indexOf( ',',k+1);
  return s.substring(k+3, k+5).toInt();
}

// Parse latitude in minute as float
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
float getRMC_LatMinFloat(String s) {
  int k1 = s.indexOf( ',',1);
  k1 = s.indexOf( ',',k1+1);
  k1 = s.indexOf( ',',k1+1);
  int k2 = s.indexOf( ',',k1+1);
  return s.substring(k1+3, k2).toFloat();
}

// Parse north or south [N|S] for latitude
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
String getRMC_LatNS(String s) {
int k=1, l;
  for(l=0;l<4;l++) { 
    k = s.indexOf( ',',k+1);
  }
  return s.substring(k+1, k+2);
}

// Parse longitude in degree
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
int getRMC_LonDeg(String s) {
int k=1, l;
  for(l=0;l<5;l++) { 
    k = s.indexOf( ',',k+1);
  }
  return s.substring(k+1, k+4).toInt();;
}

// Parse longitude in minute as integer
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
int getRMC_LonMinInt(String s) { 
int k=1, l;
  for(l=0;l<5;l++) { 
    k = s.indexOf( ',',k+1);
  }
  return s.substring(k+4, k+6).toInt();
}

// Parse longitude in minute as float
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
float getRMC_LonMinFloat(String s) { 
int k=1, k2, l;
  for(l=0;l<5;l++) { 
    k = s.indexOf( ',',k+1);
  }
  k2 = s.indexOf( ',',k+1);
  return s.substring(k+4, k2).toFloat();
}
// Parse est or west [E|W] for longitude
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
String getRMC_LonEW(String s) {
int k=1, l;
  for(l=0;l<6;l++) { 
    k = s.indexOf( ',',k+1);
  }
  return s.substring(k+1, k+2);
}

// Parse speed [m/s]
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
float getRMC_Speed(String s) {
int k1=1, k2, l;
  for(l=0;l<7;l++) { 
    k1 = s.indexOf( ',',k1+1);
  }
  k2 = s.indexOf( ',',k1+1);
  return s.substring(k1+1, k2).toFloat();
}

// Parse course in degree
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
float getRMC_Course(String s) { 
int k1=1, k2, l;
  for(l=0;l<8;l++) { 
    k1 = s.indexOf( ',',k1+1);
  }
  k2 = s.indexOf( ',',k1+1);
  return s.substring(k1+1, k2).toFloat();
}

// Parse day
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
int getRMC_Day(String s) { 
int k=1, l;
  for(l=0;l<9;l++) { 
    k = s.indexOf( ',',k+1);
  }
  return s.substring(k+1, k+3).toInt();
}

// Parse month
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
int getRMC_Month(String s) {
int k=1, l;
  for(l=0;l<9;l++) { 
    k = s.indexOf( ',',k+1);
  }
  return s.substring(k+3, k+5).toInt();
}

// Parse year
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
int getRMC_Year(String s) {  
int k=1, l;
  for(l=0;l<9;l++) { 
    k = s.indexOf( ',',k+1);
  }
  return s.substring(k+5, k+7).toInt();
}

// Parse variance of magnetic course
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
float getRMC_MagnVar(String s) { 
int k1=1, k2, l;
  for(l=0;l<10;l++) { 
    k1 = s.indexOf( ',',k1+1);
  }
  k2 = s.indexOf( ',',k1+1);
  return s.substring(k1+1, k2).toFloat();
}

// Parse est or west for magnetic course
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
String getRMC_MagnEW(String s) {
int k=1, l;
  for(l=0;l<11;l++) { 
    k = s.indexOf( ',',k+1);
  }
  return s.substring(k+1, k+2);
}

// Parse latitude in decimal notation as float
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
float getRMC_LatDec(String s) {
float lat = 0;
lat = float(getRMC_LatDeg(s)) + (getRMC_LatMinFloat(s) / 60);
return lat;
}

// Parse longitude in decimal notation as float
// $GPRMC,105724.337,A,5415.6232,N,01004.9693,E,000.0,000.0,290315,002.1,E*65
float getRMC_LonDec(String s) {
float lon = 0;
lon = float(getRMC_LonDeg(s)) + (getRMC_LonMinFloat(s) / 60);
return lon;
}

#endif
