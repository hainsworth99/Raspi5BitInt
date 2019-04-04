# Raspi5BitInt 
A simple program I wrote to familiarize myself with using Raspberry Pi GPIO input/output libraries. Prints an 5-bit integer value to an array of 5 LEDs, which can be incremented/decremented by two push buttons. 

# Dependencies
* wiringPi - A C library for connecting to Raspi GPIO pins 
```bash
git clone git://git.drogon.net/wiringPi
cd wiringPi
git pull origin
./build
```

# Usage
```bash
gcc -o Raspi5BitInt Raspi5Bitint.c -l wiringPi
sudo ./Raspi5BitInt
```
