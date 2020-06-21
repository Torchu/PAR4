SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g  -I$(INC) -c -O2

all: $(BIN)/par

# ************ Local search compilation ************
$(BIN)/par : $(OBJ)/main.o $(OBJ)/par.o $(OBJ)/aro.o
	$(CXX) -o $(BIN)/par $(OBJ)/main.o $(OBJ)/par.o $(OBJ)/aro.o

$(OBJ)/main.o : $(SRC)/main.cpp
	$(CXX) $(CPPFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/par.o : $(SRC)/par.cpp
	$(CXX) $(CPPFLAGS) -o $(OBJ)/par.o $(SRC)/par.cpp

$(OBJ)/aro.o : $(SRC)/aro.cpp
	$(CXX) $(CPPFLAGS) -o $(OBJ)/aro.o $(SRC)/aro.cpp

# ************ Cleaning ************
clean :
	-rm $(BIN)/* $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~
