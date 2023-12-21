/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-gps
 */

#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <TinyGPS++.h>
#include <WiFiClientSecure.h>
// ... rest of your includes and definitions ...


#define GPS_BAUDRATE 9600  // The default baudrate of NEO-6M is 9600
#define SS_PIN    5  // Slave Select pin
#define RST_PIN   27 // Reset pin

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
TinyGPSPlus gps;  // The TinyGPS++ object
WiFiClientSecure espClient;
PubSubClient client(espClient);

const char* ssid = "";     // Replace with your network's SSID
const char* password = ""; // Replace with your network's password

const char* mqtt_server = "";
const int mqtt_port = 8883;
const char* mqtt_user = ""; // If applicable
const char* mqtt_password = ""; // If applicable

static const char *root_ca PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";

void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
  Serial2.begin(GPS_BAUDRATE);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  espClient.setCACert(root_ca);
  client.setServer(mqtt_server, mqtt_port);
  
  Serial.println(F("ESP32 - GPS module"));
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

int timer = 0;

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Read and publish GPS data every 10 seconds
  if(millis() - timer > 10000){
    if (Serial2.available() > 0) {
      if (gps.encode(Serial2.read())) {
        if (gps.location.isValid()) {
          Serial.print(F("- latitude: "));
          Serial.println(gps.location.lat(), 6);

          Serial.print(F("- longitude: "));
          Serial.println(gps.location.lng(), 6);

          Serial.print(F("- altitude: "));
          if (gps.altitude.isValid())
            Serial.println(gps.altitude.meters());
          else
            Serial.println(F("INVALID"));
        } else {
          Serial.println(F("- location: INVALID"));
        }

        Serial.print(F("- speed: "));
        if (gps.speed.isValid()) {
          Serial.print(gps.speed.kmph());
          Serial.println(F(" km/h"));
        } else {
          Serial.println(F("INVALID"));
        }

        Serial.print(F("- GPS date&time: "));
        if (gps.date.isValid() && gps.time.isValid()) {
          Serial.print(gps.date.year());
          Serial.print(F("-"));
          Serial.print(gps.date.month());
          Serial.print(F("-"));
          Serial.print(gps.date.day());
          Serial.print(F(" "));
          Serial.print(gps.time.hour());
          Serial.print(F(":"));
          Serial.print(gps.time.minute());
          Serial.print(F(":"));
          Serial.println(gps.time.second());
        } else {
          Serial.println(F("INVALID"));
        }
        
        char iso8601Time[25];
        sprintf(iso8601Time, "%04d-%02d-%02dT%02d:%02d:%02dZ", 
                gps.date.year(), gps.date.month(), gps.date.day(),
                gps.time.hour(), gps.time.minute(), gps.time.second());

        String payload = "{ \"latitude\": " + String(gps.location.lat(), 6) 
                      + ", \"longitude\": " + String(gps.location.lng(), 6)
                      + ", \"time\": " + "\"" + String(iso8601Time) + "\""
                      //+ ", 'trackerId': " + String(ESP.getChipId())
                      + " }";
        client.publish("gps", payload.c_str());
        timer = millis();
        Serial.println();
      }
    }
  }
  
  // Check for new RFID card
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String rfidTagId = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      rfidTagId.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      rfidTagId.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    rfidTagId.toUpperCase();
    client.publish("rfid", rfidTagId.c_str());
    Serial.println("RFID Tag UID: " + rfidTagId);

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }

  // GPS error check (optional)
  
}
