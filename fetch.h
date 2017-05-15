#include <systemc.h>
#include "contexto.h"
#include "mem.h"
#include "breg.h"

/*
 * Decodificacao de uma funcao.
 *  - Acessa: mem e contexto.
 *  - Saida: ri e pc.
 */
SC_MODULE(fetch){
	// Contexto
	Contexto_t *c_fetch;

	// Entradas
	sc_fifo_in  <Contexto_t*> fetch_in;

	// Saidas
	sc_fifo_out <Contexto_t*> fetch_out;

	// Memoria
	sc_port<mem_if> p_mem_fetch;

	// Definicao do funcionamento do fetch
	void fetching();

	SC_CTOR(fetch){
		SC_THREAD(fetching);
	}
};
