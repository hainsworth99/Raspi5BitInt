CXX = gcc
CXXFLAGS = -Wall

all: raspi5BitInt.c
	$(CXX) $(CXXFLAGS) -o raspi5BitInt raspi5BitInt.c -l wiringPi

clean:
	rm raspi5BitInt
