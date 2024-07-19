float lightSensor()
{
  float LDRValue = map(analogRead(A3), 1000, 200, 0, 400);
  return(LDRValue);
}