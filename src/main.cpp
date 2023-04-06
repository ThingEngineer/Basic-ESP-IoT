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

  // Connect to WiFi using the provided SSID and password
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    // Wait for connection and print a message every second
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print WiFi received signal strength and power supply voltage
  // This could save time with an issue that is difficult to troubleshoot
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

// Function to send temperature data to the server
void sendTemperature(float tempC) {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Sending temperature");
    HTTPClient http;

    // Begin connection to the server
    http.begin(wifiClient, serverName, serverPort, String("/api/temperature"));
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Create HTTP request data and send POST request
    String httpRequestData = "temperature=" + String(tempC);
    int httpResponseCode = http.POST(httpRequestData);

    // Print response code
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

// Function to get a message from the server
void getMessage() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Getting message");
    HTTPClient http;

    // Begin connection to the server
    http.begin(wifiClient, serverName, serverPort, String("/api/message"));

    // Send GET request and store response code
    int httpResponseCode = http.GET();

    // If response is positive, print the requested message from the server
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