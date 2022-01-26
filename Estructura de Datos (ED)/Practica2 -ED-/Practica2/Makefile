SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++ -std=c++11
#CPPFLAGS = -Wall -g  -I$(INC) -c
CPPFLAGS = -g  -I$(INC) -c

# GENERAL #
all: $(BIN)/pruebacronologia
# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile


# ************ Compilación de módulos ************
# EJECUTABLE #
$(BIN)/pruebacronologia: $(OBJ)/pruebacronologia.o $(OBJ)/cronologia.o $(OBJ)/fechahistorica.o
	$(CXX) $(OBJ)/pruebacronologia.o $(OBJ)/cronologia.o $(OBJ)/fechahistorica.o -o $(BIN)/pruebacronologia


# OBJETOS #
$(OBJ)/pruebacronologia.o: $(SRC)/pruebacronologia.cpp $(INC)/cronologia.h
	$(CXX) $(CPPFLAGS) $(SRC)/pruebacronologia.cpp -o $(OBJ)/pruebacronologia.o

$(OBJ)/cronologia.o: $(INC)/cronologia.h $(INC)/fechahistorica.h $(SRC)/cronologia.cpp
	$(CXX) $(CPPFLAGS) $(SRC)/cronologia.cpp -o $(OBJ)/cronologia.o

$(OBJ)/fechahistorica.o: $(INC)/fechahistorica.h $(SRC)/fechahistorica.cpp
	$(CXX) $(CPPFLAGS) $(SRC)/fechahistorica.cpp -o $(OBJ)/fechahistorica.o


# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
