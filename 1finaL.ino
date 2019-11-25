 #include <SoftwareSerial.h>

SoftwareSerial mySerial(14, 15);
int led = 13;  // the pin that the LED is atteched to  #buzzer

int pir_led = 12;
int ultra_led = 11;
int sensor = 2;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)
#define trigPin 5
#define echoPin 6

void setup() {
  Serial.begin (9600);
  mySerial.begin(9600); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
        
}


void loop()
{ ultra();
  pir();
 
}


void pir(){
  int sensor = digitalRead(sensor);
  if (sensor == 1) {
    Serial.println("motion detected");
    digitalWrite(led, HIGH);
    digitalWrite(pir_led,HIGH);
    else{
    digitalWrite(led, LOW);
    digitalWrite(pir_led,LOW);
    }
    gsms();

  }}

void ultra(){
   long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  if (distance <= 50 ){
    digitalWrite(led, HIGH);
    digitalWrite(ultra_led,HIGH);
    gsms();
    
    Serial.println(distance);
    Serial.println("cm");
  }
  else {
    Serial.print(distance);
    Serial.println("cm, out of range");
    digitalWrite(led, LOW);
    digitalWrite(ultra_led,LOW);
  }
  delay(500);
  


 
  }

  void gsms()
  {
    if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     mySerial.println("AT+CMGS=\"+919981867769\"\r"); // Replace x with mobile number
     delay(1000);
     mySerial.println("Abnormal activity detected");// The SMS text you want to send
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
      break;



      
    case 'r':
      mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
      delay(1000);
      break;
  }

 if (mySerial.available()>0)
   Serial.write(mySerial.read());
}
