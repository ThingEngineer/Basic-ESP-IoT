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
#ifndef MAIN_H
#define MAIN_H

/****************************************************************************
* Includes
****************************************************************************/
#include <Arduino.h>                    // Compatibility library for Arduino functions
#include <ESP8266WiFi.h>                // WiFi library for network connectivity
#include <ESP8266HTTPClient.h>          // HTTP requests and responses library

#include "env.h"                        // Environment variables

/****************************************************************************
* Port aliases
****************************************************************************/
#define BUILT_IN_LED 33                 // Built in LED output pin (status indicator)

/****************************************************************************
* Constructors
****************************************************************************/
WiFiClient wifiClient;

/****************************************************************************
* Function prototypes
****************************************************************************/
void sendTemperature(float tempC);
void getMessage();

/****************************************************************************
* Variable and constant declarations
****************************************************************************/
// WiFi credentials
const char* ssid =              SECRET_SSID;
const char* password =          SECRET_PASS;

// Server credentials
const char* serverName =        SECRET_SERVER_NAME;
const int   serverPort =        SECRET_SERVER_PORT;

// Timer state variables
unsigned long lastTempCheck =   0;
unsigned long lastGetRequest =  0;

#endif /* MAIN_H */