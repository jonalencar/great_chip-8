#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <GLFW/glfw3.h>

#include "chip8.h"
#include "chip8_istr.h"

chip8_opcode chip8_disassemble(chip8_word istr_word)
{
	chip8_byte lend = (istr_word & 0x00FF);  /* little end */
	chip8_byte bend = (istr_word & 0xFF00) >> 8;  /* big end */

	switch (bend & 0xF0) {
		case 0x00: {
			switch(lend) {
				case 0xE0: return CLS;
				case 0xEE: return RET;
				default: return RCA;
			}
		}
		case 0x10: return JMP;
		case 0x20: return CALL;
		case 0x30: return SKPEI;
		case 0x40: return SKPNEI;
		case 0x50: return SKPE;
		case 0x60: return MOVI;
		case 0x70: return ADDI;
		case 0x80: {
			switch(lend & 0x0F) {
				case 0x00: return MOV;
				case 0x01: return OR;
				case 0x02: return AND;
				case 0x03: return XOR;
				case 0x04: return ADD;
				case 0x05: return SUB;
				case 0x06: return SHFR;
				case 0x07: return SUBB;
				case 0x0E: return SHFL;
			}
		}
		case 0x90: return SKPNE;
		case 0xA0: return MIV;
		case 0xB0: return JMPO;
		case 0xC0: return RNDMSK;
		case 0xD0: return DRWSPT;
		case 0xE0: {
			switch(lend) {
				case 0x9E: return SKPKEY;
				case 0xA1: return SKPNKEY;
			}
		}
		case 0xF0: {
			switch(lend) {
				case 0x07: return MOVDLY;
				case 0x0A: return WTKEY;
				case 0x15: return SETDLY;
				case 0x18: return SETSND;
				case 0x1E: return IADD;
				case 0x29: return ISETSPT;
				case 0x33: return IBCD;
				case 0x55: return REGDMP;
				case 0x65: return REGLD;
			}
		}
		default: return NOP;
	}
}

/*
 * @brief Calls RCA 1802 program at address NNN (Not required for most ROMs)
 */
void chip8_RCA(chip8_vm chip8[static 1])
{
    fputs("great-chip-8: RCA opcode executed.\n This shouldn't happen\n",
          stderr);
}

/*
 * @brief Clears the screen
 */
void chip8_CLS(chip8_vm chip8[static 1]);

/*
 * @brief Pops stack to return from subroutine
 */
void chip8_RET(chip8_vm chip8[static 1])
{
    chip8->sp -= 2;
    chip8->pc = chip8->mem[chip8->sp] << 8;
    chip8->pc += chip8->mem[chip8->sp+1];
}

/*
 * @brief Jumps to address at NNN
 */
void chip8_JMP(chip8_vm chip8[static 1])
{
    chip8->pc = chip8->istr & 0x0FFF;
}

/*
 * @brief Pushes program counter to stack and calls subroutine at NNN
 */
void chip8_CALL(chip8_vm chip8[static 1])
{
    chip8->mem[chip8->sp] = ((chip8->pc+2) & 0xFF00) >> 8;
    chip8->mem[chip8->sp+1] = (chip8->pc+2) & 0x00FF;
    chip8->sp += 2;
    chip8->pc = chip8->istr & 0x0FFF;
}

/*
 * @brief Skips next instruction if register V[X] equals NN
 */
void chip8_SKPEI(chip8_vm chip8[static 1])
{
    chip8_reg chip8_reg = (chip8->istr & 0x0F00) >> 8;

    if (chip8->regs[chip8_reg] == chip8->istr & 0x00FF) {
        chip8->pc += 2;
    }
    chip8->pc += 2;
}

/*
 * @brief Skips next instruction if register V[X] does not equal NN
 */
void chip8_SKPNEI(chip8_vm chip8[static 1])
{
    chip8_reg chip8_reg = (chip8->istr & 0x0F00) >> 8;

    if (chip8->regs[chip8_reg] != chip8->istr & 0x00FF) {
        chip8->pc += 2;
    }
    chip8->pc += 2;
}

/*
 * @brief Skips next instruction if register V[X] equals V[Y]
 */
void chip8_SKPE(chip8_vm chip8[static 1])
{
    chip8_reg chip8_regx = (chip8->istr & 0x0F00) >> 8;
    chip8_reg chip8_regy = (chip8->istr & 0x00F0) >> 4;

    if (chip8->regs[chip8_regx] == chip8->regs[chip8_regy]) {
        chip8->pc += 2;
    }
    chip8->pc += 2;
}

/*
 * @brief Sets V[X] to NN
 */
