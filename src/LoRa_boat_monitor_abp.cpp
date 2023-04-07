 /*******************************************************************************
 * Copyright (c) 2023 Norbert Walter modified by Guntmar Hoeche
 * 
 * License: GNU GPL V3
 * https://www.gnu.org/licenses/gpl-3.0.txt
 *
 * LoRa_Boat_Monitor.cpp
 * 
 * Based on work of 2015 Thomas Telkamp and Matthijs Kooijman
 *
 * This uses ABP (Activation-by-personalisation), where a DevAddr and
 * Session keys are preconfigured (unlike OTAA, where a DevEUI and
 * application key is configured, while the DevAddr and session keys are
 * assigned/generated in the over-the-air-activation procedure).
 *
 * Note: LoRaWAN per sub-band duty-cycle limitation is enforced (1% in
 * g1, 0.1% in g2), but not the TTN fair usage policy (which is probably
 * violated by this sketch when left running for longer)!
 *
 * To use this sketch, first register your application and device with
 * the things network, to set or generate a DevAddr, NwkSKey and
 * AppSKey. Each device should have their own unique values for these
 * fields.
 *
 *******************************************************************************
 *
 * Attention! Check for EU868 the build settings in plarformio.ini
 *     -D ARDUINO_LMIC_PROJECT_CONFIG_H_SUPPRESS
 *     -D CFG_eu868=1
 *     -D CFG_sx1276_radio=1
 *
 * Set the #define CFG_eu868=1
 * 
 *******************************************************************************/
 
// Includes
#include <Arduino.h>            // Arduino Environment
#include <WiFi.h>               // WiFi lib with TCP server and client
#include <WiFiClient.h>         // WiFi lib for clients
#include <WebServer.h>          // WebServer lib
#include <ESPmDNS.h>            // mDNS lib
#include <Update.h>             // Web Update server
#include <MD5Builder.h>         // MD5 lib
#include "driver/adc.h"

#include <U8x8lib.h>            // OLED Lib
#include <lmic.h>               // LoRa Lib
#include <hal/hal.h>            // LoRa Lib
#include <Wire.h>
#include <SPI.h>                // SPI/I2C Lib for OLED and BME280
#include <Adafruit_Sensor.h>    // BME280
#include <Adafruit_BME280.h>    // BME280
#include <Ticker.h>             // Timer lib
#include <EEPROM.h>             // EEPROM lib
#include <WString.h>            // Needs for structures
#include <OneWire.h>            // 1Wire lib
#include <DallasTemperature.h>  // DS18B20 lib
#include <StateMachine.h>

#include "driver/rtc_io.h"

#include "Configuration.h"      // Configuration

configData actconf;             // Actual configuration, Global variable
                                // Overload with old EEPROM configuration by start. It is necessarry for port and serial speed
                                // Don't change the position!

#include "Definitions.h"        // Global definitions
#include "GPS.h"                // GPS parsing functions
#include "vedirect.h"           // VE.direct lib
#include "Functions.h"          // Function lib
#include "NMEATelegrams.h"      // Function library for NMEA telegrams
#include "LoRa.h"               // LoRa Lib
#include "task.h"               // Task for LoRa code

#include "icon_html.h"          // Favorit icon
#include "css_html.h"           // CCS cascading style sheets
#include "js_html.h"            // JavaScript functions
#include "main_html.h"          // Main webpage
#include "sensorv_html.h"       // Sensor Values webpage
#include "lora_html.h"          // LoRa Info webpage
#include "settings_html.h"      // Settings webpage
#include "firmware_html.h"      // Firmware update webpage
#include "json_html.h"          // JSON webpage
#include "MD5_html.h"           // JavaScript crypt password with MD5
#include "fwupdate.h"           // Webpage for firmware update
#include "restart_html.h"       // Reset info webpage
#include "devinfo_html.h"       // Device info webpage
#include "error_html.h"         // Error 404 webpage

// Declarations
int value;                      // Value from first byte in EEPROM
int empty;                      // If EEPROM empty without configutation then set to 1 otherwise 0
configData defconf;             // Definition of default configuration data
configData oldconf;             // Configuration stucture for old config data in EEPROM
configData newconf;             // Configuration stucture for new config data in EEPROM

