bin/main: obj/main.o lib/libled.a
	g++ -o bin/main obj/main.o -Llib/ -lled
lib/libled.a: obj/bloqueLed.o obj/main.o
	ar rsv lib/libled.a obj/bloqueLed.o obj/main.o
obj/bloqueLed.o: src/bloqueLed.cpp include/bloqueLed.h
	g++ -c src/bloqueLed.cpp -o obj/bloqueLed.o -Iinclude/
obj/main.o: src/main.cpp include/bloqueLed.h obj/bloqueLed.o
		g++ -c src/main.cpp -o obj/main.o -Iinclude/
