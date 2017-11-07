import  RPi.GPIO as GPIO
import pyadda
from adc_consts import *
import time

# Raspberry pi pin numbering setup
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)

PIN_DRDY = 11

GPIO.setup(PIN_DRDY, GPIO.IN)

# define gain, sampling rate, and scan mode
gain = ADS1256_GAIN['1']
samplingRate = ADS1256_DRATE['30000']
scanMode = ADS1256_SMODE['SINGLE_ENDED']

adcChannels = 8 - 4 * scanMode

# clear data file
with open('test_data.csv', 'w') as f:
	f.write('Time (s)')
	for i in range(adcChannels):
		f.write(",Channel {}".format(i))
	f.write('\n')

def interruptInterpreter(ch):
	sampleTime = time.time() - startTime
	if ch == PIN_DRDY:
		# collect data from ads1256
		pyadda.collectData()

		volts = pyadda.readAllChannelsVolts(adcChannels)

		# TODO: need a faster way to write this data, as it is skipping samples
		open('test_data.csv', 'a').write(str(sampleTime) + ','.join(map(str, volts)) + '\n')


# setup ads1256 chip
pyadda.startADC(gain, samplingRate, scanMode)

startTime = time.time()

# wait for DRDY low - indicating data is ready
GPIO.add_event_detect(PIN_DRDY, GPIO.FALLING, callback=interruptInterpreter)

while True:
	pass
