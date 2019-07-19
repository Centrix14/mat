#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mat.h"
#include "mattok.h"

/*
 * Mathematical AuTomaton language
 * This file contains the Mat interpreter
 * v0.1
 * by Centrix 19.07.2019
 */

context con = {OFF, MODE_EMPTY, 0, 0, 1};
char *commandList[] = {"+", "-", "*", "/", "r", ":", "output"};
int commandCount = 7;
void (*funcList[]) (char *) = {add, subt, mult, cdiv, out, assign, print};

int findseq(char *str, char *fndlist[], int range) {
	for (int i = 0; i < range; i++) {
		if ( !strcmp(str, fndlist[i]) ) return i;
	}
	return ERROR;
}

int getCommandType(char *tok) {
	return findseq(tok, commandList, commandCount);
}

void interpret(char *tok) {
	if ( !strcmp(tok, "\n") && con.commandOn == ON )
			con.line++;
	else  {
		if ( getCommandType(tok) != ERROR ) {	
			con.commandOn = ON;
			con.mode = getCommandType(tok);
		}
		else 
			con.commandOn = OFF;	
		execCommand(con.mode, tok);
   	}	
}

void execCommand(int type, char *arg) {
	if (type == MODE_EMPTY) return;
	(*funcList[type])(arg);
}

void add(char *arg) {
	if ( isint(arg) )	
		con.acc += atoi(arg);
	else {
		if ( !strcmp(arg, "+") ) return;	
		fprintf(stderr, "[+]: Type error in line %d: expected number but passed `%s`\n", con.line, arg);
		exit(0);
	}
}

void subt(char *arg) {
	if ( isint(arg) )	
		con.acc -= atoi(arg);
	else {
		if ( !strcmp(arg, "-") ) return;	
		fprintf(stderr, "[-]: Type error in line %d: expected number but passed `%s`\n", con.line, arg);
		exit(0);
	}
}

void mult(char *arg) {
	if ( isint(arg) )	
		con.acc *= atoi(arg);
	else {
		if ( !strcmp(arg, "*") ) return;	
		fprintf(stderr, "[*]: Type error in line %d: expected number but passed `%s`\n", con.line, arg);
		exit(0);
	}
}

void cdiv(char *arg) {
	if ( isint(arg) )	
		con.acc /= atoi(arg);
	else {
		if ( !strcmp(arg, "/") ) return;	
		fprintf(stderr, "[/]: Type error in line %d: expected number but passed `%s`\n", con.line, arg);
		exit(0);
	}
}

void assign(char *arg) {
	if ( isint(arg) )
		con.acc = atoi(arg);
	else {
		if ( !strcmp(arg, ":") ) return;	
		fprintf(stderr, "[:]: Type error in line %d: expected number but passed `%s`\n", con.line, arg);
		exit(0);
	}
}

void out(char *arg) {
	printf("%d\n", con.acc);
	con.mode = MODE_EMPTY;
}

void print(char *arg) {
	if ( !strcmp(arg, "output") ) return;
	printf("%s", arg);
}
