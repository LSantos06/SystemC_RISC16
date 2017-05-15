#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// Contexto de execucao de uma instrucao
typedef struct contexto {
	uint16_t pc, ri;
	uint16_t op, regs, regs2, regd;
	int16_t const8, const4;
} Contexto_t;
