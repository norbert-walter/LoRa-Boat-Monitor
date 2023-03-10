#ifndef Definitions_h
#define Definitions_h

// Passwort settings
String transactionID = String(random(0, 99999999));// Generate a random transaction ID by initialisation
String raw = "";                    // Uncrypted raw data
String md5crypt = "";               // Crypted data

//MAC Address
uint64_t macAddress;                // MAC address equivalent to Chip-ID
uint64_t macAddressTrunc;           // Truncated MAC address
uint chipId;                        // Chip-ID as part from MAC address

// EEPROM settings (max size is 4096 Byte)
int cfgStart = 1024;                // Start adress in EEPROM (Attention! The first 32 Byte are used beginning with adress 0)
int sizeEEPROM = 2048;              // Used size of EEPROM 2kB (limit for config file size)

// WLAN client settings
String hname;                       // Hostname
int maxccounter;                    // Maximum number for connection tests until aborted (maxcounter = 60; 60 * 500ms = 30s waiting time)
int ccounter;                       // Actual connection test counter

// Settings for NMEA server 
int SendPeriod = 2000;              // SendPeriod in [ms], Attention! Range is limited [2000]
volatile bool flag1 = false;        // Flag for data sending

// LoRa timeslot counter for different spreading factors
long slotcounter = 0;               // Slot counter
int slot = 0;                       // Actual time slot
int sf = 7;                         // Actual spreading factor
int actlorachannel = 0;             // Actual LoRa channel
byte rpayload[200];                 // Received LoRa payload over downlink (array of 200 bytes)

// Measuring values
long starttime0 = millis();         // Timer0 value for measuring loop
long starttime1 = millis();         // Timer1 value for measuring loop
long starttime2 = millis();         // Timer2 value for measuring loop
float fieldstrength;                // WLAN field strength
float quality;                      // WLAN quality
float temperature;                  // Temperature in [°C]
float pressure;                     // Pressure in [hPa]
float humidity;                     // Himidity in [%]
float dewp;                         // Dewpoint in [°C]
float voltage;                      // Battery voltage in [V]
float capacity;                     // Battery capacity in [%]
float tank1;                        // Tank 1 level [V]
float tank2;                        // Tank 1 level [V]
float tank1p;                       // Tank 2 level [%]
float tank2p;                       // Tank 2 level [%]

int alarm1;                         // Digital Alarm input
int relaytimer = 0;                 // Relay timer for ontime n x 5min
float temp1wire = 0.0;              // Temperature 1Wire in [°C]
float temp1wireold = 0.0;           // Old temperature 1Wire in [°C]
float latitude = 0.0;               // Latutude in decimal notation
float longitude = 0.0;              // Longitude in decimal notation
float altitude;                     // Altitude [m]
String latitudeNS = "";             // Latitude direction N|S
String longitudeEW = "";            // Longitude direction E|W
int hour = 0;                       // Hour GPS
int minute = 0;                     // Minute GPS
int second = 0;                     // Second GPS
int day = 0;                        // Day GPS
int month = 0;                      // Month GPS
int year = 0;                       // Year GPS
int gpsspeed = 0;                   // Speed GPS
int course = 0;                     // Course GPS


// uint16_t valus for payload coding
uint16_t counter16 = 0;
uint16_t temperature16 = 0;
uint16_t pressure16 = 0;
uint16_t humidity16 = 0;
uint16_t altitude16 = 0;
uint16_t dewp16 = 0;
uint16_t voltage16 = 0;
uint16_t temp1wire16 = 0;
uint16_t longitude16_1 = 0;
uint16_t latitude16_1 = 0;
uint16_t longitude16_2 = 0;
uint16_t latitude16_2 = 0;
uint16_t tank1_16 = 0;
uint16_t tank2_16 = 0;

// Analog input 0...3.3V => 0...33V => 0...4096
const int ANALOG_IN = 36;     // Analog input GPIO36 Voltage
const int TANK1_IN = 37;      // Analog input GPIO37 Tank 1
const int TANK2_IN = 38;      // Analog input GPIO38 Tank 2

// Output Pins
const int ledPin = 25;        // Pin GPIO25, LED is high activ
const int relayPin = 25;      // Pin GPIO25, Relay is high activ

// Input Pins
const int alarmPin = 39;      // Pin GPI39, Alarm input

// 1Wire definitions
#define OneWIRE_PIN 23        // 1Wire on pin GPIO23
OneWire DS18B20(OneWIRE_PIN); // Declare 1Wire port
DallasTemperature sensors(&DS18B20);// Declare 1Wire sensor

// Serial port 1 pin definitions for VE.direct from Victron
#define RXD1 17               // VE.direct RX GPIO17
#define TXD1 22               // VE.direct TX GPIO22

// Serial port 2 pin definitions for GPS
#define RXD2 12               // GPS TX GPIO12
#define TXD2 13               // GPS RX GPIO13

