#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/def.h"
#include "../include/mat.h"
#include "../include/mattok.h"

/*
 * Minimalistic AutomaTon language
 * This file contains the Mat interpreter
 * v0.2.4
 * by Centrix 22.07.2019
 */

char *commandList[] = {"+", "-", "*", "/", "r", ":", "output", "~", "&", "|", "_!", "term"};
int commandCount = 12;
void (*funcList[]) (char *) = {add, subt, mult, cdiv, out, assign, print, comment, and, or, not, term};
char *empty = " \n_";
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
	if ( getCommandType(tok) != ERROR ) {	
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
	if ( error(arg) ) return;
	printf("%d\n", con.acc);
	con.mode = MODE_EMPTY;
}

void print(char *arg) {
	if ( !strcmp(arg, "output") || !strcmp(arg, "_") ) return;
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
	strclean(command);
}

void cat(char *dst, char *src) {
	strcat(dst, src);
}

void term(char *arg) {
	static char command[256] = "\0";

	if ( !strcmp(arg, "term") ) return;
	if ( !strcmp(arg, "$") ) {
		commandRun(command);
		return;
	}

	cat(command, arg);
}
 
void typeErrorReport(char *arg) {
	fprintf(stderr, "\n[%s]: Type error in line %d: expected number but passed `%s`\n", commandList[con.mode], con.line, arg);
}

int isMathorLog() {
	if ( (con.mode >= ADD && con.mode <= DIV) || (con.mode == ASSIGN) || (con.mode >= AND && con.mode <= NOT) )
		return 1;
	return 0;
}

int error(char *arg) {
	if ( com ) return 0;

	if ( isMathorLog() ) {
		if ( !strcmp(arg, commandList[con.mode]) || strstr(empty, arg) ) return 0;
		if ( isint(arg) ) {
			if ( !atoi(arg) && con.mode != ASSIGN && con.mode != AND ) {
				fprintf(stderr, "\nWarning line %d: operation with 0.\n", con.line);
				exit(0);
			}
			return 1;
		}
		else {
			typeErrorReport(arg);
			exit(0);
		}
	}
	else {
		if ( con.mode == findseq(arg, commandList, commandCount) ) return 0;
		return 1;
	}
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
