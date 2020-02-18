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
$(BIN)/usopilas_max: $(OBJ)/usopilas_max.o
	$(CXX) $(OBJ)/usopilas_max.o -o $(BIN)/usopilas_max -I$(INC)


# OBJETOS
#Funciona Bien!!!
$(OBJ)/usopilas_max.o: $(SRC)/usopilas_max.cpp
	$(CXX) $(CPPFLAGS) -o $(OBJ)/usopilas_max.o  $(SRC)/usopilas_max.cpp

# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
