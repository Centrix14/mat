#include <stdio.h>
#include "mattok.h"
#include "mat.h"

/*
 * mfi (mat file interpreter)
 * The main file of the mat interpreter
 * v0.2.2
 * by Centrix 19.07.2019
 */

int main(int argc, char *argv[]) {
	FILE *source;
	char line[256], *tok;

	if ( argc != 2 ) {
		fprintf(stderr, "Usage: mat <filename>\n");
		return -1;
	}

	source = fopen(argv[1], "r");
	if ( source == NULL ) {
		fprintf(stderr, "file error\n");
		return -1;
	}

	fgets(line, 256, source);
	while ( !feof(source) ) {
		tok = gettoken(line, 1);

		while ( tok != NULL ) {
			interpret(tok);
			tok = gettoken(line, 0);
		}
		fgets(line, 256, source);
	}

	fclose(source);
	return 0;
}
