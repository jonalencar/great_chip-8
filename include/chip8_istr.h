#ifndef CHIP8_ISTR_H
#define CHIP8_ISTR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef enum chip8_opcode {
	NOP = -1,
	RCA, CLS, RET, JMP, CALL,
	SKPEI, SKPNEI, SKPE, MOVI, ADDI,
	MOV, OR, AND, XOR, ADD,
	SUB, SHFR, SUBB, SHFL, SKPNE,
	MIV, JMPO, RNDMSK, DRWSPT, SKPKEY,
	SKPNKEY, MOVDLY, WTKEY, SETDLY, SETSND,
	IADD, ISETSPT, IBCD, REGDMP, REGLD,
	CHIP8_ISTR_SET_SIZE
} chip8_opcode ;

typedef void chip8_instruction(chip8_vm[static 1]);

chip8_instruction chip8_RCA;
chip8_instruction chip8_CLS;
chip8_instruction chip8_RET;
chip8_instruction chip8_JMP;
chip8_instruction chip8_CALL;
chip8_instruction chip8_SKPEI;
chip8_instruction chip8_SKPNEI;
chip8_instruction chip8_SKPE;
chip8_instruction chip8_MOVI;
chip8_instruction chip8_ADDI;
chip8_instruction chip8_MOV;
chip8_instruction chip8_OR;
chip8_instruction chip8_AND;
chip8_instruction chip8_XOR;
chip8_instruction chip8_ADD;
chip8_instruction chip8_SUB;
chip8_instruction chip8_SHFR;
chip8_instruction chip8_SUBB;
chip8_instruction chip8_SHFL;
chip8_instruction chip8_SKPNE;
chip8_instruction chip8_MIV;
chip8_instruction chip8_JMPO;
chip8_instruction chip8_RNDMSK;
chip8_instruction chip8_DRWSPT;
chip8_instruction chip8_SKPKEY;
chip8_instruction chip8_SKPNKEY;
chip8_instruction chip8_MOVDLY;
chip8_instruction chip8_WTKEY;
chip8_instruction chip8_SETDLY;
chip8_instruction chip8_SETSND;
chip8_instruction chip8_IADD;
chip8_instruction chip8_ISETSPT;
chip8_instruction chip8_IBCD;
chip8_instruction chip8_REGDMP;
chip8_instruction chip8_REGLD;

chip8_instruction* const chip8_instruction_set[CHIP8_ISTR_SET_SIZE] = {
	[RCA]		= chip8_RCA,
	[CLS]		= chip8_CLS,
	[RET]		= chip8_RET,
	[JMP]		= chip8_JMP,
	[CALL]		= chip8_CALL,
	[SKPEI]		= chip8_SKPEI,
	[SKPNEI]	= chip8_SKPNEI,
	[SKPE]		= chip8_SKPE,
	[MOVI]		= chip8_MOVI,
	[ADDI]		= chip8_ADDI,
	[MOV]		= chip8_MOV,
	[OR]		= chip8_OR,
	[AND]		= chip8_AND,
	[XOR]		= chip8_XOR,
	[ADD]		= chip8_ADD,
	[SUB]		= chip8_SUB,
	[SHFR]		= chip8_SHFR,
	[SUBB]		= chip8_SUBB,
	[SHFL]		= chip8_SHFL,
	[SKPNE]		= chip8_SKPNE,
	[MIV]		= chip8_MIV,
	[JMPO]		= chip8_JMPO,
	[RNDMSK]	= chip8_RNDMSK,
	[DRWSPT]	= chip8_DRWSPT,
	[SKPKEY]	= chip8_SKPKEY,
	[SKPNKEY]	= chip8_SKPNKEY,
	[MOVDLY]	= chip8_MOVDLY,
	[WTKEY]		= chip8_WTKEY,
	[SETDLY]	= chip8_SETDLY,
	[SETSND]	= chip8_SETSND,
	[IADD]		= chip8_IADD,
	[ISETSPT]	= chip8_ISETSPT,
	[IBCD]		= chip8_IBCD,
	[REGDMP]	= chip8_REGDMP,
	[REGLD]		= chip8_REGLD
};

#endif
