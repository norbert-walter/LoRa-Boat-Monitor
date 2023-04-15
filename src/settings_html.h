// Settings webpage
String Settings(int num, String vname[31], String value[31])
{ 
  String hash = "";
  bool reboot = false;
  
  // Print all received get arguments
  for (int i = 0; i < num; i++)
  {
    String out = vname[i] + " : " + value[i];
     DebugPrintln(3, out);
  }

  // Check new settings and save it in configuration
  for (int i = 0; i < num; i++)
  {
    // Passwort Settings
    //******************
    if(vname[i] == "password"){
      hash = value[i];
    }
    if (vname[i] == "usepassword") {
      actconf.crypt = toInteger(value[i]);
    }
    if (vname[i] == "pagepasswd") {
      value[i].toCharArray(actconf.password, 31);
    }
    // Display Settings
    //*****************
    if (vname[i] == "isize") {
      actconf.instrumentSize = toInteger(value[i]);
    }
    // Network Settings
    //*****************
    if (vname[i] == "cssid") {
      value[i].toCharArray(actconf.cssid, 31);
    }
    if (vname[i] == "cpasswd") {
      value[i].toCharArray(actconf.cpassword, 31);
    }
    if (vname[i] == "timeout") {
      actconf.timeout = toInteger(value[i]);
    }
    if (vname[i] == "sssid") {
      value[i].toCharArray(actconf.sssid, 31);
    }
    if (vname[i] == "spasswd") {
      value[i].toCharArray(actconf.spassword, 31);
    }
    if (vname[i] == "apchannel") {
      actconf.apchannel = toInteger(value[i]);
    }
    if (vname[i] == "servermode") {
      actconf.serverMode = toInteger(value[i]);
    }
    if (vname[i] == "mdnsservice") {
      actconf.mDNS = toInteger(value[i]);
    }
    // LoRa Settings
    //**************
    if (vname[i] == "devaddr") {
      char hexstring[8];
      value[i].toCharArray(hexstring, 9);
      actconf.devaddr = HexToInt(hexstring);
    }
    if (vname[i] == "nskey") {
      char mystring[33];
      char hexstring[2];
      value[i].toCharArray(mystring, 33);
      DebugPrintln(3, mystring);
      for (int j = 0; j < 16; j++){
        hexstring[0] = mystring[j*2];
        hexstring[1] = mystring[j*2+1];
        actconf.nskey[j] = HexToInt(hexstring);
        DebugPrint(3, j);
        DebugPrint(3, " ");
        DebugPrint(3, HexToInt(hexstring));
        DebugPrint(3, " ");
        DebugPrintln(3, hexstring);
      }
    }
    if (vname[i] == "appkey") {
      char mystring[33];
      char hexstring[2];
      value[i].toCharArray(mystring, 33);
      DebugPrintln(3, mystring);
      for (int j = 0; j < 16; j++){
        hexstring[0] = mystring[j*2];
        hexstring[1] = mystring[j*2+1];
        actconf.appkey[j] = HexToInt(hexstring);
        DebugPrint(3, j);
        DebugPrint(3, " ");
        DebugPrint(3, HexToInt(hexstring));
        DebugPrint(3, " ");
        DebugPrintln(3, hexstring);
      }
    } 
    if (vname[i] == "lorafrequency") {
      value[i].toCharArray(actconf.lorafrequency, 31);
    }
    if (vname[i] == "lchannel") {
      actconf.lchannel = toInteger(value[i]);
      // Enable the used LoRa channels
      setChannel(actconf.lchannel);
    }
    if (vname[i] == "dynsf") {
      actconf.dynsf = toInteger(value[i]);
    }
    if (vname[i] == "spreadf") {
      actconf.spreadf = toInteger(value[i]);
      // Set spreading factor and dynamic SF
      setSF(slot, actconf.spreadf, actconf.dynsf);
    }
    if (vname[i] == "tinterval") {
      if(actconf.tinterval != toInteger(value[i])){
        actconf.tinterval = toInteger(value[i]);
        // Set LoRa transmit interval
        TX_INTERVAL = actconf.tinterval * 30; // Send interval * 30s
        reboot = true; // Need a reboot
      }
    }
    if (vname[i] == "sendlora") {
      actconf.sendlora = toInteger(value[i]);
    }
    if (vname[i] == "relay") {
      actconf.relay = toInteger(value[i]);
      if(actconf.relay == 0){
        digitalWrite(relayPin, LOW);
        relaytimer = 0;
      }
      else{
        digitalWrite(relayPin, HIGH);
        relaytimer = 288;  // 288 x 5min = 1440min
      }
    }
    // DeviceSettings
    //*************** 
    if (vname[i] == "debugmode") {
      actconf.debug = toInteger(value[i]);
    }
    if (vname[i] == "serspeed") {
      actconf.serspeed = toInteger(value[i]);
    }
    if (vname[i] == "deviceid") {
      actconf.deviceID = toInteger(value[i]);
    }
    if (vname[i] == "devicetype") {
      value[i].toCharArray(actconf.deviceType, 10);
    }
    if (vname[i] == "sendlora") {
      actconf.sendlora = toInteger(value[i]);
    }
    if (vname[i] == "senddata") {
      actconf.senddata = toInteger(value[i]);
    }    
    if (vname[i] == "vaverage") {
      actconf.vaverage = toInteger(value[i]);
    }
    if (vname[i] == "t1average") {
      actconf.t1average = toInteger(value[i]);
    }
    if (vname[i] == "t2average") {
      actconf.t2average = toInteger(value[i]);
    }   
    if (vname[i] == "tstype") {
      value[i].toCharArray(actconf.tempSensorType, 10);
    }
    if (vname[i] == "tempunit") {
      value[i].toCharArray(actconf.tempUnit, 2);
    }
    if (vname[i] == "envSensor") {
      value[i].toCharArray(actconf.envSensor, 20);
    }
    if (vname[i] == "standbyMode") {
      value[i].toCharArray(actconf.standbyMode, 4);
    }
    if (vname[i] == "loraStandbyMode") {
      value[i].toCharArray(actconf.loraStandbyMode, 8);
    }
    // Calibration Settings
    //*********************    
    if (vname[i] == "a1vslope") {
      actconf.a1vslope = toFloat(value[i]);
    }
    if (vname[i] == "a2vslope") {
      actconf.a2vslope = toFloat(value[i]);
    }
    if (vname[i] == "voffset") {
      actconf.voffset = toFloat(value[i]);
    }
    if (vname[i] == "a1t1slope") {
      actconf.a1t1slope = toFloat(value[i]);
    }
    if (vname[i] == "a2t1slope") {
      actconf.a2t1slope = toFloat(value[i]);
    }
    if (vname[i] == "t1offset") {
      actconf.t1offset = toFloat(value[i]);
    }
    if (vname[i] == "a1t2slope") {
      actconf.a1t2slope = toFloat(value[i]);
    }
    if (vname[i] == "a2t2slope") {
      actconf.a2t2slope = toFloat(value[i]);
    }
    if (vname[i] == "t2offset") {
      actconf.t2offset = toFloat(value[i]);
    }
  }

  // Save the settings if the number of return values is greater 0
  if(num > 0) {  
    saveEEPROMConfig(actconf);      // Save the new settings in EEPROM
    DebugPrintln(3, "New settings saved");
  }

  // Debug info
  DebugPrintln(3, "Send settings.html");

  // Reboot when TX_INTERVAL is changed
  if(reboot){
    DebugPrintln(3, "Reboot");
    ESP.restart(); // Restart ESP32
  }

  // Check page password
 if(actconf.crypt == 1 && (hash.length() == 0 || hash != cryptPassword(String(actconf.password)))){
   // Generate a new transaction ID
   transID();
   
   // Page content for password input
   String content;
   content +=F( "<!DOCTYPE html>");
   content +=F( "<html>");
   content +=F( "<head>");
   content +=F( "<title>Password ");
   content += String(actconf.devname);
   content +=F( "</title>");
   content +=F( "<link rel='stylesheet' type='text/css' href='/css'>");
   content +=F( "<meta http-equiv='content-type' content='text/html; charset=UTF-8'>");
   content +=F( "<meta name=viewport content='width=device-width, initial-scale=1'>");
   content +=F( "<script src='MD5.js' type='text/javascript'></script>");
   content +=F( " <style>");
  // content += CSS();
   content +=F( "</style>");
   content +=F( "</head>");
   content +=F( "<body>");
   
   // Web page title
   content +=F( "<h2>");
   content += String(actconf.devname);
   content +=F( "</h2>");
   content += String(actconf.crights);
   content +=F( ", "); 
   content += String(actconf.fversion);
   content +=F( ", CQ: ");
   content += String(int(quality));
   content +=F( "%"); 
   content +=F( "<hr align='left'>");
   
   content +=F( "<h3>Password Required</h3>");
   content +=F( "<form id='pwdForm' action='settings' method='get'><input size=20 type='text' name='password' id='password' onkeypress='return event.keyCode != 13;'><br/><br/><button TYPE='button' onClick='proc()'>Send</button></form>");
   content +=F( "<br>");
   content +=F( "<hr align='left'>");
   content +=F( "<br>");
   content +=F( "<form id='pwdForm2' action='/' method='get'><button type='button' onClick='document.getElementById(\"pwdForm2\").submit();'>Back</button></form>");
   content +=F( "</body>");
   content +=F( "</html>");
  
   return content;
 }
 else{
   // Generate a new transaction ID
   transID();

    // Page content
    String content;
    content += F("<!DOCTYPE html>");
    content += F("<html>");
    content += F("<head>");
    content +=F( "<title>Settings ");
    content += String(actconf.devname);
    content +=F( "</title>");
    content += F("<link rel='stylesheet' type='text/css' href='/css'>");
    content += F("<meta http-equiv='content-type' content='text/html; charset=UTF-8'>");
    content += F("<meta name=viewport content='width=device-width, initial-scale=1'>");
    content += F("<style type='text/css'>");
    content += F("select {width:150px;}");
    content += F("input {width:145px;}");
    // content += CSS();
    content += F("</style>");
    content += F("<script>");
    content += F("function setSelections() {");
    // Passwort Settings
    //******************
    content += F("document.SetForm.usepassword.selectedIndex = ");
    content += getindex(usepassword, String(actconf.crypt));
    content += F(";");
    // Display Settings
    //*****************
    content += F("document.SetForm.isize.selectedIndex = ");
    content += getindex(isize, String(actconf.instrumentSize));
    content += F(";");
    // Network Settings
    //*****************
    content += F("document.SetForm.timeout.selectedIndex = ");
    content += getindex(timeout, String(actconf.timeout));
    content += F(";");  
    content += F("document.SetForm.apchannel.selectedIndex = ");
    content += getindex(apchannel, String(actconf.apchannel));
    content += F(";");
    content += F("document.SetForm.servermode.selectedIndex = ");
    content += getindex(servermode, String(actconf.serverMode));
    content += F(";");
    content += F("document.SetForm.mdnsservice.selectedIndex = ");
    content += getindex(mdnsservice, String(actconf.mDNS));
    content += F(";");
    // LoRa Settings
    //**************
    content += F("document.SetForm.lorafrequency.selectedIndex = ");
    content += getindex(lorafrequencys, String(actconf.lorafrequency));
    content += F(";");
    content += F("document.SetForm.lchannel.selectedIndex = ");
    content += getindex(lchannel, String(actconf.lchannel));
    content += F(";");
    content += F("document.SetForm.spreadf.selectedIndex = ");
    content += getindex(spreadf, String(actconf.spreadf));
    content += F(";");
    content += F("document.SetForm.dynsf.selectedIndex = ");
    content += getindex(dynsf, String(actconf.dynsf));
    content += F(";");
    content += F("document.SetForm.relay.selectedIndex = ");
    content += getindex(relay, String(actconf.relay));
    content += F(";");
    // Devive Settings
    //****************
    content += F("document.SetForm.debugmode.selectedIndex = ");
    content += getindex(debugmode, String(actconf.debug));
    content += F(";");
    content += F("document.SetForm.serspeed.selectedIndex = ");
    content += getindex(serspeed, String(actconf.serspeed));
    content += F(";");
    content += F("document.SetForm.deviceid.selectedIndex = ");
    content += getindex(deviceid, String(actconf.deviceID));
    content += F(";");
    content += F("document.SetForm.sendlora.selectedIndex = ");
    content += getindex(sendlora, String(actconf.sendlora));
    content += F(";");
    content += F("document.SetForm.senddata.selectedIndex = ");
    content += getindex(senddata, String(actconf.senddata));
    content += F(";");    
    content += F("document.SetForm.vaverage.selectedIndex = ");
    content += getindex(vaverage, String(actconf.vaverage));
    content += F(";");
    content += F("document.SetForm.t1average.selectedIndex = ");
    content += getindex(t1average, String(actconf.t1average));
    content += F(";");
    content += F("document.SetForm.t2average.selectedIndex = ");
    content += getindex(t2average, String(actconf.t2average));
    content += F(";");    
    content += F("document.SetForm.tstype.selectedIndex = ");
    content += getindex(tstype, String(actconf.tempSensorType));
    content += F(";"); 
    content += F("document.SetForm.tempunit.selectedIndex = ");
    content += getindex(tempunits, String(actconf.tempUnit));
    content += F(";");
    content += F("document.SetForm.envSensor.selectedIndex = ");
    content += getindex(envSensor, String(actconf.envSensor));
    content += F(";");
    content += F("document.SetForm.standbyMode.selectedIndex = ");
    content += getindex(standbyMode, String(actconf.standbyMode));
    content += F(";");
    content += F("document.SetForm.loraStandbyMode.selectedIndex = ");
    content += getindex(loraStandbyMode, String(actconf.loraStandbyMode));
    content += F(";");
    content += F("}");

    content += F("function check_devaddr(iname) {");
    content += F("var valuestring = \"\";");
    content += F("if(iname == \"devaddr\"){valuestring = document.SetForm.devaddr.value;}");
    content += F("var reguexp = /[^A-Z0-9]/;");
    content += F("if(reguexp.exec(valuestring) || valuestring.length !== 8)");
    content += F("{");
    content += F("document.getElementById('sub').disabled = true;");   
    content += F("alert('Error!\\nUse only A-Z, 0-9, \\nAddress Length not 8');");
    content += F("}");
    content += F("else{");
    content += F("document.getElementById('sub').disabled = false;");
    content += F("}");
    content += F("}");

    content += F("function check_key(iname) {");
    content += F("var valuestring = \"\";");
    content += F("if(iname == \"nskey\"){valuestring = document.SetForm.nskey.value;}");
    content += F("if(iname == \"appkey\"){valuestring = document.SetForm.appkey.value;}");
    content += F("var reguexp = /[^A-Z0-9]/;");
    content += F("console.log(valuestring.length);");
    content += F("if(reguexp.exec(valuestring) || valuestring.length !== 32)");
    content += F("{");
    content += F("document.getElementById('sub').disabled = true;");   
    content += F("alert('Error!\\nUse only A-Z, 0-9, \\nKey Length not 32');");
    content += F("}");
    content += F("else{");
    content += F("document.getElementById('sub').disabled = false;");
    content += F("}");
    content += F("}");
    
    content += F("function check_ssid(iname) {");
    content += F("var valuestring = \"\";");
    content += F("if(iname == \"cssid\"){valuestring = document.SetForm.cssid.value;}");
    content += F("if(iname == \"sssid\"){valuestring = document.SetForm.sssid.value;}");
    content += F("var reguexp = /[^A-z0-9_-]/;");
    content += F("if(reguexp.exec(valuestring) || valuestring.length < 1 || valuestring.length > 20)");
    content += F("{");
    content += F("document.getElementById('sub').disabled = true;");   
    content += F("alert('Error!\\nUse only a-z, A-Z, 0-9, _-\\nSSID Length 1-20');");
    content += F("}");
    content += F("else{");
    content += F("document.getElementById('sub').disabled = false;");
    content += F("}");
    content += F("}");

    content += F("function check_tinterval(iname) {");
    content += F("var valuestring = \"\";");
    content += F("if(iname == \"tinterval\"){valuestring = document.SetForm.tinterval.value;}");
    content += F("var reguexp = /[^0-9]/;");
    content += F("if(reguexp.exec(valuestring) || valuestring < 1 || valuestring > 255)");
    content += F("{");
    content += F("document.getElementById('sub').disabled = true;");   
    content += F("alert('Error!\\nUse only 0-9, \\nValues 1...255');");
    content += F("}");
    content += F("else{");
    content += F("document.getElementById('sub').disabled = false;");
    content += F("}");
    content += F("}");
  
    content += F("function check_passwd(iname) {");
    content += F("var valuestring = \"\";");
    content += F("if(iname == \"pagepasswd\"){valuestring = document.SetForm.sidepasswd.value;}");
    content += F("if(iname == \"cpasswd\"){valuestring = document.SetForm.cpasswd.value;}");
    content += F("if(iname == \"spasswd\"){valuestring = document.SetForm.spasswd.value;}");
    content += F("var reguexp = /[^A-z0-9\-]/;");
    content += F("if(reguexp.exec(valuestring) || valuestring.length < 8 || valuestring.length > 20)");
    content += F("{");
    content += F("document.getElementById('sub').disabled = true;");    
    content += F("alert('Error!\\nUse only a-z, A-Z, 0-9, '-'\\nPassword Length 8-20');");
    content += F("}");
    content += F("else{");
    content += F("document.getElementById('sub').disabled = false;");
    content += F("}");
    content += F("}");
      
    content += F("</script>");
    content += F("</head>");
    content += F("<body onload='setSelections();'>");
    
    // Web page title
    content += F("<h2>");
    content += String(actconf.devname);
    content += F("</h2>");
    content += String(actconf.crights);
    content += F(", "); 
    content += String(actconf.fversion);
    content += F(", CQ: ");
    content += String(int(quality));
    content += F("%"); 
    content += F("<hr align='left'>");
  
    content += F("<form id='form1' name='SetForm' method='get' action='settings'>");
    content += F("<table>");
  
    content += F("<tr>");
    content += F("<td><h3>Password Settings</h3></td>");
    content += F("<td></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Use Page Password</td>");
    content += F("<td>");
    content += F("<select name='usepassword' size='1'>");
    content += F("<option value='0'>Off</option>");
    content += F("<option value='1'>On</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Page Password</td>");
    content += F("<td><input type='text' required name='pagepasswd' size='20' value='");
    content += String(actconf.password);  
    content += F("' maxlength='20' onchange='check_passwd(\"pagepasswd\")'></td>");
    content += F("<td></td>");
    content += F("</tr>");
    
    content += F("<tr>");
    content += F("<td><h3>Display Settings</h3></td>");
    content += F("<td></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Instrument Size</td>");
    content += F("<td>");
    content += F("<select name='isize' size='1'>");
    content += F("<option value='200'>200x200 pix</option>");
    content += F("<option value='250'>250x250 pix</option>");
    content += F("<option value='300'>300x300 pix</option>");
    content += F("<option value='350'>350x350 pix</option>");
    content += F("<option value='400'>400x400 pix</option>");
    content += F("<option value='450'>450x450 pix</option>");
    content += F("<option value='500'>500x500 pix</option>");
    content += F("<option value='550'>550x550 pix</option>");
    content += F("<option value='600'>600x600 pix</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td><h3>Network Settings</h3></td>");
    content += F("<td></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>WLAN Client SSID</td>");
    content += F("<td><input type='text' required name='cssid' size='20' value='");
    content += String(actconf.cssid);
    content += F("' maxlength='20' onchange='check_ssid(\"cssid\")'></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>WLAN Client Password</td>");
    content += F("<td><input type='text' required name='cpasswd' size='20' value='");  
    content += String(actconf.cpassword);    
    content += F("' maxlength='20' onchange='check_passwd(\"cpasswd\")'></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Connection Timeout</td>");
    content += F("<td>");
    content += F("<select name='timeout' size='1'>");
    content += F("<option value='30'>30s</option>");
    content += F("<option value='60'>1 min</option>");
    content += F("<option value='90'>1.5 min</option>");
    content += F("<option value='120'>2 min</option>");
    content += F("<option value='150'>2.5 min</option>");
    content += F("<option value='180'>3 min</option>");
    content += F("<option value='210'>3.5 min</option>");
    content += F("<option value='240'>4 min</option>");
    content += F("<option value='270'>4.5 min</option>");
    content += F("<option value='300'>5 min</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>WLAN Server SSID</td>");
    content += F("<td><input type='text' required name='sssid' size='20' value='");
    content += String(actconf.sssid);
    content += F("' maxlength='20' onchange='check_ssid(\"sssid\")'></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>WLAN Server Password</td>");
    content += F("<td><input type='text' required name='spasswd' size='20' value='");
    content += String(actconf.spassword);  
    content += F("' maxlength='20' onchange='check_passwd(\"spasswd\")'></td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>AP Channel</td>");
    content += F("<td>");
    content += F("<select name='apchannel' size='1'>");
    content += F("<option value='1'>1</option>");
    content += F("<option value='2'>2</option>");
    content += F("<option value='3'>3</option>");
    content += F("<option value='4'>4</option>");
    content += F("<option value='5'>5</option>");
    content += F("<option value='6'>6</option>");
    content += F("<option value='7'>7</option>");
    content += F("<option value='8'>8</option>");
    content += F("<option value='9'>9</option>");
    content += F("<option value='10'>10</option>");
    content += F("<option value='11'>11</option>");
    content += F("<option value='12'>12</option>");
    content += F("<option value='13'>13</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Server Mode</td>");
    content += F("<td>");
    content += F("<select name='servermode' size='1'>");
    content += F("<option value='0'>HTTP (JSON, NMEA)</option>");
    content += F("<option value='1'>NMEA Serial</option>");
    content += F("<option value='2'>MQTT</option>");
    content += F("<option value='3'>Diagnostic</option>");
    content += F("<option value='4'>Demo Mode</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>mDNS Service</td>");
    content += F("<td>");
    content += F("<select name='mdnsservice' size='1'>");
    content += F("<option value='0'>Off</option>");
    content += F("<option value='1'>On</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td><h3>LoRa Settings (ABP)</h3></td>");
    content += F("<td></td>");
    content += F("<td></td>");
    content += F("</tr>");

/*
    // Target platform as C library
    typedef uint8_t            bit_t;
    typedef uint8_t            u1_t;
    typedef int8_t             s1_t;
    typedef uint16_t           u2_t;
    typedef int16_t            s2_t;
    typedef uint32_t           u4_t;
    typedef int32_t            s4_t;
    typedef unsigned int       uint;
    typedef const char* str_t; 
 */

    content += F("<tr>");
    content += F("<td>Device Address</td>");
    content += F("<td><input type='text' required name='devaddr' size='20' value='");
    String mystring = String(actconf.devaddr, HEX);
    mystring.toUpperCase();
    content += mystring;
    content += F("' maxlength='20' onchange='check_devaddr(\"devaddr\")'></td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>Network Session Key</td>");
    content += F("<td><input type='text' required name='nskey' size='40' value='");
    for (int i = 0; i < 16; i++){
      String mystring = String(actconf.nskey[i], HEX);
      if(mystring.length() == 1){
        mystring = "0" + mystring;
      }
      mystring.toUpperCase();
      content += mystring;
    }
    content += F("' maxlength='40' onchange='check_key(\"nskey\")'></td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>Application Key</td>");
    content += F("<td><input type='text' required name='appkey' size='40' value='");
    for (int i = 0; i < 16; i++){
      String mystring = String(actconf.appkey[i], HEX);
      if(mystring.length() == 1){
        mystring = "0" + mystring;
      }
      mystring.toUpperCase();
      content += mystring;
    }
    content += F("' maxlength='40' onchange='check_key(\"appkey\")'></td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>Frequency Region</td>");
    content += F("<td>");
    content += F("<select name='lorafrequency' size='1'>");
    content += F("<option value='EU868'>EU868");
    content += F("<option value='US915'>US915");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>LoRa Channel</td>");
    content += F("<td>");
    content += F("<select name='lchannel' size='1'>");
    content += F("<option value='0'>0</option>");
    content += F("<option value='1'>1</option>");
    content += F("<option value='2'>2</option>");
    content += F("<option value='3'>3</option>");
    content += F("<option value='4'>4</option>");
    content += F("<option value='5'>5</option>");
    content += F("<option value='6'>6</option>");
    content += F("<option value='7'>7</option>");
    content += F("<option value='8'>0...7 dynamic</option>");
    content += F("<option value='9'>0...3 dynamic</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>Spreading Factor</td>");
    content += F("<td>");
    content += F("<select name='spreadf' size='1'>");
    content += F("<option value='7'>7</option>");
    content += F("<option value='8'>8</option>");
    content += F("<option value='9'>9</option>");
    content += F("<option value='10'>10</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>Dynamic SF</td>");
    content += F("<td>");
    content += F("<select name='dynsf' size='1'>");
    content += F("<option value='0'>Off</option>");
    content += F("<option value='1'>On</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>TX Interval</td>");
    content += F("<td><input type='text' required name='tinterval' size='20' value='");
    content += String(actconf.tinterval);
    content += F("' maxlength='20' onchange='check_tinterval(\"tinterval\")'></td>");
    content += F("<td>[x30s]</td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>Relay</td>");
    content += F("<td>");
    content += F("<select name='relay' size='1'>");
    content += F("<option value='0'>Off</option>");
    content += F("<option value='1'>On</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td><h3>Device Settings</h3></td>");
    content += F("<td></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Serial Debug Mode</td>");
    content += F("<td>");
    content += F("<select name='debugmode' size='1'>");
    content += F("<option value='0'>Off</option>");
    content += F("<option value='1'>Errors</option>");
    content += F("<option value='2'>Errors + Warnings</option>");
    content += F("<option value='3'>Errors + Warnings + Messages</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Serial Speed</td>");
    content += F("<td>");
    content += F("<select name='serspeed' size='1'>");
    content += F("<option value='300'>300 Bd</option>");
    content += F("<option value='1200'>1200 Bd</option>");
    content += F("<option value='2400'>2400 Bd</option>");
    content += F("<option value='4800'>4800 Bd</option>");
    content += F("<option value='9600'>9600 Bd</option>");
    content += F("<option value='19200'>19200 Bd</option>");
    content += F("<option value='38400'>38400 Bd</option>");
    content += F("<option value='57600'>57600 Bd</option>");
    content += F("<option value='74880'>74880 Bd</option>");
    content += F("<option value='115200'>115200 Bd</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Device ID</td>");
    content += F("<td>");
    content += F("<select name='deviceid' size='1'>");
    content += F("<option value='0'>0</option>");
    content += F("<option value='1'>1</option>");
    content += F("<option value='2'>2</option>");
    content += F("<option value='3'>3</option>");
    content += F("<option value='4'>4</option>");
    content += F("<option value='5'>5</option>");
    content += F("<option value='6'>6</option>");
    content += F("<option value='7'>7</option>");
    content += F("<option value='8'>8</option>");
    content += F("<option value='9'>9</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Device Type</td>");
    content += F("<td>");
    content += F("<select name='devicetype' size='1'>");
    content += F("<option value='LoRa1000'>LoRa1000</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>Send LoRa</td>");
    content += F("<td>");
    content += F("<select name='sendlora' size='1'>");
    content += F("<option value='0'>Off</option>");
    content += F("<option value='1'>On</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
    
    content += F("<tr>");
    content += F("<td>Send NMEA0183</td>");
    content += F("<td>");
    content += F("<select name='senddata' size='1'>");
    content += F("<option value='0'>Off</option>");
    content += F("<option value='1'>On</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
    
    content += F("<tr>");
    content += F("<td>Average Voltage</td>");
    content += F("<td>");
    content += F("<select name='vaverage' size='1'>");
    content += F("<option value='1'>1</option>");
    content += F("<option value='2'>2</option>");
    content += F("<option value='3'>3</option>");
    content += F("<option value='4'>4</option>");
    content += F("<option value='5'>5</option>");
    content += F("<option value='6'>6</option>");
    content += F("<option value='7'>7</option>");
    content += F("<option value='8'>8</option>");
    content += F("<option value='9'>9</option>");
    content += F("<option value='10'>10</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>Average Tank1</td>");
    content += F("<td>");
    content += F("<select name='t1average' size='1'>");
    content += F("<option value='1'>1</option>");
    content += F("<option value='2'>2</option>");
    content += F("<option value='3'>3</option>");
    content += F("<option value='4'>4</option>");
    content += F("<option value='5'>5</option>");
    content += F("<option value='6'>6</option>");
    content += F("<option value='7'>7</option>");
    content += F("<option value='8'>8</option>");
    content += F("<option value='9'>9</option>");
    content += F("<option value='10'>10</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>Average Tank2</td>");
    content += F("<td>");
    content += F("<select name='t2average' size='1'>");
    content += F("<option value='1'>1</option>");
    content += F("<option value='2'>2</option>");
    content += F("<option value='3'>3</option>");
    content += F("<option value='4'>4</option>");
    content += F("<option value='5'>5</option>");
    content += F("<option value='6'>6</option>");
    content += F("<option value='7'>7</option>");
    content += F("<option value='8'>8</option>");
    content += F("<option value='9'>9</option>");
    content += F("<option value='10'>10</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Temp Sensor Type</td>");
    content += F("<td>");
    content += F("<select name='tstype' size='1'>");
    content += F("<option value='Off'>Off</option>");
    content += F("<option value='DS18B20'>DS18B20</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Temp Unit</td>");
    content += F("<td>");
    content += F("<select name='tempunit' size='1'>");
    content += F("<option value='C'>&deg;C</option>");
    content += F("<option value='F'>&deg;F</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>Env Sensor Type</td>");
    content += F("<td>");
    content += F("<select name='envSensor' size='1'>");
    content += F("<option value='Off'>Off</option>");
    content += F("<option value='BME280'>BME280</option>");
    content += F("<option value='VEdirect-Read'>VEdirect-Read</option>");
    content += F("<option value='VEdirect-Send'>VEdirect-Send</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td><h3>Standby Mode Settings</h3></td>");
    content += F("<td></td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>Activate Standby Mode (Alarm Input X1-3)</td>");
    content += F("<td>");
    content += F("<select name='standbyMode' size='1'>");
    content += F("<option value='Off'>Off</option>");
    content += F("<option value='On'>On</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Lora only in Standy?</td>");
    content += F("<td>");
    content += F("<select name='loraStandbyMode' size='1'>");
    content += F("<option value='Standby'>Standby</option>");
    content += F("<option value='Always'>Always (currently not working)</option>");
    content += F("</select>");
    content += F("</td>");
    content += F("<td></td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td><h3>Calibration Settings</h3></td>");
    content += F("<td></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Voltage A2</td>");
    content += F("<td><input type='text' required name='a2vslope' size='20' value='");
    char a2vslope[20];
    sprintf(a2vslope, "%.5f", actconf.a2vslope);
    content += a2vslope;
    content += F("' maxlength='20'></td>");
    content += F("<td></td>");
    content += F("</tr>");
    
    content += F("<tr>");
    content += F("<td>Voltage A1</td>");
    content += F("<td><input type='text' required name='a1vslope' size='20' value='");
    char a1vslope[20];
    sprintf(a1vslope, "%.5f", actconf.a1vslope);
    content += a1vslope;
    content += F("' maxlength='20'></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Volatge Offset</td>");
    content += F("<td><input type='text' required name='voffset' size='20' value='");
    char voffset[20];
    sprintf(voffset, "%.5f", actconf.voffset);
    content += voffset;
    content += F("' maxlength='20'></td>");
    content += F("<td>[V]</td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>Tank1 A2</td>");
    content += F("<td><input type='text' required name='a2t1slope' size='20' value='");
    char a2t1slope[20];
    sprintf(a2t1slope, "%.5f", actconf.a2t1slope);
    content += a2t1slope;
    content += F("' maxlength='20'></td>");
    content += F("<td></td>");
    content += F("</tr>");
    
    content += F("<tr>");
    content += F("<td>Tank1 A1</td>");
    content += F("<td><input type='text' required name='a1t1slope' size='20' value='");
    char a1t1slope[20];
    sprintf(a1t1slope, "%.5f", actconf.a1t1slope);
    content += a1t1slope;
    content += F("' maxlength='20'></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Tank1 Offset</td>");
    content += F("<td><input type='text' required name='t1offset' size='20' value='");
    char t1offset[20];
    sprintf(t1offset, "%.5f", actconf.t1offset);
    content += t1offset;
    content += F("' maxlength='20'></td>");
    content += F("<td>[l]</td>");
    content += F("</tr>");

    content += F("<tr>");
    content += F("<td>Tank2 A2</td>");
    content += F("<td><input type='text' required name='a2t2slope' size='20' value='");
    char a2t2slope[20];
    sprintf(a2t2slope, "%.5f", actconf.a2t2slope);
    content += a2t2slope;
    content += F("' maxlength='20'></td>");
    content += F("<td></td>");
    content += F("</tr>");
    
    content += F("<tr>");
    content += F("<td>Tank2 A1</td>");
    content += F("<td><input type='text' required name='a1t2slope' size='20' value='");
    char a1t2slope[20];
    sprintf(a1t2slope, "%.5f", actconf.a1t2slope);
    content += a1t2slope;
    content += F("' maxlength='20'></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td>Tank2 Offset</td>");
    content += F("<td><input type='text' required name='t2offset' size='20' value='");
    char t2offset[20];
    sprintf(t2offset, "%.5f", actconf.t2offset);
    content += t2offset;
    content += F("' maxlength='20'></td>");
    content += F("<td>[l]</td>");
    content += F("</tr>");
  
    content += F("<tr>");
    content += F("<td><br><button id='sub' type='submit'>Save</button></td>");
    content += F("<td></td>");
    content += F("<td></td>");
    content += F("</tr>");
  
    content += F("</table>");
  
    // Hidden input field for hash
    content += F("<input type='hidden' required name='password' size='20' value='");
    content += String(cryptPassword(String(actconf.password)));
    content += F("' maxlength='20'>");
    
    content += F("</form>");
    content += F("<br>");
  
    content += F("<hr align='left'>");
    content += F("<br>");
  /*
    content += F("<form id='form2' action='http://192.168.4.1/settings'>");
  
    content += F("<input hidden type='text' name='itype' value='simple'>");  
    content += F("<input hidden type='text' name='isize' value='200'>");  
    content += F("<input hidden type='text' name='cssid' value='MyBoat'>");
    content += F("<input hidden type='text' name='cpasswd' value='S6587rr94P'>");
    content += F("<input hidden type='text' name='sssid' value='NoWa'>");
    content += F("<input hidden type='text' name='spasswd' value='12345678'>");
    content += F("<input hidden type='text' name='servermode' value='0'>");
    content += F("<input hidden type='text' name='debugmode' value='3'>");
    content += F("<input hidden type='text' name='serspeed' value='115200'>");
    content += F("<input hidden type='text' name='sensorid' value='0'>");
    content += F("<input hidden type='text' name='wstype' value='NoWa1000'>");
    content += F("<input hidden type='text' name='sendwsdata' value='1'>");
    content += F("<input hidden type='text' name='windtype' value='R'>");
    content += F("<input hidden type='text' name='average' value='1'>");
    content += F("<input hidden type='text' name='speedunit' value='kn'>");
    content += F("<input hidden type='text' name='dwsensor' value='1'>");
    content += F("<input hidden type='text' name='dwrange' value='50'>");
    content += F("<input hidden type='text' name='tstype' value='Off'>");
    content += F("<input hidden type='text' name='sendtsd' value='0'>");
    content += F("<input hidden type='text' name='tempunit' value='C'>");
    
    content += F("<button type='submit'>Set Defaults</button></form>");
  */  
    content += F("<br>"); 
    
    content += F("<form id='form3' action='/'><button type='submit'>Back</button></form>");
    
    content += F("<br>");
    content += F("<br>");
  
    content += F("</body>");
    content += F("</html>");
  
    return content;
 }  
}

