.SUFFIXES:
.PHONY: x1, x2, clean

compilador:=g++
opcionesc:= -std=c++11 -pthread -Wfatal-errors -I.
hmonsrcs:= HoareMonitor.hpp HoareMonitor.cpp


x1: prodcons1_su_FIFO
	./$<

#x6: prodcons2_sc
	#./$<

#x7: prodcons2_su
	#./$<


#############################################
prodcons1_sc: prodcons1_su_FIFO.cpp $(hmonsrcs)
	$(compilador) $(opcionesc)  -o $@ $< HoareMonitor.cpp

#prodcons2_sc: prodcons2_sc.cpp $(hmonsrcs)
	#$(compilador) $(opcionesc)  -o $@ $<

#prodcons2_su: prodcons2_su.cpp $(hmonsrcs)
	#$(compilador) $(opcionesc)  -o $@ $<  HoareMonitor.cpp

clean:
	rm -f  prodcons1_su_FIFO #prodcons2_sc prodcons2_su
