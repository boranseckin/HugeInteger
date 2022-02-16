CC = clang++
CFLAGS = -std=c++11
INCLUDES = -I/opt/homebrew/Cellar/boost/1.76.0/include/ -I.

lab:
	$(CC) $(CFLAGS) $(INCLUDES) [!Exp]*.cpp

experiment:
	$(CC) $(CFLAGS) $(INCLUDES) HugeInteger.h HugeInteger.cpp Experiment.cpp