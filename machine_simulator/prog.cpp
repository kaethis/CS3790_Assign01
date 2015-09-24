/* Author:	Matt W. Martin, 4374851
 *		kaethis@tasmantis.net
 *
 * Project:	CS3790, Assignment 01:
 *		"SIMPLETRON" Machine Simulator
 *
 * File:	prog.cpp */

#include <stdio.h>
#include <stdlib.h>     /* atoi */
#include <cstdio>
#include <cctype>
#include <string.h>
#include <iostream>

using namespace std;


typedef int BYTE;		// Represents a signed 2-digit decimal data type.
typedef int WORD;		// Represents a data type equivalent to two BYTES.
typedef int DWORD;		// DOUBLEWORD, equiv. to two WORDS (or four BYTES).

const WORD  WORD_MAX = +9999;	// Largest possible WORD value before overflow.
const WORD  WORD_MIN = -9999;	// Smallest possible WORD value.


DWORD  accumulator;		// Register for storing and manipulating values.

BYTE  prog_counter;		// Holds address of the next instruction in memory.

WORD  inst_register;		// Register containing instruction itself.


WORD  memory[100] = {};		/* Memory segment consisting of 100 WORDS.  Each
				 *  WORD is initialized as 0000; */

char  *start_stmt =	"GO";	// Indicates end of user input; begin interpreter.


/*            ___         _               _   _            _    _    _   
 *           |_ _|_ _  __| |_ _ _ _  _ __| |_(_)___ _ _   | |  (_)__| |_ 
 *            | || ' \(_-<  _| '_| || / _|  _| / _ \ ' \  | |__| (_-<  _|
 *           |___|_||_/__/\__|_|  \_,_\__|\__|_\___/_||_| |____|_/__/\__|
 * ------------------------------------------------------------------------------- */
                                                            
const BYTE  READ =	10;	// Read WORD from bash, store into memory in operand.

const BYTE  WRITE =	11;	// Write WORD from memory loc in operand onto bash.

const BYTE  LOAD =	20;  	// Load WORD from loc in operand into accumulator.

const BYTE  STORE =	21;	// Store WORD from accumulator to loc in operand.

const BYTE  ADD =	30;	/* Add WORD from memory loc in operand to value in
				 *  the accumulator; leave result in accumulator. */

const BYTE  SUB =	31;	/* Subtract WORD from loc in operand from value in
				 *  the accumuator; leave result in accumulator. */

const BYTE  DIV =	32;	/* Divide value in accumulator by WORD in memory loc
				 *  in operand; leave result in accumulator. */

const BYTE  MUL =	33;	/* Multiply value in accumulator by WORD in memory
				 *  loc in operand; leave result in accumulator. */

const BYTE  JUMP =	40;	// Branch to memory location in operand.

const BYTE  JUMPNEG =	41;	// Branch to loc in operand if accumulator negative.

const BYTE  JUMPZER =	42;	// Branch to loc in operand if accumulator is zero.

const BYTE  HALT =	43;	// Halt program; denotes end of executable.

// ---------------------------------------------------------------------------------- 


void input(){
/* This FUNCTION requests user input for a series of instructions starting at memory
 *  location 00.  After inputing the start statement, the input routine ends. */

	char  buffer[256];	// Input buffer; all input chars are stored here.
	char  *buffer_ptr;

	buffer_ptr = buffer;


	WORD  val;

	// Set program counter to refer to first address in memory.
	prog_counter = 00;

  input_routine:
	// Print instruction line and signify start of input.
	printf("   %0*d $>", 2, prog_counter);

	// Read and store input content into buffer.
	scanf("%s", buffer_ptr);

	if(strcmp(buffer_ptr, start_stmt) == 0)
	// IF input buffer contains start statement, exit input routine.
		goto input_end;


	/* Covert contents of buffer to WORD.  If conversion is unsuccessful, 0000
	 *  will be stored at this address instead (the atoi(char*) FUNCTION returns
	 *  ZERO if the string passed cannot be cast into an integer). */
	val = atoi(buffer_ptr);

	// Commit (only last four digits of) value to memory and inc program counter.
	memory[prog_counter++] = (val % 10000);

	/* As long as the program counter does not exceed the total number of memory
	 *  addresses, repeat input routine. */
	if(prog_counter < (sizeof(memory)/sizeof(memory[0])))
		goto input_routine;

  input_end:
	// Continue to interpreter phase.
	;
}

