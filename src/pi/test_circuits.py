#!/usr/bin/python3

import AM2315
import RPi.GPIO
import time

am2315 = AM2315.AM2315()
RPi.GPIO.setmode(RPi.GPIO.BCM)
RPi.GPIO.setup(23, RPi.GPIO.OUT)

while True:
	print('Powering circuit...')
	RPi.GPIO.output(23, 1)
	print('Temperature: ', am2315.temperature(), 'C')
	print('Temperature: ', (am2315.temperature() * (9.0 / 5.0) + 32), 'F')
	print('Humidity: ', am2315.humidity())
	time.sleep(1)
	print('Killing circuit...')
	RPi.GPIO.output(23, 0)
	time.sleep(1)

