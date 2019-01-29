#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

uint8_t chip8_font[] = {
	 /* 0 */
	0b11110000,
	0b10010000,
	0b10010000,
	0b10010000,
	0b11110000,

	 /* 1 */
	0b00100000,
	0b01100000,
	0b00100000,
	0b00100000,
	0b01110000,

	 /* 2 */
	0b11110000,
	0b00010000,
	0b11110000,
	0b10000000,
	0b11110000,

	 /* 3 */
	0b11110000,
	0b00010000,
	0b11110000,
	0b00010000,
	0b11110000,

	 /* 4 */
	0b10010000,
	0b10010000,
	0b11110000,
	0b00010000,
	0b00010000,

	 /* 5 */
	0b11110000,
	0b10000000,
	0b11110000,
	0b00010000,
	0b11110000,

	 /* 6 */
	0b11110000,
	0b10000000,
	0b11110000,
	0b10010000,
	0b11110000,

	 /* 7 */
	0b11110000,
	0b00010000,
	0b01110000,
	0b01000000,
	0b01000000,

	 /* 8 */
	0b11110000,
	0b10010000,
	0b11110000,
	0b10010000,
	0b11110000,

	 /* 9 */
	0b11110000,
	0b10010000,
	0b11110000,
	0b00010000,
	0b00010000,

	 /* A */
	0b11110000,
	0b10010000,
	0b11110000,
	0b10010000,
	0b10010000,

	 /* B */
	0b11100000,
	0b10010000,
	0b11100000,
	0b10010000,
	0b11100000,
	
	 /* C */
	0b11110000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b11110000,

	 /* D */
	0b11100000,
	0b10010000,
	0b10010000,
	0b10010000,
	0b11100000,

	 /* E */
	0b11110000,
	0b10000000,
	0b11110000,
	0b10000000,
	0b11110000,

	 /* F */
	0b11110000,
	0b10000000,
	0b11100000,
	0b10000000,
	0b10000000,
};

int main(void) {
	char c;
	FILE* const file = fopen("../assets/chip8_font.c8f", "wb");

	if (!file) {
		return EXIT_FAILURE;
	}

	if (fwrite(chip8_font, 1, sizeof(chip8_font), file) != sizeof(chip8_font)) {
			fclose(file);
			return EXIT_FAILURE;
	}
	fclose(file);
	return EXIT_SUCCESS;
}
