#include <SoftwareSerial.h>
SoftwareSerial ArduinoUno(10,11);
char c;
String dataIn;
void setup() 
{
  Serial.begin(57600);
	ArduinoUno.begin(9600);
}

void loop() 
{ 
  ArduinoUno.print("1");
  ArduinoUno.print("/");
  ArduinoUno.print(tempSensor());
  ArduinoUno.print("/");
  ArduinoUno.print(salinitySensor());
  ArduinoUno.print("/");
  ArduinoUno.print(turbiditySensor());
  ArduinoUno.print("/");
  ArduinoUno.print(phSensor());
  ArduinoUno.print("/");
  ArduinoUno.print(lightSensor());
  ArduinoUno.println(" \n"); 
  delay(5000);
}
