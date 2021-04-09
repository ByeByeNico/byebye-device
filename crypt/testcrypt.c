#include <stdio.h>
#include <stdlib.h>

#include "libcrypt.h"

int getAdcValue() {
	// read 10 Bit floating ADC, which is like,
	// HW randomness
	return 42;
}

int main() {
	char *cyphertext = encrypt("fourty-two");
	printf(cyphertext);
	free(cyphertext);
	return 0;
}
