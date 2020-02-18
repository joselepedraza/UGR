.SUFFIXES:
.PHONY: x1, x2, clean

compilador:=g++
#opcionesc:= -std=c++11 -pthread -Wfatal-errors -I.
opcionesu:= -std=c++11 -pthread -o
hmonsrcs:= HoareMonitor.hpp HoareMonitor.cpp

x1: fumadoresSU
	./$<


#############################################

fumadoresSU: fumadoresSU.cpp $(hmonsrcs)
	$(compilador) $(opcionesu)  $@ $< HoareMonitor.cpp HoareMonitor.hpp

clean:
	rm -f  fumadoresSU
