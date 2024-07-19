#include <SoftwareSerial.h>
#include <Wire.h>

SoftwareSerial NodeMCU(D1, D2);

char c;
String dataIn;
float sensordata[6];
int i=0;

const int ledPin = 13;


void setup()
  {
  Serial.begin(57600);
  NodeMCU.begin(9600); // Set the baud rate to match the Arduino Uno
  setupWIFI();
  timeSetup();
  }

void loop() 
{ // Read data from Arduino Uno and print to serial monitor
  checkConnection();
  while (NodeMCU.available() > 0) 
  {
    c = NodeMCU.read();
    if(c == '\n') {break;}
    else          {dataIn += c;}
  }

  if(c == '\n') 
  {
    String time = getTime("time");
    String date = getTime("date");
    splitData(dataIn,"/",sensordata, 6);
    // Display the array elements
    if (sensordata[0] == 1){
      Serial.println("Data Received: ");
      Serial.println(date + ", " + time);
      for (int i = 1; i < 6; i++) {
        Serial.println(sensordata[i]);
      }
      sendData(sensordata, time, date);
      Serial.println("\n");
    }     
    c=0;
    dataIn ="";
  }
  //delay(3000);
}
