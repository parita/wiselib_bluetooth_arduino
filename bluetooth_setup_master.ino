#include <SoftwareSerial.h>   //Software Serial Port
#define RxD 8
#define TxD 9
 
#define DEBUG_ENABLED  1
 
#define DATARATE 38400

SoftwareSerial bSerial(RxD,TxD);

void terminal(){
  if(bSerial.available())
    Serial.write(bSerial.read());
}

void setup() 
{ 
  Serial.begin(9600);
    bSerial.begin(DATARATE);
    setupBlueToothConnection();
} 
 
void loop() 
{
  
}  
 
void setupBlueToothConnection()
{
  sendBlueToothCommand("\r\n+STWMOD=1\r\n");			//Set as master
    sendBlueToothCommand("\r\n+STNA=BTMaster\r\n");		//set name as 'BTMaster'
    sendBlueToothCommand("\r\n+STPIN=0000\r\n");		//set pin as '0000'
    sendBlueToothCommand("\r\n+STAUTO=0\r\n");			// don't permit auto-connect
    sendBlueToothCommand("\r\n+STOAUT=1\r\n");
    sendBlueToothCommand("\r\n+STBD=9600\r\n");		//Set baud rate as 9600
    delay(2000); // This delay is required.
    sendBlueToothCommand("\r\n+INQ=1\r\n");
    Serial.print("Master is inquiring");
    delay(2000); // This delay is required.
   
}
 
void sendBlueToothCommand(char command[])
{
    bSerial.print(command);
    while(bSerial.available())
      Serial.write(bSerial.read());

    delay(1000);
}
