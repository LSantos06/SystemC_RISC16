// Variavel para definicao do modelo implementado, sendo:
//   - 0 para Modelo com threads e eventos
//   - 1 para Modelo com módulos interligados por filas bloqueantes
#define MODELO 1

#if MODELO == 0
#include "stdarg.h"
#include "risc16.h"

#else
#include "stdarg.h"
#include "top.h"

#endif

// Enumeracao que representa o formato da instrucao
enum i_FORMAT {
	TIPO_R=4, TIPO_I=3, TIPO_J=2
};

// Funcao para geracao de instrucoes na memoria
short gerainst(int n, ...) {
	short inst = 0;

	va_list ap;

	va_start(ap, n);

	switch (n) {
		case TIPO_R:
			inst |= (va_arg(ap, int ) & 0xF) << 12;
			inst |= (va_arg(ap, int ) & 0xF) << 8;
			inst |= (va_arg(ap, int ) & 0xF) << 4;
			inst |= (va_arg(ap, int ) & 0xF);
			break;
		case TIPO_I:
			inst |= (va_arg(ap, int ) & 0xF) << 12;
			inst |= (va_arg(ap, int ) & 0xF) << 8;
			inst |= (va_arg(ap, int ) & 0xF) << 4;
			inst |= (va_arg(ap, int ) & 0xF);
			break;
		case TIPO_J:
			inst |= (va_arg(ap, int ) & 0xF) << 12;
			inst |= (va_arg(ap, int ) & 0xF) << 8;
			inst |= (va_arg(ap, int ) & 0xFF);
			break;
		default:
			break;
	}
	return inst;
}


