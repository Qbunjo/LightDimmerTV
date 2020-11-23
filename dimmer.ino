
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>

const char* ssid     = "SSID";
const char* password = "PASS";

const IPAddress tv_ip(192, 168, 0, 90); //TV IP
bool curState;
int lowLight = 255;
int highLight = 1023;
int pin = 2;
bool dimDone = 1;

void lightsUp() {
  for (int i = lowLight; i < highLight; i++) {
    analogWrite(pin, i);
       Serial.println(i);
    delay(10);
  }
  analogWrite(pin, 1024);
     dimDone=0;

}

void dim() {
  for (int i = highLight; i >= lowLight; i--) {
    analogWrite(pin, i);
    Serial.println(i);
    delay(10);
  }
  dimDone=1;
  }
void setup() {
//  pinMode(2, OUTPUT);
  Serial.begin(115200);
  analogWrite(pin, lowLight);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println("Connecting to WiFi");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("WiFi connected with ip ");
  Serial.println(WiFi.localIP());

  curState = Ping.ping(tv_ip);
  Serial.println("First check:");
  Serial.println(curState);
  if (curState == 0) {
    Serial.println("TV off. Lights up.");
    lightsUp();
  } else {
    Serial.println("TV on. Dimming ");
    dim();
  }
}
void loop() {
  Serial.print("Pinging ip ");
  Serial.println(tv_ip);
  curState = Ping.ping(tv_ip);
  Serial.print("Current tv state: ");
  Serial.println(curState);
  Serial.print("Light dimmed: ");
  Serial.println(dimDone);
  if (curState == 0 and dimDone==1) {
    Serial.println("TV off. Lights up.");
    lightsUp();
    Serial.println(curState);
  } else if (curState == 1 and dimDone==0) {
    Serial.println("TV on. Dimming ");
    dim();
    Serial.println(curState);
  }
  //delay(100);
}
