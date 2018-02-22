#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>

//Your MQTT Broker
const char* mqtt_server = "xxx.yyy.aaa.bbb";
const char* mqtt_user = "mqqt-user";
const char* mqtt_passwd = "secret";
const char* mqtt_topic = "topic_01";
const char* mqtt_intopic = "Back_01";
const char* mqtt_ClientID = "B01";
	

//Yout Wifi SSID
const char* ssid = "yourssid";
//Your Wifi Key
const char* password = "yourpasswd";
//after this line there is no need to edit

ESP8266WebServer server(80);

WiFiClient espClient;
PubSubClient client(espClient);

int Input3 = 3;     //the RX pin is the input!!!
int sensorValue3 = 0, oldValue3 = 0, tmp = 10, val = 0, bBestg = 0;
char msg[40];
String str1, str2, Meldung;


void setup(void)
{
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
      if(tmp)
      {
        tmp--;
      }
      else
      {
        snprintf (msg, 20,"%s: ", ssid, " failed");
        Serial.println(msg);
        break;
      }
  }
  tmp = 10;
  Serial.println("");
  Serial.print("IP-Adress: ");
  Serial.println(WiFi.localIP());
//connect to mqtt broker
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  while (!client.connected()) 
  {
    if (client.connect(mqtt_ClientID, mqtt_user, mqtt_passwd)) 
    {
       client.subscribe(mqtt_intopic);
    }
    else
    {
      if(tmp)
      {
        Serial.print("*");
        tmp--;
      }
      else
      {
        Serial.println("No broker -> break");
        break;
      }
    }
  }

  Serial.println("switching to motion dectector...");
  delay(100);
  pinMode(Input3, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  }
  
void reconnect() {
  while (!client.connected()) 
  {
    if (client.connect(mqtt_ClientID, mqtt_user, mqtt_passwd)) 
    {
       client.subscribe(mqtt_intopic);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  str1 = String(topic);
  str2 = String(mqtt_intopic);
  if(str1 == str2)
  {
    bBestg = 0;
  }
}

void loop(void){
  if(bBestg)
  {
    client.publish(mqtt_topic, msg);
    delay(1000);
  }
  sensorValue3 = digitalRead(Input3);
  if(sensorValue3 != oldValue3)
  {
    bBestg = 1;
    oldValue3 = sensorValue3;
    if (!client.connected()) {
       reconnect();
    }
    snprintf (msg, 20, "%s: %s", mqtt_ClientID, (sensorValue3 == 0) ? "0" : "1");
    client.publish(mqtt_topic, msg);
    Meldung = String(msg);
    delay(100);
  }
  client.loop();    
  delay(100);
}

 
