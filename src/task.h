
//Task1code LoRa
void Task1code( void * pvParameters ){
  while(1){
    os_runloop_once();  // LoRa code
    delay(20);          // We need a delay! Without is it not working!
  }
}

