

// NMEA telegrams
// sendmode 0 = no serial, 1 = serial active

// Send environment data
String sendXDR1(int sendmode){
  
  String HexCheckSum;
  String NMEAXdr1;
  String sendXdr1;
  
  // Create NMEA string $IIXDR,a,x.x,a,c--c, ..... *hh<CR><LF>
  NMEAXdr1 = "IIXDR,";
  NMEAXdr1 = NMEAXdr1 + "C," + String(temperature) + ",C,ATemp,";
  NMEAXdr1 = NMEAXdr1 + "P," + String(pressure) + ",C,APress,";
  NMEAXdr1 = NMEAXdr1 + "H," + String(humidity) + ",P,AHum,";
  NMEAXdr1 = NMEAXdr1 + "C," + String(dewp) + ",C,Dewp";
 
  // Build CheckSum
  HexCheckSum = String(CheckSum(NMEAXdr1), HEX);
  // Build complete NMEA string
  sendXdr1 = "$" + NMEAXdr1 + "*" + HexCheckSum;
  if((int(actconf.serverMode) == 1 && sendmode == 1) || (int(actconf.debug) >= 3 && sendmode == 1)){
    Serial.println(sendXdr1);
  }

  return sendXdr1;
}

// Send battery data
String sendXDR2(int sendmode){
  
  String HexCheckSum;
  String NMEAXdr2;
  String sendXDR2;
  
  // Create NMEA string $IIXDR,a,x.x,a,c--c, ..... *hh<CR><LF>
  NMEAXdr2 = "IIXDR,";
  NMEAXdr2 = NMEAXdr2 + "V," + String(voltage) + ",V,BVolt,";
  NMEAXdr2 = NMEAXdr2 + "C," + String(temp1wire) + ",C,BTemp,";
  if (String(actconf.envSensor) == "VEdirect-Read") {
    NMEAXdr2 = NMEAXdr2 + "I," + String(vedirectCurrent) + ",A,BCur,";
    NMEAXdr2 = NMEAXdr2 + "P," + String(vedirectPower) + ",W,BPow,";
    NMEAXdr2 = NMEAXdr2 + "P," + String(vedirectSOC) + ",P,BCap";
  }
  else{
    NMEAXdr2 = NMEAXdr2 + "P," + String(capacity) + ",P,BCap";
  }
 
  // Build CheckSum
  HexCheckSum = String(CheckSum(NMEAXdr2), HEX);
  // Build complete NMEA string
  sendXDR2 = "$" + NMEAXdr2 + "*" + HexCheckSum;
  if((int(actconf.serverMode) == 1 && sendmode == 1) || (int(actconf.debug) >= 3 && sendmode == 1)){
    Serial.println(sendXDR2);
  }

  return sendXDR2;
}

// Send level an control data
String sendXDR3(int sendmode){
  
  String HexCheckSum;
  String NMEAXdr3;
  String sendXDR3;
  
  // Create NMEA string $IIXDR,a,x.x,a,c--c, ..... *hh<CR><LF>
  NMEAXdr3 = "IIXDR,";
  NMEAXdr3 = NMEAXdr3 + "L," + String(tank1p) + ",P,Water,";
  NMEAXdr3 = NMEAXdr3 + "L," + String(tank2p) + ",P,Fuel,";
  NMEAXdr3 = NMEAXdr3 + "I," + String(alarm1) + ",B,Alarm,";
  NMEAXdr3 = NMEAXdr3 + "O," + String(actconf.relay) + ",B,Relay";
 
  // Build CheckSum
  HexCheckSum = String(CheckSum(NMEAXdr3), HEX);
  // Build complete NMEA string
  sendXDR3 = "$" + NMEAXdr3 + "*" + HexCheckSum;
  if((int(actconf.serverMode) == 1 && sendmode == 1) || (int(actconf.debug) >= 3 && sendmode == 1)){
    Serial.println(sendXDR3);
  }

  return sendXDR3;
}

// Send GPS RMC data
String sendRMC(int sendmode){
 
  if((int(actconf.serverMode) == 1 && sendmode == 1) || (int(actconf.debug) >= 3 && sendmode == 1)){
    Serial.println(nmea);
  }

  return nmea;
}
