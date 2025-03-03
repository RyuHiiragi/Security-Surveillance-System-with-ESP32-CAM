# Security Surveillance System with ESP32-CAM  

This repository contains the code and instructions for a security system using **ESP32-CAM** to detect motion, capture photos, and send real-time notifications via Telegram <button class="citation-flag" data-index="1"><button class="citation-flag" data-index="8"><button class="citation-flag" data-index="10">.  

---

## Features  
- Motion detection using PIR sensor <button class="citation-flag" data-index="7">.  
- Face detection (requires integration with a pre-trained model or cloud API) <button class="citation-flag" data-index="3"><button class="citation-flag" data-index="5">.  
- Real-time alerts via Telegram <button class="citation-flag" data-index="8"><button class="citation-flag" data-index="10">.  

---

## Components  
- **ESP32-CAM Module**  
- **PIR Motion Sensor**  
- **5V Power Supply**  
- **Jumper Wires**  

---

## Setup  
1. **Calibrate the PIR Sensor**: Adjust sensitivity to avoid false triggers <button class="citation-flag" data-index="7">.  
2. **Configure Telegram Bot**:  
   - Create a bot via [BotFather](https://core.telegram.org/bots#botfather) and replace `YOUR_BOT_TOKEN` and `YOUR_CHAT_ID` in the code.  
3. **Upload Code**: Use an FTDI programmer to upload the code to the ESP32-CAM <button class="citation-flag" data-index="9">.  

---

## How It Works  
- When motion is detected, the PIR sensor triggers the ESP32-CAM to capture a photo <button class="citation-flag" data-index="4"><button class="citation-flag" data-index="8">.  
- The photo is sent to Telegram as a security alert <button class="citation-flag" data-index="10">.  
- Face detection can be added via libraries like **ESP-WHO** or cloud APIs for advanced recognition <button class="citation-flag" data-index="3"><button class="citation-flag" data-index="5">.  

---

## License  
MIT License. See [LICENSE](LICENSE) for details.  

---

<button class="citation-flag" data-index="1"> Motion-triggered image capture with ESP32-CAM and Telegram <button class="citation-flag" data-index="10">.  
<button class="citation-flag" data-index="3"> Face detection integration for security systems <button class="citation-flag" data-index="5">.  
<button class="citation-flag" data-index="7"> PIR sensor calibration for reliable motion detection <button class="citation-flag" data-index="8">.  
