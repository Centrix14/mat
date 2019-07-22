#ifndef __MAT_EMI_H_INCLUDED__
#define __MAT_EMI_H_INCLUDED__

/*
 * Embedded interpreter mat
 * This file is attached to emi.c
 * v0.2
 * by Centrix 22.07.2019
 */

void matrun(char *prog);
void matfrun(char *fname);
int getCommandOn();
void setCommandOn(int newState);
int getMode();
void setMode(int newState);
int getAcc();
void setAcc(int newValue);
int getLine();
void setLine(int newValue);

#endif
