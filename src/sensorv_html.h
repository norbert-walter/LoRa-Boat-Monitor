// Wind values webpage
String Sensorv()
{
 // Debug info 
 DebugPrintln(3, "Send sensorv.html");

 // Page content with JavaScript and JSON for updating
 String content;
 content +=F( "<!DOCTYPE html>");
 content +=F( "<html>");
 content +=F( "<head>");
 content +=F( "<title>Sensor Values</title>");
 content +=F( "<link rel='stylesheet' type='text/css' href='/css'>");
 content +=F( "<meta http-equiv='content-type' content='text/html; charset=UTF-8'>");
 content +=F( "<meta name=viewport content='width=device-width, initial-scale=1'>");

 // Special local format
 content +=F( "<style>");
 content +=F( "</style>");
 content +=F( "</head>");
 content +=F( "<body>");
 
 content +=F( "<script>");
 content +=F( "var xmlhttp = new XMLHttpRequest();");
 content +=F( "xmlhttp.onreadystatechange = function() {");
 content +=F( "if (this.readyState == 4 && this.status == 200) {");
 content +=F( "var myObj = JSON.parse(this.responseText);");

 // Fill all values in Page
 content +=F( "document.getElementById('quality').innerHTML = myObj.Device.NetworkParameter.ConnectionQuality.Value;");
 if (String(actconf.envSensor) == "BME280") {
   content +=F( "document.getElementById('airtemp').innerHTML = myObj.Device.MeasuringValues.AirTemperature.Value;");
   content +=F( "document.getElementById('atunit').innerHTML = myObj.Device.MeasuringValues.AirTemperature.Unit;");
   content +=F( "document.getElementById('pressure').innerHTML = myObj.Device.MeasuringValues.AirPressure.Value;");
   content +=F( "document.getElementById('humidity').innerHTML = myObj.Device.MeasuringValues.AirHumidity.Value;");
   content +=F( "document.getElementById('dewpoint').innerHTML = myObj.Device.MeasuringValues.Dewpoint.Value;");
   content +=F( "document.getElementById('dunit').innerHTML = myObj.Device.MeasuringValues.Dewpoint.Unit;");
 }
 content +=F( "document.getElementById('lat').innerHTML = myObj.Device.MeasuringValues.Latitude.Value;");
 content +=F( "document.getElementById('latns').innerHTML = myObj.Device.MeasuringValues.Latitude.Unit;");
 content +=F( "document.getElementById('lon').innerHTML = myObj.Device.MeasuringValues.Longitude.Value;");
 content +=F( "document.getElementById('lonew').innerHTML = myObj.Device.MeasuringValues.Longitude.Unit;");
 content +=F( "document.getElementById('alt').innerHTML = myObj.Device.MeasuringValues.Altitude.Value;");
 content +=F( "document.getElementById('date').innerHTML = myObj.Device.MeasuringValues.Date.Value;");
 content +=F( "document.getElementById('time').innerHTML = myObj.Device.MeasuringValues.Time.Value;");
 content +=F( "document.getElementById('sunrise').innerHTML = myObj.Device.MeasuringValues.Sunrise.Value;");
 content +=F( "document.getElementById('sunset').innerHTML = myObj.Device.MeasuringValues.Sunset.Value;");
 content +=F( "document.getElementById('speed').innerHTML = myObj.Device.MeasuringValues.Speed.Value;");
 content +=F( "document.getElementById('course').innerHTML = myObj.Device.MeasuringValues.Course.Value;");
 content +=F( "document.getElementById('voltage').innerHTML = myObj.Device.MeasuringValues.BatteryVoltage.Value;");
 content +=F( "document.getElementById('capacity').innerHTML = myObj.Device.MeasuringValues.BatteryCapacity.Value;");
 content +=F( "document.getElementById('1wtemp').innerHTML = myObj.Device.MeasuringValues.Temp1Wire.Value;");
 content +=F( "document.getElementById('1wunit').innerHTML = myObj.Device.MeasuringValues.Temp1Wire.Unit;");
 content +=F( "document.getElementById('tank1').innerHTML = myObj.Device.MeasuringValues.Tank1.Value;");
 content +=F( "document.getElementById('tank2').innerHTML = myObj.Device.MeasuringValues.Tank2.Value;");
 content +=F( "document.getElementById('alarm').innerHTML = myObj.Device.MeasuringValues.Alarm.Value;");
 content +=F( "document.getElementById('relay').innerHTML = myObj.Device.MeasuringValues.Relay.Value;");
 content +=F( "var rtime = 5 * myObj.Device.MeasuringValues.RelayTimer.Value;");
 content +=F( "document.getElementById('rtimer').innerHTML = rtime;");


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
// content +=F( "xmlhttp.open('GET', 'http://192.168.4.1/json', true);");
 content +=F( "xmlhttp.open('GET', '/json', true);");
 content +=F( "xmlhttp.send();");
 content +=F( "}");
 content +=F( "setInterval(function(){read_json(); }, 2000);");
 content +=F( " </script>");
 
 // Web page title
 content +=F( "<h2>");
 content += String(actconf.devname);
 content +=F( "</h2>");
 content += String(actconf.crights);
 content +=F( ", "); 
 content += String(actconf.fversion);
 content +=F( ", CQ: <data id = 'quality'></data>%");
 content +=F( "<hr align='left'>");

 //**********************************************************************************
 if (String(actconf.envSensor) == "BME280") {
   content +=F( "<h3>Environment <blink><data id='info'></data></blink>");
   content +=F( "</h3>");
   content +=F( "<FONT SIZE='4'>");
   content +=F( "<table>");
   content +=F( "<tr>");
   content +=F( "<td>");
  
   content +=F( "<div class='svg'>");
   content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-temperature' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
   content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
   content +=F( "<path d='M10 13.5a4 4 0 1 0 4 0v-8.5a2 2 0 0 0 -4 0v8.5' />");
   content +=F( "<line x1='10' y1='9' x2='14' y2='9' />");
   content +=F( "</svg>");
   content +=F( "</div>");

   content +=F( "</td>");
   content +=F( "<td>Temp:</td>");
   content +=F( "<td><data id='airtemp'></data><data id='atunit'></data></td>");
   content +=F( "<td></td>");
   content +=F( "</tr>");
   content +=F( "<tr>");
   content +=F( "<td>");
   content +=F( "<div class='svg'>");
   content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-wind' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
   content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
   content +=F( "<path d='M5 8h8.5a2.5 2.5 0 1 0 -2.34 -3.24' />");
   content +=F( "<path d='M3 12h15.5a2.5 2.5 0 1 1 -2.34 3.24' />");
   content +=F( "<path d='M4 16h5.5a2.5 2.5 0 1 1 -2.34 3.24' />");
   content +=F( "</svg>");
   content +=F( "</div>");
   content +=F( "</td>");
   content +=F( "<td>Press:</td>");
   content +=F( "<td><data id='pressure'></data>mbar</td>");
   content +=F( "<td></td>");
   content +=F( "</tr>");
   content +=F( "<tr>");
   content +=F( "<td>");
   content +=F( "<div class='svg'>");
   content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-droplet' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
   content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
   content +=F( "<path d='M6.8 11a6 6 0 1 0 10.396 0l-5.197 -8l-5.2 8z' />");
   content +=F( "</svg>");
   content +=F( "</div>");
   content +=F( "</td>");
   content +=F( "<td>Hum:</td>");
   content +=F( "<td><data id='humidity'></data>%</td>");
   content +=F( "<td></td>");
   content +=F( "</tr>");
   content +=F( "<tr>");
   content +=F( "<td>");
   content +=F( "<div class='svg'>");
   content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-temperature' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
   content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
   content +=F( "<path d='M10 13.5a4 4 0 1 0 4 0v-8.5a2 2 0 0 0 -4 0v8.5' />");
   content +=F( "<line x1='10' y1='9' x2='14' y2='9' />");
   content +=F( "</svg>");
   content +=F( "</div>");
   content +=F( "</td>");
   content +=F( "<td>Dew:</td>");
   content +=F( "<td><data id='dewpoint'></data><data id='dunit'></data></td>");
   content +=F( "<td></td>");
   content +=F( "</tr>");
   content +=F( "</table>");
   content +=F( "</FONT><br>");
   content +=F( "<hr align='left'>");
 }
 
 content +=F( "<h3>Position Speed Course</h3>");
 content +=F( "<FONT SIZE='4'>");
 content +=F( "<table>");
 content +=F( "<tr>");
 content +=F( "<td>");

 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-current-location' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<circle cx='12' cy='12' r='3' />");
 content +=F( "<circle cx='12' cy='12' r='8' />");
 content +=F( "<line x1='12' y1='2' x2='12' y2='4' />");
 content +=F( "<line x1='12' y1='20' x2='12' y2='22' />");
 content +=F( "<line x1='20' y1='12' x2='22' y2='12' />");
 content +=F( "<line x1='2' y1='12' x2='4' y2='12' />");
 content +=F( "</svg>");
 content +=F( "</div>");

 content +=F( "</td>");
 content +=F( "<td>Lat:</td>");
 content +=F( "<td><data id='lat'></data><data id='latns'></data></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");

 content +=F( "</div>");
 content +=F( "</td>");
 content +=F( "<td>Lon:</td>");
 content +=F( "<td><data id='lon'></data><data id='lonew'></data></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-satellite' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<path d='M3.707 6.293l2.586 -2.586a1 1 0 0 1 1.414 0l5.586 5.586a1 1 0 0 1 0 1.414l-2.586 2.586a1 1 0 0 1 -1.414 0l-5.586 -5.586a1 1 0 0 1 0 -1.414z' />");
 content +=F( "<path d='M6 10l-3 3l3 3l3 -3' />");
 content +=F( "<path d='M10 6l3 -3l3 3l-3 3' />");
 content +=F( "<line x1='12' y1='12' x2='13.5' y2='13.5' />");
 content +=F( "<path d='M14.5 17a2.5 2.5 0 0 0 2.5 -2.5' />");
 content +=F( "<path d='M15 21a6 6 0 0 0 6 -6' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");
 content +=F( "<td>Alt:</td>");
 content +=F( "<td><data id='alt'></data>m</td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-speedboat' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<path d='M3 17h13.4a3 3 0 0 0 2.5 -1.34l3.1 -4.66h0h-6.23a4 4 0 0 0 -1.49 .29l-3.56 1.42a4 4 0 0 1 -1.49 .29h-3.73h0h-1l-1.5 4z' />");
 content +=F( "<line x1='6' y1='13' x2='7.5' y2='8' />");
 content +=F( "<path d='M6 8h8l2 3' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");
 content +=F( "<td>Spd:</td>");
 content +=F( "<td><data id='speed'></data>kn</td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-gps' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<circle cx='12' cy='12' r='9' />");
 content +=F( "<path d='M12 17l-1 -4l-4 -1l9 -4z' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");
 content +=F( "<td>Crs:</td>");
 content +=F( "<td><data id='course'></data>°</td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "</table>");
 content +=F( "</FONT><br>");
 content +=F( "<hr align='left'>");

 content +=F( "<h3>Date Time Daylight</h3>");
 content +=F( "<FONT SIZE='4'>");
 content +=F( "<table>");
 content +=F( "<tr>");
 content +=F( "<td>");

 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-calendar' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<rect x='4' y='5' width='16' height='16' rx='2' />");
 content +=F( "<line x1='16' y1='3' x2='16' y2='7' />");
 content +=F( "<line x1='8' y1='3' x2='8' y2='7' />");
 content +=F( "<line x1='4' y1='11' x2='20' y2='11' />");
 content +=F( "<line x1='11' y1='15' x2='12' y2='15' />");
 content +=F( "<line x1='12' y1='15' x2='12' y2='18' />");
 content +=F( "</svg>");
 content +=F( "</div>");

 content +=F( "</td>");
 content +=F( "<td>Date:</td>");
 content +=F( "<td><data id='date'></data></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-clock' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<circle cx='12' cy='12' r='9' />");
 content +=F( "<polyline points='12 7 12 12 15 15' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");
 content +=F( "<td>Time:</td>");
 content +=F( "<td><data id='time'></data></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-sunrise' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<path d='M3 17h1m16 0h1m-15.4 -6.4l.7 .7m12.1 -.7l-.7 .7m-9.7 5.7a4 4 0 0 1 8 0' />");
 content +=F( "<line x1='3' y1='21' x2='21' y2='21' />");
 content +=F( "<path d='M12 9v-6l3 3m-6 0l3 -3' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");
 content +=F( "<td>Sunrise:</td>");
 content +=F( "<td><data id='sunrise'></data></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-sunset' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<path d='M3 17h1m16 0h1m-15.4 -6.4l.7 .7m12.1 -.7l-.7 .7m-9.7 5.7a4 4 0 0 1 8 0' />");
 content +=F( "<line x1='3' y1='21' x2='21' y2='21' />");
 content +=F( "<path d='M12 3v6l3 -3m-6 0l3 3' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");
 content +=F( "<td>Sunset:</td>");
 content +=F( "<td><data id='sunset'></data></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "</table>");
 content +=F( "</FONT><br>");
 content +=F( "<hr align='left'>");

 content +=F( "<h3>Battery</h3>");
 content +=F( "<FONT SIZE='4'>");
 content +=F( "<table>");
 content +=F( "<tr>");
 content +=F( "<td>");

 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-battery-automotive' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<rect x='3' y='6' width='18' height='14' rx='2' />");
 content +=F( "<path d='M6 6v-2' />");
 content +=F( "<line x1='19' y1='4' x2='19' y2='6' />");
 content +=F( "<line x1='6.5' y1='13' x2='9.5' y2='13' />");
 content +=F( "<line x1='14.5' y1='13' x2='17.5' y2='13' />");
 content +=F( "<line x1='16' y1='11.5' x2='16' y2='14.5' />");
 content +=F( "</svg>");
 content +=F( "</div>");

 content +=F( "</td>");
 content +=F( "<td>Volt:</td>");
 content +=F( "<td><data id='voltage'></data>V</td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "<td>");
/*
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-battery-automotive' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<rect x='3' y='6' width='18' height='14' rx='2' />");
 content +=F( "<path d='M6 6v-2' />");
 content +=F( "<line x1='19' y1='4' x2='19' y2='6' />");
 content +=F( "<line x1='6.5' y1='13' x2='9.5' y2='13' />");
 content +=F( "<line x1='14.5' y1='13' x2='17.5' y2='13' />");
 content +=F( "<line x1='16' y1='11.5' x2='16' y2='14.5' />");
 content +=F( "</svg>");
 content +=F( "</div>");
*/
 content +=F( "</td>");
 content +=F( "<td>Cap:</td>");
 content +=F( "<td><data id='capacity'></data>%</td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-temperature' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<path d='M10 13.5a4 4 0 1 0 4 0v-8.5a2 2 0 0 0 -4 0v8.5' />");
 content +=F( "<line x1='10' y1='9' x2='14' y2='9' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");
 content +=F( "<td>Temp:</td>");
 content +=F( "<td><data id='1wtemp'></data><data id='1wunit'></data></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "</table>");
 content +=F( "</FONT><br>");
 content +=F( "<hr align='left'>");

 content +=F( "<h3>Levels </h3>");
 content +=F( "<FONT SIZE='4'>");
 content +=F( "<table>");
 content +=F( "<tr>");
 content +=F( "<td>");

 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-droplet' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<path d='M6.8 11a6 6 0 1 0 10.396 0l-5.197 -8l-5.2 8z' />");
 content +=F( "</svg>");
 content +=F( "</div>");

 content +=F( "</td>");
 content +=F( "<td>Water:</td>");
 content +=F( "<td><data id='tank1'></data>%</td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-charging-pile' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<line x1='18' y1='7' x2='17' y2='8' />");
 content +=F( "<path d='M14 11h1a2 2 0 0 1 2 2v3a1.5 1.5 0 0 0 3 0v-7l-3 -3' />");
 content +=F( "<path d='M4 20v-14a2 2 0 0 1 2 -2h6a2 2 0 0 1 2 2v14' />");
 content +=F( "<path d='M9 11.5l-1.5 2.5h3l-1.5 2.5' />");
 content +=F( "<line x1='3' y1='20' x2='15' y2='20' />");
 content +=F( "<line x1='4' y1='8' x2='14' y2='8' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");
 content +=F( "<td>Fuel:</td>");
 content +=F( "<td><data id='tank2'></data>%</td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "</table>");
 content +=F( "</FONT><br>");
 content +=F( "<hr align='left'>");

 content +=F( "<h3>Control</h3>");
 content +=F( "<FONT SIZE='4'>");
 content +=F( "<table>");
 content +=F( "<tr>");
 content +=F( "<td>");

 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-volume' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<path d='M15 8a5 5 0 0 1 0 8' />");
 content +=F( "<path d='M17.7 5a9 9 0 0 1 0 14' />");
 content +=F( "<path d='M6 15h-2a1 1 0 0 1 -1 -1v-4a1 1 0 0 1 1 -1h2l3.5 -4.5a0.8 .8 0 0 1 1.5 .5v14a0.8 .8 0 0 1 -1.5 .5l-3.5 -4.5' />");
 content +=F( "</svg>");
 content +=F( "</div>");

 content +=F( "</td>");
 content +=F( "<td>Alarm:</td>");
 content +=F( "<td><data id='alarm'></data></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-bolt' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<polyline points='13 3 13 10 19 10 11 21 11 14 5 14 13 3' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");
 content +=F( "<td>Relay:</td>");
 content +=F( "<td><data id='relay'></data></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-alarm' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<circle cx='12' cy='13' r='7' />");
 content +=F( "<polyline points='12 10 12 13 14 13' />");
 content +=F( "<line x1='7' y1='4' x2='4.25' y2='6' />");
 content +=F( "<line x1='17' y1='4' x2='19.75' y2='6' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");
 content +=F( "<td>OnTime:</td>");
 content +=F( "<td><data id='rtimer'></data>min</td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "</table>");
 content +=F( "</FONT><br>");
 content +=F( "<hr align='left'>");

 content +=F( "<br>");
 content +=F( "<form action='/'><button type='submit'>Back</button></form>");
 content +=F( "</body>");

 content +=F( "</html>");


 return content;
}
