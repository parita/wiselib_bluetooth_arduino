#include <SoftwareSerial.h>   //Software Serial Port
#define RxD 8
#define TxD 9
 
#define DEBUG_ENABLED  1
 
#define DATARATE 38400

SoftwareSerial bSerial(RxD,TxD);
/*
String retSymb = "+RTINQ=";//start symble when there's any return
String slaveName = ";BTSlave";//Set the Slave name ,caution that ';'must be included
int nameIndex = 0;
int addrIndex = 0;
 
String recvBuf;
String slaveAddr;
 
String connectCmd = "\r\n+CONN=";
 */
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
    /*
    char recvChar;
    while(1){
    if(bSerial.available()){
      recvChar = bSerial.read();
      Serial.print(recvChar);
      recvBuf += recvChar;
      nameIndex = recvBuf.indexOf(slaveName);//get the position of slave name
      //nameIndex -= 1;//decrease the ';' in front of the slave name, to get the position of the end of the slave address
      if ( nameIndex != -1 ){
        //Serial.print(recvBuf);
 	addrIndex = (recvBuf.indexOf(retSymb,(nameIndex - retSymb.length()- 18) ) + retSymb.length());//get the start position of slave address	 		
 	slaveAddr = recvBuf.substring(addrIndex, nameIndex);//get the string of slave address 			
 	break;
      }
    }
  }
  //form the full connection command
  connectCmd += slaveAddr;
  connectCmd += "\r\n";
  int connectOK = 0;
  Serial.print("Connecting to slave:");
  Serial.print(slaveAddr);
  Serial.println(slaveName);
  //connecting the slave till they are connected
  do{
    bSerial.print(connectCmd);//send connection command
    recvBuf = "";
    while(1){
      if(bSerial.available()){
        recvChar = bSerial.read();
 	recvBuf += recvChar;
 	if(recvBuf.indexOf("CONNECT:OK") != -1){
          connectOK = 1;
 	  Serial.println("Connected!");
 	  bSerial.print("Connected!");
 	  break;
 	}else if(recvBuf.indexOf("CONNECT:FAIL") != -1){
 	  Serial.println("Connect again!");
 	  break;
 	}
      }
    }
  }while(0 == connectOK);*/
}
 
void sendBlueToothCommand(char command[])
{
    bSerial.print(command);
    while(bSerial.available())
      Serial.write(bSerial.read());

    delay(1000);
}
