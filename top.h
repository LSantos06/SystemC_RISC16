#include <systemc.h>
#include "execute.h"

/*
 * Instanciacao do risc, interconectando os componentes.
 */
SC_MODULE(top){
	//// Instanciacoes

	// MEM
	mem_risc memoria;

	// BREG
	breg_risc banco_registradores;

	// Filas
	sc_fifo <Contexto_t*> fetch_decode;
	sc_fifo <Contexto_t*> decode_execute;
	sc_fifo <Contexto_t*> execute_fetch;

	// Componentes
	fetch fetcher;
	decode decoder;
	execute executer;

	SC_CTOR(top): memoria("memoria", 1024),
				  banco_registradores("banco_registradores"),
				  fetcher("fetcher"),
				  decoder("decoder"),
				  executer("executer"){

		//// Conexoes

		// Fetch -> Decode
		fetcher.fetch_out(fetch_decode);
		decoder.decode_in(fetch_decode);

		// Decode -> Execute
		decoder.decode_out(decode_execute);
		executer.execute_in(decode_execute);

		// Execute -> Fetch
		executer.execute_out(execute_fetch);
		fetcher.fetch_in(execute_fetch);

		// Memoria
		fetcher.p_mem_fetch(memoria);
		executer.p_mem_ex(memoria);

		// BREG
		executer.p_breg_ex(banco_registradores);
	}
};
