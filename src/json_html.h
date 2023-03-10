String JSON()
{
    DebugPrintln(3, "Send json.html");
        
    // Page content
    String content = "";
    content +=F(  "{");
    content +=F( "\"Device\": {");
    content +=F( "\"Type\": \"");
    content += String(actconf.devname);
    content +=F( "\",");
    content +=F( "\"CopyRights\": \"");
    content += String(actconf.crights);
    content +=F( "\",");
    content +=F( "\"FirmwareVersion\": \"");
    content += String(actconf.fversion);
    content +=F( "\",");
    content +=F( "\"License\": \"");
    content += String(actconf.license);
    content +=F( "\",");
    content +=F( "\"ESP32\": {");
    content +=F( "\"SDKVersion\": \"");
    content += String(ESP.getSdkVersion());
    content +=F( "\",");
    content +=F( "\"ChipID\": ");
    content += String(chipId);
    content +=F( ",");
    content +=F( "\"CPUSpeed\": {");
    content +=F( "\"Value\": ");
    content += String(ESP.getCpuFreqMHz());
    content +=F( ",");
    content +=F( "\"Unit\": \"MHz\"");
    content +=F( "},");
    content +=F( "\"FreeHeapSize\": {");
    content +=F( "\"Value\": ");
    content += String(ESP.getFreeHeap());
    content +=F( ",");
    content +=F( "\"Unit\": \"Byte\"");
    content +=F( "}");
    content +=F( "},");
    content +=F( "\"NetworkParameter\": {");
    content +=F( "\"WLANClientSSID\": \"");
    content += String(actconf.cssid);
    content +=F( "\",");
    content +=F( "\"WLANClientIP\": \"");
    content += WiFi.localIP().toString();
    content +=F( "\",");

    content +=F( "\"FieldStrength\": {");
    content +=F( "\"Value\": ");
    content += String(fieldstrength);
    content +=F( ",");
    content +=F( "\"Unit\": \"dBm\"");
    content +=F( "},");
    content +=F( "\"ConnectionQuality\": {");
    content +=F( "\"Value\": ");
    content += String(quality);
    content +=F( ",");
    content +=F( "\"Unit\": \"%\"");
    content +=F( "},");
    
    content +=F( "\"WLANServerSSID\": \"");
    content += String(actconf.sssid);
    content +=F( "\",");
    content +=F( "\"WLANServerIP\": \"");
    content += WiFi.softAPIP().toString();
    content +=F( "\",");
    content +=F( "\"ServerMode\": ");
    content += String(actconf.serverMode);
    content +=F( ",");
    content +=F( "\"ServerHostName\": \"");
    content += String(actconf.hostname);
    content +=F( "\"");
    content +=F( "},");

    content +=F( "\"LoRaSettings\": {");
    
    content +=F( "\"DeviceAddress\": \"");
    String mystring = String(actconf.devaddr, HEX);
    mystring.toUpperCase();
    content += String(mystring);
    content +=F( "\",");
    content +=F( "\"Frequency\": \"");
    content += String(actconf.lorafrequency);
    content +=F( "\",");
    content +=F( "\"Channel\": ");
    content += String(actconf.lchannel);
    content +=F( ",");
    content +=F( "\"ActualChannel\": ");
    content += String(LMIC.txChnl);
    content +=F( ",");
    content +=F( "\"SpreadingFactor\": ");
    content += String(actconf.spreadf);
    content +=F( ",");
    content +=F( "\"ActualSF\": ");
    content += String(sf);
    content +=F( ",");
    content +=F( "\"DynamicSF\": ");
    content += String(actconf.dynsf);
    content +=F( ",");
    content +=F( "\"TXInterval\": ");
    content += String(actconf.tinterval);
    content +=F( ",");
    content +=F( "\"TimeSlot\": ");
    content += String(slot);
    content +=F( ",");
    content +=F( "\"TXCounter\": ");
    content += String(counter16 - 1);
    content +=F( ",");    
    content +=F( "\"Relay\": \"");
    content += String(actconf.relay);
    content +=F( "\"");
    
    content +=F( "},");
    
    
    content +=F( "\"DisplaySettings\": {");
    
    content +=F( "\"Skin\": ");
    content += String(actconf.skin);
    content +=F( ",");
    content +=F( "\"InstrumentSize\": \"");
    content += String(actconf.instrumentSize);
    content +=F( "\"");
    
    content +=F( "},");
    
    content +=F( "\"DeviceSettings\": {");
    
    content +=F( "\"SerialDebugMode\": ");
    content += String(actconf.serverMode);
    content +=F( ",");
    content +=F( "\"SerialSpeed\": ");
    content += String(actconf.serspeed);
    content +=F( ",");
    content +=F( "\"DeviceID\": ");
    content += String(actconf.deviceID);
    content +=F( ",");
    content +=F( "\"DeviceType\": \"");
    content += String(actconf.deviceType);
    content +=F( "\",");
    content +=F( "\"SendData\": ");
    content += String(actconf.senddata);
    content +=F( ",");
    
    content +=F( "\"VoltageOffset\": ");
    content += String(actconf.voffset, 4);
    content +=F( ",");
    content +=F( "\"VoltageSlopeA1\": ");
    content += String(actconf.a1vslope, 4);
    content +=F( ",");
    content +=F( "\"VoltageSlopeA2\": ");
    content += String(actconf.a2vslope, 4);
    content +=F( ",");
    content +=F( "\"VoltageAverage\": ");
    content += String(actconf.vaverage);
    content +=F( ",");

    content +=F( "\"Tank1Offset\": ");
    content += String(actconf.t1offset, 4);
    content +=F( ",");
    content +=F( "\"Tank1SlopeA1\": ");
    content += String(actconf.a1t1slope, 4);
    content +=F( ",");
    content +=F( "\"Tank1SlopeA2\": ");
    content += String(actconf.a2t1slope, 4);
    content +=F( ",");
    content +=F( "\"Tank1Average\": ");
    content += String(actconf.t1average);
    content +=F( ",");

    content +=F( "\"Tank2Offset\": ");
    content += String(actconf.t2offset, 4);
    content +=F( ",");
    content +=F( "\"Tank2SlopeA1\": ");
    content += String(actconf.a1t2slope, 4);
    content +=F( ",");
    content +=F( "\"Tank2SlopeA2\": ");
    content += String(actconf.a2t2slope, 4);
    content +=F( ",");
    content +=F( "\"Tank2Average\": ");
    content += String(actconf.t2average);
    content +=F( ",");

    content +=F( "\"TempSensorType\": \"");
    content += String(actconf.tempSensorType);
    content +=F( "\",");
    content +=F( "\"TempUnit\": \"");
    content += String(actconf.tempUnit);
    content +=F( "\",");

    content +=F( "\"envSensor\": \"");
    content += String(actconf.envSensor);
    content +=F( "\"");
    
    content +=F( "},");
    
    content +=F( "\"MeasuringValues\": {");
    
    content +=F( "\"AirTemperature\": {");
    content +=F( "\"Value\": ");
    content += String(temperature, 1);
    content +=F( ",");
    content +=F( "\"Unit\": \"°");
    content += String(actconf.tempUnit);
    content +=F( "\"");
    content +=F( "},");

    content +=F( "\"AirPressure\": {");
    content +=F( "\"Value\": ");
    content += String(pressure, 0);
    content +=F( ",");
    content +=F( "\"Unit\": \"mbar\"");
    content +=F( "},");

    content +=F( "\"AirHumidity\": {");
    content +=F( "\"Value\": ");
    content += String(humidity, 0);
    content +=F( ",");
    content +=F( "\"Unit\": \"%\"");
    content +=F( "},");

    content +=F( "\"Dewpoint\": {");
    content +=F( "\"Value\": \"");
    content += String(dewp, 1);
    content +=F( "\",");
    content +=F( "\"Unit\": \"°");
    content += String(actconf.tempUnit);
    content +=F( "\"");
    content +=F( "},");

    content +=F( "\"Temp1Wire\": {");
    content +=F( "\"Value\": ");
    content += String(temp1wire, 1);
    content +=F( ",");
    content +=F( "\"Unit\": \"°");
    content += String(actconf.tempUnit);
    content +=F( "\"");
    content +=F( "},");

    content +=F( "\"BatteryVoltage\": {");
    content +=F( "\"Value\": ");
    content += String(voltage, 3);
    content +=F( ",");
    content +=F( "\"Unit\": \"V\"");
    content +=F( "},");

    content +=F( "\"BatteryCapacity\": {");
    content +=F( "\"Value\": ");
    content += String(capacity, 0);
    content +=F( ",");
    content +=F( "\"Unit\": \"%\"");
    content +=F( "},");

    content +=F( "\"Tank1Voltage\": {");
    content +=F( "\"Value\": ");
    content += String(tank1, 3);
    content +=F( ",");
    content +=F( "\"Unit\": \"V\"");
    content +=F( "},");

    content +=F( "\"Tank2Voltage\": {");
    content +=F( "\"Value\": ");
    content += String(tank2, 3);
    content +=F( ",");
    content +=F( "\"Unit\": \"V\"");
    content +=F( "},");

    content +=F( "\"Tank1\": {");
    content +=F( "\"Value\": ");
    content += String(tank1p, 0);
    content +=F( ",");
    content +=F( "\"Unit\": \"%\"");
    content +=F( "},");

    content +=F( "\"Tank2\": {");
    content +=F( "\"Value\": ");
    content += String(tank2p, 0);
    content +=F( ",");
    content +=F( "\"Unit\": \"%\"");
    content +=F( "},");

    content +=F( "\"Alarm\": {");
    content +=F( "\"Value\": ");
    content += String(alarm1);
    content +=F( ",");
    content +=F( "\"Unit\": \"bin\"");
    content +=F( "},");

    content +=F( "\"Relay\": {");
    content +=F( "\"Value\": ");
    content += String(actconf.relay);
    content +=F( ",");
    content +=F( "\"Unit\": \"bin\"");
    content +=F( "},");

    content +=F( "\"RelayTimer\": {");
    content +=F( "\"Value\": ");
    content += String(int(relaytimer * 5));
    content +=F( ",");
    content +=F( "\"Unit\": \"x5min\"");
    content +=F( "},");

    content +=F( "\"EnvSensor\": {");
    content +=F( "\"Value\": \"");
    content += String(actconf.envSensor);
    content +=F( "\",");
    content +=F( "\"Unit\": \"\"");
    content +=F( "},");

    content +=F( "\"VEdirectV\": {");
    content +=F( "\"Value\": ");
    content += String(vedirectVoltage, 3);
    content +=F( ",");
    content +=F( "\"Unit\": \"V\"");
    content +=F( "},");

    content +=F( "\"VEdirectC\": {");
    content +=F( "\"Value\": ");
    content += String(vedirectCurrent, 2);
    content +=F( ",");
    content +=F( "\"Unit\": \"A\"");
    content +=F( "},");
    
    content +=F( "\"VEdirectT\": {");
    content +=F( "\"Value\": ");
    content += String(vedirectTemp, 1);
    content +=F( ",");
    content +=F( "\"Unit\": \"°C\"");
    content +=F( "},");

    content +=F( "\"Latitude\": {");
    content +=F( "\"Value\": ");
    content += String(latitude, 6);
    content +=F( ",");
    content +=F( "\"Unit\": \"");
    content += String(latitudeNS);
    content +=F( "\"");
    content +=F( "},");

    content +=F( "\"Longitude\": {");
    content +=F( "\"Value\": ");
    content += String(longitude, 6);
    content +=F( ",");
    content +=F( "\"Unit\": \"");
    content += String(longitudeEW);
    content +=F( "\"");
    content +=F( "},");
    
    content +=F( "\"Altitude\": {");
    content +=F( "\"Value\": ");
    content += String(altitude, 0);
    content +=F( ",");
    content +=F( "\"Unit\": \"m\"");
    content +=F( "},");

    content +=F( "\"Time\": {");
    content +=F( "\"Value\": ");

    String zhour = firstzero(hour);
    String zminute = firstzero(minute);
    String zsecond = firstzero(second);
    
    String timestr = "\"" + String(zhour) + ":" + String(zminute) + ":" + String(zsecond) + "\"";
    content += String(timestr);
    content +=F( ",");
    content +=F( "\"Unit\": \"UTC\"");
    content +=F( "},");

    String zday = firstzero(day);
    String zmonth = firstzero(month);
    String zyear = firstzero(year);

    content +=F( "\"Date\": {");
    content +=F( "\"Value\": ");
    String datestr = "\"" + String(zday) + "." + String(zmonth) + "." + String(zyear) + "\"";
    content += String(datestr);
    content +=F( ",");
    content +=F( "\"Unit\": \"GMT\"");
    content +=F( "},");

    content +=F( "\"Sunrise\": {");
    content +=F( "\"Value\": ");
    String sunrisestr = "\"" + String(zhour) + ":" + String(zminute) + ":" + String(zsecond) + "\"";
    content += String(sunrisestr);
    content +=F( ",");
    content +=F( "\"Unit\": \"UTC\"");
    content +=F( "},");

    content +=F( "\"Sunset\": {");
    content +=F( "\"Value\": ");
    String sunsetstr = "\"" + String(zhour) + ":" + String(zminute) + ":" + String(zsecond) + "\"";
    content += String(sunsetstr);
    content +=F( ",");
    content +=F( "\"Unit\": \"UTC\"");
    content +=F( "},");

    content +=F( "\"Speed\": {");
    content +=F( "\"Value\": ");
    content += String(gpsspeed);
    content +=F( ",");
    content +=F( "\"Unit\": \"kn\"");
    content +=F( "},");

    content +=F( "\"Course\": {");
    content +=F( "\"Value\": ");
    content += String(course);
    content +=F( ",");
    content +=F( "\"Unit\": \"°\"");
    content +=F( "}");
    
    content +=F( "},");
    
    content +=F( "\"NMEAValues\": {");
    content +=F( "\"String1\": \"");
    content += sendXDR1(0);
    content +=F( "\",");
    content +=F( "\"String2\": \"");
    content += sendXDR2(0);
    content +=F( "\",");
    content +=F( "\"String3\": \"");
    content += sendXDR3(0);
    content +=F( "\",");
    content +=F( "\"String4\": \"");
//    content += "";
    content +=F( "\",");
    content +=F( "\"String5\": \"");
//    content += "";
    content +=F( "\"");
    content +=F( "}");
    content +=F( "}");
    content +=F( "}");
    
    return content;
}
