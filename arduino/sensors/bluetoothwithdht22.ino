//http://howtomechatronics.com/tutorials/arduino/arduino-and-hc-05-bluetooth-module-tutorial/
//https://create.arduino.cc/projecthub/attari/temperature-monitoring-with-dht22-arduino-15b013

#include <DHT.h>

#define ledPin 13
#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
int state = 0;

int chk;
float hum;
float temp;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);

  dht.begin();
}

void loop() {
  if (Serial.available() > 0) {
    state = Serial.read();
  }

  if (state == '1') {
    digitalWrite(ledPin, LOW);
    Serial.println("LED: OFF");
  }
  else if (state == '2') {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED: ON");
    delay(2000);
    hum = dht.readHumidity();
    temp = dht.readTemperature();
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.print(" Celcius");    
  }
}
