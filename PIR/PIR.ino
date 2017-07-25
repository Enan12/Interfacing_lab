volatile byte intruder;
void setup()
{
  Serial.begin(115200);
  pinMode(4, INPUT);
  attachInterrupt(2, intruder_detect, RISING);//Initialize the intterrupt pin for the motion sensor (Arduino digital pin 2)
  intruder = 0;
}
void loop()
{
  if(digitalRead(4)==HIGH) Serial.println("gotcha");
  else Serial.println("nope");
}
void intruder_detect()//This function is called whenever an intruder is detected by the arduino
{
  intruder++;
  Serial.println("Intruder detected");
}