TaskHandle_t Task1;             // Declare task for LoRa code

WebServer httpServer(actconf.httpport);   // Port for HTTP server
MDNSResponder mdns;                       // Activate DNS responder
WiFiServer server(actconf.dataport);      // Declare WiFi NMEA server port

Ticker Timer1;                  // Declare Timer for GPS data reading
Ticker Timer2;                  // Declare Timer for relay ontime
Ticker Timer3;                  // Declare Timer for NMEA sending

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  15        /* Time ESP32 will go to sleep (in seconds) */
RTC_DATA_ATTR int bootCount = 0;
RTC_DATA_ATTR uint loraCount = 0;

const int STATE_DELAY = 1000;
int randomState = 0;

StateMachine machine = StateMachine();
int loopcounter = 0;

/*
 *  States:
 *  S0 = Setup
 *  S1 = Collecting Data from sensors, and send via Lora, go into standby, wakeup every x Minutes, WiFi and Bluetooth and Webserver off.
 *  S2 = Haushalt Batterie "On", Enable Wifi, no standby, local Webserver for deliver data to mobilephone. Maybe in long intervals also to a local server.
 *  S3 = Motor Bat "On", Send data continous to a local server.
 */

void UBLOX_GPS_Wakeup()
{
  Serial2.println();                                   //send some characters to GPS to wake it up
}

void UBLOX_GPS_Shutdown()
{
  //sends command over serial interface to GPS to put it in PMREQ backup mode
  uint8_t index;
  uint8_t UBLOX_GPSStandby[] = {0xB5, 0x62, 0x02, 0x41, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x4D, 0x3B}; 

  for (index = 0; index < sizeof(UBLOX_GPSStandby); index++)
  {
    Serial2.write(UBLOX_GPSStandby[index]);
    Serial.print(UBLOX_GPSStandby[index], HEX);
    Serial.print(" ");
  }
}

void enableWiFi(){
  adc_power_on();
  WiFi.disconnect(false);  // Reconnect the network
  WiFi.mode(WIFI_STA);    // Switch WiFi off
 
  Serial.println("START WIFI");
  WiFi.begin(actconf.cssid, actconf.cpassword);
 
  int i = 0;
  while ((WiFi.status() != WL_CONNECTED) && (i <= 20))
  {
    delay(500);
    Serial.print(".");
    i++;
  }
  if (i <= 20)
  {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("");
    Serial.println("WiFi not connected");
  }
}

void state0(){
  if(machine.executeOnce){
    if (alarm1 == true) {
      // disable gps
      Timer1.detach();

      u8x8.clearDisplay();
      u8x8.setFont(u8x8_font_chroma48medium8_r);
      u8x8.drawString(0,0,"State 0   ");
      u8x8.drawString(0,1,"Batt switch off");
      u8x8.drawString(0,2,"Lora mode");
      u8x8.refreshDisplay();    // Only required for SSD1606/7

      UBLOX_GPS_Shutdown();
      rtc_gpio_pullup_en(GPIO_NUM_39);
      esp_sleep_enable_ext0_wakeup(GPIO_NUM_39,0);
    }
  }

  static unsigned long lastPrintTime = 0;
  const bool timeCriticalJobs = os_queryTimeCriticalJobs(ms2osticksRound((TX_INTERVAL * 1000)));
  if (!timeCriticalJobs && GOTO_DEEPSLEEP == true && !(LMIC.opmode & OP_TXRXPEND)) {
    Serial.print(F("Can go sleep "));
    LoraWANPrintLMICOpmode();
    SaveLMICToRTC(TX_INTERVAL);
    GoDeepSleep();
  }
  else if (lastPrintTime + 2000 < millis())
  {
    Serial.print(F("Cannot sleep "));
    Serial.print(F("TimeCriticalJobs: "));
    Serial.print(timeCriticalJobs);
    Serial.print(" ");

    LoraWANPrintLMICOpmode();
    PrintRuntime();
    lastPrintTime = millis();
  }

  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,0,"State 0   ");
  u8x8.drawString(0,1,"in loop");
  u8x8.refreshDisplay();    // Only required for SSD1606/7
}