void chip8_MOVI(chip8_vm chip8[static 1])
{
    chip8_byte chip8_imdt = (chip8->istr & 0x00FF);
    chip8_reg chip8_reg = (chip8->istr & 0x0F00) >> 8;

    chip8->regs[chip8_reg] = chip8_imdt;
    chip8->pc += 2;
}

/*
 * @brief Adds NN to V[X]
 */
void chip8_ADDI(chip8_vm chip8[static 1])
{
    chip8_byte chip8_imdt = (chip8->istr & 0x00FF);
    chip8_reg chip8_reg = (chip8->istr & 0x0F00) >> 8;

    chip8->regs[chip8_reg] += chip8_imdt;
    chip8->pc += 2;
}

/*
 * @brief Sets V[X] to value of V[Y]
 */
void chip8_MOV(chip8_vm chip8[static 1])
{
    chip8_reg chip8_regx = (chip8->istr & 0x0F00) >> 8;
    chip8_reg chip8_regy = (chip8->istr & 0x00F0) >> 4;

    chip8->regs[chip8_regx] = chip8->regs[chip8_regy];
    chip8->pc += 2;
}

/*
 * @brief Sets V[X] to V[X] OR V[Y]
 */
void chip8_OR(chip8_vm chip8[static 1])
{
    chip8_reg chip8_regx = (chip8->istr & 0x0F00) >> 8;
    chip8_reg chip8_regy = (chip8->istr & 0x00F0) >> 4;

    chip8->regs[chip8_regx] |= chip8->regs[chip8_regy];
    chip8->pc += 2;
}

/*
 * @brief Sets V[X] to V[X] AND V[Y]
 */
void chip8_AND(chip8_vm chip8[static 1])
{
    chip8_reg chip8_regx = (chip8->istr & 0x0F00) >> 8;
    chip8_reg chip8_regy = (chip8->istr & 0x00F0) >> 4;

    chip8->regs[chip8_regx] &= chip8->regs[chip8_regy];
    chip8->pc += 2;
}

/*
 * @brief Sets V[X] to V[X] XOR V[Y]
 */
void chip8_XOR(chip8_vm chip8[static 1])
{
    chip8_reg chip8_regx = (chip8->istr & 0x0F00) >> 8;
    chip8_reg chip8_regy = (chip8->istr & 0x00F0) >> 4;

    chip8->regs[chip8_regx] ^= chip8->regs[chip8_regy];
    chip8->pc += 2;
}

/*
 * @brief Adds V[Y] to V[X] and sets V[F] to 0 or 1 if a carry occurs
 */
void chip8_ADD(chip8_vm chip8[static 1])
{
    chip8_reg chip8_regx = (chip8->istr & 0x0F00) >> 8;
    chip8_reg chip8_regy = (chip8->istr & 0x00F0) >> 4;

    if ((uint16_t) chip8->regs[chip8_regx] + chip8->regs[chip8_regy] < 0xFF) {
        chip8->regs[VF] = 0;
    } else {
        chip8->regs[VF] = 1;
    }
    chip8->regs[chip8_regx] += chip8->regs[chip8_regy];
    chip8->pc += 2;
}

/*
 * @brief Subtracts V[Y] from V[X] and sets V[F] to 1 or 0 if a borrow occurs
 */
void chip8_SUB(chip8_vm chip8[static 1])
{
    chip8_reg chip8_regx = (chip8->istr & 0x0F00) >> 8;
    chip8_reg chip8_regy = (chip8->istr & 0x00F0) >> 4;

    if (chip8->regs[chip8_regx] < chip8->regs[chip8_regy]) {
        chip8->regs[VF] = 0;
    } else {
        chip8->regs[VF] = 1;
    }
    chip8->regs[chip8_regx] -= chip8->regs[chip8_regy];
    chip8->pc += 2;
}

/*
 * @brief Sets V[F] to the LSB of V[X] and shifts V[X] to the right by 1
 */
void chip8_SHFR(chip8_vm chip8[static 1])
{
    chip8_reg chip8_regx = (chip8->istr & 0x0F00) >> 8;

    chip8->regs[VF] = chip8->regs[chip8_regx] & 0x01;
    chip8->regs[chip8_regx] >>= 1;
    chip8->pc += 2;
}

/*
 * @brief Subtracts V[X] from V[Y] and sets V[F] to 1 or to 0 if a borrow occurs
 */
