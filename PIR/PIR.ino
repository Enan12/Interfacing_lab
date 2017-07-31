volatile byte intruder;
void setup()
{
  Serial.begin(9600);
  pinMode(A7, INPUT);
}
void loop()
{
  Serial.println(analogRead(A7));
}
