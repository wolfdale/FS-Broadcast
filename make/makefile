CC=g++
FLAGS= -c -g -std=c++0x  

BIN=../bin/
SRC=../src/
OBJ=../obj/
HEADER=../include/
INCLUDE=-I../include/
FILE=../files/
TEST=../bcast_listener

$(BIN)fs_bcast:$(OBJ)svr.o
	mkdir -p $(BIN)
	$(CC) -o $(BIN)fs_bcast $(OBJ)svr.o $(INCLUDE) -pthread

$(OBJ)svr.o:$(SRC)svr.cpp $(HEADER)fs_header.h
	mkdir -p $(OBJ)
	$(CC) $(FLAGS) -pthread $(INCLUDE) $(SRC)svr.cpp -o $(OBJ)svr.o




clean:
	rm -rf $(OBJ)
	rm -rf $(BIN)







