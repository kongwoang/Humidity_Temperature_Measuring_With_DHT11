
#define BLYNK_TEMPLATE_ID "TMPLOaggLw_j"
#define BLYNK_DEVICE_NAME "phamconghoang1"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial


#define APP_DEBUG
#define USE_NODE_MCU_BOARD
#include "BlynkEdgent.h"
#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
unsigned long times=millis();

WidgetLED led(V0);
BlynkTimer timer;


void blinkLedWidget(){
  if (led.getValue()) {
    led.off();
  } else {
    led.on();
  }
}

void setup(){
  Serial.begin(115200);
  delay(100);
  BlynkEdgent.begin();
  dht.begin();
  timer.setInterval(1000L, blinkLedWidget);
}

void loop() {
  BlynkEdgent.run();
  timer.run();
  if(millis()-times>2000){

    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (isnan(h) || isnan(t)) {
      Serial.println(F("Khong nhan duoc tin hieu!"));
      return;
    }
    Blynk.virtualWrite(V1,t);
    Blynk.virtualWrite(V2,h);
    Serial.print(F("Temperature: "));
    Serial.print(t);
    Serial.print(F("°C "));
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.println(F("%"));
    times = millis();
  }
}
