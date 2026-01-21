/* I Francis Olakangil certify that this programming assignment reflects my own work,
without the use of any external individuals (other than course/department staff ), generative-AI,
or any other forbidden resources. I understand/accept the consequences of cheating as outlined
in the course syllabus.*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct _regFile {
	char rax[64];
	char rbx[64];
    	char rcx[64];
    	char rdx[64];
    	char rsi[64];
    	char rdi[64];
    	char rsp[64];
    	char rbp[64];
    	char r8[64];
    	char r9[64];
    	char r10[64];
    	char r11[64];
    	char r12[64];
    	char r13[64];
    	char r14[64];
    	char r15[64];
} regFile;

void mov(char * sourceReg, char * DestReg, char suffix) {
	int bytes_being_copied = 0;
	
	// suffix param is assumed to correctly be given as w, b, l, or q
	if (suffix == 'q') {
		bytes_being_copied = 8; // quad word - 64 bits
	}
	else if (suffix == 'l') {
		bytes_being_copied = 4; // double word - 32 bits
	}
	else if (suffix == 'b') {
		bytes_being_copied = 1; // plain byte - 8 bits
	}
	else {
		bytes_being_copied = 2; // plain word - 16 bits
	}

	int i = 0;
	for (i = 0; i < bytes_being_copied; i++) {
		DestReg[i] = sourceReg[i];
	} // copying given amt of bytes in bytes_being_copied based on switch case into dest register
}

void movs(char * sourceReg, char * DestReg, char suffix) {
	int bytes_being_copied = 0;

	// again assuming that suffix is correctly passed
	if (suffix == 'q') {
                bytes_being_copied = 8; // quad word - 64 bits
        }
        else if (suffix == 'l') {
                bytes_being_copied = 4; // double word - 32 bits
        }
        else if (suffix == 'b') {
                bytes_being_copied = 1; // plain byte - 8 bits
        }
        else {
                bytes_being_copied = 2; // plain word - 16 bits
        }

	int i = 0;
	for (i = 0; i < bytes_being_copied; i++) {
		DestReg[i] = sourceReg[i];
	} // copying to destination again before sign extension as in above function

	char most_sig_bit = sourceReg[bytes_being_copied - 1]; // classifies msb as most significant specifically in copied portion of register currently in destination since we're copying lower-order bytes
	
	int checkNegativity = (most_sig_bit < 0); // boolean statement checking whether msb is neg or not, setting to 1 if it is negative, 0 if not
	
	i = 0;
	for (i = bytes_being_copied; i < 64; i++) {
		if (checkNegativity) {
			DestReg[i] = '1';
		} else {
			DestReg[i] = '0';
		}
	}
}

void and(char * sourceReg, char * DestReg, char suffix) {
	int bytes_to_apply_and = 0;
	
	// again assuming that suffix is correctly passed
        if (suffix == 'q') {
                bytes_to_apply_and = 8; // quad word - 64 bits, assumes entire register
        }
        else if (suffix == 'l') {
                bytes_to_apply_and = 4; // double word - 32 bits, lower_order long  
        }
        else if (suffix == 'b') {
                bytes_to_apply_and = 1; // plain byte - 8 bits, lower-order byte
        }
        else {
                bytes_to_apply_and = 2; // plain word - 16 bits, lower-order word
        }

	int i = 0;
	for (i = 0; i < bytes_to_apply_and; i++) {
		if (sourceReg[i] == '1' && DestReg[i] == '1') {
			DestReg[i] = '1'; // keeping element the same as 1 b/c both bits in source and dest are 1
		} else {
			DestReg[i] = '0'; // changes elem to 0 if source differs
		}
	}
}

void xor(char * sourceReg, char * DestReg, char suffix) {
	int bytes_to_apply_xor = 0;

	// again assuming that suffix is correctly passed
        if (suffix == 'q') {
                bytes_to_apply_xor = 8; // quad word - 64 bits, assumes entire register
        } 
        else if (suffix == 'l') {
                bytes_to_apply_xor = 4; // double word - 32 bits, lower_order long
        }
        else if (suffix == 'b') {
                bytes_to_apply_xor = 1; // plain byte - 8 bits, lower-order byte
        }
        else {
                bytes_to_apply_xor = 2; // plain word - 16 bits, lower-order word
        }

	// apply xor bitwise operation for specified number of bites from source
	int i = 0;
	for (i = 0; i < bytes_to_apply_xor; i++) {
		if (sourceReg[i] != DestReg[i]) {
			DestReg[i] = '1'; // bits are different and so sets dest elem to 1
		} else {
			DestReg[i] = '0';
		}
	}
}

void hexRep(char * reg) {
	char hex_rep; // for singular hexa digits 0-F

	printf("0x");
	// starting hexa represen. with hexa tag at the beginning

	int i = 0;
	for (i = 0; i < 64; i+=4) { //  incrementing by for through register b/c four binary bits = 1 hexa value
		hex_rep = 0;
		if (reg[i] == '1') {
			hex_rep += 8; // adds based on first binary value of set of 4 being msb
		}
		if (reg[i + 1] == '1') {
			hex_rep += 4;
		}
		if (reg[i+2] == '1') {
			hex_rep += 2;
		}
		if (reg[i + 3] == '1') {
			hex_rep += 1;
		}

		if (hex_rep < 10) { // hexa conversion below
			printf("%c", '0' + hex_rep); // keeps hexa rep as a num from 0-9 if less than 10
		} else {
			printf("%c", 'A' + (hex_rep - 10)); // conversion to lettering in hexa system if hexa value is 10 or greater
		}
	}
	
	printf("\n"); // move to new line after hexa rep of register is done
}

int main() {
	regFile * regFileObj = (regFile *)malloc(sizeof(regFile));
	// allocates memory for size of regFile datatype

	int i = 0;
	for (i = 0; i < 64; i++) { // initializing each element in char registers to 0
		regFileObj -> rax[i] = 0;
		regFileObj -> rbx[i] = 0;
		regFileObj -> rcx[i] = 0;
		regFileObj -> rdx[i] = 0;
		regFileObj -> rsi[i] = 0;
		regFileObj -> rdi[i] = 0;
		regFileObj -> rsp[i] = 0;
		regFileObj -> rbp[i] = 0;
		regFileObj -> r8[i] = 0;
		regFileObj -> r9[i] = 0;
		regFileObj -> r10[i] = 0;
		regFileObj -> r11[i] = 0;
		regFileObj -> r12[i] = 0;
		regFileObj -> r13[i] = 0;
		regFileObj -> r14[i] = 0;
		regFileObj -> r15[i] = 0;
	}

	// testing goes here post-initialization of values in register arrays in regFile struct:







	return 0;
}


