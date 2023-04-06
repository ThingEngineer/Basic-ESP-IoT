/*
 * main.h
 * 
 * This file is part of the 'Basic ESP IoT' distribution (https://github.com/ThingEngineer/Basic-ESP-IoT).
 * Copyright (c) 2023 Josh Campbell.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 */
#include "main.h"

/**
 * Initialization routines
 */
void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

/**
 * Main program loop
 */
void loop() {
  if ((millis() - lastTempCheck) > 60000) {
    lastTempCheck = millis();
    float tempF = random(60.00,69.99);
    sendTemperature(tempF);
  }

  if ((millis() - lastGetRequest) > 30000) {
    lastGetRequest = millis();
    getMessage();
  }
}

void sendTemperature(float tempC) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(wifiClient, serverName, serverPort, String("/api/temperature"));
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "temperature=" + String(tempC);
    int httpResponseCode = http.POST(httpRequestData);
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }
}

void getMessage() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(wifiClient, serverName, serverPort, String("/api/message"));
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.println("Message from server: " + payload);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }
}