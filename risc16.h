#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <systemc.h>

// Tamanho maximo da memoria
const short MAX_MEM=1024;

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

// Definicao do risc16
SC_MODULE (risc16){

	// Funcoes para o funcionamento
	void start();
	void fetch();
	void decode();
	void execute();

	// Funcoes auxiliares para debug/impressao
	void dump_breg();
	void debug_decode();
	void dump_mem(uint16_t inicio, uint16_t fim, char formato);
	void write_mem(uint16_t endereco, int16_t dado);

	// Threads utilizadas no funcionamento do risc16
	SC_CTOR (risc16){
		breg = new int16_t[16];
		mem = new int16_t[MAX_MEM];
		SC_THREAD(start);
		SC_THREAD(fetch);
		SC_THREAD(decode);
		SC_THREAD(execute);
	}

private:
	// Componentes do risc16
	uint16_t pc, ri;
	uint16_t op, regs, regs2, regd;
	int16_t const8, const4;
	int16_t *breg;
	int16_t *mem;

	// Eventos para a sincronizacao
	sc_event fetch_ev, decode_ev, execute_ev;

};
