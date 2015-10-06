# a2 makefile

# compiler
CC = g++

# compiler flags
CFLAGS = -Wall -std=c++11 -Wfatal-errors

# build target executable
AWGET = awget
SS = ss

all: $(AWGET) $(SS)

$(AWGET): reader.cc
	$(CC) $(CFLAGS) -o $(AWGET) reader.cc chain.cc chainfileParser.cc netTuple.cc utils.cc requestEvent.cc tcpConnection.cc

$(SS): steppingStone.cc
	$(CC) $(CFLAGS) -o $(SS) steppingStone.cc chain.cc chainfileParser.cc netTuple.cc utils.cc requestEvent.cc tcpConnection.cc

clean:
	$(RM) $(AWGET) $(SS)
