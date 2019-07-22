#ifndef __MAT_H_INCLUDED__
#define __MAT_H_INCLUDED__

/*
 * Minimalistic AutomaTon language
 * This file is attached to mat.c
 * v0.2.4
 * by Centrix 22.07.2019
 */

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
void comment(char *arg);
void and(char *arg);
void or(char *arg);
void not(char *arg);
void term(char *arg);

int isint(char *tok);
int error(char *arg);

#endif