void state1(){
  //Serial.println("State 1");
  DebugPrint(3, "State 1");
  if(machine.executeOnce){
    enableWiFi();
    u8x8.setPowerSave(0);
    u8x8.clearDisplay();
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    u8x8.drawString(0,0,"State 1   ");
    u8x8.drawString(0,1,"Batt switch on");
    u8x8.drawString(0,2,"WiFI mode");
    u8x8.refreshDisplay();    // Only required for SSD1606/7

    UBLOX_GPS_Wakeup();                               //wakeup GPS 
    Timer1.attach_ms(5000, readGPSValues);     // Start timer 1 all 5s cyclic GPS data reading

    //*****************************************************************************************
      // Starting access point for update server
      DebugPrint(3, "Access point started with SSID: ");
      DebugPrintln(3, actconf.sssid);
      DebugPrint(3, "Access point channel: ");
      DebugPrintln(3, WiFi.channel());
    //  DebugPrintln(3, actconf.apchannel);
      DebugPrint(3, "Max AP connections: ");
      DebugPrintln(3, actconf.maxconnections);
      WiFi.mode(WIFI_AP_STA);
      WiFi.softAP(actconf.sssid, actconf.spassword, actconf.apchannel, false, actconf.maxconnections);
      hname = String(actconf.hostname) + "-" + String(actconf.deviceID);
      WiFi.hostname(hname);   // Provide the hostname
      DebugPrint(3, "Host name: ");
      DebugPrintln(3, hname);
      if(actconf.mDNS == 1){
        MDNS.begin(hname.c_str());                              // Start mDNS service
        MDNS.addService("http", "tcp", actconf.httpport);       // HTTP service
        MDNS.addService("nmea-0183", "tcp", actconf.dataport);  // NMEA0183 dada service for AVnav
      }  
      DebugPrintln(3, "mDNS service: activ");
      DebugPrint(3, "mDNS name: ");
      DebugPrint(3, hname);
      DebugPrintln(3, ".local");

      // Sart update server
      httpServer.begin();
      DebugPrint(3, "HTTP Update Server started at port: ");
      DebugPrintln(3, actconf.httpport);
      DebugPrint(3, "Use this URL: ");
      DebugPrint(3, "http://");
      DebugPrint(3, WiFi.softAPIP());
      DebugPrintln(3, "/update");
      DebugPrintln(3, "");

      #include "ServerPages.h"    // Webserver pages request functions
      
      // Connect to WiFi network
      DebugPrint(3, "Connecting WiFi client to ");
      DebugPrintln(3, actconf.cssid);

      // Load connection timeout from configuration (maxccount = (timeout[s] * 1000) / 500[ms])
      maxccounter = (actconf.timeout * 1000) / 500;

      // Wait until is connected otherwise abort connection after x connection trys
      WiFi.begin(actconf.cssid, actconf.cpassword);
      ccounter = 0;
      while ((WiFi.status() != WL_CONNECTED) && (ccounter <= maxccounter)) {
        delay(500);
        DebugPrint(3, ".");
        ccounter ++;
      }
      DebugPrintln(3, "");
      if (WiFi.status() == WL_CONNECTED){
        DebugPrint(3, "WiFi client connected with IP: ");
        DebugPrintln(3, WiFi.localIP());
        DebugPrintln(3, "");
        u8x8.drawString(0,4,"Connected IP:");
        u8x8.drawString(0,5, WiFi.localIP().toString().c_str());
        u8x8.refreshDisplay();    // Only required for SSD1606/7
        delay(100);
      }
      else{
        WiFi.disconnect(true);                // Abort connection
        DebugPrintln(3, "Connection aborted");
        DebugPrintln(3, "");
        u8x8.drawString(0,3,"Conection aborted");
        u8x8.refreshDisplay();    // Only required for SSD1606/7
      }
      
      // Start the NMEA TCP server
      server.begin();
      DebugPrint(3, "NMEA-Server started at port: ");
      DebugPrintln(3, actconf.dataport);
      // Print the IP address
      DebugPrint(3, "Use this URL : ");
      DebugPrint(3, "http://");
      if (WiFi.status() == WL_CONNECTED){
        DebugPrintln(3, WiFi.localIP());
      }
      else{
        DebugPrintln(3, WiFi.softAPIP());
      };
      DebugPrintln(3, "");
    //*****************************************************************************************

    //os_setTimedCallback(&sendjob, os_getTime()+sec2osticks(TX_INTERVAL), do_send);
    // stop Lora
    os_clearCallback(&sendjob);
  }
  loopcounter++;
}

