#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h> 

const char *ssid =  "***************";
const char *pass =  "***************";

const char* host = "http://us-central1-iot-workshop-w2021.cloudfunctions.net";
String url = "/changeData/";

int buttonPin = 16;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  delay(10);
               
  Serial.println("Connecting to: ");
  Serial.println(ssid); 

  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, pass); 
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
  Serial.print("Host: ");
  Serial.println(host); // Use WiFiClient class to create TCP connections
}

void doIncrementNumber(int num){
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  Serial.print("Requesting URL: "); 
  Serial.println(url); //Post Data 
  String postData = "num=" + String(num); 
  String address = host + url; 
  HTTPClient http; 
  http.begin(address); 
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
  auto httpCode = http.POST(postData); 
  Serial.println(httpCode); // Print HTTP return code
  String payload = http.getString(); 
  Serial.println(payload); // Print request response payload
  http.end(); // Close connection
  Serial.println("closing connection");
}

int buttonState = 0;
int x = 1;
void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.println("PRESSED");
    doIncrementNumber(x++);
    delay(500);
    if (digitalRead(buttonPin)){
      x = 0;
    }
  }
}
