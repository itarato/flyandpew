LIBS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

CXXFLAGS=-std=c++2a -Wall -pedantic -Wformat

BIN=main
SRC=$(wildcard src/*.cpp)
OBJ=$(addsuffix .o,$(basename $(SRC)))

all: CXXFLAGS += -O3
all: executable

debug: CXXFLAGS += -g -O0
debug: executable

executable: $(OBJ)
	$(CXX) -o $(BIN) $^ $(CXXFLAGS) $(LIBS)

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f ./src/*.o
	rm -f ./$(BIN)

run: clean all
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib ./main

rebuild: clean
rebuild: all