bool interpret(){
/* This FUNCTION attempts to make sense of the series of instructions inserted into
 *  the memory segment.  If successful, the FUNCTION returns TRUE (and proceeds to
 *  the execution phase); otherwise, it returns FALSE. */

	BYTE  inst_code;			// First 2 digits in inst_register.

	BYTE  inst_operand;			/* Last 2 digits of inst_register.
						 * Refers to an address in memory. */


	printf("\n");

	// Set program counter to refer to first address in memory.
	prog_counter = 00;

	while(prog_counter < (sizeof(memory)/sizeof(memory[0]))){
	/* WHILE the program counter does not exceed the total number of addresses,
	 *  parse each WORD for instruction code and operand. */

		inst_register = memory[prog_counter++];	/* Program counter should
							 *  always refer to next
							 *  instruction. */

		inst_code = inst_register/100;

		inst_operand = inst_register%100;


		switch(inst_code){
		// Compare the instruction code to the following valid operations.

		  case READ:	printf("  READ@%0*d\n", 2, (prog_counter-1));
				break;

		  case WRITE:	printf("  WRITE@%0*d\n", 2, (prog_counter-1));
				break;

		  case LOAD:	printf("  LOAD@%0*d\n", 2, (prog_counter-1));
				break;

		  case STORE:	printf("  STORE@%0*d\n", 2, (prog_counter-1));
				break;

		  case ADD:	printf("  ADD@%0*d\n", 2, (prog_counter-1));
				break;

		  case SUB:	printf("  SUB@%0*d\n", 2, (prog_counter-1));
				break;

		  case DIV:	printf("  DIV@%0*d\n", 2, (prog_counter-1));
				break;

		  case MUL:	printf("  MUL@%0*d\n", 2, (prog_counter-1));
				break;

		  case JUMP:	printf("  JUMP@%0*d\n", 2, (prog_counter-1));
				break;

		  case JUMPNEG:	printf("  JUMPNEG@%0*d\n", 2, (prog_counter-1));
				break;

		  case JUMPZER:	printf("  JUMPZER@%0*d\n", 2, (prog_counter-1));
				break;

		  case HALT:	// Exit interpreter and prepare for execution.
				printf("  HALT@%0*d\n", 2, (prog_counter-1));
				return true;

		  default:	// Exit interpreter as the result of an error.
				printf("  INV INS@%0*d\n", 2, (prog_counter-1));
				return false;
		}
	}

	// Exit interpreter as the result of overflow in prog_counter.
	printf("\n  PROG COUNT OVFL\n");
	return false;
}

bool execute(){
/* This FUNCTION executes the series of instructions input into the memory segment.
 * If it encounters an error at runtime (accumulator overflow, etc.) the FUNCTION
 *  returns FALSE; otherwise, it returns TRUE. */

	BYTE  inst_code;

	BYTE  inst_operand;


	printf("\n");

	// Set program counter to refer to first address in memory.
	prog_counter = 00;

	while(prog_counter < (sizeof(memory)/sizeof(memory[0]))){

		inst_register = memory[prog_counter++];

		inst_code = inst_register/100;

		inst_operand = inst_register%100;


		WORD  val;

		switch(inst_code){

		  case READ:	char  buffer[256];
				char  *buffer_ptr;

				buffer_ptr = buffer;


				// Signify start of input.
				printf("  @%0*d $>", 2, inst_operand);

				// Read and store input into buffer.
				scanf("%s", buffer_ptr);


				// Convert contents of buffer to WORD.
				val = atoi(buffer_ptr);

				if((val < WORD_MIN) || (val > WORD_MAX))
				// IF val outside of range, truncate.
					val = val % 10000;

				// Commit value to memory at address in operand.
				memory[inst_operand] = val;

				break;


		  case WRITE:	printf("   %0*d", 2, inst_operand);
				printf(" >%0*d\n", 4, memory[inst_operand]);
				break;


		  case LOAD:	accumulator = memory[inst_operand];
				break;


		  case STORE:	memory[inst_operand] = accumulator;
				break;


		  case ADD:	accumulator += memory[inst_operand];

				if((accumulator < WORD_MIN) ||
				   (accumulator > WORD_MAX)){
				/* IF accumulator value out of possible WORD range,
				 *  signify overflow and terminate program. */
					printf("\n  ACCUM OVFL\n");
					return false;
				}

				break;


		  case SUB:	accumulator -= memory[inst_operand];

				if((accumulator < WORD_MIN) ||
				   (accumulator > WORD_MAX)){
					printf("\n  ACCUM OVFL\n");
					return false;
				}

				break;

		  case DIV:
				if(memory[inst_operand] == 0000){
				// IF dividing by 0, signify error and terminate.
					printf("\n  DIV ZERO\n");
					return false;
				}

				accumulator = (accumulator / memory[inst_operand]);

				if((accumulator < WORD_MIN) ||
				   (accumulator > WORD_MAX)){
					printf("\n  ACCUM OVFL\n");
					return false;
				}

				break;


		  case MUL:	accumulator = (accumulator / memory[inst_operand]);

				if((accumulator < WORD_MIN) ||
				   (accumulator > WORD_MAX)){
					printf("\n  ACCUM OVFL\n");
					return false;
				}

				break;


		  case JUMP:	prog_counter = inst_operand;
				break;


		  case JUMPNEG: if(accumulator < 00)
					prog_counter = inst_operand;
				break;


		  case JUMPZER: if(accumulator == 00)
					prog_counter = inst_operand;
				break;


		  case HALT:	// Terminate program.
				return true;
		}
	}

	// Terminate program as the result of overflow in prog_counter.
	printf("\n  PROG COUNT OVFL\n");	
	return false;	
}

