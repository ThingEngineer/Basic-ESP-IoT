# Basic-ESP-IoT (firmware)
Basic Microcontroller API Consumption

This repository is part of a series on how to consume an API with a microcontroller. The other repository in the series is the API backend and web frontend: [Basic-IoT-API](https://github.com/ThingEngineer/Basic-IoT-API).

“Consume API” means to engage with the API, this is done by sending requests to the API and receiving responses. 

The API will respond to requests with data, which is often in the form of JSON. It will also respond to requests with a status code, which indicates whether the request was successful or not.

---
## Getting Started
1) Clone this repository or download it as a zip file.
```sh
git clone https://github.com/ThingEngineer/Basic-ESP-IoT.git
```
2) Edit platformio.ini with your configuration.
You can find more information on the configurations used here: [platformio.ini docs](https://docs.platformio.org/en/stable/projectconf/index.html).

3) Edit .env with your WiFi credentials and server settings.

4) Build and upload the project to your microcontroller.

5) Open the serial monitor to see the output.

6) Open the web frontend to see the data. If you have not set this up yet, you can find the repository here: [Basic-IoT-API](https://github.com/ThingEngineer/Basic-IoT-API).

---
## References
[PlatformIO Documentation](https://docs.platformio.org/en/latest/)
