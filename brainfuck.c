#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc != 2){
		printf("[!] ERROR: no input file!\n");
		return 1;
	}
	FILE *codeFile = fopen(argv[1], "r");
	if(codeFile == NULL)
	{
		printf("[!] ERROR: cannot read %s!\n", argv[1]);
		return 1;
	}

	size_t sizeOfMainArray = 1;
	size_t blockPtr = 0;
	unsigned char *mainArray = (unsigned char*)malloc(1 * sizeof(unsigned char));
	if(mainArray == NULL){
		printf("[!] ERROR: Cannot allocate space for mainArray!\n");
		return 1;
	}
	mainArray[0] = 0;

	size_t sizeOfIntructions = 1;
	unsigned char *instructions = (unsigned char*)malloc(sizeOfIntructions * sizeof(unsigned char*));
	if(instructions == NULL){
		printf("[!] Cannot allocate space for instructions!\n");
		return 1;
	}
	while(1){
		char c = fgetc(codeFile);
		if(c == EOF){
			instructions[sizeOfIntructions - 1] = '\0';
			break;
		}
		instructions[sizeOfIntructions - 1] = c;
		instructions = (unsigned char*)realloc(instructions, (++sizeOfIntructions) * sizeof(unsigned char));
		if(instructions == NULL){
			printf("[!] ERROR: Cannot allocate space for instructions!\n");
			return 1;
		}
	}

	size_t instructionPtr = 0;
	while(1)
	{
		char instruction = instructions[instructionPtr];
		instructionPtr++;
		if(instruction == '\0'){
			free(mainArray);
			free(instructions);
			fclose(codeFile);
			exit(0);
		}
		else if(instruction == '+'){ // Adds one to the block
			mainArray[blockPtr]++;
			continue;
		}
		else if(instruction == '-'){ // Subtracts one from the block
			mainArray[blockPtr]--;
			continue;
		}
		else if(instruction == '<'){ // Changes the block pointer to the right
			if(blockPtr != 0){
				blockPtr--;
			}
			continue;
		}
		else if(instruction == '>'){ // Changes the block pointer to the right
			blockPtr++;
			if(blockPtr == sizeOfMainArray){
				mainArray = (unsigned char*)realloc(mainArray, (++sizeOfMainArray) * sizeof(unsigned char));
				if(mainArray == NULL){
					printf("[!] ERROR: Cannot allocate space for mainArray!\n");
				}
				mainArray[blockPtr] = 0;
			}
			continue;
		}
		else if(instruction == '.'){ // Writes whatever in the current block
			printf("%c", mainArray[blockPtr]);
		}
		else if(instruction == ','){ // Gets input from the user and puts it in the current block
			mainArray[blockPtr] = fgetc(stdin);
			if(mainArray[blockPtr] == '\n' || mainArray[blockPtr] == EOF){
				mainArray[blockPtr] = 0;
			}
		}
		else if(instruction == '['){ // starts a loop
			if(mainArray[blockPtr] == 0){
				int eqBracket = 0;
				while(1)
				{
					if(instructions[instructionPtr] == '[')
						eqBracket++;
					else if(instructions[instructionPtr] == ']'){
						if(eqBracket != 0)
							eqBracket--;
						else{
							instructionPtr++;
							break;
						}
					}
					instructionPtr++;
				}
			}
			continue;
		}
		else if(instruction == ']'){ // ends a loop
			if(mainArray[blockPtr] != 0){
				int eqBracket = 0;
				instructionPtr-=2;
				while(1)
				{
					if(instructions[instructionPtr] == ']')
						eqBracket++;
					else if(instructions[instructionPtr] == '['){
						if(eqBracket != 0)
							eqBracket--;
						else{
							instructionPtr++;
							break;
						}
					}
					instructionPtr--;
				}
			}
			continue;
		}
	}
return 0;
}