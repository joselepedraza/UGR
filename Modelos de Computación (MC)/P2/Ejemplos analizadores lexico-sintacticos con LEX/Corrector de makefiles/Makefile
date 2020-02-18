SRC = src
INC = include
OBJ = obj
BIN = bin

CXX = g++
CXXFLAGS= -g -I$(INC) -std=c++11

$(BIN)/practica3: $(OBJ)/practica3.o $(OBJ)/escena.o $(OBJ)/ejes.o $(OBJ)/file_ply_stl.o $(OBJ)/grua.o $(OBJ)/figura.o $(OBJ)/revolucion.o $(OBJ)/ply.o $(OBJ)/octaedro.o $(OBJ)/cubo.o $(OBJ)/tetraedro.o
	$(CXX) -o $@ $(CXXFLAGS) $(OBJ)/practica3.o $(OBJ)/escena.o $(OBJ)/ejes.o $(OBJ)/file_ply_stl.o $(OBJ)/grua.o $(OBJ)/figura.o $(OBJ)/revolucion.o $(OBJ)/ply.o $(OBJ)/octaedro.o $(OBJ)/cubo.o $(OBJ)/tetraedro.o $(LDFLAGS)

$(OBJ)/practica3.o: $(SRC)/practica3.cc $(INC)/escena.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/practica3.cc

$(OBJ)/escena.o: $(SRC)/escena.cc $(INC)/escena.h $(INC)/tetraedro.h $(INC)/cubo.h $(INC)/octaedro.h $(INC)/ply.h $(INC)/revolucion.h $(INC)/figura.h $(INC)/ejes.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/escena.cc

$(OBJ)/ejes.o: $(SRC)/ejes.cc $(INC)/ejes.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/ejes.cc

$(OBJ)/file_ply_stl.o: $(SRC)/file_ply_stl.cc $(INC)/file_ply_stl.h $(INC)/vertex.h $(INC)/figura.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/file_ply_stl.cc

$(OBJ)/grua.o: $(SRC)/grua.cc $(INC)/grua.h $(INC)/ply.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/grua.cc

$(OBJ)/figura.o: $(SRC)/figura.cc $(INC)/figura.h $(INC)/vertex.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/figura.cc

$(OBJ)/revolucion.o: $(SRC)/revolucion.cc $(INC)/revolucion.h $(INC)/file_ply_stl.h $(INC)/figura.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/revolucion.cc

$(OBJ)/ply.o: $(SRC)/ply.cc $(INC)/ply.h $(INC)/file_ply_stl.h $(INC)/figura.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/ply.cc

$(OBJ)/octaedro.o: $(SRC)/octaedro.cc $(INC)/octaedro.h $(INC)/figura.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/octaedro.cc

$(OBJ)/cubo.o: $(SRC)/cubo.cc $(INC)/cubo.h $(INC)/figura.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/cubo.cc

$(OBJ)/tetraedro.o: $(SRC)/tetraedro.cc $(INC)/tetraedro.h $(INC)/figura.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/tetraedro.cc

