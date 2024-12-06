#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = "Arul";
const char* password = "123456789";

#define BOT_TOKEN "7694565589:AAEmz2EF-cs8m6bwqMYP_pkcF-nnGASljKM"
#define CHAT_ID "6425706210"
#define DHTPIN D4
#define DHTTYPE DHT11

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime = 0;
const unsigned long BOT_MTBS = 1000;

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void displayError() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error Sensor!");
    lcd.setCursor(0, 1);
    lcd.print("Check DHT11");
    Serial.println("Error: Failed to read DHT11 sensor");
    bot.sendMessage(CHAT_ID, "⚠️ Alert: Sensor DHT11 error! Please check the connection");
}

String getSensorData() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (isnan(h) || isnan(t)) {
        displayError();
        return "";
    }
    
    return "📊 Status:\n🌡️ " + String(t, 1) + "°C\n💧 " + String(h, 1) + "%";
}

void handleNewMessages(int numNewMessages) {
    for (int i = 0; i < numNewMessages; i++) {
        if (bot.messages[i].text.equalsIgnoreCase("/info")) {
            String data = getSensorData();
            if (data.length() > 0) {
                bot.sendMessage(bot.messages[i].chat_id, data, "");
            } else {
                bot.sendMessage(bot.messages[i].chat_id, "⚠️ Sensor error! Unable to read data", "");
            }
        }
    }
}

void updateLCD(float t, float h) {
    lcd.setCursor(0, 0);
    lcd.print("Suhu: " + String(t, 1) + (char)223 + "C    ");
    lcd.setCursor(0, 1);
    lcd.print("Kelembapan: " + String(h, 1) + "%    ");
}

void setup() {
    Serial.begin(115200);
    lcd.init();
    lcd.backlight();
    lcd.print("Connecting...");
    
    configTime(0, 0, "pool.ntp.org");
    secured_client.setTrustAnchors(&cert);
    
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        lcd.setCursor(0, 1);
        lcd.print("Connecting WiFi..");
        delay(500);
        lcd.clear();
    }
    
    dht.begin();
    if (!dht.read()) {
        displayError();
    } else {
        bot.sendMessage(CHAT_ID, "✅ System Connected Successfully");
        lcd.clear();
        lcd.print("System Ready!");
        delay(1000);
        lcd.clear();
    }
}

void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (isnan(h) || isnan(t)) {
        static unsigned long lastErrorTime = 0;
        if (millis() - lastErrorTime > 5000) {
            displayError();
            lastErrorTime = millis();
        }
    } else {
        updateLCD(t, h);
        Serial.printf("T: %.1f°C, H: %.1f%%\n", t, h);
    }
    
    if (millis() - bot_lasttime > BOT_MTBS) {
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        if (numNewMessages) handleNewMessages(numNewMessages);
        bot_lasttime = millis();
    }
    
    delay(500);
}