#ifndef __MAT_H_INCLUDED__
#define __MAT_H_INCLUDED__

/*
 * Minimalistic AutomaTon language
 * This file is attached to mat.c
 * v0.3.2
 * by Centrix 26.07.2019
 */

void setPrintError(int newValue);
void setStopWhenError(int newValue);

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
void neg(char *arg);
void module(char *arg);
void root(char *arg);
void power(char *arg);
void bigger(char *arg);
void biggerOrEq(char *arg);
void smaller(char *arg);
void smallerOrEq(char *arg);
void eq(char *arg);
void notEq(char *arg);
void cmpr(char *arg);
void isTrue(char *arg);
void isFalse(char *arg);
void end(char *arg);

int isint(char *tok);
int error(char *arg);

#endif
