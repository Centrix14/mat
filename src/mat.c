#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "../include/def.h"
#include "../include/mat.h"
#include "../include/mattok.h"

/*
 * Minimalistic AutomaTon language
 * This file contains the Mat interpreter
 * v0.3.1
 * by Centrix 26.07.2019
 */

char *commandList[] = {"+", "-", "*", "/", ":", "&", "|", "_!", "neg", "abs", "sqrt", "^", "output", "term", "r",\
		">", "<", ">=", "<=", "=", "!=", "cmpr", "TRUE", "FALSE", "END"};
int commandCount = 25;
void (*funcList[]) (char *) = {add, subt, mult, cdiv, assign, and, or, not, neg, module, root, power, print, term,\
		out, bigger, smaller, biggerOrEq, smallerOrEq, eq, notEq, cmpr, isTrue, isFalse, end};
char *empty = " \n_";
char *single[] = {"r", "_!", "neg", "abs", "sqrt", "cmpr", "TRUE", "FALSE"};
int singleCount = 8; 
int com = 0;

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
	if ( !strcmp(tok, "\n") )
			con.line++;
	if ( !strcmp(tok, "~") ) {
		comment(tok);
		return;
	}
	if ( getCommandType(tok) != ERROR && !com ) {	
		con.commandOn = ON;
		con.mode = getCommandType(tok);
	}
	else 
		con.commandOn = OFF;	
	execCommand(con.mode, tok);
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
	if ( error(arg) ) { 
		printf("%d\n", con.acc);
		con.mode = MODE_EMPTY;
	}
}

void print(char *arg) {
	if ( (!strcmp(arg, "output") || !strcmp(arg, "_")) || com ) return;
	if ( con.enableExec )
		printf("%s", arg);
}

void comment(char *arg) {
	if ( !strcmp(arg, "~") && com == 0 ) com = 1;
	else if ( !strcmp(arg, "~") && com == 1 ) com = 0;
}

void and(char *arg) {
	if ( error(arg) )
		con.acc &= atoi(arg);
}

void or(char *arg) {
	if ( error(arg) )
		con.acc |= atoi(arg);	
}

void not(char *arg) {
	if ( error(arg) )
		con.acc = !con.acc;	
}

void strclean(char *str) {
	int i = 0;

	while ( str[i] ) str[i++] = ' ';
	str[0] = '\0';
}

void commandRun(char *command) {
	if ( system(NULL) )
		system(command);
	else {
		fprintf(stderr, "Automaton error: the terminal is unavailable, the transition to the term state is not made.");
		exit(0);
	}
	strclean(command);
}

void cat(char *dst, char *src) {
	strcat(dst, src);
}

void term(char *arg) {
	static char command[256] = "\0";

	if ( !strcmp(arg, "term") || com ) return;
	if ( !strcmp(arg, "$") ) {
		commandRun(command);
		return;
	}
	cat(command, arg);
}

void neg(char *arg) {
	if ( error(arg) )
		con.acc = -con.acc;	
	
	con.mode = MODE_EMPTY;
}

void module(char *arg) {
	if ( error(arg) )
		con.acc = abs(con.acc);
	con.mode = MODE_EMPTY;
}

void root(char *arg) {
	if ( error(arg) )
		con.acc = sqrt(con.acc);
	con.mode = MODE_EMPTY;
}

int powi(int base, int exp) {
	int out = 1;
	
	while ( exp ) {
		out = base * out;
		exp--;
	}
	return out;
}

void power(char *arg) {
	if ( error(arg) )
		con.acc = powi(con.acc, atoi(arg));	
}

void bigger(char *arg) {
	if ( error(arg) )
		con.cmpResult = con.acc > atoi(arg);	
}

void smaller(char *arg) {
	if ( error(arg) ) 
		con.cmpResult = con.acc < atoi(arg);
}

void eq(char *arg) {
	if ( error(arg) ) 
		con.cmpResult = con.acc == atoi(arg);
}

void notEq(char *arg) {
	if ( error(arg) ) 
		con.cmpResult = con.acc != atoi(arg);
}

void biggerOrEq(char *arg) {
	if ( error(arg) ) 
		con.cmpResult = con.acc >= atoi(arg);
}

void smallerOrEq(char *arg) {
	if ( error(arg) ) 
		con.cmpResult = con.acc <= atoi(arg);
}

void cmpr(char *arg) {
	if ( error(arg) ) 
		printf("%d", con.cmpResult);
	con.mode = MODE_EMPTY;
}

void isTrue(char *arg) {
	if ( con.cmpResult )
		con.enableExec = 1;
	else
		con.enableExec = 0;	
	con.mode = MODE_EMPTY;
}

void isFalse(char *arg) {
	if ( !con.cmpResult )
		con.enableExec = 1;
	else
		con.enableExec = 0;	
	con.mode = MODE_EMPTY;
}

void end(char *arg) {
	con.enableExec = 1;
	con.mode = MODE_EMPTY;
}
 
void typeErrorReport(char *arg) {
	fprintf(stderr, "\n[%s]: Type error in line %d: expected number but passed `%s`\n", commandList[con.mode], con.line, arg);
}

int isMathorLog() {
	if ( con.mode >= 0 && con.mode <= 11 )
		return 1;
	return 0;
}

int error(char *arg) {
	if ( com ) return 0;
	if ( !con.enableExec ) return 0;

	if ( isMathorLog() ) {
		if ( findseq(arg, single, singleCount) != ERROR ) return 1;	
		if ( !strcmp(arg, commandList[con.mode]) || strstr(empty, arg) ) return 0;
		if ( isint(arg) ) {
			if ( !atoi(arg) && con.mode != ASSIGN && con.mode != AND ) {
				fprintf(stderr, "\nWarning line %d: operation with 0.\n", con.line);
				exit(0);
			}
			return 1;
		}
		else {
			if ( findseq(arg, single, singleCount) != ERROR ) return 1;	
			typeErrorReport(arg);
			exit(0);
		}
	}
	else 
		if ( findseq(arg, single, singleCount) != ERROR ) return 1;	
		if ( !strcmp(commandList[con.mode], arg) && findseq(arg, single, singleCount) == ERROR ) return 0;
	
	return 1;
}

int getCommandOn() {
	return con.commandOn;
}

void setCommandOn(int newState) {
	con.commandOn = newState;
}

int getMode() {
	return con.mode;
}

void setMode(int newState) {
	con.mode = newState;
}

int getAcc() {
	return con.acc;
}

void setAcc(int newValue) {
	con.acc = newValue;
}

int getLine() {
	return con.line;
}

void setLine(int newValue) {
	con.line = newValue;
}
