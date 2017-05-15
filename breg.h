#include <systemc.h>
#include "breg_if.h"

/*
 *  Banco de registradores que implementa a interface breg_if, eh
 * utilizado na fase de EXECUTE.
 */
struct breg_risc: public sc_module, public breg_if {

	// Leitura
	int16_t read_breg(uint16_t reg);
	// Escrita
	void write_breg(uint16_t reg, int16_t dado);
	// Impressao
	void dump_breg();

	SC_HAS_PROCESS(breg_risc);

	// Declaracao do breg
	breg_risc (sc_module_name n) :
		sc_module(n){
		breg = new int16_t[16];
	}

private:
	int16_t *breg;

};