int inByte = 0;               // Incoming byte from serial port 2
int start = 0;                // Marker for found telegram RMC
int c_counter = 0;            // Number of commata in RMC telegram

// BME280 environment sensor (temperature, humidity, pressure)
#define SEALEVELPRESSURE_HPA (1023.0) // Adjustment for altitude calculation
#define I2C_SDA 17            // SDA changed from GPIO21 to GPIO17
#define I2C_SCL 22            // SCL standard GPIO22
#define I2C_SPEED 100000      // I2C Speed 100KHz
uint8_t address = 0x76;       // BME280 I2C address
TwoWire I2CBME = TwoWire(0);  // Redefinition of I2C because changed pins
Adafruit_BME280 bme;          // Instance for BME280

// VE.direct battery monitor (BMV-712) Victron
float vedirectVoltage = 0;    // Battery voltage
float vedirectCurrent = 0;    // Battery current
float vedirectTemp = 0;       // Battery temperature
float vedirectPower = 0;      // Power consumption
float vedirectSOC = 0;        // State of charge

// GPS sensor
String nmea_all = "";         // All NMEA0183 GPS telegrams
String nmea = "";             // NMEA0183 RMC telegram
bool rmc_finish = false;      // Reading of RMC telegram finished [false not finished|true finished]
String gpsStatus = "";        // GPS status [A fix ok|V no fix]

// OLED SSD1306
// U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(clock, data, reset);
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(15, 4, 16);         // Heltec ESP32 LoRa (V2) pin definitions
                                                           // Clock GPIO15, Data GPIO4, Reset GPIO16
// Pin mapping for lmic LoRa chip SX1276
const lmic_pinmap lmic_pins = {
    .nss = 18,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 14,
    .dio = {26, 34, 35},
};

// Payload arry;
static uint8_t mydata[28];// 13 words + 1 word for array end
                          // mydata[0] Low Byte Counter
                          // mydata[1] High Byte Counter
                          // mydata[2] Low Byte Temperature
                          // mydata[3] High Byte Temperature
                          // mydata[4] Low Byte Pressure
                          // mydata[5] High Byte Pressure
                          // mydata[6] Low Byte Humidity
                          // mydata[7] High Byte Humidity
                          // mydata[8] Low Byte Dewpoint
                          // mydata[9] High Byte Dewpoint
                          // mydata[10] Low Byte Voltage
                          // mydata[11] High Byte Voltage
                          // mydata[12] Low Byte Temperature 1Wire
                          // mydata[13] High Byte Temperature 1Wire
                          // mydata[14] Low Byte Longitude 1
                          // mydata[15] High Byte Longitude 1
                          // mydata[16] Low Byte Longitude 2
                          // mydata[17] High Byte Longitude 2
                          // mydata[18] Low Byte Latitude 1
                          // mydata[19] High Byte Latitude 1
                          // mydata[20] Low Byte Latitude 2
                          // mydata[21] High Byte Latitude 2
                          // mydata[22] Low Byte Tank Level 1
                          // mydata[23] High Byte Tank Level 1
                          // mydata[24] Low Byte Tank Level 2
                          // mydata[25] High Byte Tank Level 2
                          // mydata[26] Low Byte Alarm1 and Relay
                          // mydata[27] Array End
                          // mydata[28] Array End

// Schedule TX every this many seconds (might become longer due to duty
// cycle limitations).
unsigned TX_INTERVAL = actconf.tinterval * 30;        // Send interval
bool lora_activ = false;                              // Marker for LoRa is activ

// Style parameter
int style = 1;                    // Toggle display between day (1) und night (0) illumination
int resetESP = 0;                 // Global marker for reset the ESP32

// Selection arrays (list of arguments in HTTP get response for index calculation)
String usepassword[2] = {"0", "1"};
String itype[2] = {"simple", "complex"};
String isize[9] = {"200", "250", "300", "350", "400", "450", "500", "550", "600"};
String timeout[10] = {"30", "60", "90", "120", "150", "180", "210", "240", "270", "300"};
String apchannel[13] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13"};
String servermode[5] = {"0", "1", "2", "3", "4"};
String mdnsservice[2] = {"0", "1"};
String lorafrequencys[2] = {"EU868", "US915"};
String lchannel[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
String spreadf[4] = {"7", "8", "9", "10"};
String dynsf[2] = {"0", "1"};
String relay[2] = {"0", "1"};
String debugmode[4] = {"0", "1", "2", "3"};
String serspeed[10] = {"300", "1200", "2400", "4800", "9600", "19200", "38400", "57600", "74880", "115200"};
String deviceid[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
String sendlora[2] = {"0", "1"};
String senddata[2] = {"0", "1"};
String vaverage[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
String t1average[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
String t2average[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
String dwrange[9] = {"20", "25", "30", "35", "40", "45", "50", "55", "60"};
String tstype[2] = {"Off", "DS18B20"};
String tempunits[2] = {"C", "F"};
String envSensor[4] = {"Off", "BME280", "VEdirect-Read", "VEdirect-Send"};

#endif
