#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mat.h"
#include "mattok.h"

/*
 * Minimalistic AutomaTon language
 * This file contains the Mat interpreter
 * v0.2.1
 * by Centrix 20.07.2019
 */

enum states {
	ADD = 0,
	SUBT,
	MULT,
	DIV,
	ASSIGN = 5		
};

context con = {OFF, MODE_EMPTY, 0, 0, 1};
char *commandList[] = {"+", "-", "*", "/", "r", ":", "output"};
int commandCount = 7;
void (*funcList[]) (char *) = {add, subt, mult, cdiv, out, assign, print};
char *empty = "+-*/: \n";

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
	if ( error(arg) )	
		con.acc += atoi(arg);
}

void subt(char *arg) {
	if ( error(arg) )	
		con.acc -= atoi(arg);
}

void mult(char *arg) {
	if ( error(arg) )	
		con.acc *= atoi(arg);
}

void cdiv(char *arg) {
	if ( error(arg) )	
		con.acc /= atoi(arg);
}

void assign(char *arg) {
	if ( error(arg) )	
		con.acc = atoi(arg);
}

void out(char *arg) {
	printf("%d\n", con.acc);
	con.mode = MODE_EMPTY;
}

void print(char *arg) {
	if ( !strcmp(arg, "output") ) return;
	printf("%s", arg);
}

void typeErrorReport(char *arg) {
	fprintf(stderr, "[%s]: Type error in line %d: expected number but passed `%s`\n", commandList[con.mode], con.line, arg);
}

int error(char *arg) {
	if ( con.mode >= ADD && con.mode <= DIV || con.mode == ASSIGN ) {
		if ( !strcmp(arg, commandList[con.mode]) ) return 0;
		if ( isint(arg) ) {
			if ( atoi(arg) ) return 1;
			else {
				fprintf(stderr, "Warning line %d: operation with 0.\n", con.line);
				exit(0);
			}
		}
		else {
			typeErrorReport(arg);
			exit(0);
		}
	}
}
