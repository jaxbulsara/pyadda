# pyadda
Python 3 wrapper for Waveshare High Precision AD/DA board (ads1256 and dac8532)

## Installing the library
Navigate to the cloned/downloaded directory on your Raspberry Pi and type in the following command to install pyadda.
```
sudo python3 setup.py install
```

## Running sample code
The C library requires root permission, so any time you run a script with pyadda, you must run it with sudo.
```
sudo python3 channel_read_example.py
```
