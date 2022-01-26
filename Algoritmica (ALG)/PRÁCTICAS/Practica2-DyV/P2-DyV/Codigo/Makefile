SRC = src
BIN = bin
CXX = g++

all: $(BIN)/mezcla_DyV $(BIN)/matrix_DyV $(BIN)/mezcla_bruta $(BIN)/matrix_bruta 

$(BIN)/mezcla_DyV: $(SRC)/mezcla_DyV.cpp
	$(CXX) -std=gnu++0x $(SRC)/mezcla_DyV.cpp -o $(BIN)/mezcla_DyV 

$(BIN)/mezcla_bruta: $(SRC)/mezcla_bruta.cpp
	$(CXX) -std=gnu++0x $(SRC)/mezcla_bruta.cpp -o $(BIN)/mezcla_bruta 

$(BIN)/matrix_DyV: $(SRC)/matrix_DyV.cpp
	$(CXX) -std=gnu++0x $(SRC)/matrix_DyV.cpp -o $(BIN)/matrix_DyV 

$(BIN)/matrix_bruta: $(SRC)/mezcla_bruta.cpp
	$(CXX) -std=gnu++0x $(SRC)/matrix_bruta.cpp -o $(BIN)/matrix_bruta

clean :
	-rm $(SRC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/*
