#include <stdio.h>
#include "../include/mattok.h"
#include "../include/mat.h"

/*
 * mfi (mat file interpreter)
 * The main file of the mat interpreter
 * v0.3.2
 * by Centrix 26.07.2019
 */

void readConfig(char *name);

int main(int argc, char *argv[]) {
	FILE *source;
	char line[256], *tok;

	if ( argc < 2 ) {
		fprintf(stderr, "Usage: mat <filename>\n");
		return -1;
	}

	source = fopen(argv[1], "r");
	if ( source == NULL ) {
		fprintf(stderr, "mat: Cannot open the file `%s`\n", argv[1]);
		return -1;
	}

	if (argc == 3) {
		readConfig(argv[2]);
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

void silence() {
	setPrintError(0);
}

void noStop() {
	setStopWhenError(0);
}

void readConfig(char *name) {
	char *options[] = {"silence", "noStop"};	
	void (*funcs[]) () = {silence, noStop};	
	FILE *config = fopen(name, "r");
	char line[256];
	char *word;
	int funcCount = 2;
	int indx = 0;

	if ( config == NULL ) {
		fprintf(stderr, "readConfig: Can`t open configuration file `%s`\n", name);
		return;
	}

	fgets(line, 256, config);

	while ( !feof(config) ) {
		word = gettoken(line, 1);

		while ( word ) {	
			indx = findseq(word, options, funcCount);

			if ( indx != -1 ) {
				(*funcs[indx])();
			}

			word = gettoken(line, 0);
		}
		fgets(line, 256, config);
	}

	fclose(config);
}
