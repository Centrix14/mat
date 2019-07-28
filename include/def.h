#ifndef __MAT_DEF_H_INCLUDED__
#define __MAT_DEF_H_INCLUDED__

#define ERROR -1
#define ON 1
#define OFF -1

#define MODE_EMPTY -1

#define TRUE 1
#define FALSE 0

enum mathStates {
	ADD = 0,
	SUBT,
	MULT,
	DIV,
	ASSIGN,
	AND,
	OR,
	NOT,
	NEG,
	ABS,
	ROOT,
	POW,
	BIGGER = 15,
	SMALLER,
	BIGGER_OR_EQ,
	SMALLER_OR_EQ,
	EQ,
	NOT_EQ
};

typedef struct {
	int commandOn;
	int mode;
	int fpos;
	int acc;
	int line;
	int cmpResult;
	int enableExec;
} context;

context con = {OFF, MODE_EMPTY, 0, 0, 1, 0, 1};

#endif
