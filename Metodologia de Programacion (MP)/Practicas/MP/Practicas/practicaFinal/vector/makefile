SRC = src
INC = include
OBJ = obj
BIN = bin
LIB = lib

CPPFLAGS = -Wall -g -c -I$(INC) 

all:$(BIN)/prueba

$(BIN)/prueba : $(OBJ)/prueba.o $(LIB)/libimagen.a
	g++ -o $(BIN)/prueba $(OBJ)/prueba.o -L$(LIB) -limagen
	
$(OBJ)/prueba.o : $(SRC)/prueba.cpp  $(INC)/imagen.h $(INC)/byte.h $(INC)/codificar.h
	g++ -c -g -I$(INC) -o $(OBJ)/prueba.o $(SRC)/prueba.cpp

$(OBJ)/byte.o : $(SRC)/byte.cpp $(INC)/byte.h
	g++ -c -g -I$(INC) -o $(OBJ)/byte.o $(SRC)/byte.cpp

$(OBJ)/codificar.o : $(SRC)/codificar.cpp $(INC)/codificar.h $(INC)/byte.h $(INC)/imagen.h
	g++ -c -g -I$(INC) -o $(OBJ)/codificar.o $(SRC)/codificar.cpp

$(OBJ)/imagen.o : $(SRC)/imagen.cpp $(INC)/imagen.h $(INC)/pgm.h
	g++ -c -g -I$(INC) -o $(OBJ)/imagen.o $(SRC)/imagen.cpp

$(OBJ)/pgm.o : $(SRC)/pgm.cpp $(INC)/pgm.h
	g++ -c -g -I$(INC) -o $(OBJ)/pgm.o $(SRC)/pgm.cpp


$(LIB)/libimagen.a : $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/codificar.o $(OBJ)/byte.o
	ar rvs $(LIB)/libimagen.a $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/codificar.o $(OBJ)/byte.o



# ************ documentación *******   

documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Limpieza ************

clean:
	echo "Limpiando..."
	rm obj/*.o lib/lib*.a

mrproper: clean
	rm bin/*
