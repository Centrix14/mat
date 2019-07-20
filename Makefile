all:
	gcc -o mat ./mat.c ./mattok.c ./main.c -O6
	gcc -o mi2 ./mat.c ./mattok.c ./mi2.c -O6