int sc_main (int arc, char * argv[]){

	#if MODELO == 0

	////// Instanciacao do risc16
	risc16 risc16_instance("risc16_instance");

	cout << "|||||||||||||Modelo com Eventos|||||||||||||" << endl;

	////// Escrevendo instrucoes na memoria
	//// Aritmeticas
	/* addi $1, 0 */
	// Resultado esperado => reg1 += 0
	risc16_instance.write_mem(0,gerainst(TIPO_J, i_ADDi, 1, 0));

	/* addi $1, 8 */
	// Resultado esperado => reg1 += 8
	risc16_instance.write_mem(1,gerainst(TIPO_J, i_ADDi, 1, 8));

	/* addi $2, -12 */
	// Resultado esperado => reg2 -= 12
	risc16_instance.write_mem(2,gerainst(TIPO_J, i_ADDi, 2, -12));

	/* add $3, $2, $1 */
	// Resultado esperado => reg3 = reg2 + reg1
	risc16_instance.write_mem(3,gerainst(TIPO_R, i_ADD, 1, 2, 3));

	/* sub $4, $2, $3 */
	// Resultado esperado => reg4 = reg2 - reg3
	risc16_instance.write_mem(4,gerainst(TIPO_R, i_SUB, 2, 3, 4));

	/* add $5, $0, $1 */
	// Resultado esperado => reg5 = reg1
	risc16_instance.write_mem(5,gerainst(TIPO_R, i_ADD, 1, 0, 5));

	/* shift $5, 2 */
	// Resultado esperado => reg5 >> 2
	risc16_instance.write_mem(6,gerainst(TIPO_J, i_SHIFT, 5, 2));

	/* add $6, $0, $1 */
	// Resultado esperado => reg6 = reg1
	risc16_instance.write_mem(7,gerainst(TIPO_R, i_ADD, 1, 0, 6));

	/* shift $6, -4 */
	// Resultado esperado => reg6 << 4
	risc16_instance.write_mem(8,gerainst(TIPO_J, i_SHIFT, 6, -4));

	//// Logicas
	/* and $8, $7, $4 */
	// Resultado esperado => reg8 = reg7 & reg4
	risc16_instance.write_mem(9,gerainst(TIPO_R, i_AND, 4, 7, 8));

	/* not $9 */
	// Resultado esperado => reg9 = ~reg9
	risc16_instance.write_mem(10,gerainst(TIPO_J, i_NOT, 9, 0, 0));

	/* xor $10, $4, $7  */
	// Resultado esperado => reg10 = reg4 ^ reg7
	risc16_instance.write_mem(11,gerainst(TIPO_R, i_XOR, 4, 7, 10));

	/* slt $11, $5, $1  */
	// Resultado esperado => reg11 = reg5<reg1 ? 1 : 0
	risc16_instance.write_mem(12,gerainst(TIPO_R, i_SLT, 5, 1, 11));

	//// Transferencia
	/* lui $7, FF */
	// Resultado esperado => reg7 = const8 << 8
	risc16_instance.write_mem(13,gerainst(TIPO_J, i_LUI, 7, 0xFF));

	/* sw $5, $0, $6  */
	// Resultado esperado => salva o que esta em $5 no endereco que esta em $6 da memoria
	risc16_instance.write_mem(14,gerainst(TIPO_R, i_SW, 6, 0, 5));

	/* lw $12, $0, $6  */
	// Resultado esperado => carrega em $12 o que esta no endereco que esta em $6 da memoria
	risc16_instance.write_mem(15,gerainst(TIPO_R, i_LW, 6, 0, 12));

	//// Saltos
	/* jal 20  */
	// Resultado esperado => PC = 20
	risc16_instance.write_mem(16,gerainst(TIPO_J, i_JAL, 0, 20));

	/* j 30  */
	// Resultado esperado => PC = 30
	risc16_instance.write_mem(20,gerainst(TIPO_J, i_J, 0, 30));

	/* beq $0, $8, 5  */
	// Resultado esperado => reg8 == reg0 ? PC += 5 : PC += 1 => PC = 36
	risc16_instance.write_mem(30,gerainst(TIPO_I, i_BEQ, 8, 0, 5));

	/* blt $0, $1, 5  */
	// Resultado esperado => reg0 < reg1 ? PC += 5 : PC += 1 => PC = 42
	risc16_instance.write_mem(36,gerainst(TIPO_I, i_BLT, 0, 1, 5));

	////// Execucao
	sc_start();
	risc16_instance.start();

	#else

	////// Instanciacao do top
	top top_instance("top_instance");

	cout << "|||||||||||||Modelo com Modulos e Filas Bloqueantes|||||||||||||" << endl;

	////// Contexto inicial
	Contexto_t *contexto = (Contexto_t*)malloc(sizeof(Contexto_t));
	contexto->pc = 0;
	top_instance.execute_fetch.write(contexto);

	////// Escrevendo instrucoes na memoria (mesmas do caso risc16)
	//// Aritmeticas
	/* addi $1, 0 */
	top_instance.memoria.write_mem(0, gerainst(TIPO_J, i_ADDi, 1, 0));

	/* addi $1, 8 */
	top_instance.memoria.write_mem(1,gerainst(TIPO_J, i_ADDi, 1, 8));

	/* addi $2, -12 */
	top_instance.memoria.write_mem(2,gerainst(TIPO_J, i_ADDi, 2, -12));

	/* add $3, $2, $1 */
	top_instance.memoria.write_mem(3,gerainst(TIPO_R, i_ADD, 1, 2, 3));

	/* sub $4, $2, $3 */
	top_instance.memoria.write_mem(4,gerainst(TIPO_R, i_SUB, 2, 3, 4));

	/* add $5, $0, $1 */
	top_instance.memoria.write_mem(5,gerainst(TIPO_R, i_ADD, 1, 0, 5));

	/* shift $5, 2 */
	top_instance.memoria.write_mem(6,gerainst(TIPO_J, i_SHIFT, 5, 2));

	/* add $6, $0, $1 */
	top_instance.memoria.write_mem(7,gerainst(TIPO_R, i_ADD, 1, 0, 6));

	/* shift $6, -4 */
	top_instance.memoria.write_mem(8,gerainst(TIPO_J, i_SHIFT, 6, -4));

	//// Logicas
	/* and $8, $7, $4 */
	top_instance.memoria.write_mem(9,gerainst(TIPO_R, i_AND, 4, 7, 8));

	/* not $9 */
	top_instance.memoria.write_mem(10,gerainst(TIPO_J, i_NOT, 9, 0, 0));

	/* xor $10, $4, $7  */
	top_instance.memoria.write_mem(11,gerainst(TIPO_R, i_XOR, 4, 7, 10));

	/* slt $11, $5, $1  */
	top_instance.memoria.write_mem(12,gerainst(TIPO_R, i_SLT, 5, 1, 11));

	//// Transferencia
	/* lui $7, FF */
	top_instance.memoria.write_mem(13,gerainst(TIPO_J, i_LUI, 7, 0xFF));

	/* sw $5, $0, $6  */
	top_instance.memoria.write_mem(14,gerainst(TIPO_R, i_SW, 6, 0, 5));

	/* lw $12, $0, $6  */
	top_instance.memoria.write_mem(15,gerainst(TIPO_R, i_LW, 6, 0, 12));

	//// Saltos
	/* jal 20  */
	top_instance.memoria.write_mem(16,gerainst(TIPO_J, i_JAL, 0, 20));

	/* j 30  */
	top_instance.memoria.write_mem(20,gerainst(TIPO_J, i_J, 0, 30));

	/* beq $0, $8, 5  */
	top_instance.memoria.write_mem(30,gerainst(TIPO_I, i_BEQ, 8, 0, 5));

	/* blt $0, $1, 5  */
	top_instance.memoria.write_mem(36,gerainst(TIPO_I, i_BLT, 0, 1, 5));

	////// Execucao
	sc_start();

	#endif

    return 0;
}
