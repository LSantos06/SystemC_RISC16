#include "fetch.h"

/*
 * Decodificacao de uma funcao.
 *  - Acessa: contexto.
 *  - Saida: op, regs, regs2, regd, const4, const8.
 */
SC_MODULE(decode){
	// Ponteiro para o contexto
	Contexto_t *c_decode;

	// Entradas
	sc_fifo_in  <Contexto_t*> decode_in;

	// Saidas
	sc_fifo_out <Contexto_t*> decode_out;

	// Definicao do funcionamento do decode
	void decoding();

	SC_CTOR(decode){
		SC_THREAD(decoding);
	}
};
