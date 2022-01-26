.SUFFIXES:
.PHONY: x1, x2, clean

compilador:=g++
opcionesc:= -std=c++11 -pthread -Wfatal-errors -I.
opcionesu:= -std=c++11 -pthread -o
hmonsrcs:= HoareMonitor.hpp HoareMonitor.cpp


#x1: prodcons1_sc_lifo
#	./$<

x2: ProdCons1SU_lifo
	./$<

#x3: prodcons1SU_fifo
	#./$<


#############################################
prodcons1_sc_lifo: prodcons1_sc.cpp $(hmonsrcs)
	$(compilador) $(opcionesc)  -o $@ $< HoareMonitor.cpp

ProdCons1SU_lifo: ProdCons1SU.cpp $(hmonsrcs)
	$(compilador) $(opcionesu)  $@ $< HoareMonitor.cpp HoareMonitor.hpp

#prodcons1SU_fifo: prodcons1SU_fifo.cpp $(hmonsrcs)
	#$(compilador) $(opcionesc)  -o $@ $<  HoareMonitor.cpp HoareMonitor.hpp

clean:
	rm -f  prodcons1_sc_lifo prodcons1SU_lifo #prodcons2_su
