#include <WiFi.h>  
#include <esp_camera.h>  
#include <ArduinoJson.h>  
#include <HTTPClient.h>  

// Wi-Fi credentials  
const char* ssid = "YOUR_SSID";  
const char* password = "YOUR_PASSWORD";  

// Telegram Bot API (replace with your bot token and chat ID)  
const String telegramBotToken = "YOUR_BOT_TOKEN";  
const String chatID = "YOUR_CHAT_ID";  

// PIR sensor pin  
#define PIR_PIN 13  

void setup() {  
  Serial.begin(115200);  
  pinMode(PIR_PIN, INPUT);  

  // Initialize camera  
  camera_config_t config;  
  config.ledc_channel = LEDC_CHANNEL_0;  
  config.ledc_timer = LEDC_TIMER_0;  
  config.pin_d0 = Y2_GPIO_NUM;  
  config.pin_d1 = Y3_GPIO_NUM;  
  config.pin_d2 = Y4_GPIO_NUM;  
  config.pin_d3 = Y5_GPIO_NUM;  
  config.pin_d4 = Y6_GPIO_NUM;  
  config.pin_d5 = Y7_GPIO_NUM;  
  config.pin_d6 = Y8_GPIO_NUM;  
  config.pin_d7 = Y9_GPIO_NUM;  
  config.pin_xclk = XCLK_GPIO_NUM;  
  config.pin_pclk = PCLK_GPIO_NUM;  
  config.pin_vsync = VSYNC_GPIO_NUM;  
  config.pin_href = HREF_GPIO_NUM;  
  config.pin_sscb_sda = SIOD_GPIO_NUM;  
  config.pin_sscb_scl = SIOC_GPIO_NUM;  
  config.pin_pwdn = PWDN_GPIO_NUM;  
  config.pin_reset = RESET_GPIO_NUM;  
  config.xclk_freq_hz = 20000000;  
  config.pixel_format = PIXFORMAT_JPEG;  

  if (psramFound()) {  
    config.frame_size = FRAMESIZE_UXGA;  
    config.jpeg_quality = 10;  
  } else {  
    config.frame_size = FRAMESIZE_SVGA;  
    config.jpeg_quality = 12;  
  }  

  esp_camera_init(&config);  

  // Connect to Wi-Fi  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);  
    Serial.print(".");  
  }  
  Serial.println("Wi-Fi connected");  
}  

void loop() {  
  if (digitalRead(PIR_PIN) == HIGH) {  
    delay(200); // Debounce  
    if (digitalRead(PIR_PIN) == HIGH) {  
      // Capture photo  
      camera_fb_t* fb = esp_camera_fb_get();  
      if (!fb) {  
        Serial.println("Camera capture failed");  
        return;  
      }  

      // Send photo to Telegram  
      sendTelegramPhoto(fb->buf, fb->len);  
      esp_camera_fb_return(fb);  
    }  
  }  
}  

void sendTelegramPhoto(uint8_t* imageBuffer, size_t imageSize) {  
  HTTPClient http;  
  String url = "https://api.telegram.org/bot" + telegramBotToken + "/sendPhoto";  
  http.begin(url);  
  http.addHeader("Content-Type", "multipart/form-data");  

  // Prepare payload  
  String payload = "--boundary\n";  
  payload += "Content-Disposition: form-data; name=\"chat_id\"\n\n";  
  payload += chatID + "\n";  
  payload += "--boundary\n";  
  payload += "Content-Disposition: form-data; name=\"photo\"; filename=\"capture.jpg\"\n";  
  payload += "Content-Type: image/jpeg\n\n";  
  http.addHeader("Content-Type", "multipart/form-data; boundary=boundary");  

  // Send image  
  uint8_t* data = (uint8_t*)malloc(imageSize + payload.length());  
  memcpy(data, payload.c_str(), payload.length());  
  memcpy(data + payload.length(), imageBuffer, imageSize);  
  int httpResponseCode = http.POST(data, payload.length() + imageSize);  

  if (httpResponseCode == 200) {  
    Serial.println("Photo sent to Telegram!");  
  } else {  
    Serial.println("Failed to send photo");  
  }  
  http.end();  
}  
