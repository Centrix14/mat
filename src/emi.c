#include <stdio.h>
#include "../include/def.h"
#include "../include/mat.h"
#include "../include/mattok.h" 

/*
 * Embedded interpreter mat 
 * It can be used to interpret programs on mat in other programs.
 * v0.1
 * by Centrix 21.07.2019
 */

void matrun(char *prog) {
	char *tok = gettoken(prog, 1);

	while ( tok != NULL ) {
		interpret(tok);
		tok = gettoken(prog, 0);
	}
}

void matfrun(char *fname) {
	FILE *source = fopen(fname, "r");
	char *tok, line[256];

	if ( source == NULL ) {
		fprintf(stderr, "Can`t open `%s`\n", fname);
		return;
	}

	fgets(line, 256, source);
	while ( !feof(source) ) {
		tok = gettoken(line, 1);

		while (tok != NULL) {
			interpret(tok);
			tok = gettoken(line, 0);
		}
		fgets(line, 256, source);
	}

	fclose(source);
}
