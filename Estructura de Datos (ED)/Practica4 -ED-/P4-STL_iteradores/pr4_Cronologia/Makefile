SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++ -std=c++11
#CPPFLAGS = -Wall -g  -I$(INC) -c
CPPFLAGS = -g  -I$(INC) -c

# GENERAL #
all: $(BIN)/filtradoIntervalo $(BIN)/filtradoPalabraClave $(BIN)/union_cronologia $(BIN)/estadisticaEventos
# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile


# ************ Compilación de módulos ************
# EJECUTABLES #
$(BIN)/pruebacronologia: $(OBJ)/pruebacronologia.o $(OBJ)/cronologia.o $(OBJ)/fechahistorica.o
	$(CXX) $(OBJ)/pruebacronologia.o $(OBJ)/cronologia.o $(OBJ)/fechahistorica.o -o $(BIN)/pruebacronologia

$(BIN)/filtradoIntervalo: $(OBJ)/filtradoIntervalo.o $(OBJ)/cronologia.o $(OBJ)/fechahistorica.o
	$(CXX) $(OBJ)/filtradoIntervalo.o $(OBJ)/cronologia.o $(OBJ)/fechahistorica.o -o $(BIN)/filtradoIntervalo

$(BIN)/filtradoPalabraClave: $(OBJ)/filtradoPalabraClave.o $(OBJ)/cronologia.o $(OBJ)/fechahistorica.o
	$(CXX) $(OBJ)/filtradoPalabraClave.o $(OBJ)/cronologia.o $(OBJ)/fechahistorica.o -o $(BIN)/filtradoPalabraClave
	
$(BIN)/union_cronologia: $(OBJ)/union_cronologia.o $(OBJ)/cronologia.o $(OBJ)/fechahistorica.o
	$(CXX) $(OBJ)/union_cronologia.o $(OBJ)/cronologia.o $(OBJ)/fechahistorica.o -o $(BIN)/union_cronologia

$(BIN)/estadisticaEventos: $(OBJ)/estadisticaEventos.o $(OBJ)/cronologia.o $(OBJ)/fechahistorica.o
	$(CXX) $(OBJ)/estadisticaEventos.o $(OBJ)/cronologia.o $(OBJ)/fechahistorica.o -o $(BIN)/estadisticaEventos

# OBJETOS #
$(OBJ)/pruebacronologia.o: $(SRC)/pruebacronologia.cpp $(INC)/cronologia.h
	$(CXX) $(CPPFLAGS) $(SRC)/pruebacronologia.cpp -o $(OBJ)/pruebacronologia.o
	
$(OBJ)/filtradoIntervalo.o: $(SRC)/filtradoIntervalo.cpp $(INC)/cronologia.h
	$(CXX) $(CPPFLAGS) $(SRC)/filtradoIntervalo.cpp -o $(OBJ)/filtradoIntervalo.o
	
$(OBJ)/filtradoPalabraClave.o: $(SRC)/filtradoPalabraClave.cpp $(INC)/cronologia.h
	$(CXX) $(CPPFLAGS) $(SRC)/filtradoPalabraClave.cpp -o $(OBJ)/filtradoPalabraClave.o	
	
$(OBJ)/union_cronologia.o: $(SRC)/union_cronologia.cpp $(INC)/cronologia.h
	$(CXX) $(CPPFLAGS) $(SRC)/union_cronologia.cpp -o $(OBJ)/union_cronologia.o
	
$(OBJ)/estadisticaEventos.o: $(SRC)/estadisticaEventos.cpp $(INC)/cronologia.h
	$(CXX) $(CPPFLAGS) $(SRC)/estadisticaEventos.cpp -o $(OBJ)/estadisticaEventos.o	

$(OBJ)/cronologia.o: $(INC)/cronologia.h $(INC)/fechahistorica.h $(SRC)/cronologia.cpp
	$(CXX) $(CPPFLAGS) $(SRC)/cronologia.cpp -o $(OBJ)/cronologia.o

$(OBJ)/fechahistorica.o: $(INC)/fechahistorica.h $(SRC)/fechahistorica.cpp
	$(CXX) $(CPPFLAGS) $(SRC)/fechahistorica.cpp -o $(OBJ)/fechahistorica.o
	
	
	


# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
