# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CC = g++
CFLAGS = -Wall -g

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o functions.o 
	$(CC) $(CFLAGS) -o main main.o functions.o

main.o: main.cpp functions.h
	$(CC) $(CFLAGS) -c main.cpp

functions.o: functions.h
