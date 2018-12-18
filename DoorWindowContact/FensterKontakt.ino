#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>

//Your MQTT Broker
const char* mqtt_server = "192.168.xx.xx";
const char* mqtt_user = "aaaaaa";
const char* mqtt_passwd = "bbbbbb";
const char* mqtt_topic = "Fenster_01";
const char* mqtt_ClientID = "Sensor01";
  

//Your Wifi SSID
const char* ssid = "cccccc";
//Your Wifi Key
const char* password = "dddddd";
//after this line there is no need to edit
//message to send is: snprintf (msg, 30, "%s:,%s,VCC: %1.2fV", mqtt_ClientID, sensorValue3, volt)

ESP8266WebServer server(80);

WiFiClient espClient;
PubSubClient client(espClient);

int Input3 = 3;     //the RX pin is the input!!!
int Voltage = 0;    //GPIO0 is to hold the voltage
int sensorValue3 = 0;
int Abort = 0;
char msg[30];
float volt = 0;

ADC_MODE(ADC_VCC);


void setup(void)
{
  pinMode(Voltage, OUTPUT);
  digitalWrite(Voltage, 0);      // own voltage on
  pinMode(Input3, INPUT);
  delay(2000);      //wait for door or window is sure open or closed
  sensorValue3 = digitalRead(Input3);
  delay(100);
  Serial.begin(115200); 
  Serial.println("");
 //connect to WIFI
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  // Wait for WiFi
  Serial.println("");
  Serial.print("Connecting to:  ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
    Abort++;
    if(Abort > 20)
    {
      digitalWrite(Voltage, 1);      // own voltage off
      delay(10);
      ESP.deepSleep(0);
    }
  }
  
  Serial.println("");
  Serial.print("IP-Adress: ");
  Serial.println(WiFi.localIP());
//connect to mqtt broker
  client.setServer(mqtt_server, 1883);

  Serial.println("");
  Abort = 0;
  while (!client.connected()) 
  {
    if (client.connect(mqtt_ClientID, mqtt_user, mqtt_passwd)) 
    {
      delay(10);
      Abort++;
      if(Abort > 200)
      {
        digitalWrite(Voltage, 1);      // own voltage off
        delay(10);
        ESP.deepSleep(0);
      }
    }     
  }
  volt = ESP.getVcc()/1000.0;
  snprintf (msg, 30, "%s:,%1d,VCC: %1.2f V", mqtt_ClientID, sensorValue3, volt);
  Serial.println(msg);
  client.publish(mqtt_topic, msg);    
  delay(500);
  digitalWrite(Voltage, 1);      // own voltage off
  delay(10);
  ESP.deepSleep(0);
  }

void loop(void){
}

 
