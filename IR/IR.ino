int obstacle= 7;
int LED=13;
int obstacleCheck= HIGH;

void setup() {
  // put your setup code here, to run once:
  pinMode(obstacle,INPUT);
  pinMode(LED,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  obstacleCheck= digitalRead(obstacle);
  if(obstacleCheck==LOW){
      Serial.println("Medecine Despensing");
      //digitalWrite(LED,HIGH);
    }
    else{
        Serial.println("CLEAR");
       // digitalWrite(LED,LOW);
      }
  delay(300);
}