void chip8_SUBB(chip8_vm chip8[static 1]);
{
    chip8_reg chip8_regx = (chip8->istr & 0x0F00) >> 8;
    chip8_reg chip8_regy = (chip8->istr & 0x00F0) >> 4;

    if (chip8->regs[chip8_regy] < chip8->regs[chip8_regx]) {
        chip8->regs[VF] = 0;
    } else {
        chip8->regs[VF] = 1;
    }
    chip8->regs[chip8_regx] = chip8->regs[chip8_regy] - chip8->regs[chip8_regx]
    chip8->pc += 2;
}

/*
 * @brief Sets V[F] to the MSB of V[X] and shifts V[X] to the left by 1
 */
void chip8_SHFL(chip8_vm chip8[static 1]);
{
    chip8_reg chip8_regx = (chip8->istr & 0x0F00) >> 8;

    chip8->regs[VF] = chip8->regs[chip8_regx] & 0x80;
    chip8->regs[chip8_regx] <<= 1;
    chip8->pc += 2;
}

/*
 * @brief Skips next instruction if V[X] does not equal V[Y]
 */
void chip8_SKPNE(chip8_vm chip8[static 1])
{
    chip8_reg chip8_regx = (chip8->istr & 0x0F00) >> 8;
    chip8_reg chip8_regy = (chip8->istr & 0x00F0) >> 4;

    if (chip8->regs[chip8_regx] != chip8->regs[chip8_regy]) {
        chip8->pc += 2;
    }
    chip8->pc += 2;
}

/*
 * @brief Sets I to the address NNN
 */
void chip8_MIV(chip8_vm chip8[static 1])
{
    chip8->idx = chip8->istr & 0x0FFF;
    chip8->pc += 2;
}

/*
 * @brief Jumps to address NNN plus V[0]
 */
void chip8_JMPO(chip8_vm chip8[static 1])
{
    chip8->pc = (chip8->istr & 0x0FFF) + chip8->regs[V0];
}

/*
 * @brief Sets V[X] equal to a bitwise AND between a random number and NN
 */
void chip8_RNDMSK(chip8_vm chip8[static 1])
{
    chip8_reg chip8_regx = (chip8->istr & 0x0F00) >> 8;
    chip8->regs[chip8_regx] = (rand() % 256) & (chip8->istr & 0x00FF);
}

/*
 * @brief Draws a sprite at coordinate (V[X], V[Y]) with width 8xN
 */
void chip8_DRWSPT(chip8_vm chip8[static 1])
{
	chip8_reg chip8_regx = (chip8->istr & 0x0F00) >> 8;
	chip8_reg chip8_regy = (chip8->istr & 0x00F0) >> 4;
	chip8_byte spt_hgt = chip8->istr & 0x0F;
	chip8->regs[VF] = 0;

	for (chip8_byte bit_row, i = 0; i < spt_hgt; i++) {
		bit_row = chip8->mem[idx+i];
		for (chip8_byte j = 0; j < 8; j++) {
			if (bit_row >> (7-j)) {
				if (chip8->gfx[chip8_regx+i][chip8_regy+j]) {
					chip8->regs[VF] = 1;
				}
				chip8->gfx[chip8_regx+i][chip8_regy+j] ^= 1;
			}
		}
	}
	chip8->pc += 2;
}

/*
 * @brief Skips next instruction if key stored in V[X] is pressed
 */
void chip8_SKPKEY(chip8_vm chip8[static 1]);

/*
 * @brief Skips next instruction if key stored in V[X] is not pressed
 */
void chip8_SKPNKEY(chip8_vm chip8[static 1]);

/*
 * @brief Sets V[X] to the value of the delay timer
 */
void chip8_MOVDLY(chip8_vm chip8[static 1]);

/*
 * @brief Halts all instructions and stores next key press in V[X]
 */
void chip8_WTKEY(chip8_vm chip8[static 1]);

/*
 * @brief Sets delay timer to V[X]
 */
void chip8_SETDLY(chip8_vm chip8[static 1]);

/*
 * @brief Sets sound timer to V[X]
 */
void chip8_SETSND(chip8_vm chip8[static 1]);

/*
 * @brief Adds V[X] to I
 */
void chip8_IADD(chip8_vm chip8[static 1]);

/*
 * @brief Sets index register to the location of the sprite located at V[X]
 */
void chip8_ISETSPT(chip8_vm chip8[static 1]);

/*
 * @brief Stores the BCD representation of V[X] in memory starting at the index
 */
void chip8_IBCD(chip8_vm chip8[static 1]);

/*
 * @brief Stores V[0] to V[X] in memory starting at the index
 */
void chip8_REGDMP(chip8_vm chip8[static 1]);

/*
 * @brief Fills V[0] to V[X] with values from memory starting at the index
 */
void chip8_REGLD(chip8_vm chip8[static 1]);
