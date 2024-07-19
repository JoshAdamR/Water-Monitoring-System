#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
// Provide the token generation process info.
#include "addons/TokenHelper.h"

#define DATABASE_URL "aquacare-7ab95-default-rtdb.asia-southeast1.firebasedatabase.app"
//Your Firebase Project URL goes here without "http:" , "\" and "/"
#define DATABASE_SECRET "4qnDsWff5MFsIjjezohgHhTgFIS69OCQFUWJ7otq" 
#define API_KEY "AIzaSyDPU0D-U3j6yBHpWee2oczq_yf27D2LSKM"
//Your Firebase Database Secret goes here
#define WIFI_SSID "isaingaranku123"                                              
//WiFi SSID to which you want NodeMCU to connect
#define WIFI_PASSWORD "joshua123"                                      
//Password of your wifi network 
// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "joshua.adampin@gmail.com"
#define USER_PASSWORD "12345678" 

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;

// Database main path (to be updated in setup with the user UID)
String databasePath;
String realtime;
String realtimePath;
// Database child nodes
String tempPath = "/Temperature(C)";
String salPath = "/Salinity(PSU)";
String turbPath = "/Turbidity(NTU)";
String phPath = "/pH";
String lightPath = "/LightIntensity(LUX)";
String timePath = "/date";
String datePath = "/time";

// Parent Node (to be updated in every loop)
String parentPath;

FirebaseJson json;
FirebaseJson json2;

void setupWIFI() 
{       
  Serial.println("Connecting to ");
  Serial.println(WIFI_SSID); 
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  checkConnection();  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());//print local IP address
  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  // Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config, &auth);

  // Getting the user UID might take a few seconds
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);

  // Update database path
  databasePath = "/System/System1";
  delay(1000);
}

void checkConnection(){
  while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
}

void sendData(float sensorData[6], String time, String date)
{ 
  // Send new readings to database
  if (Firebase.ready())
  {
    realtime = "/RSystem/System1";
    //realtimePath = realtime + "/System1/" + time + ", " + date;
    int i = 0;
    parentPath = databasePath + "/" + time + ", " + date;
    json.set(tempPath.c_str(), sensorData[1]);
    json.set(salPath.c_str(), sensorData[2]);
    json.set(turbPath.c_str(), sensorData[3]);
    json.set(phPath.c_str(), sensorData[4]);
    json.set(lightPath.c_str(), sensorData[5]);
    json.set(datePath.c_str(), date);
    json.set(timePath.c_str(), time);
    json2.set("System1", time + ", " + date);
    json2.set("System2", time + ", " + date);
    json2.set("System3", time + ", " + date);
    json2.set("System4", time + ", " + date);
    if (i == 60) {
      Serial.printf("Set json... %s\n", Firebase.setJSON(fbdo, parentPath.c_str(), json) ? "ok" : fbdo.errorReason().c_str());
      i = 0;
    }
    else {
      //Serial.printf("Set json... %s\n", Firebase.setJSON(fbdo, realtime, json2) ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Set json... %s\n", Firebase.setJSON(fbdo, realtime.c_str(), json) ? "ok" : fbdo.errorReason().c_str());
      i++;
    }
  }
}