bool transitionS0S1(){
  if (alarm1 == false) {
    return true;
  } else {
    return false;
  }
}

bool transitionS1S0(){
  //return true;
  if (alarm1 == true) {
    return true;
  } else {
    return false;
  }
}

bool transitionS1S2(){
  return true;
}

State* S0 = machine.addState(&state0); 
State* S1 = machine.addState(&state1);

/*
Method to print the reason by which ESP32
has been awaken from sleep
*/
void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}


void VEdirectSend()
{
// Send VE.direct data all 1s
  if(millis() > starttime0 + 1000){
    static int count;
    starttime0 = millis();          // Read actual time
    if (String(actconf.envSensor) == "VEdirect-Send") {
      DebugPrintln(3, "VE.direct Output");
      sendVEdirect();               // Send VE.direct text data
      // ":78DED000B05C4\n"
      int voltageOut = voltage * 100;
      sendBinaryValue(":78DED00", voltageOut); // Send binary data
      if(count == 0){
        sendVEdirectBinary();       // VEdirect binary data (setup and data) al 10 times
      }
    }
    count ++;
    count = count % 10;
  }

/*
  // Mirror all Ve.direct data to serial 0
  int data;
  while (Serial1.available()) {
    //Show VE.direct Daten on serial port 0
    data = Serial1.read();
    Serial.write(data);
  }
*/
}

void VEdirectRead()
{
// Read VE.direct values (BMV-712 tested)
  if (String(actconf.envSensor) == "VEdirect-Read") {
    int rawvoltage = 0;
    char rc;
    String receivedChars;

    if (Serial1.available()) {
      rc = Serial1.read();
      receivedChars += String(rc);
      // Read actual voltage
      if (receivedChars == "V"){
        rawvoltage = Serial1.parseInt();
        if(rawvoltage > 712){
          vedirectVoltage = rawvoltage / 1000.0;
//          Serial.print("VE.direct V: ");
//          Serial.println(vedirectVoltage, 3);
          receivedChars = "";
        }
      }
      // Read actual current
      if (receivedChars == "I"){
        vedirectCurrent = Serial1.parseInt() / 1000.0;
//        Serial.print("VE.direct I: ");
//        Serial.println(vedirectCurrent);
        receivedChars = "";
      }
      // Read actual power
      if (receivedChars == "P"){
        vedirectPower = Serial1.parseInt();
//        Serial.print("VE.direct P: ");
//        Serial.println(vedirectPower);
        receivedChars = "";
      }
      // Read actual SOC
      if (receivedChars == "S"){
        vedirectSOC = Serial1.parseInt();
//        Serial.print("VE.direct SOC: ");
//        Serial.println(vedirectSOC);
        receivedChars = "";
      }
      // Read actual temperature
      if (receivedChars == "T"){
        vedirectTemp = Serial1.parseInt() / 10.0;
//        Serial.print("VE.direct T: ");
//        Serial.println(vedirectTemp);
        receivedChars = "";
      }
      // If line end then clear lina data
      if (rc == '\n'){
        receivedChars = "";
      }
    }
  }
}


