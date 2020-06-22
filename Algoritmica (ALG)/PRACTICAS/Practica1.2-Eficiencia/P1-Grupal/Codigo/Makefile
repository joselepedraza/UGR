SRC = src
BIN = bin
CXX = g++

all: $(BIN)/burbuja $(BIN)/insercion $(BIN)/seleccion $(BIN)/burbujaO2 $(BIN)/insercionO2 $(BIN)/seleccionO2 $(BIN)/heapsort $(BIN)/mergesort $(BIN)/quicksort $(BIN)/heapsortO2 $(BIN)/mergesortO2 $(BIN)/quicksortO2 $(BIN)/floyd $(BIN)/floydO2 $(BIN)/hanoi $(BIN)/hanoiO2

$(BIN)/burbuja: $(SRC)/burbuja.cpp
	$(CXX) -std=gnu++0x $(SRC)/burbuja.cpp -o $(BIN)/burbuja 

$(BIN)/insercion: $(SRC)/insercion.cpp
	$(CXX) -std=gnu++0x $(SRC)/insercion.cpp -o $(BIN)/insercion 

$(BIN)/seleccion: $(SRC)/seleccion.cpp
	$(CXX) -std=gnu++0x $(SRC)/seleccion.cpp -o $(BIN)/seleccion 

$(BIN)/burbujaO2: $(SRC)/burbuja.cpp
	$(CXX) -O2 -std=gnu++0x $(SRC)/burbuja.cpp -o $(BIN)/burbujaO2 

$(BIN)/insercionO2: $(SRC)/insercion.cpp
	$(CXX) -O2 -std=gnu++0x $(SRC)/insercion.cpp -o $(BIN)/insercionO2 

$(BIN)/seleccionO2: $(SRC)/seleccion.cpp
	$(CXX) -O2 -std=gnu++0x $(SRC)/seleccion.cpp -o $(BIN)/seleccionO2 



$(BIN)/heapsort: $(SRC)/heapsort.cpp
	$(CXX) -std=gnu++0x $(SRC)/heapsort.cpp -o $(BIN)/heapsort 

$(BIN)/mergesort: $(SRC)/mergesort.cpp
	$(CXX) -std=gnu++0x $(SRC)/mergesort.cpp -o $(BIN)/mergesort 

$(BIN)/quicksort: $(SRC)/quicksort.cpp
	$(CXX) -std=gnu++0x $(SRC)/quicksort.cpp -o $(BIN)/quicksort 

$(BIN)/heapsortO2: $(SRC)/heapsort.cpp
	$(CXX) -O2 -std=gnu++0x $(SRC)/heapsort.cpp -o $(BIN)/heapsortO2

$(BIN)/mergesortO2: $(SRC)/mergesort.cpp
	$(CXX) -O2 -std=gnu++0x $(SRC)/mergesort.cpp -o $(BIN)/mergesortO2

$(BIN)/quicksortO2: $(SRC)/quicksort.cpp
	$(CXX) -O2 -std=gnu++0x $(SRC)/quicksort.cpp -o $(BIN)/quicksortO2


$(BIN)/floyd: $(SRC)/floyd.cpp
	$(CXX) -std=gnu++0x $(SRC)/floyd.cpp -o $(BIN)/floyd

$(BIN)/floydO2: $(SRC)/floyd.cpp
	$(CXX) -O2 -std=gnu++0x $(SRC)/floyd.cpp -o $(BIN)/floydO2


$(BIN)/hanoi: $(SRC)/hanoi.cpp
	$(CXX) -std=gnu++0x $(SRC)/hanoi.cpp -o $(BIN)/hanoi

$(BIN)/hanoiO2: $(SRC)/hanoi.cpp
	$(CXX) -O2 -std=gnu++0x $(SRC)/hanoi.cpp -o $(BIN)/hanoiO2

clean :
	-rm $(SRC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/*
