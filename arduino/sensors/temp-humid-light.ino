//http://howtomechatronics.com/tutorials/arduino/arduino-and-hc-05-bluetooth-module-tutorial/
//https://create.arduino.cc/projecthub/attari/temperature-monitoring-with-dht22-arduino-15b013

/** Strict format of output
 *  String JSON {"Key":"value"}
 *  Valid Keys:
 *    - Humidity
 *    - Temp
 *    - Light_a
 *    - Light_d
 *    - Motion
 *  All keys are NOT needed and order does NOT matter.
 *  E.g.:
 *  {"Humidity":"val","Light_a":"val","Light_d":"val","Temp":"val","Motion":"val"}
 */

#include <DHT.h>

#define DHTPIN 8
#define DHTTYPE DHT22

#define PHOTOA_PIN A0
#define PHOTOD_PIN 7

DHT dht(DHTPIN, DHTTYPE);

int state = 0;

float hum;
float temp;
int lightA;
int lightD;

void setup() {
  Serial.begin(9600);

  dht.begin();

  pinMode(PHOTOD_PIN, INPUT);
}

void loop() {
  delay(1000);
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  lightA = analogRead(PHOTOA_PIN);
  lightD = digitalRead(PHOTOD_PIN);
  Serial.print("{\"Humidity\":\"");
  Serial.print(hum);
  Serial.print("\",\"Temp\":\"");
  Serial.print(temp);
  Serial.print("\",\"Light_a\":\"");
  Serial.print(lightA);
  Serial.print("\",\"Light_d\":\"");
  Serial.print(lightD);
  Serial.print("\",\"Motion\":\"");
  Serial.println("\"}");
}
