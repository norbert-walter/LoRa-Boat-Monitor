// Functions for VE.direct bus from Victron Energy to read data from BMV-712 smart

/*
 * https://forum.arduino.cc/t/how-to-serial-parseint/400992/40
 *
 * Real data output on VE.direct port
 * 19200 Bd 8N1
 *
PID  0xA381
V 12341
T ---
I 0
P 0
CE  0
SOC 1000
TTG -1
Alarm OFF
Relay OFF
AR  0
BMV 712 Smart
FW  0408
MON 0
Checksum  /
H1  -188890
H2  0
H3  -133402
H4  1
H5  0
H6  -1183888
H7  12333
H8  14499
H9  0
H10 4
H11 0
H12 0
H15 0
H16 0
H17 1563
H18 2095
Checksum  ⸮
*/

// Output data from LoRa monitor via VE.direct as fake device BMV-712 smart
void sendVEdirect(){
  int i = 0;
  int checksum = 0;
  int strLength = 0;
  unsigned int sendvoltage = 0;
  int sendtemp = 0;
  unsigned int sendsoc = 0;
  String sendalarm = "";
  String sendrelay = "";
  String vedirectOutput = "";
  char veOutput[200];

  // Concat all values in a string
  vedirectOutput += "\r\n";                           // Carridge return and new line
  vedirectOutput += "PID\t0xA381\r\n";                // Device Type ID
  sendvoltage = voltage * 1000.0;
  vedirectOutput += "V\t" + String(sendvoltage) + "\r\n";// Battery volatge
  sendtemp = int(temp1wire);                          // Use 1Wire temperature sensor
  vedirectOutput += "T\t" + String(sendtemp) + "\r\n";// Actual battery temperature
  vedirectOutput += "I\t0\r\n";                       // Acual current outwards
  vedirectOutput += "P\t0\r\n";                       // Actual current
  vedirectOutput += "CE\t0\r\n";                      // Actual consumed ampere hours
  sendsoc = capacity * 10;                            // Actual battery capacity in %
  vedirectOutput += "SOC\t" + String(sendsoc) + "\r\n";// Actual state of charge (battery capacity)
  vedirectOutput += "TTG\t-1\r\n";                    // Time to go in minutes (-1 = unlimited)
  if(alarm1 == 0){                                    // Read alarm status
    sendalarm = "OFF";
  }
  else{
    sendalarm = "ON";
  }
  vedirectOutput += "Alarm\t" + sendalarm + "\r\n";   // Alarm status
  if(actconf.relay == 0){                             // Read alarm status
    sendrelay = "OFF";
  }
  else{
    sendrelay = "ON";
  }
  vedirectOutput += "Relay\t" + sendrelay + "\r\n";   // Relay status
  vedirectOutput += "AR\t0\r\n";                      // Alarm reason
  vedirectOutput += "BMV\t712 Smart\r\n";             // Actual consumed ampere hours
  vedirectOutput += "FW\t0408\r\n";                   // Firmware version Attention! Correct firmware version neccessary!
  vedirectOutput += "MON\t0\r\n";                     // DC monitor mode afer V4.08
  vedirectOutput += "Checksum\t";                     // Checksum


  // Checksum calculation Modulo 256
  //  https://www.victronenergy.com/live/vedirect_protocol:faq#q8how_do_i_calculate_the_text_checksum
  strLength = vedirectOutput.length() +1;
  checksum = 0;
  vedirectOutput.toCharArray(veOutput, strLength);    // Convert output to char array
  for(i = 0; i < vedirectOutput.length(); i++) {      // Calculate sum total over all characters
    checksum = (checksum + veOutput[i]) & 255;        // Modulo 256
  }
  checksum = 256 - checksum;
 
  Serial1.print(vedirectOutput);                      // Wirite data
  Serial1.write(checksum);                            // Write checksum
  delay(100);

  // Write H data
  vedirectOutput = "\r\n";
  vedirectOutput += "H1\t-188890\r\n";
  vedirectOutput += "H2\t0\r\n";
  vedirectOutput += "H3\t-133402\r\n";
  vedirectOutput += "H4\t1\r\n";
  vedirectOutput += "H5\t0\r\n";
  vedirectOutput += "H6\t-1183888\r\n";
  vedirectOutput += "H7\t12333\r\n";
  vedirectOutput += "H8\t14499\r\n";
  vedirectOutput += "H9\t0\r\n";
  vedirectOutput += "H10\t4\r\n";
  vedirectOutput += "H11\t0\r\n";
  vedirectOutput += "H12\t0\r\n";
  vedirectOutput += "H15\t0\r\n";
  vedirectOutput += "H16\t0\r\n";
  vedirectOutput += "H17\t1563\r\n";
  vedirectOutput += "H18\t2095\r\n";
  vedirectOutput += "Checksum\t";

  checksum = 0;
  vedirectOutput.toCharArray(veOutput, strLength);    // Convert output to char array
  for(i = 0; i < vedirectOutput.length(); i++) {      // Calculate sum total over all characters
    checksum = (checksum + veOutput[i]) & 255;        // Modulo 256
  }
  checksum = 256 - checksum;

  Serial1.print(vedirectOutput);                      // Wirite data
  Serial1.write(checksum);                            // Write checksum
}