void setup() {
  //##### Start OLED #####
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFlipMode(1);    // ToDo: config via webinterface.

  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,0,"Booting...");
  u8x8.refreshDisplay();    // Only required for SSD1606/7  

  // Create task for LoRa code
  xTaskCreatePinnedToCore(
                    Task1code,  /* Task function */
                    "Task1",    /* Name of task */
                    10000,      /* Stack size of task */
                    NULL,       /* Parameter of the task */
                    1,          /* Priority of the task */
                    &Task1,     /* Task handle to keep track of created task */
                    0);         /* Pin task to core 0 */
  delay(500);

  vTaskDelete(Task1);

  // Read the first byte from the EEPROM
  EEPROM.begin(sizeEEPROM);
  value = EEPROM.read(cfgStart);
  EEPROM.end();
  // If the fist Byte not identical to the first value in the default configuration then saving a default configuration in EEPROM.
  // Means if the EEPROM empty then saving a default configuration.
  if(value == defconf.valid){
    empty = 0;                  // Marker for configuration is present
  }
  else{
    saveEEPROMConfig(defconf);
    empty = 1;                  // Marker for configuration is missing
  }

  // Loading EEPROM configuration
  actconf = loadEEPROMConfig(); // Overload with old EEPROM configuration by start. It is necessarry for serspeed

  // If the firmware version in EEPROM different to defconf then save the new version in EEPROM
  if(String(actconf.fversion) != String(defconf.fversion)){
    String fver = defconf.fversion;
    fver.toCharArray(actconf.fversion, 6);
    saveEEPROMConfig(actconf);
  }

  //##### Start serial 0 and serial 2 connections #####
  Serial.begin(actconf.serspeed);               // NMEA0183 an debug messages
  delay(200);
  if(String(actconf.envSensor) == "VEdirect-Read" || String(actconf.envSensor) == "VEdirect-Send"){
    Serial1.begin(19200, SERIAL_8N1, RXD1, TXD1); // VE.direct Victron interface (read and write)
  }
  delay(200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);  // GPS (NMEA0183)
  delay(200);

  macAddress = ESP.getEfuseMac();
  macAddressTrunc = macAddress << 40;
  chipId = macAddressTrunc >> 40;

  //##### Start OLED #####
  //u8x8.begin();
  //u8x8.setPowerSave(0);

  /*u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.clearDisplay();
  u8x8.drawString(0,0,"NoWa(C)OBP");
  u8x8.drawString(11,0,actconf.fversion);
  u8x8.drawString(0,2,"Connection to:");
  u8x8.drawString(0,3,actconf.cssid);
  u8x8.refreshDisplay();*/    // Only required for SSD1606/7

  // ESP8266 Information Data
  DebugPrintln(3, "Booting Sketch...");
  DebugPrintln(3, "");
  DebugPrint(3, actconf.devname);
  DebugPrint(3, " ");
  DebugPrint(3, actconf.fversion);
  DebugPrintln(3, " (C) Norbert Walter and modified by Guntmar Hoeche");
  DebugPrintln(3, "******************************************");
  DebugPrintln(3, "");
  DebugPrintln(3, "Modul Type: Heltec LoRa-32");
  DebugPrint(3, "SDK-Version: ");
  DebugPrintln(3, ESP.getSdkVersion());
  DebugPrint(3, "ESP32 Chip-ID: ");
  DebugPrintln(3, chipId);
  DebugPrint(3, "ESP32 Speed [MHz]: ");
  DebugPrintln(3, ESP.getCpuFreqMHz());
  DebugPrint(3, "Free Heap Size [Bytes]: ");
  DebugPrintln(3, ESP.getFreeHeap());
  DebugPrintln(3, "");

  // Debug info for initialize the EEPROM
  if(empty == 1){
    DebugPrintln(3, "EEPROM config missing, initialization done");
  }
  else{
    DebugPrintln(3, "EEPROM config present");
  }

  // Loading EEPROM config
  DebugPrintln(3, "Loading actual EEPROM config");
  actconf = loadEEPROMConfig();
  DebugPrintln(3, "");

  DebugPrint(3, "Sensor ID: ");
  DebugPrintln(3, actconf.deviceID);
  DebugPrintln(3, "Sensor Type: LoRa1000");
  DebugPrintln(3, "Info: LoRa Boat Monitor");
  DebugPrintln(3, "Voltage Input [V]: 0...12 ");
  DebugPrint(3, "Input Pin: GPIO ");
  DebugPrintln(3, ANALOG_IN);
  DebugPrintln(3, "Tank1 [%]: 0...100");
  DebugPrint(3, "Input Pin: GPIO ");
  DebugPrintln(3, TANK1_IN);
  DebugPrintln(3, "Tank2 [%]: 0...100");
  DebugPrint(3, "Input Pin: GPIO ");
  DebugPrintln(3, TANK2_IN);
  DebugPrintln(3, "Temp Sensor: SD18B20 1Wire");
  DebugPrintln(3, "Value Range [°C]: -55...125");
  DebugPrint(3, "Input Pin: GPIO ");
  DebugPrintln(3, OneWIRE_PIN);
  DebugPrint(3, "Temp Unit: ");
  DebugPrintln(3, actconf.tempUnit);
  DebugPrintln(3, "");
  if (String(actconf.envSensor) == "Off") {
    DebugPrintln(3, "Env Sensor: Off");
  }
  if (String(actconf.envSensor) == "BME280") {
    DebugPrintln(3, "Env Sensor: BME280");
  }
  if (String(actconf.envSensor) == "VEdirect-Read") {
    DebugPrintln(3, "Env Sensor: VEdirect reading");
  }
  if (String(actconf.envSensor) == "VEdirect-Send") {
    DebugPrintln(3, "Env Sensor: VE.direct sending");
  }
  DebugPrintln(3,"Serial0 Txd is on pin: "+String(TX));
  DebugPrintln(3,"Serial0 Rxd is on pin: "+String(RX));
  DebugPrintln(3,"Serial1 Txd is on pin: "+String(TXD1));
  DebugPrintln(3,"Serial1 Rxd is on pin: "+String(RXD1));
  DebugPrintln(3,"Serial2 Txd is on pin: "+String(TXD2));
  DebugPrintln(3,"Serial2 Rxd is on pin: "+String(RXD2));
  DebugPrintln(3, "");

  DebugPrint(3, "LoRa Frequency: ");
  DebugPrintln(3, actconf.lorafrequency);
  DebugPrint(3, "LoRa Channel: ");
  DebugPrintln(3, actconf.lchannel);
  DebugPrint(3, "Send Period [x30s]: ");
  DebugPrintln(3, actconf.tinterval);
  DebugPrint(3, "Spreading Factor: ");
  DebugPrintln(3, actconf.spreadf);
  DebugPrint(3, "Dynamic SF: ");
  DebugPrintln(3, actconf.dynsf);
  DebugPrintln(3, "");


  //##### Pin Settings #####
  pinMode(ledPin, OUTPUT);          // LED Pin output
  pinMode(relayPin, OUTPUT);        // Relay Pin output
  pinMode(alarmPin, INPUT_PULLUP);  // Alarm Pin input

  //##### Start 1Wire sensors #####
  if (String(actconf.tempSensorType) == "DS18B20") {
    sensors.begin();
  }  

  //##### Cyclic timer #####
  Timer1.attach_ms(5000, readGPSValues);     // Start timer 1 all 5s cyclic GPS data reading
  Timer2.attach_ms(300000, relayTimer);      // Start timer 2 all 5min cyclic counter increment
  Timer3.attach_ms(SendPeriod, sendNMEA);    // Data transmission timer for NMEA

  //####### Starting BME280 ######
  if (String(actconf.envSensor) == "BME280") {
    DebugPrint(3, "BME280 test at address: ");
    DebugPrintln(3, "0x"+String(address, HEX));
    I2CBME.begin(I2C_SDA, I2C_SCL, I2C_SPEED); // Redefinition of I2C pins see Definition.h

    //  if (! bme.begin(address, &Wire)) { // Standard using I2C
    if (! bme.begin(address, &I2CBME)) {
      DebugPrintln(3,"Could not find a valid BME280 sensor, check wiring!");
      //actconf.envSensor = "BME280";

      u8x8.drawString(0,6,"Could not find a");
      u8x8.drawString(0,7,"valid BME280!");
      u8x8.refreshDisplay();    // Only required for SSD1606/7
      delay(10000);

      /*u8x8.setFont(u8x8_font_chroma48medium8_r);
      u8x8.drawString(0,0,"NoWa(C)OBP");
      u8x8.drawString(11,0,actconf.fversion);
      u8x8.drawString(0,1,"Could not find a");
      u8x8.drawString(0,2,"valid BME280!");
      u8x8.drawString(0,4,"System stop");
      u8x8.refreshDisplay();    // Only required for SSD1606/7  
    } else {
      DebugPrint(3, "BME280 found at address: ");
      DebugPrintln(3, "0x"+String(address, HEX));
      DebugPrintln(3, "");
      
      // For more details on the following scenarious, see chapter
      // 3.5 "Recommended modes of operation" in the datasheet
      bme.setSampling(Adafruit_BME280::MODE_FORCED,   // Mode [NORMAL|FORCED|SLEEP]
                      Adafruit_BME280::SAMPLING_X2,   // Temperature [NONE|X2|X4|X8|X16]
                      Adafruit_BME280::SAMPLING_X16,  // Pressure [NONE|X2|X4|X8|X16]
                      Adafruit_BME280::SAMPLING_X1,   // Humidity [NONE|X2|X4|X8|X16]
                      Adafruit_BME280::FILTER_OFF     // Filter [OFF|X1...X16]
    //                  Adafruit_BME280::STANDBY_MS_0_5 ) //Only used in Normal Mode 0,5ms stand by time
                      );*/
    }
  }
  //delay(3000);
  u8x8.clearDisplay();

  //####### Starting LoRaWAN ######
  DebugPrintln(3,"Starting LoRaWAN");
  DebugPrint(3, "LoRa Frequency: ");
  DebugPrintln(3, actconf.lorafrequency);
  DebugPrint(3, "LoRa Channel: ");
  DebugPrintln(3, actconf.lchannel);
  DebugPrint(3, "Send Period [x30s]: ");
  DebugPrintln(3, actconf.tinterval);
  DebugPrint(3, "Spreading Factor: ");
  DebugPrintln(3, actconf.spreadf);
  DebugPrint(3, "Dynamic SF: ");
  DebugPrintln(3, actconf.dynsf);
  /*DebugPrint(3, "Device Adr: ");
  DebugPrintln(3, actconf.devaddr);
  DebugPrint(3, "nwkskey: ");
  DebugPrintln(3, actconf.nskey);
  DebugPrint(3, "appskey: ");
  DebugPrintln(3, actconf.appkey);*/
  DebugPrintln(3, "");

  #ifdef VCC_ENABLE
  // For Pinoccio Scout boards
  pinMode(VCC_ENABLE, OUTPUT);
  digitalWrite(VCC_ENABLE, HIGH);
  delay(1000);
  #endif

  // Set send interval
  TX_INTERVAL = actconf.tinterval * 30;

  // LMIC init
  os_init();
  // Reset the MAC state. Session and pending data transfers will be discarded.
  LMIC_reset();
