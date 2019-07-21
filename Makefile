mat:
	gcc -o mat ./mat.c ./mattok.c ./main.c -O6

mi2:	
	gcc -o mi2 ./mat.c ./mattok.c ./mi2.c -O6

emi:
	gcc -c emi.c
	gcc -c mat.c
	gcc -c mattok.c
	ar rc libemi.a emi.o mat.o mattok.o

clean:
	rm -rf *.o

del:
	rm -rf *.c
	rm -rf *.h
