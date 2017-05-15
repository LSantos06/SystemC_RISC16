#include <systemc.h>

// Interface do breg
struct breg_if: public sc_interface {

	// Leitura
	virtual
	    int16_t read_breg(uint16_t reg) = 0;

	// Escrita
	virtual
		void write_breg(uint16_t reg, int16_t dado) = 0;

	// Impressao
	virtual
		void dump_breg() = 0;
};
