#include <WiFi.h>
#include <FirebaseESP32.h>

#define WIFI_SSID "Oalis" // nome da rede wifi
#define WIFI_PASSWORD "oalis636807" // senha da rede wifi

#define API_KEY "" // Chave de API do firebase
#define USER_EMAIL "" // email do usuário cadastrado
#define USER_PASSWORD "" // senha do usuário cadastrado
#define DATABASE_URL "" // url do nó do firebase

#define LAMPADA_PIN 15

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  pinMode(LAMPADA_PIN, OUTPUT);
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.println(WiFi.localIP());

  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.getString(fbdo, "/lampada/")) {
    String LAMPADAState = fbdo.stringData();
    
    if (LAMPADAState == "ON") {
      digitalWrite(LAMPADA_PIN, HIGH);
    } else if (LAMPADAState == "OFF") {
      digitalWrite(LAMPADA_PIN, LOW);
    }
  } else {
    Serial.println(fbdo.errorReason());
  }

  delay(1000);
}
