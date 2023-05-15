# Meds_Butler
Meds_Butler is a medicine delievery system for the elderly, the code is for three pieces of the system, the Atmega2560 used as the main driver of the device,
The times at which to deliver the medicines are received on a esp8266 which is serially attached to the arduino, at the time of the medicine delivery, a signal is
sent to the arm band of the patient, which itself has a battery run esp8266, and a small motor to create vibrations as a signal that "it is time to take medicine".
Medibox.ino is the code for the Atmega2560, 
esp8266_connection.ino is the code for the esp8266 serially connected to the man controller,
serial_esp8266 has the code for the arm_band esp8266.

The video demonstration of the device can be found on the following link:
https://youtu.be/XA4y3OvXI9I
