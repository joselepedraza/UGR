SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++ -std=c++11
CPPFLAGS = -g  -I$(INC) -c

# GENERAL
all: mrproper $(BIN)/usopilas_max
# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile


# ************ Compilación de módulos ************

# EJECUTABLE
#Funciona Bien!!!
$(BIN)/usopilas_max: $(OBJ)/usopilas_max.o $(OBJ)/pila_max_vd.o $(OBJ)/pila_max_cola.o
	$(CXX) $(OBJ)/usopilas_max.o $(OBJ)/pila_max_vd.o $(OBJ)/pila_max_cola.o -o $(BIN)/usopilas_max


# OBJETOS
#Funciona Bien!!!
#$(OBJ)/usopilas_max.o: $(SRC)/usopilas_max.cpp $(INC)/pila_max_vd.h $(INC)/pila_max_cola.h
	#$(CXX) $(CPPFLAGS) $(SRC)/usopilas_max.cpp -o $(OBJ)/usopilas_max.o
$(OBJ)/usopilas_max.o: $(SRC)/usopilas_max.cpp $(INC)/pila_max.h $(INC)/pila_max_vd.h $(INC)/pila_max_cola.h 
		$(CXX) $(CPPFLAGS) $(SRC)/usopilas_max.cpp -o $(OBJ)/usopilas_max.o

$(OBJ)/pila_max_vd.o: $(SRC)/pila_max_vd.cpp $(INC)/pila_max_vd.h
	$(CXX) $(CPPFLAGS) $(SRC)/pila_max_vd.cpp -o $(OBJ)/pila_max_vd.o

$(OBJ)/pila_max_cola.o: $(SRC)/pila_max_cola.cpp $(INC)/pila_max_cola.h
	$(CXX) $(CPPFLAGS) $(SRC)/pila_max_cola.cpp -o $(OBJ)/pila_max_cola.o

# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
