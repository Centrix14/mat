init:
	mkdir ./bin
	mkdir ./lib
mat:
	gcc -o ./bin/mat ./src/mat.c ./src/mattok.c ./src/main.c -O6

mi2:
	gcc -o ./bin/mi2 ./src/mat.c ./src/mattok.c ./src/mi2.c -O6

emi:
	gcc -c ./src/emi.c
	gcc -c ./src/mat.c
	gcc -c ./src/mattok.c
	ar rc ./lib/libemi.a emi.o mat.o mattok.o

clean:
	rm -rf *.o

del:
	rm -rf ./src/*.c
	rm -rf ./include/*.h
