#include "breg.h"

// Leitura
int16_t breg_risc::read_breg(uint16_t reg){
	return breg[reg];
}
// Escrita
void breg_risc::write_breg(uint16_t reg, int16_t dado){
	breg[reg] = dado;
}
// Impressao
void breg_risc::dump_breg(){
	for (int i=0; i<=16; i++) {
		printf("BREG[%2d] = \t%4d \t\t\t%x\n", i, breg[i], breg[i]);
	}
}
