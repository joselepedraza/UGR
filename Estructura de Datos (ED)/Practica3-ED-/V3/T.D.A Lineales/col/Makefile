SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++ -std=c++11
#CPPFLAGS = -Wall -g  -I$(INC) -c
CPPFLAGS = -g  -I$(INC) -c

# GENERAL #
all: $(BIN)/usopilas_max
# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

	
# ************ Compilación de módulos ************
# EJECUTABLE #
$(BIN)/usopilas_max: $(OBJ)/usopilas_max.o $(OBJ)/Pila_max_Cola.o $(OBJ)/Pila_max_VD.o $(OBJ)/VDG.o $(OBJ)/cola.o
	$(CXX) $(OBJ)/usopilas_max.o $(OBJ)/Pila_max_VD.o $(OBJ)/Pila_max_Cola.o $(OBJ)/VDG.o $(OBJ)/cola.o -o $(BIN)/usopilas_max


# OBJETOS #
$(OBJ)/usopilas_max.o: $(SRC)/usopilas_max.cpp $(INC)/Pila_max_VD.h $(INC)/Pila_max_Cola.h
	$(CXX) $(CPPFLAGS) $(SRC)/usopilas_max.cpp -o $(OBJ)/usopilas_max.o	

$(OBJ)/Pila_max_Cola.o: $(INC)/Pila_max_Cola.h $(INC)/cola.h
	$(CXX) $(CPPFLAGS) $(SRC)/Pila_max_Cola.cpp -o $(OBJ)/Pila_max_Cola.o	

$(OBJ)/Pila_max_VD.o: $(INC)/Pila_max_VD.h $(INC)/VDG.h
	$(CXX) $(CPPFLAGS) $(SRC)/Pila_max_VD.cpp -o $(OBJ)/Pila_max_VD.o	

$(OBJ)/VDG.o: $(INC)/VDG.h $(SRC)/VDG.cpp
	$(CXX) $(CPPFLAGS) $(SRC)/VDG.cpp -o $(OBJ)/VDG.o
	
$(OBJ)/cola.o: $(INC)/cola.h $(SRC)/cola.cpp
	$(CXX) $(CPPFLAGS) $(SRC)/cola.cpp -o $(OBJ)/cola.o


# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
