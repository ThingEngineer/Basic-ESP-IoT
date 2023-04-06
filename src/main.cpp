/*
 * main.h
 *
 *      ____  _____ _     _             _____            _                      
 *     / / / |_   _| |   (_)           |  ___|          (_)                     
 *    / / /    | | | |__  _ _ __   __ _| |__ _ __   __ _ _ _ __   ___  ___ _ __ 
 *   / / /     | | | '_ \| | '_ \ / _` |  __| '_ \ / _` | | '_ \ / _ \/ _ \ '__|
 *  / / /      | | | | | | | | | | (_| | |__| | | | (_| | | | | |  __/  __/ |   
 * /_/_/       \_/ |_| |_|_|_| |_|\__, \____/_| |_|\__, |_|_| |_|\___|\___|_|   
 *                                 __/ |            __/ |                       
 *                                |___/            |___/                        
 * 
 * This file is part of the 'Basic ESP IoT' distribution (https://github.com/ThingEngineer/Basic-ESP-IoT).
 * Copyright (c) 2023 Josh Campbell (https://thing.engineer)
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

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Help rule out signal and power issues
  long rssi = WiFi.RSSI();
  Serial.print("RSSI:");
  Serial.println(rssi);
  Serial.print("Vcc:");
  Serial.println(ESP.getVcc()/1000.00);
}

/**
 * Main program loop
 */
void loop() {
  // Send temperature data to server every 60 seconds
  if ((millis() - lastTempCheck) > 60000) {
    lastTempCheck = millis();
    float tempF = random(60.00,69.99);
    sendTemperature(tempF);
  }

  // Get message from server every 30 seconds
  if ((millis() - lastGetRequest) > 30000) {
    lastGetRequest = millis();
    getMessage();
  }
}

void sendTemperature(float tempC) {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Sending temperature");
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
    Serial.println("Getting message");
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