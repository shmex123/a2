# a2 makefile

# compiler
CC = g++

# compiler flags
CFLAGS = -Wall -std=c++11 -Wfatal-errors

# build target executable
TARGET1 = awget

all: $(TARGET1)

$(TARGET1): reader.cc
	$(CC) $(CFLAGS) -o $(TARGET1) reader.cc chain.cc chainfileParser.cc netTuple.cc utils.cc requestEvent.cc

clean:
	$(RM) $(TARGET1)
