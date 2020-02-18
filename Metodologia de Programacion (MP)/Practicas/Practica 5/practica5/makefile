
SRC = src
INC = include
OBJ = obj
BIN = bin
LIB = lib

CXX = g++
CPPFLAGS = -Wall -g -c -I$(INC)

all: $(BIN)/testimagen $(BIN)/testplano $(BIN)/testarteASCII $(BIN)/arteASCII2

$(LIB)/libimagen.a: $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/byte.o $(OBJ)/lista.o
	ar rsv $(LIB)/libimagen.a $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/byte.o $(OBJ)/lista.o

$(OBJ)/byte.o: $(SRC)/byte.cpp $(INC)/byte.h
	$(CXX) -c -I$(INC) -o $(OBJ)/byte.o $(SRC)/byte.cpp

$(OBJ)/imagen.o: $(SRC)/imagen.cpp $(INC)/imagen.h $(INC)/pgm.h $(INC)/lista.h
	$(CXX) -c $(SRC)/imagen.cpp -std=c++11 -o $(OBJ)/imagen.o -I$(INC)/

$(OBJ)/pgm.o: $(SRC)/pgm.cpp $(INC)/pgm.h
	$(CXX) -c $(SRC)/pgm.cpp -o $(OBJ)/pgm.o -I$(INC)/

$(OBJ)/lista.o: $(SRC)/lista.cpp $(INC)/lista.h
	$(CXX) -c $(SRC)/lista.cpp -o $(OBJ)/lista.o -I$(INC)/

$(OBJ)/testimagen.o: $(SRC)/testimagen.cpp $(INC)/imagen.h
	$(CXX) -c $(SRC)/testimagen.cpp -o $(OBJ)/testimagen.o -I$(INC)/

$(BIN)/testimagen: $(OBJ)/testimagen.o $(LIB)/libimagen.a
	$(CXX) -g -o $(BIN)/testimagen $(OBJ)/testimagen.o -Llib/ -limagen

$(OBJ)/testplano.o: $(SRC)/testplano.cpp $(INC)/imagen.h
	$(CXX) -c $(SRC)/testplano.cpp -o $(OBJ)/testplano.o -I$(INC)/

$(BIN)/testplano: $(OBJ)/testplano.o $(LIB)/libimagen.a
	$(CXX) -g -o $(BIN)/testplano $(OBJ)/testplano.o -Llib/ -limagen

$(OBJ)/testarteASCII.o: $(SRC)/testarteASCII.cpp $(INC)/imagen.h
	$(CXX) -c $(SRC)/testarteASCII.cpp -o $(OBJ)/testarteASCII.o -I$(INC)/

$(BIN)/testarteASCII: $(OBJ)/testarteASCII.o $(LIB)/libimagen.a
	$(CXX) -g -o $(BIN)/testarteASCII $(OBJ)/testarteASCII.o -Llib/ -limagen

$(OBJ)/arteASCII2.o: $(SRC)/arteASCII2.cpp $(INC)/imagen.h
	$(CXX) -c $(SRC)/arteASCII2.cpp -std=c++11 -o $(OBJ)/arteASCII2.o -I$(INC)/

$(BIN)/arteASCII2: $(OBJ)/arteASCII2.o $(LIB)/libimagen.a
	$(CXX) -g -o $(BIN)/arteASCII2 $(OBJ)/arteASCII2.o -Llib/ -limagen


documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Limpieza ************
clean:
	echo "Limpiando..."
	rm $(OBJ)/* $(LIB)/*
	
mrproper: clean
	rm $(BIN)/* doc/html/*
