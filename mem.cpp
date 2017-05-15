#include <systemc.h>
#include "mem.h"

// Leitura
int16_t mem_risc::read_mem(uint16_t endereco){
	return mem[endereco];
}
// Escrita
void  mem_risc::write_mem(uint16_t endereco, int16_t dado){
	mem[endereco] = dado;
}
// Impressao
void  mem_risc::dump_mem(uint16_t inicio, uint16_t fim, char formato){
	switch (formato) {
		case 'h':
		case 'H':
			for (uint16_t i = inicio; i <= fim; i++)
				printf("%x \t%x\n", i, mem[i]);
			break;

		case 'd':
		case 'D':
			for (uint16_t i = inicio; i <= fim; i++)
				printf("%x \t%d\n", i, mem[i]);
			break;

		default:
			break;
	}
}
