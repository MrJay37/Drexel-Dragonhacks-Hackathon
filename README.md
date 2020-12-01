# Drexel-Dragonhacks-Hackathon
## Smart Kitchen Smoke Detector

This repository contains the code for the project demonstrated at Drexel DragonHacks Hackathon 2020. Aim of the project was to build a sensor network for kitchens to detect smoke and activity related to fire that could be deemed hazardous. It consists of several components, which are as follows

* Sensor network capable of sending readings to a local server
* Object detection and recognition module running on local system
* Web app used to log, record and analyse everyday activity and utilization of resources
* Machine learning model to distinguish and classify fire activities as human intended usage or accidental
* Notification service running on a cloud server

![Project Setup](images\hackathon_setup.jpeg)

Following are the parts present in the the setup picture above

- First laptop is providing power to Arduino and internet connection using Ethernet bridge. It can also read data on the serial link.

- The Arduino and Raspberry Pi work together as a sensor network module and a local server respectively. To the Arduino, a DHT11 Temperature and Humidity sensor, a smoke sensor and an Air Quality Index (AQI) sensors are connected. Sensors can be seen placed over the breadboard. A HC05 bluetooth module is also connected in order to communicate wiht the Raspberry Pi.

- The second laptop has 2 windows open. The window on the left is a remote desktop terminal to the Raspberry Pi which is logging the incoming data on the terminal. The window on the left is a Google Sheets window which is logging the Arduino data into a spreadsheet. This spreadsheet data is later used to draw analytics for the same.

Team Members: Kavy Jain, Sanket Jain, Raghav Daga, Meet Patel