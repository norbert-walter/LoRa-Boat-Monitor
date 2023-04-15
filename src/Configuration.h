#ifndef Configuration_h
#define Configuration_h

// Default configuration
// Types 'byte' und 'word' doesn't work!
typedef struct {
  int valid = 8;                            // Number of configuration (Please change when the structure or values are changed)
  int crypt = 0;                            // Activate for critical webside a password query [0 = off|1 = on]
  char password[31] = "12345678";           // Password for critical websides (settings, update and reboot)
  char devname[21] = "LoRa Boat Monitor";   // Device name for web configuration
  char crights[14] = "NoWa (C) 2023";       // Copy rights
  char fversion[6] = "V1.06";               // Firmware version
  char license[12] = "GPL3";                // License type
  int debug = 3;                            // Debug mode 0=off 1=Errors 2=Errors + Warnings 3=Errors + Warnings + Messages
  char cssid[31] = "MyBoat";                // SSID of WiFi Client
  char cpassword[31] = "S6587rr94P";        // Password of WiFi Client
  int timeout = 30;                         // Connection timeout for client in [s] [30|90|120|150|180|210|240|270|300]
  char sssid[31] = "LoRaBoatMonitor";       // SSID of WiFi Server
  char spassword[31] = "12345678";          // Password of WiFi Server
  int apchannel = 1;                        // Assess Point channel [1...13]
  int maxconnections = 2;                   // Max number of connection for WiFi clients [1...4]
  int mDNS = 1;                             // Using mDNS service [0|1] 0=off, 1=on
  char hostname [31] = "boatmonitor";       // Hostname WiFi Server
  int dataport = 6666;                      // Port for NMEA data output
  int httpport = 80;                        // Port for HTTP and update pages
  int serverMode = 0;                       // Used server mode [0|1|2] 0=LoRa (HTTP, JSON, NMEA), 1=NMEA Serial, 2=Demo (Simulation data)
  int serspeed = 115200;                    // Serial speed in [Bd] 8N1 [300|1200|2400|4800|9600|19200|38400|57600|74880|115200]
  int skin = 0;                             // Skin for websides [0|1|2]

  // LoRaWAN device, network and session key
  u4_t devaddr = 0x12345678;                // LoRa device address
  u1_t nskey[16] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00 };  // LoRa Network session key
  u1_t appkey[16] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00 }; // LoRa Application Key


  char lorafrequency[6] = "EU868";          // LoRa frequency region [EU868|US915]
  int lchannel = 1;                         // Used LoRa channel [0...7|8|9] 0...7 single channel mode, 8 dynamic channel mode with channel 0...7, 9 dynamic channel mode with channel 0...2
  int spreadf = 10;                         // Spreading factor (SF) [7|8|9|10]
  int dynsf = 1;                            // Dynamic spreading factor [0|1] 0=off, 1=on (transmit schema SF SF SF SF SF SF SF SF SF SF SF+1 SF+2)
  int tinterval = 1;                        // LoRa transmit interval x30s, [1...255] (value x 30s, 10 X 30s = 300s = 5min)
  int sendlora = 1;                         // Send LoRa telegrams [0|1] 0=off 1=on
  int relay = 0;                            // Relay status [0|1] 0=off 1=on
                                            // Info: see relaytimer [0|1...255] 0=off 1...255= value x 5min on time for relay

  int instrumentSize = 400;                 // Instrument size X * Y [pix] [200|250|300|350|400|450|500|550|600]
  int deviceID = 0;                         // ID of LoRa device [0...9]
  char deviceType[10] = "LoRa1000";         // Type of LoRa boat monitor [LoRa1000]
  int senddata = 1;                         // Send sensor data to NMEA0183 [0|1] 0=off 1=on (WIMWV, WIVWR, WIVPW, PWINF) for Serial or JSON
  int sendubidots = 0;                      // Send telegrams to Ubidots [0|1] 0=off 1=on

  float voffset = 6.47301;                  // Voltage offset [V]
  float a1vslope = 0.02860676;              // Volatge calibration coefficient a1
  float a2vslope = 0;                       // Volatge calibration coefficient a2
  int vaverage = 1;                         // Volatge number of values for average building [1...100]

  float t1offset = 0;                       // Tank1 offset [l]
  float a1t1slope = 143.1974;               // Tank1 calibration coefficient a1
  float a2t1slope = 0;                      // Tank1 calibration coefficient a2
  int t1average = 1;                        // Tank2 number of values for average building [1...100]

  float t2offset = 0;                       // Tank2 offset [l]
  float a1t2slope = 143.1974;               // Tank2 calibration coefficient a1
  float a2t2slope = 0;                      // Tank2 calibration coefficient a2
  int t2average = 1;                        // Tank2 number of values for average building [1...100]

  char tempSensorType[10] = "Off";          // Type of temperature sensor [Off|DS18B20]
  char tempUnit[2] = "C";                   // Unit of temperature [C|F]

  char envSensor[20] = "Off";               // Select environment sensor [Off|BME280|VEdirect-Read|VEdirect-Send]
  char standbyMode[4] = "Off";              // Select Standby mode [Off|On]
  char loraStandbyMode[8] = "Standby";      // Select is Lora only sends in Standby mode [Standby|Always]
} configData;

#endif
