// Device information webpage
String Devinfo()
{
 // Debug info
 DebugPrintln(3, "Send info.html");

 // Page content with auto reload
 String content;
 content +=F( "<!DOCTYPE html>");
 content +=F( "<html>");
 content +=F( "<head>");
 content +=F( "<title>Info ");
 content += String(actconf.devname);
 content +=F( "</title>");
 content +=F( "<link rel='stylesheet' type='text/css' href='/css'>");
 content +=F( "<meta http-equiv='content-type' content='text/html; charset=UTF-8'>");
 content +=F( "<meta name=viewport content='width=device-width, initial-scale=1'>");
 content +=F( "<style>");
// content += CSS();
 content +=F( "</style>");
 content +=F( "</head>");
 content +=F( "<body>");
 content +=F( "<script src='/js' type='text/javascript'></script>");
 
 // Web page title
 content +=F( "<h2>");
 content += String(actconf.devname);
 content +=F( "</h2>");
 content += String(actconf.crights);
 content +=F( ", "); 
 content += String(actconf.fversion);
 content +=F( ", CQ: <data id='quality2'></data>%");
 content +=F( "<hr align='left'>");
 
 content +=F( "<table>");

 content +=F( "<tr>");
 content +=F( "<td><h3>Firmware Information</h3></td>");
 content +=F( "<td></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 
 content +=F( "<tr>");
 content +=F( "<td>Firmware Version</td>");
 content +=F( "<td><input type='text' name='fwv' size='15' value='");
 content += String(actconf.fversion);
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>License Type</td>");
 content +=F( "<td><input type='text' name='lic' size='15' value='");
 content += String(actconf.license);
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 
 content +=F( "<tr>");
 content +=F( "<td><h3>ESP32 Informations</h3></td>");
 content +=F( "<td></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 
 content +=F( "<tr>");
 content +=F( "<td>SDK Version</td>");
 content +=F( "<td><input type='text' name='sdk' size='15' value='");
 content += String(ESP.getSdkVersion());
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>ESP32 Chip ID</td>");
 content +=F( "<td><input type='text' name='cid' size='15' value='");
 content += String(chipId);
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>ESP32 Speed</td>");
 content +=F( "<td><input type='text' name='spd' size='15' value='");
 content += String(ESP.getCpuFreqMHz());
 content +=F( "'></td>");
 content +=F( "<td>[MHz]</td>");
 content +=F( "</tr>");

 // String(ESP.getFreeHeap());
 content +=F( "<tr>");
 content +=F( "<td>Free Heap Size</td>");
 content +=F( "<td><input id='heapsize' type='text' name='heapsize' size='15' value='0'></td>");
 content +=F( "<td>[<data id='hunit'></data>]</td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td><h3>Network Parameter</h3></td>");
 content +=F( "<td></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Hostname</td>");
 content +=F( "<td><input id='hostname' type='text' name='hostname' size='15' value='");
 content += String(hname);
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>mDNS Name</td>");
 content +=F( "<td><input id='mdnsname' type='text' name='mdnsname' size='15' value='");
 if(actconf.mDNS == 1){
  content += String(hname) + ".local";
 }
 else{
  content +=F( "not activ");
 }
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 
 content +=F( "<tr>");
 content +=F( "<td>WLAN Server SSID</td>");
 content +=F( "<td><input id='sssid' type='text' name='sssid' size='15' value=' '></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>WLAN Server IP</td>");
 content +=F( "<td><input type='text' name='serverip' size='15' value='");
 content += WiFi.softAPIP().toString();
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Activ AP Channel</td>");
 content +=F( "<td><input type='text' name='apchannel' size='15' value='");
 content += String(WiFi.channel());
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>WLAN Client SSID</td>");
 content +=F( "<td><input id='cssid' type='text' name='cssid' size='15' value=' '></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>WLAN Client IP</td>");
 content +=F( "<td><input type='text' name='clientip' size='15' value='");
 content += WiFi.localIP().toString();
 content +=F( "'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Client Field Strength</td>");
 content +=F( "<td><input id='strength' type='text' name='strength' size='15' value='0'></td>");
 content +=F( "<td>[<data id='sunit'></data>]</td>");
 content +=F( "</tr>");
 
 content +=F( "<tr>");
 content +=F( "<td>Connection Quality</td>");
 content +=F( "<td><input id='quality' type='text' name='quality' size='15' value='0'></td>");
 content +=F( "<td>[<data id='qunit'></data>]</td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td><h3>LoRa Parameter</h3></td>");
 content +=F( "<td></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content += F("<tr>");
 content += F("<td>Device Address</td>");
 content += F("<td><input type='text' required name='devaddr' size='15' value='");
 String mystring = String(actconf.devaddr, HEX);
 mystring.toUpperCase();
 content += mystring;
 content += F("' maxlength='20'></td>");
 content += F("<td></td>");
 content += F("</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Actual Channel</td>");
 content +=F( "<td><input id='actualch' type='text' name='actualch' size='15' value='0'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Actual SF</td>");
 content +=F( "<td><input id='actualsf' type='text' name='actualsf' size='15' value='0'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>TX Interval</td>");
 content +=F( "<td><input id='tinterval' type='text' name='tinterval' size='15' value='0'></td>");
 content +=F( "<td>[s]</td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Time Slot</td>");
 content +=F( "<td><input id='slot' type='text' name='slot' size='15' value='0'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>TX Counter</td>");
 content +=F( "<td><input id='counter' type='text' name='counter' size='15' value='0'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 
 content +=F( "<tr>");
 content +=F( "<td><h3>Device Informations<br><blink><data id='info'></data></blink></h3></td>");
 content +=F( "<td></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 
 content +=F( "<tr>");
 content +=F( "<td>Latiitude</td>");
 content +=F( "<td><input id='lat' type='text' name='lat' size='15' value='0'></td>");
 content +=F( "<td>[dez]</td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Longitude</td>");
 content +=F( "<td><input id='lon' type='text' name='lon' size='15' value='0'></td>");
 content +=F( "<td>[dez]</td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Altiitude</td>");
 content +=F( "<td><input id='alt' type='text' name='alt' size='15' value='0'></td>");
 content +=F( "<td>[m]</td>");
 content +=F( "</tr>");

 if (String(actconf.envSensor) == "BME280") {
   content +=F( "<tr>");
   content +=F( "<td>Air Temperature</td>");
   content +=F( "<td><input id='airtemp' type='text' name='airtemp' size='15' value='0'></td>");
   content +=F( "<td>[<data id='atunit'></data>]</td>");
   content +=F( "</tr>");
  
   content +=F( "<tr>");
   content +=F( "<td>Air Pressure</td>");
   content +=F( "<td><input id='pressure' type='text' name='pressure' size='15' value='0'></td>");
   content +=F( "<td>[mbar]</td>");
   content +=F( "</tr>");
  
   content +=F( "<tr>");
   content +=F( "<td>Air Humidity</td>");
   content +=F( "<td><input id='humidity' type='text' name='humidity' size='15' value='0'></td>");
   content +=F( "<td>[%]</td>");
   content +=F( "</tr>");
  
   content +=F( "<tr>");
   content +=F( "<td>Dewpoint</td>");
   content +=F( "<td><input id='dewpoint' type='text' name='dewpoint' size='15' value='0'></td>");
   content +=F( "<td>[<data id='dpunit'></data>]</td>");
   content +=F( "</tr>");
 }

 content +=F( "<tr>");
 content +=F( "<td>Battery Voltage</td>");
 content +=F( "<td><input id='voltage' type='text' name='voltage' size='15' value='0'></td>");
 content +=F( "<td>[V]</td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>1Wire Temp</td>");
 content +=F( "<td><input id='1wtemp' type='text' name='1wtemp' size='15' value='0'></td>");
 content +=F( "<td>[<data id='1wunit'></data>]</td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Tank 1</td>");
 content +=F( "<td><input id='tank1' type='text' name='tank1' size='15' value='0'></td>");
 content +=F( "<td>[V]</td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Tank 2</td>");
 content +=F( "<td><input id='tank2' type='text' name='tank2' size='15' value='0'></td>");
 content +=F( "<td>[V]</td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Alarm</td>");
 content +=F( "<td><input id='alarm' type='text' name='alarm' size='15' value='0'></td>");
 content +=F( "<td>[bin]</td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Relay</td>");
 content +=F( "<td><input id='relay' type='text' name='relay' size='15' value='0'></td>");
 content +=F( "<td>[bin]</td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Relay Timer</td>");
 content +=F( "<td><input id='rtimer' type='text' name='rtimer' size='15' value='0'></td>");
 content +=F( "<td>[min]</td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>Env Sensor</td>");
 content +=F( "<td><input id='envSensor' type='text' name='envSensor' size='15' value='0'></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 
 content +=F( "</table>");

 content +=F( "<br>");
 content +=F( "<hr align='left'>");
 content +=F( "<br>");
 content +=F( "<form action='/'><button type='submit'>Back</button></form>");
 content +=F( "<br>");
 content +=F( "<br>");
 content +=F( "</body>");
 content +=F( "</html>");

 return content;
}
