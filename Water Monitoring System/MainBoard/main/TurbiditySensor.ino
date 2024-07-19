float turbiditySensor()
{
  float sensorValue = map(analogRead(A0), 27.00, 653.00, 100, 0);// read the input on analog pin 0:
  if (sensorValue < 0){sensorValue = 0;}
  return(sensorValue);
}