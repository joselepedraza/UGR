.PHONY: x clean tar

# Directorios
BIN		= bin
SRC		= src
INCLUDE	= include
DATA = data

# Ejecutable Practica
TARGETS = main

# Compilador
CXX	= g++ -Ofast -Wno-write-strings
CC		= gcc -Ofast

# Flags: 
#banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuraci�n
CFLAGS	= -g -DXWINDOWS -DSHM -I/usr/include -I$(INCLUDE) - Wno-deprecated
CXXFLAGS	= -g -DXWINDOWS -DSHM -I/usr/include -I$(INCLUDE) -Wno-deprecated

CPPFLAGS:= -Wall -fmax-errors=2 -g

# banderas para el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
LDFLAGS	= -lglut -lGLU -lGL -lsupc++ -lm -lc -lstdc++ -lpthread -L/usr/lib/nvidia-331

# Ordenes Compilacion
#all: clean $(TARGETS)

x: $(TARGETS)
	./$(BIN)/$(TARGETS) $(DATA)/beethoven $(DATA)/peon

$(TARGETS):
	$(CXX) -o $(BIN)/$@ $(SRC)/$@.cc $(CPPFLAGS) $(SRC)/puntos3D.cpp $(SRC)/triangulos3D.cpp $(SRC)/modelos_basicos.cpp\
			$(SRC)/modelos_revolucion.cpp $(SRC)/modelo_ply.cpp $(SRC)/file_ply_stl.cc $(LDFLAGS) 

# Limpiador
#
clean:
	rm -f $(BIN)/*.o
	rm -f $(TARGETS)

#
#
redo:
	touch *.cc
	make

#
#
superclean:
	rm -f $(BIN)/*.o
	rm *~
	rm -f $(TARGETS)

#
#
tgz:
	rm -f $(BIN)/*.o
	rm *~
	rm -f $(TARGETS)
	tar -zcvf $(TARGETS).tgz *