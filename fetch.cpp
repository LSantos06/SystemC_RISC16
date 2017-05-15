#include "fetch.h"

// Definicao do funcionamento do fetch
void fetch::fetching(){
	while(true){
		// Pega o ponteiro do contexto
		c_fetch = fetch_in.read();

		//// Pega a instrucao e incrementa o PC
		//ri = mem[pc];
		c_fetch->ri = p_mem_fetch->read_mem(c_fetch->pc);
		//pc++;
		c_fetch->pc++;

		// Se nao possui mais instrucoes
		if(c_fetch->ri == 0){
			cout << "Nao possui mais instrucoes!" << endl;
			sc_stop();
			exit(0);
		}

		// Passa o ponteiro do contexto para o decode
		fetch_out.write(c_fetch);
	}
}