// Send binary value (2 bytes)
// ":78DED000B05C4\n"
// "TTTTTTTTVVVVCC\n"
void sendBinaryValue(String type, int value){
  int strLength = 0;              // String length of output string
  String valueOut = "";           // Value type as string
  char cvalue[] = "0000";         // Value as char
  byte valueLow = 0;              // Value low byte
  byte valueHigh = 0;             // Value high byte
  byte checksum = 0x00;           // Checksum with offset 0x00
  char cchecksum[] = "00";        // Checksum as char
  char hexbyte[] = "00";          // Hex byte
  char veOutput[200];             // Output char array without checksum

  valueLow = lowByte(value);      // Separate low byte
  valueHigh = highByte(value);    // Separate hih byte
  sprintf(cvalue,"%02X%02X", valueLow, valueHigh); // Concat high and low byte
  // Generate output string
  valueOut += type;
  valueOut += cvalue;
  strLength = valueOut.length() +1;
  valueOut.toCharArray(veOutput, strLength);  // Convert output to char array
  // Calculate checksum
  for(int i = 0; i < valueOut.length(); i = i +2) { // Calculate sum total over all Hex bytes
    if(i > 0){                          // Ignore first char ":"
      hexbyte[0] = veOutput[i];         // Build the hex byte
    }
    hexbyte[1] = veOutput[i+1];
    checksum = (checksum + strtol(hexbyte, NULL, 16)) & 255; // Convert Hex to Bin and accumulate
  }
  checksum = 85 - checksum;   // 0x55 = 85 dez
  sprintf(cchecksum,"%02X", checksum); // Convert int value in hex value
/*
  // Debug information on Serial output
  Serial.print("VE.direct Value: ");
  Serial.print(valueOut);
  Serial.print(cchecksum);
  Serial.println("\\n");
*/

  Serial1.print(valueOut);
  Serial1.print(cchecksum);
  Serial1.print("\n");
}

