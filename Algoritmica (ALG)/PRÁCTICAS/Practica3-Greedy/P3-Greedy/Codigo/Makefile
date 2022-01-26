SRC = src
BIN = bin
CXX = g++

all: $(BIN)/tsp_vmc $(BIN)/tsp_insercion $(BIN)/tsp_2opt $(BIN)/grafo $(BIN)/arbol

$(BIN)/tsp_vmc: $(SRC)/tsp_vmc.cpp
	$(CXX) -std=gnu++0x $(SRC)/tsp_vmc.cpp -o $(BIN)/tsp_vmc

$(BIN)/tsp_insercion: $(SRC)/tsp_insercion.cpp
	$(CXX) -std=gnu++0x $(SRC)/tsp_insercion.cpp -o $(BIN)/tsp_insercion

$(BIN)/tsp_2opt: $(SRC)/tsp_2opt.cpp
	$(CXX) -std=gnu++0x $(SRC)/tsp_2opt.cpp -o $(BIN)/tsp_2opt

$(BIN)/grafo: $(SRC)/grafo.cpp
	$(CXX) -std=gnu++0x $(SRC)/grafo.cpp -o $(BIN)/grafo

$(BIN)/arbol: $(SRC)/arbol.cpp
	$(CXX) -std=gnu++0x $(SRC)/arbol.cpp -o $(BIN)/arbol

clean :
	-rm $(SRC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/*
