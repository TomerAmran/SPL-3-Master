CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system

all: EchoClient
	g++ -o bin/echoExample bin/ConnectionHandler.o bin/echoClient.o bin/Database.o bin/Protocol.o bin/StompFrame.o bin/InputProcessor.o $(LDFLAGS)

EchoClient: bin/ConnectionHandler.o bin/echoClient.o bin/Database.o bin/Protocol.o bin/StompFrame.o bin/InputProcessor.o

bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/echoClient.o: src/echoClient.cpp
	g++ $(CFLAGS) -o bin/echoClient.o src/echoClient.cpp

bin/Database.o: src/Database.cpp
	g++ $(CFLAGS) -o bin/Database.o src/Database.cpp

bin/Protocol.o: src/Protocol.cpp
	g++ $(CFLAGS) -o bin/Protocol.o src/Protocol.cpp

bin/StompFrame.o: src/StompFrame.cpp
	g++ $(CFLAGS) -o bin/StompFrame.o src/StompFrame.cpp

bin/InputProcessor.o: src/InputProcessor.cpp
	g++ $(CFLAGS) -o bin/InputProcessor.o src/InputProcessor.cpp
	
.PHONY: clean
clean:
	rm -f bin/*
