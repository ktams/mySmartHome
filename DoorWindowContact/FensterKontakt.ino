#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>

//Your MQTT Broker
const char* mqtt_server = "192.168.178.48";
const char* mqtt_user = "openhabian";
const char* mqtt_passwd = "Rilly123";
const char* mqtt_topic = "EG/WZ/Fenster";
const char* mqtt_ClientID = "Sensor01";
	

//Yout Wifi SSID
const char* ssid = "TamsHome2";
//Your Wifi Key
const char* password = "wssd3_11_89v";
//after this line there is no need to edit

ESP8266WebServer server(80);

WiFiClient espClient;
PubSubClient client(espClient);

int Input3 = 3;
int sensorValue3 = 0;
char msg[20];


void setup(void)
{
  pinMode(Input3, INPUT_PULLUP);
  delay(1000);      //wait for door or window is sure open or closed
  sensorValue3 = digitalRead(Input3);
  Serial.begin(9600); 
  Serial.println("");
 //connect to WIFI
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  // Wait for WiFi
  Serial.println("");
  Serial.print("VConnecting to:  ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("IP-Adress: ");
  Serial.println(WiFi.localIP());
//connect to mqtt broker
  client.setServer(mqtt_server, 1883);
 
  while (!client.connected()) 
  {
    if (client.connect(mqtt_ClientID, mqtt_user, mqtt_passwd)) 
    {
       client.subscribe(mqtt_topic);
    }     
  }

  snprintf (msg, 20, "%s: %s", mqtt_ClientID, sensorValue3 ? "0" : "1");
  Serial.println(msg);
  client.publish(mqtt_topic, msg);    
  delay(500);
  ESP.deepSleep(0);
  }

void loop(void){
}

 
