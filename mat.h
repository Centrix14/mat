#ifndef __MAT_H_INCLUDED__
#define __MAT_H_INCLUDED__

/*
 * Minimalistic AutomaTon language
 * This file is attached to mat.c
 * v0.2.1
 * by Centrix 19.07.2019
 */

#define ERROR -1
#define ON 1
#define OFF -1

#define MODE_EMPTY -1

typedef struct {
	int commandOn;
	int mode;
	int fpos;
	int acc;
	int line;
} context;

int findseq(char *str, char *fndlist[], int range);
int getCommandType(char *tok);
void interpret(char *tok);
void execCommand(int type, char *arg);

void add(char *arg);
void subt(char *arg);
void mult(char *arg);
void cdiv(char *arg);
void out(char *arg);
void assign(char *arg);
void print(char *arg);

int isint(char *tok);
int error(char *arg);

#endif
