# a2 makefile

# compiler
CC = g++

# compiler flags
CFLAGS = -Wall -std=c++11 -Wfatal-errors

# build target executable
TARGET1 = reader

all: $(TARGET1)

$(TARGET1): $(TARGET1).cc
	$(CC) $(CFLAGS) -o $(TARGET1) $(TARGET1).cc chain.cc chainfileParser.cc netTuple.cc

clean:
	$(RM) $(TARGET1)
