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
samplingRate = ADS1256_DRATE['10']
scanMode = ADS1256_SMODE['SINGLE_ENDED']

adcChannels = 8 - 4 * scanMode

def interruptInterpreter(ch):
	if ch == PIN_DRDY:
		# collect data from ads1256
		pyadda.collectData()

		volts = pyadda.readAllChannelsVolts(adcChannels)

		i = 0
		for val in volts:
			print("Channel {:d} - {:.3f}mV".format(i, val * 1000))
			i += 1

		# reset to first line
		print("\033[{:d}A".format(len(volts)+1))


# setup ads1256 chip
pyadda.startADC(gain, samplingRate, scanMode)

prevTime = time.time()
meanSampleRate = 0
counter = 0

# wait for DRDY low - indicating data is ready
GPIO.add_event_detect(PIN_DRDY, GPIO.FALLING, callback=interruptInterpreter)

while True:
	pass
