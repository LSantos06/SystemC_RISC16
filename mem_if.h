#include <systemc.h>

// Interface da memoria
struct mem_if: public sc_interface {

	// Leitura
	virtual
		int16_t read_mem(uint16_t endereco) = 0;

	// Escrita
	virtual
		void write_mem(uint16_t endereco, int16_t dado) = 0;

	// Impressao
	virtual
		void dump_mem(uint16_t inicio, uint16_t fim, char formato) = 0;
};
