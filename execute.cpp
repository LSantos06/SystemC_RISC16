#include "execute.h"

// Funcao para impressao do decode
void execute::debug_decode() {
	cout << "MEM[" << c_execute->pc-1 << "]" << endl;
	cout << "PC = " << c_execute->pc << endl;
	cout << "op = " << c_execute->op
		 << " regs = " << c_execute->regs
		 << " regs2 = " << c_execute->regs2
		 << " regd = " << c_execute->regd
		 << " const4 = " << c_execute->const4
		 << " const8 = " << c_execute->const8 << endl;
}

// Definicao do funcionamento do execute
void execute::executing(){
	while(true){
		// Pega o ponteiro do contexto
		c_execute = execute_in.read();

		switch (c_execute->op) {
			//// Aritmeticas
			// R
			case i_ADD:	  //breg[regd] = breg[regs] + breg[regs2];
						  p_breg_ex->write_breg(c_execute->regd,
								  p_breg_ex->read_breg(c_execute->regs)+p_breg_ex->read_breg(c_execute->regs2));
						  break;
			// R
			case i_SUB:   //breg[regd] = breg[regs] - breg[regs2];
						  p_breg_ex->write_breg(c_execute->regd,
								  p_breg_ex->read_breg(c_execute->regs)-p_breg_ex->read_breg(c_execute->regs2));
						  break;
			// J
			case i_ADDi:  //breg[regs] = breg[regs] + const8;
						  p_breg_ex->write_breg(c_execute->regs,
								  p_breg_ex->read_breg(c_execute->regs)+c_execute->const8);
						  break;
			// J
			case i_SHIFT: // const8 < 0
						  if (c_execute->const8 < 0){
							  //breg[regs] = breg[regs] << (-const8);
							  p_breg_ex->write_breg(c_execute->regs,
									  p_breg_ex->read_breg(c_execute->regs)<<(-c_execute->const8));
						  }
						  else{
							  //breg[regs] = breg[regs] >> const8;
							  p_breg_ex->write_breg(c_execute->regs,
									  p_breg_ex->read_breg(c_execute->regs)>>c_execute->const8);
						  }
						  break;

			//// Logicas
			// R
			case i_AND: //breg[regd] = breg[regs] & breg[regs2];
						p_breg_ex->write_breg(c_execute->regd,
								p_breg_ex->read_breg(c_execute->regs)&p_breg_ex->read_breg(c_execute->regs2));
						break;
			// R
			case i_OR : //breg[regd] = breg[regs] | breg[regs2];
						p_breg_ex->write_breg(c_execute->regd,
								p_breg_ex->read_breg(c_execute->regs)|p_breg_ex->read_breg(c_execute->regs2));
						break;
			// R
			case i_XOR: //breg[regd] = breg[regs] ^ breg[regs2];
						p_breg_ex->write_breg(c_execute->regd,
								p_breg_ex->read_breg(c_execute->regs)^p_breg_ex->read_breg(c_execute->regs2));
						break;
			// J
			case i_NOT: //breg[regs] = ~breg[regs];
						p_breg_ex->write_breg(c_execute->regs,
								~p_breg_ex->read_breg(c_execute->regs));
						break;
			// R
			case i_SLT: //breg[regd] = breg[regs] < breg[regs2];
						p_breg_ex->write_breg(c_execute->regd,
								p_breg_ex->read_breg(c_execute->regs)<p_breg_ex->read_breg(c_execute->regs2));
						break;

			//// Transferencia
			// R
			case i_LW:  cout << "Mem:" << endl;
						//dump_mem(breg[regs]+breg[regs2],breg[regs]+breg[regs2],'H');
						p_mem_ex->dump_mem(p_breg_ex->read_breg(c_execute->regs)+p_breg_ex->read_breg(c_execute->regs2),
								p_breg_ex->read_breg(c_execute->regs)+p_breg_ex->read_breg(c_execute->regs2),
								'H');

						//breg[regd] = mem[breg[regs] + breg[regs2]];
						p_breg_ex->write_breg(c_execute->regd,
								p_mem_ex->read_mem(p_breg_ex->read_breg(c_execute->regs)+p_breg_ex->read_breg(c_execute->regs2)));
						break;

			// R
			case i_SW:  cout << "Mem antes:" << endl;
						//dump_mem(breg[regs]+breg[regs2],breg[regs]+breg[regs2],'H');
						p_mem_ex->dump_mem(p_breg_ex->read_breg(c_execute->regs)+p_breg_ex->read_breg(c_execute->regs2),
								p_breg_ex->read_breg(c_execute->regs)+p_breg_ex->read_breg(c_execute->regs2),
								'H');

						//mem[breg[regs] + breg[regs2]] = breg[regd];
						p_mem_ex->write_mem(p_breg_ex->read_breg(c_execute->regs)+p_breg_ex->read_breg(c_execute->regs2),
								p_breg_ex->read_breg(c_execute->regd));

						cout << "Mem depois:" << endl;
						//dump_mem(breg[regs]+breg[regs2],breg[regs]+breg[regs2],'H');
						p_mem_ex->dump_mem(p_breg_ex->read_breg(c_execute->regs)+p_breg_ex->read_breg(c_execute->regs2),
								p_breg_ex->read_breg(c_execute->regs)+p_breg_ex->read_breg(c_execute->regs2),
								'H');
						break;

			// J
			case i_LUI: //breg[regs] = const8 << 8;
						p_breg_ex->write_breg(c_execute->regs,c_execute->const8<<8);
						break;

			//// Desvios
			// I
			case i_BEQ:	//if (breg[regs] == breg[regs2]){
							//pc = pc + const4;
						//}
						if(p_breg_ex->read_breg(c_execute->regs) == p_breg_ex->read_breg(c_execute->regs2)){
							debug_decode();
							cout << endl;
							c_execute->pc += c_execute->const4;
						}
						break;

			// I
			case i_BLT:	//if (breg[regs] < breg[regs2]){
							//pc = pc + const4;
						//}
						if(p_breg_ex->read_breg(c_execute->regs) < p_breg_ex->read_breg(c_execute->regs2)){
							debug_decode();
							cout << endl;
							c_execute->pc += c_execute->const4;
						}
						break;

			// J
			case i_J:
						debug_decode();
						cout << endl;
						//pc = breg[regs] + const8;
						c_execute->pc = p_breg_ex->read_breg(c_execute->regs) + c_execute->const8;
						break;

			// J
			case i_JAL:
						debug_decode();
						cout << endl;
						//breg[16] = pc;
						p_breg_ex->write_breg(16, c_execute->pc);
						//pc = breg[regs] + const8;
						c_execute->pc = p_breg_ex->read_breg(c_execute->regs) + c_execute->const8;
						break;
		}

		// Endereco 0 do breg nao pode ser escrito
		//breg[0] = 0;
		p_breg_ex->write_breg(0, 0);

		debug_decode();
		p_breg_ex->dump_breg();
		cout << endl;

		// Passa o ponteiro do contexto para o decode
		execute_out.write(c_execute);
	}
}

