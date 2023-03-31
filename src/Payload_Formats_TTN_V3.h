// This component is not for the Arduino code. The component is neccessary for implementation in the TTN network.
// The function Decoder() decode the received payload in the TTN network. Please copy the function in the TTN console
// under PAYLOAD FORMATS and save it.
// https://console.thethingsnetwork.org/applications/lora-testsensor/payload-formats

// The paylod has 21 bytes
// Test payload: 

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


// Payload smaple: 0A00541FE027770B9517D6043F1AA702751AFF133D0F0000000001

/*
Decode result JSON:

{
  "alarm1": 1,
  "dewpoint": 10.4,
  "humidity": 29.35,
  "latitude": 51.193901,
  "longitude": 6.796773,
  "position": {
    "context": {
      "lat": 51.193901,
      "lng": 6.796773
    },
    "value": 0
  },
  "pressure": 1020.8,
  "tempbattery": 17.2,
  "voltage": 11.28
}

*/

// Copy the following code under PAYLOAD FORMATS in the TTN console

// Attention!! Ubidots accept only 10 values. In this case we reduce the number of values.
// If you using more values the stopps the datatransmission to Ubidots. Ubidots accept in the
// free version only 10 devices and transmis for 5000 datapoints per day. Send not more as
// 10 values all 5 minutes.

function decodeUplink(input) {
  var data = {};
  var events = {
    1: "setup",
    2: "interval",
    3: "motion",
    4: "button"
  };
//  data.event = events[input.fPort];

  var voffset = 0;      // Voltage offset
  var toffset = 0;      // Temperature offset for BME280
  var poffset = 0;      // Pressure offset for altitude

//  data.counter = ((input.bytes[1] << 8) | input.bytes[0]);
  var temperature = (((input.bytes[3] << 8) | input.bytes[2]) / 100) - 50 + toffset;
//  data.temperature = Math.round(temperature * 10) / 10;
  data.pressure = ((input.bytes[5] << 8) | input.bytes[4]) / 10 + poffset;
  data.humidity = ((input.bytes[7] << 8) | input.bytes[6]) / 100;
  var dewpoint = (((input.bytes[9] << 8) | input.bytes[8]) / 100) - 50;
  data.dewpoint = Math.round(dewpoint * 10) / 10;
  var voltage = ((input.bytes[11] << 8) | input.bytes[10]) / 1000 + voffset;
  data.voltage = Math.round(voltage * 1000) / 1000;
  var tempbattery = (((input.bytes[13] << 8) | input.bytes[12]) / 100) - 50;
  data.tempbattery = Math.round(tempbattery * 10) / 10;
  var longitude = ((input.bytes[15] << 8) | input.bytes[14]) / 100 + ((input.bytes[17] << 8) | input.bytes[16]) / 1000000;
  data.longitude = longitude;
  var latitude = ((input.bytes[19] << 8) | input.bytes[18]) / 100 + ((input.bytes[21] << 8) | input.bytes[20]) / 1000000;
  data.latitude = latitude;
  data.altitude = 1;
  data.hdop = 1.1;
  data.position = {"value": 0, context:{"lat": latitude, "lng": longitude}};
//  data.level1 = ((input.bytes[23] << 8) | input.bytes[22]) / 100;
//  data.level2 = ((input.bytes[25] << 8) | input.bytes[24]) / 100;
  data.alarm1 = input.bytes[26] & 0x01;
//  data.relay = (input.bytes[26] & 0x10) / 0x10;

  var warnings = [];
  if (data.voltage < 10) {
    warnings.push("Battery undervolteage");
  }
  if (data.voltage > 14.7) {
    warnings.push("Battery overload");
  }
  return {
    data: data,
    warnings: warnings
  };
}