//  LMIC_setClockError(MAX_CLOCK_ERROR * 1 / 100);
  LMIC_setClockError(MAX_CLOCK_ERROR * 10 / 100);  // For better receiving results

  // Set static session parameters. Instead of dynamically establishing a session
  // by joining the network, precomputed session parameters are be provided.
  #ifdef PROGMEM
  // On AVR, these values are stored in flash and only copied to RAM
  // once. Copy them to a temporary buffer here, LMIC_setSession will
  // copy them into a buffer of its own again.
  uint8_t appskey[sizeof(actconf.appkey)];
  uint8_t nwkskey[sizeof(actconf.nskey)];
  memcpy_P(appskey, actconf.appkey, sizeof(actconf.appkey));
  memcpy_P(nwkskey, actconf.nskey, sizeof(actconf.nskey));
  LMIC_setSession (0x1, actconf.devaddr, nwkskey, appskey);
  #else
  // If not running an AVR with PROGMEM, just use the arrays directly
  LMIC_setSession (0x1, actconf.devaddr, actconf.nskey, actconf.appkey);
  #endif

  #if defined(CFG_eu868)
  // Set up the channels used by the Things Network, which corresponds
  // to the defaults of most gateways. Without this, only three base
  // channels from the LoRaWAN specification are used, which certainly
  // works, so it is good for debugging, but can overload those
  // frequencies, so be sure to configure the full frequency range of
  // your network here (unless your network autoconfigures them).
  // Setting up channels should happen after LMIC_setSession, as that
  // configures the minimal channel set.
  // NA-US channels 0-71 are configured automatically
  LMIC_setupChannel(0, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(1, 868300000, DR_RANGE_MAP(DR_SF12, DR_SF7B), BAND_CENTI);      // g-band
  LMIC_setupChannel(2, 868500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(3, 867100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(4, 867300000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(5, 867500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(6, 867700000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(7, 867900000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(8, 868800000, DR_RANGE_MAP(DR_FSK,  DR_FSK),  BAND_MILLI);      // g2-band
  // TTN defines an additional channel at 869.525Mhz using SF9 for class B
  // devices' ping slots. LMIC does not have an easy way to define set this
  // frequency and support for class B is spotty and untested, so this
  // frequency is not configured here.
  #elif defined(CFG_us915)
  // NA-US channels 0-71 are configured automatically
  // but only one group of 8 should (a subband) should be active
  // TTN recommends the second sub band, 1 in a zero based count.
  // https://github.com/TheThingsNetwork/gateway-conf/blob/master/US-global_conf.json
  LMIC_selectSubBand(1);
  #endif

  // Enable the used channels
  setChannel(actconf.lchannel);

  // Disable link check validation
  LMIC_setLinkCheckMode(0);

  // TTN uses SF9 for its RX2 window.
  LMIC.dn2Dr = DR_SF9;

  // Set spreading factor depends on transmit slot and transmit power for uplink
  // (note: txpow seems to be ignored by the library)
  setSF(slot, actconf.spreadf, actconf.dynsf);

  if (RTC_LMIC.seqnoUp != 0)
  {
    LoadLMICFromRTC();
  }

  LoraWANDebug(LMIC);

  // Start job
  do_send(&sendjob);

  // sleep config...
  //Increment boot number and print it every reboot
  ++bootCount;
  //Print the wakeup reason for ESP32
  print_wakeup_reason();
  /*
  First we configure the wake up source
  We set our ESP32 to wake up every 5 seconds
  */
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  //Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");

  S0->addTransition(&transitionS0S1,S1);    // Transition to itself (see transition logic for details)
  S1->addTransition(&transitionS1S0,S0);  // S1 transition to S0
}

void loop() {
  // LoRa activities
  os_runloop_once();

	httpServer.handleClient();   // HTTP Server-handler for HTTP update server
  readValues();
  machine.run();
  
  //VEdirectSend();

  // Read measuring data and display on OLED all 1s
  /*if(millis() > starttime1 + 1000){
    starttime1 = millis();        // Read actual time

    // BME280 measuerement
    if (String(actconf.envSensor) == "BME280") {
      bme.takeForcedMeasurement(); // has no effect in normal mode
    }
    readValues();
    writeDisplay();
  }*/

  //VEdirectRead();

  // HTTP Server-handler for HTTP update server
  //httpServer.handleClient();

  // TCP-Server for NMEA0183
  /*WiFiClient client = server.available();// Check if a client is connected
  int i = 0;

  // While TCP client is connected or Serial Mode is active
  while ((client.connected() && !client.available()) || (int(actconf.serverMode) == 1)) {

    httpServer.handleClient();      // HTTP Server-handler for HTTP update server

    if ((i == 0) && ((int(actconf.serverMode) == 0) || (int(actconf.serverMode) == 4))) {
      DebugPrintln(3, "TCP client connected");
      DebugPrintln(3, "");
    }*/

    // Read measuring data and display on OLED all 1s
    /*if(millis() > starttime2 + 1000){
      starttime2 = millis();        // Read actual time

      // BME280 measuerement
      if (String(actconf.envSensor) == "BME280") {
        bme.takeForcedMeasurement();  // has no effect in normal mode
      }  
      readValues();
      writeDisplay();
    }*/

    // Sending XDR data
    /*if (flag1 == true){
      i++;
      DebugPrintln(3, "");
      DebugPrint(3, "Send package:");
      DebugPrintln(3, i);

      if((int(actconf.serverMode) == 0) || (int(actconf.serverMode) == 1) || (int(actconf.serverMode) == 4)){
         if(int(actconf.senddata) == 1){
            if (String(actconf.envSensor) == "BME280") {
              client.println(sendXDR1(1));  // Send XDR1 telegram environment sensors
            }
            client.println(sendXDR2(1));    // Send XDR2 telegram battery sensors
            client.println(sendXDR3(1));    // Send XDR3 telegram level and control
            if(nmea != ""){
              client.println(sendRMC(1));   // Send GPS RMC telegram
            }
         }
      }
      flag1 = false;                        // Reset the send flag
    }
  }*/

}

void disableWiFi(){
    adc_power_off();
    WiFi.disconnect(true);  // Disconnect from the network
    WiFi.mode(WIFI_OFF);    // Switch WiFi off
    Serial.println("STOP WIFI");
}