void dump(){


	// Print formatted "REGISTER" header:
	printf("                               ");
	printf(" _   _  __ ___  __ ___  _  _   __\n");
	printf("                               ");
	printf("|_) |_ /__  |  (_   |  |_ |_) (_\n");
	printf("                               ");
	printf("| \\ |_ \\_| _|_ __)  |  |_ | \\ __)\n");
	printf("                               ");
	printf("---------------------------------\n");


	BYTE  inst_code = inst_register/100;	// First 2 digits of inst_register.

	BYTE  inst_operand = inst_register%100;	/* Last 2 digits of inst_register.
						 * Refers to an address in memory. */

	// Print contents of registers:
	printf("                               ");
	printf("ACCUMULATOR              %0*d\n", 8, accumulator);
	printf("                               ");
	printf("PROGRAM COUNTER                %0*d\n", 2, prog_counter);
	printf("                               ");
	printf("INSTRUCTION REGISTER         %0*d\n", 4, inst_register);
	printf("                               ");
	printf("CODE %0*d  ", 2, inst_register/100);
	printf("OPERAND %0*d\n", 2, inst_register%100);


	//Print formatted "MEMORY" header:
	printf("        _       _   _\n");
	printf("  |\\/| |_ |\\/| / \\ |_) \\_/\n");
	printf("  |  | |_ |  | \\_/ | \\  |\n");
	printf("  --------------------------------------------------------------");
	printf("\n");

	int offset = 0;		/* Refers to the number of WORDs traversed from the
				 *  first memory location. */


	// Print column headers:
	for(int col = 0; col < 10; col++){

		if(col == 0)
			printf("    ");

		printf("_____%d", col);
	}


	int row = 0;

	while(offset < (sizeof(memory)/sizeof(memory[0]))){
	// WHILE offset has not exceeded the final memory address...

		/* Newline after every tenth value and print header at beginning
		 * of every row. */
		if(offset % 10 == 0)
			printf("\n%3d| ", row++);

		// Before printing the value of the WORD, display its sign.
		if(memory[offset] >= 0000)
			printf("+");
		else if(memory[offset] < 0000)
			printf("-");

		/* Print value of WORD.
		 * NOTE:  Since the sign has already been accounted for, I'm using
		 *	   the abs(int) FUNCTION here for its absolute value. */
		printf("%0*d ", 4, abs(memory[offset++]));
	}

	printf("\n");
}

int main(){

	printf("           __  ___         _        _  ___  _    _\n");
	printf("          (_    |   |\\/|  |_)  |   |_   |  |_)  / \\  |\\ |\n");
	printf("          __)  _|_  |  |  |    |_  |_   |  | \\  \\_/  | \\|\n");
	printf("  --------------------------------------------------------------\n");
	printf("      Input your SML program below and enter \"GO\" to execute. \n");
	printf("  --------------------------------------------------------------\n");


	// Request user for sequence of instructions.
	input();

	if(interpret()){
	// IF successful at interpreting input as SML program, execute it.

		if(execute())
			printf("  END PROG\n");
		else
			printf("  TRY AGAIN\n");
	}

	// Dump contents of registers & memory.
	dump();


	return 0;
}
