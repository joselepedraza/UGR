SRC = src
INC = include
OBJ = obj
BIN = bin
LIB = lib

CPPFLAGS = -Wall -g -c -I$(INC) 

all:$(BIN)/testimagen $(BIN)/testcodificar $(BIN)/esteganografia

$(BIN)/esteganografia : $(OBJ)/esteganografia.o $(LIB)/libimagen.a
	g++ -o $(BIN)/esteganografia $(OBJ)/esteganografia.o -L$(LIB) -limagen
	
$(OBJ)/esteganografia.o : $(SRC)/esteganografia.cpp  $(INC)/imagen.h $(INC)/byte.h $(INC)/codificar.h
	g++ -c -I$(INC) -o $(OBJ)/esteganografia.o $(SRC)/esteganografia.cpp

$(BIN)/testcodificar : $(OBJ)/testcodificar.o $(LIB)/libimagen.a
	g++ -o $(BIN)/testcodificar $(OBJ)/testcodificar.o -L$(LIB) -limagen

$(OBJ)/testcodificar.o : $(SRC)/testcodificar.cpp  $(INC)/imagen.h $(INC)/byte.h $(INC)/codificar.h
	g++ -c -I$(INC) -o $(OBJ)/testcodificar.o $(SRC)/testcodificar.cpp

$(OBJ)/byte.o : $(SRC)/byte.cpp $(INC)/byte.h
	g++ -c -I$(INC) -o $(OBJ)/byte.o $(SRC)/byte.cpp

$(OBJ)/codificar.o : $(SRC)/codificar.cpp $(INC)/codificar.h $(INC)/byte.h $(INC)/imagen.h
	g++ -c -I$(INC) -o $(OBJ)/codificar.o $(SRC)/codificar.cpp

$(BIN)/testimagen : $(OBJ)/testimagen.o $(LIB)/libimagen.a
	g++ -o $(BIN)/testimagen $(OBJ)/testimagen.o -L$(LIB) -limagen

$(OBJ)/testimagen.o : $(SRC)/testimagen.cpp $(INC)/imagen.h
	g++ -c -I$(INC) -o $(OBJ)/testimagen.o $(SRC)/testimagen.cpp

$(OBJ)/imagen.o : $(SRC)/imagen.cpp $(INC)/imagen.h $(INC)/pgm.h
	g++ -c -I$(INC) -o $(OBJ)/imagen.o $(SRC)/imagen.cpp

$(OBJ)/pgm.o : $(SRC)/pgm.cpp $(INC)/pgm.h
	g++ -c -I$(INC) -o $(OBJ)/pgm.o $(SRC)/pgm.cpp


$(LIB)/libimagen.a : $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/codificar.o $(OBJ)/byte.o
	ar rvs $(LIB)/libimagen.a $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/codificar.o $(OBJ)/byte.o



# ************ documentación *******   

documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Limpieza ************
