#ifndef Functions_h
#define Functions_h

// Debugging functions
void DebugPrintln(int type, const char* x){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrintln(int type, char x[]){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrintln(int type, float x){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrintln(int type, char x){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrintln(int type, int x){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrintln(int type, uint32_t x){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrintln(int type, unsigned long x){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrintln(int type, String x){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrintln(int type, IPAddress x){
  if(type <= actconf.debug){
    Serial.println(x);
  }
}

void DebugPrint(int type, const char* x){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

void DebugPrint(int type, char x[]){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

void DebugPrint(int type, float x){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

void DebugPrint(int type, char x){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

void DebugPrint(int type, int x){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

void DebugPrint(int type, uint32_t x){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

void DebugPrint(int type, unsigned long x){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

void DebugPrint(int type, String x){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

void DebugPrint(int type, IPAddress x){
  if(type <= actconf.debug){
    Serial.print(x);
  }
}

void eraseEEPROMConfig(configData cfg) {
  // Reset EEPROM bytes to '0' for the length of the data structure
  noInterrupts();                       // Stop all interrupts important for writing in EEPROM
  EEPROM.begin(sizeEEPROM);
  for (int i = cfgStart ; i < sizeof(cfg) ; i++) {
    EEPROM.write(i, 0);
  }
  delay(200);
  EEPROM.commit();
  EEPROM.end();
  interrupts();                         // Activate all interrupts
}

void saveEEPROMConfig(configData cfg) {
  // Save configuration from RAM into EEPROM
  noInterrupts();                       // Stop all interrupts important for writing in EEPROM
  EEPROM.begin(sizeEEPROM);
  EEPROM.put( cfgStart, cfg );
  delay(200);
  EEPROM.commit();                      // Only needed for ESP8266 to get data written
  EEPROM.end();                         // Free RAM copy of structure
  interrupts();                         // Activate all interrupts
}

configData loadEEPROMConfig() {
  // Loads configuration from EEPROM into RAM
  configData cfg;
  EEPROM.begin(sizeEEPROM);
  EEPROM.get( cfgStart, cfg );
  EEPROM.end();
  return cfg;
}

//**************************************************************************************
// Converting bool to int
int boolToInt(bool value){
  if(value == HIGH){
    return 1;
  }
  else{
    return 0;
  }
}

// Converting string to int
 int toInteger(String settingValue){
   char intbuf[settingValue.length()+1];
   settingValue.toCharArray(intbuf, sizeof(intbuf));
   int f = atof(intbuf);
   return f;
 }

// Converting string to float
float toFloat(String settingValue){
  char floatbuf[settingValue.length()+1];
  settingValue.toCharArray(floatbuf, sizeof(floatbuf));
  float f = atof(floatbuf);
  return f;
}

// Converting string to long
long toLong(String settingValue){
  char longbuf[settingValue.length()+1];
  settingValue.toCharArray(longbuf, sizeof(longbuf));
  long l = atol(longbuf);
  return l;
}

// Converting String to integer and then to boolean
// 1 = true
// 0 = false
boolean toBoolean(String settingValue) {
  if(settingValue.toInt()==1){
    return true;
  } else {
    return false;
  }
}

// Convert string to char
char* toChar(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}

// Convert Hex to Int
int HexToInt(char str[])
{
  return (int) strtol(str, 0, 16);
}

// Seaching the index for a value in a string array
int getindex(String data[], String compare){
  // For all array elements
  for(int i=0; data[i].length() != 0; i++){
    DebugPrint(3, i);
    DebugPrint(3, " : ");
     DebugPrintln(3, data[i]);
    if(data[i] == compare){
      return i; 
    }
  }
  return 0;
}

// Displays a WLAN field strength symbol with characters
// 0))))
String wlansymbol(){
  String symbol = "O";
  float fieldstr = float(WiFi.RSSI());
  if(fieldstr > 0){
    fieldstr = -100.0;
  }
  float wlqual = 100  - (((fieldstr * -1) - 50) * 2);
  if(wlqual < 0){
    wlqual = 0;
  }
  if(wlqual > 100){
    wlqual = 100;
  }
  if(wlqual > 20){symbol = "0)";}
  if(wlqual > 40){symbol = "0))";}
  if(wlqual > 60){symbol = "0)))";}
  if(wlqual > 80){symbol = "0))))";}
  return symbol;
}

// Displays a WLAN field strength quality in %
int wlanquality(){
  float fieldstr = float(WiFi.RSSI());
  if(fieldstr > 0){
    fieldstr = -100.0;
  }
  int wlqual = 100  - (((fieldstr * -1) - 50) * 2);
  if(wlqual < 0){
    wlqual = 0;
  }
  if(wlqual > 100){
    wlqual = 100;
  }
  return wlqual;
}

// Truncate a float number 23.234 -> 23.2
float truncate1(float value){
  float result = roundf(value * 10) / 10;
  return result;
}

// Truncate a float number 23.234 -> 23.23
float truncate2(float value){
  float result = roundf(value * 100) / 100;
  return result;
}

// First zero character for integer lower 10
// value range from 0...99
String firstzero(int value){
  String output;
  if(value < 0){
    value = 0;
  }
  if(value > 99){
    value = 99;
  }
  if(value < 10){
    output = "0" + String(value);
  }
  else{
    output = String(value);
  }
  return output;
}

String transID(){
  transactionID = String(random(0, 99999999));    // Generate a random transaction ID, global defined

  return transactionID;
}

String cryptPassword(String password){
  MD5Builder md5;
  md5.begin();
  raw = password + transactionID;
  md5.add(raw);
  md5.calculate();
  md5crypt = md5.toString();
  DebugPrintln(3, "Crypt password");
  DebugPrint(3, "Password: ");
  DebugPrintln(3, password);
  DebugPrint(3, "Transaction ID: ");
  DebugPrintln(3, transactionID);
  DebugPrint(3, "Raw Data: ");
  DebugPrintln(3, raw);
  DebugPrint(3, "MD5 Hash: ");
  DebugPrintln(3, md5crypt);
  // Give back the crypted password
  return md5crypt;
}

int encryptPassword(String password, String md5hash){
  MD5Builder md5;
  md5.begin();
  raw = password + transactionID;
  md5.add(raw);
  md5.calculate();
  md5crypt = md5.toString();
  DebugPrintln(3, "Encrypt password");
  DebugPrint(3, "Password: ");
  DebugPrintln(3, password);
  DebugPrint(3, "Transaction ID: ");
  DebugPrintln(3, transactionID);
  DebugPrint(3, "Raw Data: ");
  DebugPrintln(3, raw);
  DebugPrint(3, "MD5 Hash: ");
  DebugPrintln(3, md5crypt);
  DebugPrint(3, "MD5 Hash2: ");
  DebugPrintln(3, md5crypt);
  // Compare the received hash
  if(md5crypt == md5hash){
    return 1;
  }
  else{
    return 0;
  }
}
//**************************************************************************************
// Clear serial 1 RX buffer
void Serial1Clear(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
} 

// Clear serial 2 RX buffer
void Serial2Clear(){
  while(Serial2.available() > 0) {
    char t = Serial2.read();
  }
} 

// Convert float to int 48.2345678 -> 4823
// Only usable for float 0.000...655.35
uint16_t float2int(float value){
  float result = roundf(value * 100);
  if(result < 0){
    result = 0;
  }
  if(result > 65535){
    result = 65535;
  }
  return result;
}

// Convert float to int 48.2345678 -> 48234
// Only usable for float 0.000...65.535
uint16_t float3int(float value){
  float result = roundf(value * 1000);
  if(result < 0){
    result = 0;
  }
  if(result > 65535){
    result = 65535;
  }
  return result;
}

// Convert float to int 3.2345678 -> 323456
// Only usable for float 0.000...6.5535
uint16_t float4int(float value){
  float result = roundf(value * 10000);
  if(result < 0){
    result = 0;
  }
  if(result > 65535){
    result = 65535;
  }
  return result;
}

// Flash LED for x ms
void flashLED(int duration){
 digitalWrite(ledPin, HIGH);   // On (High activ)
 delay(duration);
 digitalWrite(ledPin, LOW);    // Off
}

// Dewpoint calculation
// Refer: https://de.wikipedia.org/wiki/Taupunkt
float dewpoint(float temp, float humidity) {
  float K1 = 6.112;   // [hPa]
  float K2 = 17.62;   // [1]
  float K3 = 243.12;  // [°C]
  float term1 = (K2 * temp) / (K3 + temp);
  float term2 = (K2 * K3) / (K3 + temp);
  float term3 = log(humidity / 100);                  // Humidiy range 0...1
  float dewp = K3 *((term1 + term3)/(term2 - term3));
  return dewp;
}

// Checksum calculation over binary array
byte BinCheckSum(byte Data[]) {
  byte checksum = 0;
  // Iterate over the string, ADD each byte with the total sum
  for (int c = 0; c < sizeof(Data); c++) {
    checksum += Data[c];
  } 
  // Return the result
  return checksum;
}

// Checksum calculation for NMEA
char CheckSum(String NMEAData) {
  char checksum = 0;
  // Iterate over the string, XOR each byte with the total sum
  for (int c = 0; c < NMEAData.length(); c++) {
    checksum = char(checksum ^ NMEAData.charAt(c));
  } 
  // Return the result
  return checksum;
}

// Check NMEA string
bool CheckNMEA(String NMEAstring) {
  bool check = false;
  int i1 = NMEAstring.indexOf( '$');
  int i2 = NMEAstring.indexOf( '*');
  int i3 = NMEAstring.length();
  String NMEApartial = NMEAstring.substring(i1+1, i2);
  String cksum1 = NMEAstring.substring(i2+1, i3);
  String cksum2 = String(CheckSum(NMEApartial), HEX);
  int cksum3 = HexToInt(toChar(cksum1));
  int cksum4 = HexToInt(toChar(cksum2));
//  DebugPrintln(3, cksum1);
//  DebugPrintln(3, cksum2);
//  DebugPrintln(3, cksum3);
//  DebugPrintln(3, cksum4);
  if(cksum3 == cksum4){
    check = true;
  }
  else{
    check = false;
  }
  return check;
}

// Enable the used LoRa channels
void setChannel(int channel){
  switch (channel) {
  case 0:
    // Single channel 0
    LMIC_disableChannel (1);
    LMIC_disableChannel (2);
    LMIC_disableChannel (3);
    LMIC_disableChannel (4);
    LMIC_disableChannel (5);
    LMIC_disableChannel (6);
    LMIC_disableChannel (7);
    break;
  case 1:
    // Single channel 1
    LMIC_disableChannel (0);
    LMIC_disableChannel (2);
    LMIC_disableChannel (3);
    LMIC_disableChannel (4);
    LMIC_disableChannel (5);
    LMIC_disableChannel (6);
    LMIC_disableChannel (7);
    break;
  case 2:
    // Single channel 2
    LMIC_disableChannel (0);
    LMIC_disableChannel (1);
    LMIC_disableChannel (3);
    LMIC_disableChannel (4);
    LMIC_disableChannel (5);
    LMIC_disableChannel (6);
    LMIC_disableChannel (7);
    break;
  case 3:
    // Single channel 3
    LMIC_disableChannel (0);
    LMIC_disableChannel (1);
    LMIC_disableChannel (2);
    LMIC_disableChannel (4);
    LMIC_disableChannel (5);
    LMIC_disableChannel (6);
    LMIC_disableChannel (7);
    break;
  case 4:
    // Single channel 4
    LMIC_disableChannel (0);
    LMIC_disableChannel (1);
    LMIC_disableChannel (2);
    LMIC_disableChannel (3);
    LMIC_disableChannel (5);
    LMIC_disableChannel (6);
    LMIC_disableChannel (7);
    break;
  case 5:
    // Single channel 5
    LMIC_disableChannel (0);
    LMIC_disableChannel (1);
    LMIC_disableChannel (2);
    LMIC_disableChannel (3);
    LMIC_disableChannel (4);
    LMIC_disableChannel (6);
    LMIC_disableChannel (7);
    break;
  case 6:
    // Single channel 6
    LMIC_disableChannel (0);
    LMIC_disableChannel (1);
    LMIC_disableChannel (2);
    LMIC_disableChannel (3);
    LMIC_disableChannel (4);
    LMIC_disableChannel (5);
    LMIC_disableChannel (7);
    break;
  case 7:
    // Single channel 7
    LMIC_disableChannel (0);
    LMIC_disableChannel (1);
    LMIC_disableChannel (2);
    LMIC_disableChannel (3);
    LMIC_disableChannel (4);
    LMIC_disableChannel (5);
    LMIC_disableChannel (6);
    break;
  case 8:
    // Multi channel 0...7
    break;
  case 9:
    // Multi channel 0...2
    LMIC_disableChannel (3);
    LMIC_disableChannel (4);
    LMIC_disableChannel (5);
    LMIC_disableChannel (6);
    LMIC_disableChannel (7);
    break;        
  default:
    // Channel 0
    LMIC_disableChannel (1);
    LMIC_disableChannel (2);
    LMIC_disableChannel (3);
    LMIC_disableChannel (4);
    LMIC_disableChannel (5);
    LMIC_disableChannel (6);
    LMIC_disableChannel (7);
    break;
  }
}

// Set dynamically the spreading factor depends from time slot
void setSF(int tslot, int spreadingfactor, int dynamicsf){
  // If dynamic spreading factor active
  if(dynamicsf == 1){
    switch (spreadingfactor) {
    case 7:
      // SF7
      switch (tslot) {
        case 0:
          LMIC_setDrTxpow(DR_SF7,14);  // SF7
          sf = 7;
          break;
        case 1:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 2:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 3:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 4:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 5:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 6:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 7:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 8:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 9:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 10:
          LMIC_setDrTxpow(DR_SF8,14);  // SF8
          sf = 8;
          break;
        case 11:
          LMIC_setDrTxpow(DR_SF9,14);  // SF9
          sf = 9;
          break;         
        default:
          LMIC_setDrTxpow(DR_SF7,14);  // Default
          sf = 7;
          break;
      }
      break;
    case 8:
      // SF8
      switch (tslot) {
        case 0:
          LMIC_setDrTxpow(DR_SF8,14);  // SF8
          sf = 8;
          break;
        case 1:
          LMIC_setDrTxpow(DR_SF8,14);
          sf = 8;
          break;
        case 2:
          LMIC_setDrTxpow(DR_SF8,14);
          sf = 8;
          break;
        case 3:
          LMIC_setDrTxpow(DR_SF8,14);
          sf = 8;
          break;
        case 4:
          LMIC_setDrTxpow(DR_SF8,14);
          sf = 8;
          break;
        case 5:
          LMIC_setDrTxpow(DR_SF8,14);
          sf = 8;
          break;
        case 6:
          LMIC_setDrTxpow(DR_SF8,14);
          sf = 8;
          break;
        case 7:
          LMIC_setDrTxpow(DR_SF8,14);
          sf = 8;
          break;
        case 8:
          LMIC_setDrTxpow(DR_SF8,14);
          sf = 8;
          break;
        case 9:
          LMIC_setDrTxpow(DR_SF8,14);
          sf = 8;
          break;
        case 10:
          LMIC_setDrTxpow(DR_SF9,14);  // SF9
          sf = 9;
          break;
        case 11:
          LMIC_setDrTxpow(DR_SF10,14); // SF10
          sf = 10;
          break;         
        default:
          LMIC_setDrTxpow(DR_SF8,14);  // Default
          sf = 8;
          break;
      }
      break;
    case 9:
      // SF9
      switch (tslot) {
        case 0:
          LMIC_setDrTxpow(DR_SF9,14);  // SF9
          sf = 9;
          break;
        case 1:
          LMIC_setDrTxpow(DR_SF9,14);
          sf = 9;
          break;
        case 2:
          LMIC_setDrTxpow(DR_SF9,14);
          sf = 9;
          break;
        case 3:
          LMIC_setDrTxpow(DR_SF9,14);
          sf = 9;
          break;
        case 4:
          LMIC_setDrTxpow(DR_SF9,14);
          sf = 9;
          break;
        case 5:
          LMIC_setDrTxpow(DR_SF9,14);
          sf = 9;
          break;
        case 6:
          LMIC_setDrTxpow(DR_SF9,14);
          sf = 9;
          break;
        case 7:
          LMIC_setDrTxpow(DR_SF9,14);
          sf = 9;
          break;
        case 8:
          LMIC_setDrTxpow(DR_SF9,14);
          sf = 9;
          break;
        case 9:
          LMIC_setDrTxpow(DR_SF9,14);
          sf = 9;
          break;
        case 10:
          LMIC_setDrTxpow(DR_SF10,14); // SF10
          sf = 10;
          break;
        case 11:
          LMIC_setDrTxpow(DR_SF11,14); // SF11
          sf = 11;
          break;         
        default:
          LMIC_setDrTxpow(DR_SF9,14);  // Default
          sf = 9;
          break;
      }
      break;
    case 10:
      // SF10
      switch (tslot) {
        case 0:
          LMIC_setDrTxpow(DR_SF10,14);  // SF10
          sf = 10;
          break;
        case 1:
          LMIC_setDrTxpow(DR_SF10,14);
          sf = 10;
          break;
        case 2:
          LMIC_setDrTxpow(DR_SF10,14);
          sf = 10;
          break;
        case 3:
          LMIC_setDrTxpow(DR_SF10,14);
          sf = 10;
          break;
        case 4:
          LMIC_setDrTxpow(DR_SF10,14);
          sf = 10;
          break;
        case 5:
          LMIC_setDrTxpow(DR_SF10,14);
          sf = 10;
          break;
        case 6:
          LMIC_setDrTxpow(DR_SF10,14);
          sf = 10;
          break;
        case 7:
          LMIC_setDrTxpow(DR_SF10,14);
          sf = 10;
          break;
        case 8:
          LMIC_setDrTxpow(DR_SF10,14);
          sf = 10;
          break;
        case 9:
          LMIC_setDrTxpow(DR_SF10,14);
          sf = 10;
          break;
        case 10:
          LMIC_setDrTxpow(DR_SF11,14);  // SF11
          sf = 11;
          break;
        case 11:
          LMIC_setDrTxpow(DR_SF12,14);  // SF12
          sf = 12;
          break;         
        default:
          LMIC_setDrTxpow(DR_SF10,14);  // Default
          sf = 10;
          break;
      }
      break;
    default:
      // SF7
      switch (tslot) {
        case 0:
          LMIC_setDrTxpow(DR_SF7,14);  // SF7
          sf = 7;
          break;
        case 1:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 2:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 3:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 4:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 5:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 6:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 7:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 8:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 9:
          LMIC_setDrTxpow(DR_SF7,14);
          sf = 7;
          break;
        case 10:
          LMIC_setDrTxpow(DR_SF8,14);  // SF8
          sf = 8;
          break;
        case 11:
          LMIC_setDrTxpow(DR_SF9,14);  // SF9
          sf = 9;
          break;         
        default:
          LMIC_setDrTxpow(DR_SF7,14);  // Default
          sf = 7;
          break;
      }
      break;  
    }
  }
  // If dynamic spreading factor not active
  else{
    switch (spreadingfactor) {
    case 7:
      // SF7
      LMIC_setDrTxpow(DR_SF7,14);
      sf = 7;
      break;
    case 8:
      // SF8
      LMIC_setDrTxpow(DR_SF8,14);
      sf = 8;
      break;
    case 9:
      // SF9
      LMIC_setDrTxpow(DR_SF9,14);
      sf = 9;
      break;
    case 10:
      // SF10
      LMIC_setDrTxpow(DR_SF10,14);
      sf = 10;
      break;  
    default:
      // SF7
      LMIC_setDrTxpow(DR_SF7,14);
      sf = 7;
      break;
    }
  }
}

// Read and print sensor values
void readValues() {
    // Is connected with extern WLAN network
    if(WiFi.localIP().toString() != "0.0.0.0"){
      fieldstrength = float(WiFi.RSSI());
      if(fieldstrength > 0){
        fieldstrength = -100.0;
      }
      quality = 100  - (((fieldstrength * -1) - 50) * 2);
      if(quality < 0){
        quality = 0;
      }
      if(quality > 100){
        quality = 100;
      }
    }
    else{
      fieldstrength = 0;
      quality = 0;
    }
    
    // Read BME280 sensor values
    if (String(actconf.envSensor) == "BME280") {
      DebugPrint(3, "Temperature = ");
      if(String(actconf.tempUnit) == "C"){
        temperature = bme.readTemperature();
        DebugPrint(3, temperature);
        DebugPrintln(3, " *C");
      }
      else{
        temperature = bme.readTemperature() * 9 / 5 + 32;
        DebugPrint(3, temperature);
        DebugPrintln(3, " *F");
      }
  
      DebugPrint(3, "Pressure = ");
      pressure = bme.readPressure() / 100.0F;
      DebugPrint(3, pressure);
      DebugPrintln(3, " hPa");
  
      DebugPrint(3, "Approx. Altitude = ");
      altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
      DebugPrint(3, altitude);
      DebugPrintln(3, " m");
  
      DebugPrint(3, "Humidity = ");
      humidity = bme.readHumidity();
      DebugPrint(3, humidity);
      DebugPrintln(3, " %");
  
      DebugPrint(3, "Dewpoint = ");
      dewp = dewpoint(temperature, humidity);
      // temperature is chnanged in the correct unit!
      if(String(actconf.tempUnit) == "C"){
        DebugPrint(3, dewp);
        DebugPrintln(3, " *C");
      }
      else{
        DebugPrint(3, dewp);
        DebugPrintln(3, " *F");
      }
    }

    // Show and copy BMV-712 battery monitor values
    if (String(actconf.envSensor) == "VEdirect-Read") {
      DebugPrint(3, "VE.direct Voltage = ");
      DebugPrint(3, vedirectVoltage);
      DebugPrintln(3, " V");

      DebugPrint(3, "VE.direct Current = ");
      DebugPrint(3, vedirectCurrent);
      DebugPrintln(3, " A");

      DebugPrint(3, "VE.direct Temperature = ");
      DebugPrint(3, vedirectTemp);
      DebugPrintln(3, " *C");

      //Copy voltage and temperature in in original values
      voltage = vedirectVoltage;
      temp1wire = vedirectTemp;
    }
    else{
      vedirectVoltage = 0.0;
      vedirectCurrent= 0.0;
      vedirectTemp = 0.0;
    }
    
    // Analog input 0...3.3V => 0...33V => 0...4096
    if (String(actconf.envSensor) != "VEdirect-Read") {
      DebugPrint(3, "Voltage = ");
      voltage = actconf.a2vslope * actconf.a2vslope * analogRead(ANALOG_IN) + actconf.a1vslope * analogRead(ANALOG_IN) + actconf.voffset;
      DebugPrint(3, analogRead(ANALOG_IN));
      DebugPrintln(3, " dig");
    }
    DebugPrint(3, "Voltage = ");
    DebugPrint(3, voltage);
    DebugPrintln(3, " V");
    // Battery Capacity 100% = 12,70V, 0% = 10,50V Pb-Accu
    capacity = (voltage * 100 / 2.2) - 477.27;
    if(capacity < 0){
      capacity = 0;
    }
    if(capacity > 100){
      capacity = 100;
    }
    DebugPrint(3, "Capacity = ");
    DebugPrint(3, capacity);
    DebugPrintln(3, " %");

    DebugPrint(3, "Tank1 = ");
    // Analog input 0...3.3V => 0...33V => 0...4096
    tank1 = 3.3 / 4096 * analogRead(TANK1_IN);
    DebugPrint(3, tank1);
    DebugPrint(3, " V ");
    if(tank1 < 1){
      tank1p = (tank1 * actconf.a2t1slope * actconf.a2t1slope) + (tank1 * actconf.a1t1slope) + actconf.t1offset;
    }
    else{
      tank1p = 0;
    }
  	// Limiting
  	if(tank1p > 100){
      tank1p = 100;
    }
    if(tank1p < 0){
      tank1p = 0;
    }
    DebugPrint(3, tank1p);
    DebugPrintln(3, " %");

    DebugPrint(3, "Tank2 = ");
    // Analog input 0...3.3V => 0...33V => 0...4096
    tank2 = 3.3 / 4096 * analogRead(TANK2_IN);
    DebugPrint(3, tank2);
    DebugPrint(3, " V ");
     if(tank2 < 1){
      tank2p = (tank2 * actconf.a2t2slope * actconf.a2t2slope) + (tank2 * actconf.a1t2slope) + actconf.t2offset;
    }
    else{
      tank2p = 0;
    }
  	// Limiting
  	if(tank2p > 100){
      tank2p = 100;
    }
    if(tank2p < 0){
      tank2p = 0;
    }
    DebugPrint(3, tank2p);
    DebugPrintln(3, " %");

    DebugPrint(3, "Alarm = ");
    // Digital input 12V activ via opto coupler
    alarm1 = digitalRead(alarmPin);
    DebugPrint(3, alarm1);
    DebugPrintln(3, "  ");

    DebugPrint(3, "Relay = ");
    // Digital relay output high activ 
    DebugPrint(3, actconf.relay);
    DebugPrintln(3, "  ");

    DebugPrint(3, "envSensor = ");
    DebugPrint(3, String(actconf.envSensor));
    DebugPrintln(3, "  ");

    // Read 1Wire sensor values for battery temperature
    if (String(actconf.envSensor) != "VEdirect-Read") {
      sensors.requestTemperatures();            // Send the command to get temperatures
      temp1wire = sensors.getTempCByIndex(0);   // Read 1Wire sensor 0
      // Error correction for wrong 1Wire values (-127)
      if(temp1wire < float(-50)){
        temp1wire = temp1wireold;
      }
      else{
        temp1wireold = temp1wire;
      }
    }
    // Unit selection
    DebugPrint(3, "BattTemp = ");
    if(String(actconf.tempUnit) == "C"){
      DebugPrint(3, temp1wire);
      DebugPrintln(3, " *C");
    }
    else{
      temp1wire = temp1wire * 9 / 5 + 32;
      DebugPrint(3, temp1wire);
      DebugPrintln(3, " *F");
    }
    DebugPrintln(3, "");
}

// Display sensor values on OLED
void writeDisplay() {
  
  // Formating display data
  char cnt[10];
  dtostrf(int(counter16), 5, 0, cnt);
  char tmp[10];      
  dtostrf(temperature, 5, 1, tmp);
  char pres[10];
  dtostrf(pressure, 5, 0, pres);
  char hum[10];
  dtostrf(humidity, 5, 1, hum);
  char dew[10];
  dtostrf(dewp, 5, 1, dew);
  char dt[10];
  dtostrf(float(TX_INTERVAL), 4, 0, dt);
  char vol[10];
  dtostrf(voltage, 5, 1, vol);
  char tmp2[10];
  dtostrf(temp1wire, 5, 1, tmp2);
  char lat[10];
  dtostrf(latitude, 5, 3, lat);
  char lon[10];
  dtostrf(longitude, 6, 4, lon);
  char tnk1[10];
  dtostrf(tank1p, 5, 1, tnk1);
  char tnk2[10];
  dtostrf(tank2p, 5, 1, tnk2);
  char alm[10];
  dtostrf(int(alarm1), 5, 0, alm);
  char rel[10];
  dtostrf(int(actconf.relay), 5, 0, rel);
  
  // Refresh OLED data
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,0,"NoWa(C)OBP");
  u8x8.drawString(11,0,actconf.fversion);
  u8x8.drawString(0,1,"C:");
  u8x8.drawString(2,1,cnt);
  u8x8.drawString(0,2,"T:");
  u8x8.drawString(2,2,tmp);
  u8x8.drawString(0,3,"P:");
  u8x8.drawString(2,3,pres);
  u8x8.drawString(0,4,"H:");
  u8x8.drawString(2,4,hum);
  u8x8.drawString(0,5,"D:");
  u8x8.drawString(2,5, dew);
  u8x8.drawString(8,1,"dT:");
  u8x8.drawString(11,1, dt);
  u8x8.drawString(15,1, "s");
  u8x8.drawString(9,2,"V:");
  u8x8.drawString(11,2, vol);
  u8x8.drawString(8,3,"T2:");
  u8x8.drawString(11,3, tmp2);
  u8x8.drawString(8,4,"Y:");
  u8x8.drawString(10,4, lat);
  u8x8.drawString(8,5,"X:");
  u8x8.drawString(10,5, lon);
  u8x8.drawString(0,6,"L:");
  u8x8.drawString(2,6, tnk1);
  u8x8.drawString(8,6,"L2:");
  u8x8.drawString(11,6, tnk2);
  u8x8.drawString(0,7,"A:");
  u8x8.drawString(2,7, alm);
  u8x8.drawString(8,7,"R:");
  u8x8.drawString(11,7, rel);
  u8x8.refreshDisplay();    // Only required for SSD1606/7 
}

// Timer 1 interrupt Read and print GPS values
void readGPSValues() {
  DebugPrintln(3, "Timer1");
  rmc_finish = false;
  // Special hack to restart the hanging serial 2 port
  while(!Serial2.available()){
    while(Serial2.read() >= 0);  // Clear read buffer
    Serial2.end();
    delay(200);
    Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
    delay(200);
  }
  // Read serial 2 if data coming and RMC not finished and no LoRa telegram sending
  while(Serial2.read() >= 0);  // Clear read buffer
  delay(1500);                 // Wait 1.5s for new telegrams form GPS
  c_counter = 0;               // Clear commata counter
  while(Serial2.available() && !rmc_finish && !lora_activ) { // If data on serial 2 available
    inByte = Serial2.read(); // Read data
    // Start by $ or ! string
    if ((start==0) && ((inByte == '$')||(inByte == '!'))) {
      start = 1;
      c_counter = 0;          // Clear commata counter
      nmea = "";
      nmea_all = "";
    }
    if(start==1 && (inByte==44)) {c_counter++;}   // Count all commata
    if(start==1) {nmea_all.concat((char)inByte);} // Concat character
    if((inByte==13) && (start==1)) { // Detect end of NMEA0183 telegram (CR)
      start=0;
      DebugPrintln(3, nmea_all); // Print all NMEA0183 telegrams
      if (nmea_all.substring(3,6) == "RMC") {
        nmea = nmea_all;            // Take over RMC telegram
        DebugPrint(3, "Commata: ");
        DebugPrintln(3, c_counter); // Print commata counter for RMC
        // If NMEA cecksum ok
        if(CheckNMEA(nmea) && c_counter == 12) {
          DebugPrintln(3, "RMC message processed"); // Only print RMC telegram
          DebugPrint(3, "Sta ");
          gpsStatus = getRMC_status(nmea);
          DebugPrintln(3, gpsStatus);
          DebugPrint(3, "Lat ");
          latitude = getRMC_LatDec(nmea);
          DebugPrint(3, String(latitude, 6));
          latitudeNS = getRMC_LatNS(nmea);
          DebugPrintln(3, String(latitudeNS));         
          DebugPrint(3, "Lon ");         
          longitude = getRMC_LonDec(nmea);
          DebugPrint(3, String(longitude, 6));
          longitudeEW = getRMC_LonEW(nmea);
          DebugPrintln(3, String(longitudeEW));
          DebugPrintln(3, "");

          DebugPrint(3, "Time ");
          hour = getRMC_hour(nmea);
          DebugPrint(3, String(hour));
          DebugPrint(3, ":");
          minute = getRMC_min(nmea);
          DebugPrint(3, String(minute));
          DebugPrint(3, ":");
          second = getRMC_sec(nmea);
          DebugPrintln(3, String(second));
          DebugPrintln(3, "");

          DebugPrint(3, "Date ");
          day = getRMC_Day(nmea);
          DebugPrint(3, String(day));
          DebugPrint(3, ".");
          month = getRMC_Month(nmea);
          DebugPrint(3, String(month));
          DebugPrint(3, ".");
          year = getRMC_Year(nmea);
          DebugPrintln(3, String(year));
          DebugPrintln(3, "");

          DebugPrint(3, "Speed ");
          gpsspeed = getRMC_Speed(nmea);
          DebugPrintln(3, String(gpsspeed));
          DebugPrint(3, "Course ");
          course = getRMC_Course(nmea);
          DebugPrintln(3, String(course));
          DebugPrintln(3, "");

          DebugPrint(3, "Env Sensor ");
          DebugPrintln(3, String(actconf.envSensor));
          DebugPrintln(3, "");

          rmc_finish = true;
        }
        else{
          DebugPrintln(3, "Checksum wrong!");
          while(Serial2.read() >= 0 && Serial2.read() != '$'); // Clear read buffer until $
          nmea = "";
          nmea_all = "";
        }
      }
      else{
        DebugPrintln(3, "No RMC message found! ");
        delay(250);
        while(Serial2.read() >= 0 && Serial2.read() != '$'); // Clear read buffer until $
        nmea = "";
        nmea_all = "";
      }
    }
  }
  while(Serial2.read() >= 0);  // Clear read buffer
}

// Timer2 Interrupt relay timer
void relayTimer(){
  relaytimer--; // Decrement relay timer
  if(relaytimer <= 0){
    relaytimer = 0;
    digitalWrite(relayPin, LOW); // Relay off
    actconf.relay = 0;
    saveEEPROMConfig(actconf);
  }
  else{
    digitalWrite(relayPin, HIGH); // Relay on
  }
}

// Timer3 routine for NMEA data sending with normal speed (all 2s)
void sendNMEA() {
  // Set data sending flag1
  flag1 = true;
}

#endif
