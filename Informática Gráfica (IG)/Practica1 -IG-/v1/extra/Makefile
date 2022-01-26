# Directorios
BIN		= bin
SRC		= src
INCLUDE	= include

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


# banderas para el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
LDFLAGS	= -lGL -lGLU -lglut -lm

# Ordenes Compilacion
all: clean $(TARGETS)

$(TARGETS):
	$(CXX) -o $(BIN)/$@ $(SRC)/$@.cc $(CXXFLAGS) $(SRC)/puntos3D.cpp $(SRC)/triangulos.cpp $(SRC)/cubo.cpp $(SRC)/cubo_centrado.cpp $(SRC)/piramide.cpp $(SRC)/diamante.cpp $(LDFLAGS)

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