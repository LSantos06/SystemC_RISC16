#include "decode.h"

// Definicao do funcionamento do decode
void decode::decoding(){
	while(true){
		// Pega o ponteiro do contexto
		c_decode = decode_in.read();

		// Preenchendo os campos de acordo com o RI
		c_decode->op = (c_decode->ri >> 12) & 0xF;
		c_decode->regs = (c_decode->ri >> 8) & 0xF;
		c_decode->regs2 = (c_decode->ri >> 4) & 0xF;
		c_decode->regd = c_decode->ri & 0xF;
		c_decode->const4 = (c_decode->ri & 0x8)?
								  (0xFFF0 | c_decode->regd):c_decode->regd;
		c_decode->const8 = (char) (c_decode->ri & 0xFF);

		// Passa o ponteiro do contexto para o decode
		decode_out.write(c_decode);
	}
}
