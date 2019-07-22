#ifndef __MAT_DEF_H_INCLUDED__
#define __MAT_DEF_H_INCLUDED__

#define ERROR -1
#define ON 1
#define OFF -1

#define MODE_EMPTY -1

enum states {
	ADD = 0,
	SUBT,
	MULT,
	DIV,
	ASSIGN = 5,
	AND = 8,
	OR,
	NOT
};

typedef struct {
	int commandOn;
	int mode;
	int fpos;
	int acc;
	int line;
} context;

context con = {OFF, MODE_EMPTY, 0, 0, 1};

#endif