// Send settings and values in binary format
// Not all parts are documented. These parts have been sniffed.
// Some values are updated but not all (battery temperature, voltage and state of charge).
void sendVEdirectBinary(){
  Serial1.print(":5084404\n");                        // Ping with application version 4.08
  delay(15);
  Serial1.print(":181A330\n");                        // Return answare for 
  delay(15); 
  Serial1.print(":5084404\n");                        // Ping with application version 4.08
  delay(15);
  Serial1.print(":71001013C\n");                      
  delay(15);
  Serial1.print(":70A01004851313933325747475443000000000000000000000000005F\n"); // Serial number
  delay(15);
  Serial1.print(":74101010B\n");
  delay(15);
  Serial1.print(":711EC0150\n");
  delay(15);
  Serial1.print(":70D01013F\n");
  delay(15);
  Serial1.print(":77FEC01E2\n");
  delay(15);
  Serial1.print(":7920001BB\n");
  delay(15);
  Serial1.print(":70FEC0152\n");
  delay(15);
  Serial1.print(":70EEC0153\n");
  delay(15);
  Serial1.print(":70C01000041\n");                    // Description 
  delay(15);
  Serial1.print(":7B8EE000000A8\n");
  delay(15);
  Serial1.print(":7F8EE000266\n");
  delay(15);
  Serial1.print(":700EF0000005F\n");
  delay(15);
  Serial1.print(":7FCEE000163\n");
  delay(15);
  Serial1.print(":72803003200F1\n");
  delay(15);
  Serial1.print(":72003007800B3\n");
  delay(15);
  Serial1.print(":72103007900B1\n");
  delay(15);
  Serial1.print(":7220300000029\n");
  delay(15);
  Serial1.print(":7230300000028\n");
  delay(15);
  Serial1.print(":7240300000027\n");
  delay(15);
  Serial1.print(":7250300000026\n");
  delay(15);
  Serial1.print(":7260300000025\n");
  delay(15);
  Serial1.print(":7270300000024\n");
  delay(15);
  Serial1.print(":72C030000001F\n");
  delay(15);
  Serial1.print(":72D030000001E\n");
  delay(15);
  Serial1.print(":72A0300000021\n");
  delay(15);
  Serial1.print(":72B0300000020\n");
  delay(15);
  Serial1.print(":7310300140006\n");
  delay(15);
  Serial1.print(":73203000F000A\n");
  delay(15);
  Serial1.print(":73003011A\n");
  delay(15);
  Serial1.print(":74F030000FC\n");
  delay(15);
  Serial1.print(":74D030000FE\n");
  delay(15);
  Serial1.print(":70A1000000034\n");
  delay(15);
  Serial1.print(":70B1000000033\n");
  delay(15);
  Serial1.print(":75003000000FB\n");
  delay(15);
  Serial1.print(":75103000000FA\n");
  delay(15);
  Serial1.print(":75203000000F9\n");
  delay(15);
  Serial1.print(":75303000000F8\n");
  delay(15);
  Serial1.print(":75403000000F7\n");
  delay(15);
  Serial1.print(":75503000000F6\n");
  delay(15);
  Serial1.print(":75603000000F5\n");
  delay(15);
  Serial1.print(":75703000000F4\n");
  delay(15);
  Serial1.print(":75C03000000EF\n");
  delay(15);
  Serial1.print(":75D03000000EE\n");
  delay(15);
  Serial1.print(":75A03000000F1\n");
  delay(15);
  Serial1.print(":75B03000000F0\n");
  delay(15);
  Serial1.print(":76103000000EA\n");
  delay(15);
  Serial1.print(":76203000000E9\n");
  delay(15);
  Serial1.print(":7600301EA\n");
  delay(15);
  Serial1.print(":70910008403AE\n");
  delay(15);
  Serial1.print(":70010004001FD\n");
  delay(15);
  Serial1.print(":70110008700B6\n");
  delay(15);
  Serial1.print(":7021000280014\n");
  delay(15);
  Serial1.print(":7031000030038\n");
  delay(15);
  Serial1.print(":70510007D00BC\n");
  delay(15);
  Serial1.print(":70410005F00DB\n");
  delay(15);
  Serial1.print(":70610000A002E\n");
  delay(15);
  Serial1.print(":7071000030034\n");
  delay(15);
  Serial1.print(":7FD0F00141\n");
  delay(15);
  Serial1.print(":7FEEE00055D\n");
  delay(15);
  Serial1.print(":70004000149\n");
  delay(15);
  Serial1.print(":7F5EE00016A\n");
  delay(15);
  Serial1.print(":7E0EE00017F\n");
  delay(15);
  Serial1.print(":7E3EE00017C\n");
  delay(15);
  Serial1.print(":7E8EE000177\n");
  delay(15);
  Serial1.print(":7E4EE00017B\n");
  delay(15);
  Serial1.print(":7E5EE00017A\n");
  delay(15);
  Serial1.print(":7E6EE000179\n");
  delay(15);
  Serial1.print(":7E1EE00017E\n");
  delay(15);
  Serial1.print(":7E7EE000178\n");
  delay(15);
  Serial1.print(":7E2EE00017D\n");
  delay(15);
  Serial1.print(":7F6EE00006A\n");
  delay(15);
  Serial1.print(":7F7EE000069\n");
  delay(15);
  Serial1.print(":7F4EE0000006C\n");
  delay(15);
  Serial1.print(":7FBEE00F40170\n");
  delay(15);
  Serial1.print(":7FAEE00320034\n");
  delay(15);
  
  
  Serial1.print(":78FED000000D2\n");                  // Actual current (v, 0000)
  delay(15);
  Serial1.print(":78CED0000000000D5\n");              // Actual current 2 and 3
  delay(15);
  Serial1.print(":7820300FFFFCB\n");
  delay(15);
//  Serial1.print(":7ECED00FFFF77\n");                  // Actual battery temperature (v, -1) in K 1823
  int tempOut = int((temp1wire + 273.15) * 100.0);
  sendBinaryValue(":7ECED00", tempOut); // Send binary data
  delay(15);
//  Serial1.print(":78DED000B05C4\n");                  // Voltage service battery (v, 1291)
  int voltageOut = int(voltage * 100.0);
  sendBinaryValue(":78DED00", voltageOut); // Send binary data
  delay(15);
  Serial1.print(":7830300FF7F4A\n");
  delay(15);
  Serial1.print(":77DED00FF7F66\n");                  // Voltage starter battery
  delay(15);
  Serial1.print(":7FE0F00FFFF43\n");
  delay(15);
//  Serial1.print(":7FF0F00102709\n");                  // SOC (State Of Charge) (v 10000)
  int capacityOut = int(capacity * 100.0);
  sendBinaryValue(":7FF0F00", capacityOut); // Send binary data
  Serial1.print(":71D03012D\n");
  delay(15);
  Serial1.print(":71E03012C\n");
  delay(15);
  Serial1.print(":71C03012E\n");
  delay(15);

  
  Serial1.print(":7FFEE000000000061\n");
  delay(15);
  Serial1.print(":70003009FF8FFFFB6\n");
  delay(15);
  Serial1.print(":7090300040000003E\n");
  delay(15);
  Serial1.print(":70A0300060000003B\n");
  delay(15);
  Serial1.print(":70B03000000000040\n");
  delay(15);
  Serial1.print(":70E0300000000003D\n");
  delay(15);
  Serial1.print(":70F0300000000003C\n");
  delay(15);
  Serial1.print(":71003001C06000019\n");
  delay(15);
  Serial1.print(":711030033080000FF\n");
  delay(15);
  Serial1.print(":7010300000000004A\n");
  delay(15);
  Serial1.print(":7020300CAFAFFFF87\n");
  delay(15);
  Serial1.print(":70203000100000047\n");
  delay(15);
  Serial1.print(":70403000000000047\n");
  delay(15);
  Serial1.print(":7050300B5D1FFFFC2\n");
  delay(15);
  Serial1.print(":7060300E5FFFFFF63\n");
  delay(15);
  Serial1.print(":70703004F060000EF\n");
  delay(15);
  Serial1.print(":70803000000000043\n");
  delay(15);
  Serial1.print(":74E030000FD\n");
  delay(15);
  Serial1.print(":750010021000000DC\n");
  delay(15);
  Serial1.print(":75DEC0104\n");
  delay(15);
  Serial1.print(":75CEC0105\n");
  delay(15);
  Serial1.print(":75BEC0106\n");
  delay(15);
  Serial1.print(":763EC01FE\n");
  delay(15);
  Serial1.print(":764EC01FD\n");
  delay(15);
  Serial1.print(":75FEC0102\n");
  delay(15);
  Serial1.print(":75AEC0107\n");
  delay(15);
  Serial1.print(":74AEC0117\n");
  delay(15);
  Serial1.print(":752EC010F\n");
  delay(15);
  Serial1.print(":74BEC0116\n");
  delay(15);
  Serial1.print(":753EC010E\n");
  delay(15);
  Serial1.print(":74CEC0115\n");
  delay(15);
  Serial1.print(":754EC010D\n");
  delay(15);
  Serial1.print(":74DEC0114\n");
  delay(15);
  Serial1.print(":755EC010C\n");
  delay(15);
  Serial1.print(":74EEC0113\n");
  delay(15);
  Serial1.print(":756EC010B\n");
  delay(15);
  Serial1.print(":74FEC0112\n");
  delay(15);
  Serial1.print(":757EC010A\n");
  delay(15);
  Serial1.print(":750EC0111\n");
  delay(15);
  Serial1.print(":758EC0109\n");
  delay(15);
  Serial1.print(":751EC0110\n");
  delay(15);
  Serial1.print(":759EC0108\n");
  delay(15);
  Serial1.print(":790000001BD\n");
  delay(15);
  Serial1.print(":7910001BC\n");
  delay(15);
  Serial1.print(":77DEC01E4\n");
  delay(15);
  Serial1.print(":710EC0151\n");
  delay(15);
  Serial1.print(":73FEC0122\n");
  delay(15);
  Serial1.print(":712EC014F\n");
  delay(15);
  
  
  delay(1500);
}


