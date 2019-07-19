#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "mattok.h"

/*
 * Mat Tokenizer
 * This file contains my tokenizer for an interpreter Mat
 * v0.1
 * by Centrix 19.07.2019
 */

char __tok[256];

int gettypec(int c) {
	int (*func[]) (int) = {isalpha, isdigit, ispunct, isspace, iscntrl};

	for (int i = 0; i < 5; i++) 
		if ( (*func[i])(c) )
			return i;
	
	return -1;
}

char *gettoken(char *src, int new) {
	static int pos = 0;
	int i = 0;
	
	if ( new ) 
		pos = 0;
	if ( !src[pos] ) return NULL;

	while (1) {
		if ( gettypec(src[pos]) == gettypec(src[pos+1]) ) __tok[i++] = src[pos++];
		else {
			__tok[i++] = src[pos++];
			break;
		}
	}		
	__tok[i] = '\0';

	return __tok;
}

int gettoktype(char *tok) {
	int (*funcs[]) (char *) = {isword, isint, ischaracter, isempty, iscontrol};

	for (int i = 0; i < 5; i++) {
		if ( (*funcs[i])(tok) ) return i;
	}
	return -1;
}

int istoktype(char *src, int type) {
	int i = 0;

	while (src[i])
		if (gettypec(src[i++]) != type) return 0;
	return 1;
}

int isword(char *src) {
	return istoktype(src, LETTER); 
}

int isint(char *src) {
	return istoktype(src, DIGIT);
}

int ischaracter(char *src) {
	return istoktype(src, CHARACTER);
}

int isempty(char *src) {
	return istoktype(src, SPACE);
}

int iscontrol(char *src) {
	return istoktype(src, CONTROL);
}
