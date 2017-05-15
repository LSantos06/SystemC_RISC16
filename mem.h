#include <systemc.h>
#include "mem_if.h"

/*
 *  Memoria que implementa a interface mem_if, eh
 * utilizada nas fases de FETCH e EXECUTE.
 */
struct mem_risc: public sc_module, public mem_if {

	// Leitura
	int16_t read_mem(uint16_t endereco);
	// Escrita
	void write_mem(uint16_t endereco, int16_t dado);
	// Impressao
	void dump_mem(uint16_t inicio, uint16_t fim, char formato);

	SC_HAS_PROCESS(mem_risc);

	// Declaracao da memoria
	mem_risc (sc_module_name n, uint16_t tam) :
		sc_module(n), tamanho(tam){
		mem = new int16_t[tamanho];
	}

private:
	int16_t *mem;
	uint16_t tamanho;

};
