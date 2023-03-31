// This component is not for the Arduino code. The component is neccessary for implementation in the TTN network.
// The function Decoder() decode the received payload in the TTN network. Please copy the function in the TTN console
// under PAYLOAD FORMATS and save it.
// https://console.thethingsnetwork.org/applications/lora-testsensor/payload-formats

// For a data transmission from TTN V3 to Ubidots you need an Webhook in TTN.
// At fist create a The Things Stack Plugin in Ubitots.
// Then copy the following code under Decoding Function in Ubidots Decoder Settings

function format_payload(args){
  var ubidots_payload = {};
  // Log received data for debugging purposes:
  // console.log(JSON.stringify(args));
  // Get RSSI and SNR variables using gateways data:
  var gateways = args['uplink_message']['rx_metadata'];
  for (const i in gateways) {  
    // Get gateway EUI and name
    var gw = gateways[i];
    var gw_eui = gw['gateway_ids']['eui'];
    var gw_id = gw['gateway_ids']['gateway_id'];
    // Build RSSI and SNR variables
    ubidots_payload['rssi-' + gw_id] = {
      "value": gw['rssi'],
      "context": {
        "channel_index": gw['channel_index'],
        "channel_rssi": gw['channel_rssi'],
        "gw_eui": gw_eui,
        "gw_id": gw_id,
        "uplink_token": gw['uplink_token']
      }
    }
    ubidots_payload['snr-' + gw_id] = gw['snr'];
  }

  // Get Fcnt and Port variables:
  ubidots_payload['f_cnt'] = args['uplink_message']['f_cnt'];
  ubidots_payload['f_port'] = args['uplink_message']['f_port'];

  // Get uplink's timestamp
  ubidots_payload['timestamp'] = new Date(args['uplink_message']['received_at']).getTime(); 

  // If you're already decoding in TTS using payload formatters, 
  // then uncomment the following line to use "uplink_message.decoded_payload".
  // PROTIP: Make sure the incoming decoded payload is an Ubidots-compatible JSON (See https://ubidots.com/docs/hw/#sending-data)
  // var decoded_payload = args['uplink_message']['decoded_payload'];
 
  // By default, this plugin uses "uplink_message.frm_payload" and sends it to the decoding function "decodeUplink".
  // For more vendor-specific decoders, check out https://github.com/TheThingsNetwork/lorawan-devices/tree/master/vendor
  let bytes =  Buffer.from(args['uplink_message']['frm_payload'], 'base64');
  var decoded_payload = decodeUplink(bytes)['data'];
  // Merge decoded payload into Ubidots payload
  Object.assign(ubidots_payload, decoded_payload);
  // return ubidots_payload
  return decoded_payload
}

function decodeUplink(bytes) {
  // Decoder for the LoRa Boat Monitor
  var decoded = {};
  
  // If received data is of Environment Monitoring type
  var voffset = 0;      // Voltage offset
  var toffset = 0;      // Temperature offset for BME280
  var poffset = 0;      // pressure offset for altitude
//  decoded.counter = ((bytes[1] << 8) | bytes[0]);
  var temperature = (((bytes[3] << 8) | bytes[2]) / 100) - 50 + toffset;
//  decoded.temperature = Math.round(temperature * 10) / 10;
  decoded.pressure = ((bytes[5] << 8) | bytes[4]) / 10 + poffset;
  decoded.humidity = ((bytes[7] << 8) | bytes[6]) / 100;
  var dewpoint = (((bytes[9] << 8) | bytes[8]) / 100) - 50;
  decoded.dewpoint = Math.round(dewpoint * 10) / 10;
  var voltage = ((bytes[11] << 8) | bytes[10]) / 1000 + voffset;
  decoded.voltage = Math.round(voltage * 1000) / 1000;
  var tempbattery = (((bytes[13] << 8) | bytes[12]) / 100) - 50;
  decoded.tempbattery = Math.round(tempbattery * 10) / 10;
  decoded.longitude = ((bytes[15] << 8) | bytes[14]) / 100 + ((bytes[17] << 8) | bytes[16]) / 1000000;
  decoded.latitude = ((bytes[19] << 8) | bytes[18]) / 100 + ((bytes[21] << 8) | bytes[20]) / 1000000;
//  decoded.level1 = ((bytes[23] << 8) | bytes[22]) / 100;
//  decoded.level2 = ((bytes[25] << 8) | bytes[24]) / 100;
  decoded.alarm1 = bytes[26] & 0x01;
  decoded.relay = (bytes[26] & 0x10) / 0x10;
  return {"data": decoded};
}

module.exports = { format_payload };
