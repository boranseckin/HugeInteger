CC = clang++
CFLAGS = -std=c++11
INCLUDES = -I/opt/homebrew/opt/boost/include/ -I.

lab:
	$(CC) $(CFLAGS) $(INCLUDES) [!Exp]*.cpp

experiment:
	$(CC) $(CFLAGS) $(INCLUDES) HugeInteger.h HugeInteger.cpp Experiment.cpp