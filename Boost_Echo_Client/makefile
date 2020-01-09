CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude -pthread
LDFLAGS:=-lboost_system

all: StompBookClubClient
	g++ -o bin/StompBookClubClient bin/ConnectionHandler.o bin/StompClient.o bin/InputProcessor.o bin/StompFrame.o bin/Database.o bin/ServerTask.o bin/Protocol.o $(LDFLAGS)

StompBookClubClient: bin/ConnectionHandler.o bin/StompClient.o bin/InputProcessor.o bin/StompFrame.o bin/Database.o bin/ServerTask.o bin/Protocol.o

bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/StompClient.o: src/StompClient.cpp
	g++ $(CFLAGS) -o bin/StompClient.o src/StompClient.cpp

bin/InputProcessor.o: src/InputProcessor.cpp
	g++ $(CFLAGS) -o bin/InputProcessor.o src/InputProcessor.cpp

bin/StompFrame.o: src/StompFrame.cpp
	g++ $(CFLAGS) -o bin/StompFrame.o src/StompFrame.cpp

bin/Database.o: src/Database.cpp
	g++ $(CFLAGS) -o bin/Database.o src/Database.cpp

bin/ServerTask.o: src/ServerTask.cpp
	g++ $(CFLAGS) -o bin/ServerTask.o src/ServerTask.cpp

bin/Protocol.o: src/Protocol.cpp
	g++ $(CFLAGS) -o bin/Protocol.o src/Protocol.cpp

.PHONY: clean
clean:
	rm -f bin/*
