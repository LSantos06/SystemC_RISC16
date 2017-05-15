#include "risc16.h"

// Funcao que inicializa o funcionamento do risc16
void risc16::start(){
	wait(SC_ZERO_TIME);
	pc = 0;
	execute_ev.notify();
}

// Busca de uma instrucao
void risc16::fetch() {
	while(true){
		wait(execute_ev);

		// Pega a instrucao e incrementa o PC
		ri = mem[pc];
		pc++;

		// Se nao possui mais instrucoes
		if(ri == 0){
			cout << "Nao possui mais instrucoes!" << endl;
			sc_stop();
			exit(0);
		}

		fetch_ev.notify();
	}
}

// Decodificacao de uma instrucao
void risc16::decode() {
	while(true){
		wait(fetch_ev);

		// Preenchendo os campos de acordo com o RI
		op = (ri >> 12) & 0xF;
		regs = (ri >> 8) & 0xF;
		regs2 = (ri >> 4) & 0xF;
		regd = ri & 0xF;
		const4 = (ri & 0x8)?(0xFFF0 | regd) : regd;
		const8 = (char) (ri & 0xFF);



		decode_ev.notify();
	}
}

// Execucao de uma instrucao
void risc16::execute() {
	while(true){
		wait(decode_ev);

		switch (op) {
			//// Aritmeticas
			// R
			case i_ADD:	  breg[regd] = breg[regs] + breg[regs2];
						  break;
			// R
			case i_SUB:   breg[regd] = breg[regs] - breg[regs2];
						  break;
			// J
			case i_ADDi:  breg[regs] = breg[regs] + const8;
						  break;
			// J
			case i_SHIFT: if (const8 < 0)
						      breg[regs] = breg[regs] << (-const8);
						  else
							  breg[regs] = breg[regs] >> const8;
						  break;

			//// Logicas
			// R
			case i_AND: breg[regd] = breg[regs] & breg[regs2];
						break;
			// R
			case i_OR : breg[regd] = breg[regs] | breg[regs2];
						break;
			// R
			case i_XOR: breg[regd] = breg[regs] ^ breg[regs2];
						break;
			// J
			case i_NOT: breg[regs] = ~breg[regs];
						break;
			// R
			case i_SLT: breg[regd] = breg[regs] < breg[regs2];
						break;

			//// Transferencia
			// R
			case i_LW:  cout << "Mem:" << endl;
						dump_mem(breg[regs]+breg[regs2],breg[regs]+breg[regs2],'H');

						breg[regd] = mem[breg[regs] + breg[regs2]];
						break;

			// R
			case i_SW:  cout << "Mem antes:" << endl;
						dump_mem(breg[regs]+breg[regs2],breg[regs]+breg[regs2],'H');

						mem[breg[regs] + breg[regs2]] = breg[regd];

						cout << "Mem depois:" << endl;
						dump_mem(breg[regs]+breg[regs2],breg[regs]+breg[regs2],'H');
						break;

			// J
			case i_LUI: breg[regs] = const8 << 8;
						break;

			//// Desvios
			// I
			case i_BEQ:	if (breg[regs] == breg[regs2]){
							debug_decode();
							cout << endl;
							pc = pc + const4;
						}
						break;

			// I
			case i_BLT:	if (breg[regs] < breg[regs2]){
							debug_decode();
							cout << endl;
							pc = pc + const4;
						}
						break;

			// J
			case i_J:
						debug_decode();
						cout << endl;
						pc = breg[regs] + const8;
						break;

			// J
			case i_JAL:
						debug_decode();
						cout << endl;
						breg[16] = pc;
						pc = breg[regs] + const8;
						break;
		}

		// Endereco 0 do breg nao pode ser escrito
		breg[0] = 0;

		debug_decode();
		dump_breg();
		cout << endl;

		execute_ev.notify();
	}
}

// Impressao do breg
void risc16::dump_breg() {
	for (int i=0; i<=16; i++) {
		printf("BREG[%2d] = \t%4d \t\t\t%x\n", i, breg[i], breg[i]);
	}
}

// Impressao apos a fase de decode
void risc16::debug_decode() {
	cout << "MEM[" << pc-1 << "]" << endl;
	cout << "PC = " << pc << endl;
	cout << "op = " << op
		 << " regs = " << regs
		 << " regs2 = " << regs2
		 << " regd = " << regd
		 << " const4 = " << const4
		 << " const8 = " << const8 << endl;
}

// Impressao da memoria
void risc16::dump_mem(uint16_t inicio, uint16_t fim, char formato) {
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

// Escrita na memoria
void risc16::write_mem(uint16_t endereco, int16_t dado) {
	mem[endereco] = dado;
}
