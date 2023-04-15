String JS()
{
 // Debug info 
 DebugPrintln(3, "Send js.html");

 String content;

 content +=F( "var xmlhttp = new XMLHttpRequest();");
 content +=F( "xmlhttp.onreadystatechange = function() {");
 content +=F( "if (this.readyState == 4 && this.status == 200) {");
 content +=F( "var myObj = JSON.parse(this.responseText);");
 
 content +=F( "cssid = document.getElementById('cssid');");
 content +=F( "cssid.value = myObj.Device.NetworkParameter.WLANClientSSID;");
 content +=F( "sssid = document.getElementById('sssid');");
 content +=F( "sssid.value = myObj.Device.NetworkParameter.WLANServerSSID;");
 
 content +=F( "heapsize = document.getElementById('heapsize');");
 content +=F( "heapsize.value = myObj.Device.ESP32.FreeHeapSize.Value;");
 content +=F( "document.getElementById('hunit').innerHTML = myObj.Device.ESP32.FreeHeapSize.Unit;");

 content +=F( "strength = document.getElementById('strength');");
 content +=F( "strength.value = myObj.Device.NetworkParameter.FieldStrength.Value;");
 content +=F( "document.getElementById('sunit').innerHTML = myObj.Device.NetworkParameter.FieldStrength.Unit;");
 
 content +=F( "quality = document.getElementById('quality');");
 content +=F( "quality.value = myObj.Device.NetworkParameter.ConnectionQuality.Value;");
 content +=F( "document.getElementById('qunit').innerHTML = myObj.Device.NetworkParameter.ConnectionQuality.Unit;");
 content +=F( "document.getElementById('quality2').innerHTML = myObj.Device.NetworkParameter.ConnectionQuality.Value;");
 
 content +=F( "actualch = document.getElementById('actualch');");
 content +=F( "actualch.value = myObj.Device.LoRaSettings.ActualChannel;");
 content +=F( "actualsf = document.getElementById('actualsf');");
 content +=F( "actualsf.value = myObj.Device.LoRaSettings.ActualSF;");
 content +=F( "tinterval = document.getElementById('tinterval');");
 content +=F( "tinterval.value = myObj.Device.LoRaSettings.TXInterval * 30;");
 content +=F( "slot = document.getElementById('slot');");
 content +=F( "slot.value = myObj.Device.LoRaSettings.TimeSlot;");
 content +=F( "counter = document.getElementById('counter');");
 content +=F( "counter.value = myObj.Device.LoRaSettings.TXCounter;");

 content +=F( "lat = document.getElementById('lat');");
 content +=F( "lat.value = myObj.Device.MeasuringValues.Latitude.Value;");

 content +=F( "lon = document.getElementById('lon');");
 content +=F( "lon.value = myObj.Device.MeasuringValues.Longitude.Value;");

 content +=F( "alt = document.getElementById('alt');");
 content +=F( "alt.value = myObj.Device.MeasuringValues.Altitude.Value;");

 if (String(actconf.envSensor) == "BME280") {
   content +=F( "airtemp = document.getElementById('airtemp');");
   content +=F( "airtemp.value = myObj.Device.MeasuringValues.AirTemperature.Value;");
   content +=F( "document.getElementById('atunit').innerHTML = myObj.Device.MeasuringValues.AirTemperature.Unit;");
  
   content +=F( "pressure = document.getElementById('pressure');");
   content +=F( "pressure.value = myObj.Device.MeasuringValues.AirPressure.Value;");
  
   content +=F( "humidity = document.getElementById('humidity');");
   content +=F( "humidity.value = myObj.Device.MeasuringValues.AirHumidity.Value;");
  
   content +=F( "dewpoint = document.getElementById('dewpoint');");
   content +=F( "dewpoint.value = myObj.Device.MeasuringValues.Dewpoint.Value;");
   content +=F( "document.getElementById('dpunit').innerHTML = myObj.Device.MeasuringValues.Dewpoint.Unit;");
 }

 content +=F( "voltage = document.getElementById('voltage');");
 content +=F( "voltage.value = myObj.Device.MeasuringValues.BatteryVoltage.Value;");

 content +=F( "temp1w = document.getElementById('1wtemp');");
 content +=F( "temp1w.value = myObj.Device.MeasuringValues.Temp1Wire.Value;");
 content +=F( "document.getElementById('1wunit').innerHTML = myObj.Device.MeasuringValues.Temp1Wire.Unit;");

 content +=F( "tank1 = document.getElementById('tank1');");
 content +=F( "tank1.value = myObj.Device.MeasuringValues.Tank1Voltage.Value;");

 content +=F( "tank2 = document.getElementById('tank2');");
 content +=F( "tank2.value = myObj.Device.MeasuringValues.Tank2Voltage.Value;");

 content +=F( "alarm = document.getElementById('alarm');");
 content +=F( "alarm.value = myObj.Device.MeasuringValues.Alarm.Value;");

 content +=F( "relay = document.getElementById('relay');");
 content +=F( "relay.value = myObj.Device.MeasuringValues.Relay.Value;");
 
 content +=F( "rtimer = document.getElementById('rtimer');");
 content +=F( "rtimer.value = myObj.Device.MeasuringValues.RelayTimer.Value;");

 content +=F( "envSensor = document.getElementById('envSensor');");
 content +=F( "envSensor.value = myObj.Device.MeasuringValues.EnvSensor.Value;");

 content +=F( "standbyMode = document.getElementById('standbyMode');");
 content +=F( "standbyMode.value = myObj.Device.MeasuringValues.standbyMode.Value;");

 content +=F( "loraStandbyMode = document.getElementById('loraStandbyMode');");
 content +=F( "loraStandbyMode.value = myObj.Device.MeasuringValues.loraStandbyMode.Value;");

 // If Demo Mode active the give out a message
 content += F("servermode = myObj.Device.NetworkParameter.ServerMode;");
 content += F("if (servermode == 4) {");
 content += F("document.getElementById('info').innerHTML = '(Demo Mode)';");
 content += F("}");
 content += F("else {");
 content += F("document.getElementById('info').innerHTML = '';");
 content += F("}");
 
 content +=F( "}");
 content +=F( "};");

 content +=F( "function read_json() {");
//content +=F( "xmlhttp.open('GET', 'http://192.168.4.1/json', true);");
 content +=F( "xmlhttp.open('GET', '/json', true);");
 content +=F( "xmlhttp.send();");
 content +=F( "}");

 content +=F( "setInterval(function(){read_json(); }, 2000);");

 return content;
}
