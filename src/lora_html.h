// Wind values webpage
String Lora()
{
 // Debug info 
 DebugPrintln(3, "Send sensorv.html");

 // Page content with JavaScript and JSON for updating
 String content;
 content +=F( "<!DOCTYPE html>");
 content +=F( "<html>");
 content +=F( "<head>");
 content +=F( "<title>LoRa Info</title>");
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
 content +=F( "document.getElementById('region').innerHTML = myObj.Device.LoRaSettings.Frequency;");
 content +=F( "document.getElementById('address').innerHTML = myObj.Device.LoRaSettings.DeviceAddress;");
 content +=F( "document.getElementById('actualch').innerHTML = myObj.Device.LoRaSettings.ActualChannel;");
 content +=F( "document.getElementById('actualsf').innerHTML = myObj.Device.LoRaSettings.ActualSF;");
 content +=F( "document.getElementById('tinterval').innerHTML = myObj.Device.LoRaSettings.TXInterval * 30;");
 content +=F( "document.getElementById('slot').innerHTML = myObj.Device.LoRaSettings.TimeSlot;");
 content +=F( "document.getElementById('counter').innerHTML = myObj.Device.LoRaSettings.TXCounter;");

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
 
 content +=F( "<h3>LoRa Info <blink><data id='info'></data></blink>");
 content +=F( "</h3>");
 content +=F( "<FONT SIZE='4'>");
 content +=F( "<table>");

 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-access-point' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<line x1='12' y1='12' x2='12' y2='12.01' />");
 content +=F( "<path d='M14.828 9.172a4 4 0 0 1 0 5.656' />");
 content +=F( "<path d='M17.657 6.343a8 8 0 0 1 0 11.314' />");
 content +=F( "<path d='M9.168 14.828a4 4 0 0 1 0 -5.656' />");
 content +=F( "<path d='M6.337 17.657a8 8 0 0 1 0 -11.314' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");

 content +=F( "<td>Freq Region:</td>");
 content +=F( "<td><data id='region'></data></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-medical-cross' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<path d='M13 3a1 1 0 0 1 1 1v4.535l3.928 -2.267a1 1 0 0 1 1.366 .366l1 1.732a1 1 0 0 1 -.366 1.366l-3.927 2.268l3.927 2.269a1 1 0 0 1 .366 1.366l-1 1.732a1 1 0 0 1 -1.366 .366l-3.928 -2.269v4.536a1 1 0 0 1 -1 1h-2a1 1 0 0 1 -1 -1v-4.536l-3.928 2.268a1 1 0 0 1 -1.366 -.366l-1 -1.732a1 1 0 0 1 .366 -1.366l3.927 -2.268l-3.927 -2.268a1 1 0 0 1 -.366 -1.366l1 -1.732a1 1 0 0 1 1.366 -.366l3.928 2.267v-4.535a1 1 0 0 1 1 -1h2z' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");

 content +=F( "<td>Device Addr:</td>");
 content +=F( "<td><data id='address'></data></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");

 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-square-x' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<rect x='4' y='4' width='16' height='16' rx='2' />");
 content +=F( "<path d='M10 10l4 4m0 -4l-4 4' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");

 content +=F( "<td>Actual Chan:</td>");
 content +=F( "<td><data id='actualch'></data></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-separator-vertical' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<line x1='12' y1='4' x2='12' y2='20' />");
 content +=F( "<polyline points='8 8 4 12 8 16' />");
 content +=F( "<polyline points='16 16 20 12 16 8' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");
 content +=F( "<td>Actual SF:</td>");
 content +=F( "<td><data id='actualsf'></data></td>");
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

 content +=F( "<td>TX Interval:</td>");
 content +=F( "<td><data id='tinterval'></data>s</td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-square-dot' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<rect x='4' y='4' width='16' height='16' rx='2' />");
 content +=F( "<circle cx='12' cy='12' r='1' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");

 content +=F( "<td>Time Slot:</td>");
 content +=F( "<td><data id='slot'></data></td>");
 content +=F( "<td></td>");
 content +=F( "</tr>");
 content +=F( "<tr>");
 content +=F( "<td>");
 content +=F( "<div class='svg'>");
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-wave-square' width='30' height='30' viewBox='0 0 24 24' stroke-width='1.5' stroke='#FFFFFF' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<path d='M3 12h5v8h4v-16h4v8h5' />");
 content +=F( "</svg>");
 content +=F( "</div>");
 content +=F( "</td>");

 content +=F( "<td>TX Counter:</td>");
 content +=F( "<td><data id='counter'></data></td>");
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
