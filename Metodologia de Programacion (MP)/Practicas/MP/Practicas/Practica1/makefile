INCLUDE = include
LIB = lib
OBJ = obj
SRC = src
BIN = bin

all: $(BIN)/test2

$(BIN)/test2 : $(OBJ)/Demo2.o $(LIB)/libprueba.a
	g++ -o $(BIN)/test2 $(OBJ)/Demo2.o -L$(LIB) -lprueba

$(OBJ)/Demo2.o : $(SRC)/Demo2.cpp $(INCLUDE)/Punto.h $(INCLUDE)/Circulo.h
	g++ -c -I$(INCLUDE) -o $(OBJ)/Demo2.o $(SRC)/Demo2.cpp

$(OBJ)/Punto.o : $(SRC)/Punto.cpp $(INCLUDE)/Punto.h
	g++ -c -I$(INCLUDE) -o $(OBJ)/Punto.o $(SRC)/Punto.cpp

$(OBJ)/Circulo.o : $(SRC)/Circulo.cpp $(INCLUDE)/Punto.h $(INCLUDE)/Circulo.h
	g++ -c -I$(INCLUDE) -o $(OBJ)/Circulo.o $(SRC)/Circulo.cpp

$(LIB)/libprueba.a : $(OBJ)/Punto.o $(OBJ)/Circulo.o
	ar rvs $(LIB)/libprueba.a $(OBJ)/Punto.o $(OBJ)/Circulo.o

clean :
	echo "Limpiando..."
	rm $(OBJ)/*.o

mrproper: clean

	rm $(BIN)/test2


