# DHT11 Telegram Monitoring System

Sistem monitoring suhu dan kelembaban menggunakan sensor DHT11 dengan tampilan LCD dan integrasi Telegram Bot. Proyek ini memungkinkan Anda untuk memantau kondisi lingkungan secara real-time melalui display LCD dan mendapatkan update melalui Telegram messenger.

## Fitur

- Monitoring suhu dan kelembaban real-time menggunakan sensor DHT11
- Tampilan LCD 16x2 dengan interface I2C
- Integrasi dengan Telegram Bot untuk monitoring jarak jauh
- Automatic reconnection ke WiFi
- Notifikasi status koneksi melalui Telegram
- Command `/info` untuk mendapatkan data sensor terkini

## Komponen yang Dibutuhkan

1. NodeMCU ESP8266
2. Sensor DHT11
3. LCD 16x2 dengan modul I2C (alamat 0x27)
4. Kabel jumper
5. Power supply 5V

## Spesifikasi Pin

- DHT11 Data Pin: D4 (GPIO2)
- LCD I2C SDA: D2 (GPIO4)
- LCD I2C SCL: D1 (GPIO5)

## Library yang Dibutuhkan

- DHT sensor library by Adafruit
- Wire library (built-in)
- LiquidCrystal_I2C
- ESP8266WiFi
- WiFiClientSecure
- UniversalTelegramBot
- ArduinoJson

## Cara Instalasi

1. Install semua library yang dibutuhkan melalui Arduino IDE Library Manager
2. Konfigurasikan kredensial WiFi:
   ```cpp
   const char* ssid = "Arul";
   const char* password = "123456789";
   ```
3. Sesuaikan konfigurasi Telegram Bot:
   ```cpp
   #define BOT_TOKEN "7694565589:AAEmz2EF-cs8m6bwqMYP_pkcF-nnGASljKM"
   #define CHAT_ID "6425706210"
   ```
4. Upload kode ke NodeMCU ESP8266

## Penggunaan

1. Setelah sistem terhubung ke WiFi, bot akan mengirimkan pesan "Connected Successfully"
2. Kirim perintah `/info` ke bot Telegram untuk mendapatkan data suhu dan kelembaban terkini
3. LCD akan menampilkan data secara real-time dengan interval update setiap 500ms
4. Serial monitor dapat digunakan untuk debugging dengan baud rate 115200

## Fitur Telegram Bot

- `/info` - Mendapatkan data suhu dan kelembaban terkini
- Format tampilan data:
  ```
  📊 Status:
  🌡️ XX.X°C
  💧 XX.X%
  ```

## Troubleshooting

1. Jika LCD tidak menampilkan data:
   - Periksa alamat I2C (default: 0x27)
   - Periksa koneksi kabel SDA dan SCL

2. Jika sensor DHT11 error:
   - Periksa koneksi pin data
   - Pastikan power supply stabil
   - Cek pesan error di serial monitor

3. Jika Telegram Bot tidak merespons:
   - Verifikasi BOT_TOKEN
   - Pastikan CHAT_ID benar
   - Periksa koneksi internet

## Pemeliharaan

- Bersihkan sensor DHT11 secara berkala
- Pastikan ventilasi udara di sekitar sensor tidak terhalang
- Monitor serial output untuk debugging jika terjadi masalah
- Periksa kualitas koneksi WiFi secara berkala

## Pengembangan Lebih Lanjut

Beberapa ide untuk pengembangan sistem:
1. Menambahkan fitur logging data ke SD card
2. Implementasi web server untuk monitoring via browser
3. Menambahkan alert system untuk nilai suhu/kelembaban di luar ambang batas
4. Integrasi dengan platform IoT seperti Blynk atau ThingSpeak

## Keamanan

- Ganti password WiFi secara berkala
- Jangan membagikan BOT_TOKEN Telegram
- Simpan CHAT_ID dalam variable terpisah
- Gunakan koneksi WiFi yang aman

## Support

Jika Anda menemukan masalah atau membutuhkan bantuan, silakan buat issue baru di repository ini atau hubungi pembuat sistem.

---
Project ini dikembangkan untuk monitoring suhu dan kelembaban menggunakan NodeMCU ESP8266 dan sensor DHT11 dengan integrasi Telegram Bot.