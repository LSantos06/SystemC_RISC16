#include "decode.h"

// Enumeracao que define os opcodes das instrucoes
enum INSTRUCTIONS {
	i_ADD	= 0x2,
	i_SUB	= 0x3,
	i_ADDi	= 0x8,
	i_SHIFT	= 0x9,
	i_AND	= 0x4,
	i_OR	= 0x5,
	i_NOT	= 0xA,
	i_XOR	= 0x6,
	i_SLT	= 0x7,
	i_LW	= 0,
	i_SW	= 0x1,
	i_LUI	= 0xB,
	i_BEQ	= 0xC,
	i_BLT	= 0xD,
	i_J		= 0xE,
	i_JAL	= 0xF
};

/*
 * Execucao de uma funcao.
 *  - Acessa: breg, mem e contexto.
 *  - Saida: breg, mem ou pc.
 */
SC_MODULE(execute){
	// Ponteiro para o contexto
	Contexto_t *c_execute;

	// Entradas
	sc_fifo_in  <Contexto_t*> execute_in;

	// Saidas
	sc_fifo_out <Contexto_t*> execute_out;

	// Memoria
	sc_port<mem_if> p_mem_ex;

	// BREG
	sc_port<breg_if> p_breg_ex;

	// Funcao para impressao do decode
	void debug_decode();

	// Definicao do funcionamento do execute
	void executing();

	SC_CTOR(execute){
		SC_THREAD(executing);
	}
};
