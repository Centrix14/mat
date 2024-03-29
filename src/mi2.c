#include <stdio.h>
#include <string.h>
#include "../include/mattok.h"
#include "../include/mat.h"

/*
 * mi2.c Interactive Mat interpreter 
 * The main file of the interactive Mat interpreter 
 * v0.3.1
 * by Centrix 26.07.2019
 */

int main(int argc, char *argv[]) {
	char line[256], *tok;

	printf("-- IMI v0.3.1 (Interactive Mat interpreter) by Centrix 26.07.2019 --\n\n");
	while ( 1 ) {
		tok = gettoken(line, 1);

		while ( tok != NULL ) {
			interpret(tok);
			tok = gettoken(line, 0);
		}
		printf("mi2> ");
		fgets(line, 256, stdin);
	}
	return 0;
}
