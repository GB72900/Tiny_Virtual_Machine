#include <stdio.h>
#define IM_SIZE 250 // Size of the Instruction Memory
#define DM_SIZE 10 // Size of the Data Memory

typedef struct {
    int instructions;  // Assume you have an opcode as part of your instruction register.
    int address; // The member you're trying to access.
} InstructionRegister;

InstructionRegister IR; // Now IR is a variable of type InstructionRegister.
InstructionRegister MDR1;  // Memory Data Register 1 (holds instruction data)


// Define registers and memory as specified
    int PC = 0; // Program Counter, starts at 0
    int MAR1; // Memory Address Register 1
    int MAR2; // Memory Address Register 2
    int MDR2; // Memory Data Register 2
    int ACC=0; // Accumulator
    int RUN = 1; // CPU control flag - 1 means the CPU is running

    
// Initialize Instruction Memory and Data Memory
    InstructionRegister IM[IM_SIZE] = {0}; // Instruction Memory of size 250
    int DM[DM_SIZE] = {0}; // Data Memory of size 10

// Enumerate the opcode definitions for readability
    enum {LOAD = 1, ADD, STORE, SUB, IN, OUT, END, JMP, SKIPZ}; 


// Fetch operation: Fetch the next instruction from IM into IR 
    void fetch() {

        MAR1 = PC; // Set MAR1 to the current value of PC
        PC += 1;   // Increment PC to point to the next instruction
        MDR1 = IM[MAR1];  // Load the instruction into MDR1 from the instruction memory
         IR = MDR1;  // Move the instruction from MDR1 to IR

    }

// Execute the instruction from IR
    void executeInstruction (int instructions, int address) {

        switch (instructions) {
            case LOAD:
                MAR2 = IR.address;
                MDR2 = DM[MAR2];
                ACC = MDR2;
                break;

            case ADD:
                MAR2 = IR.address;
                MDR2 = DM[MAR2];
                ACC = ACC + MDR2;
                break;

            case STORE:
                MAR2 = IR.address;
                MDR2 = ACC;
                DM[MAR2] = MDR2;
                break;
            
            case SUB:
                MAR2 = IR.address;
                MDR2 = DM[MAR2];
                ACC = ACC - MDR2;
                break;
            
            case IN:
                printf("Input data: ");
                scanf("%d", &ACC);  // Take input directly into ACC
                break;
            
            case OUT:
                printf("The result is: %d\n", ACC);
                break;

            case END:
                RUN = 0; // Stop execution
                break;

            case JMP:
                PC = IR.address; // Jump to the address in IR
                break;

            case SKIPZ:
                if (ACC == 0){
                    PC += 1;  // Skip the next instruction if ACC is zero
                }
                break;

            }
    }
// Main function: Entry point of the program
            int main(int argc, char *argv[]){
                if (argc != 2) {
                printf("Usage: %s <input_file>\n", argv[0]);
                return 1;
                }

                printf("Reading Program...\n");
                FILE *file = fopen(argv[1], "r");
                if (file == NULL) {
                printf("Error opening file.\n");
                return 1;
                }

                // Load the program into Instruction Memory from the file
                int opcodeValue, addressValue;
                int i = 0;
                while (fscanf(file, "%d %d", &opcodeValue, &addressValue) == 2 && i < IM_SIZE) {
                    IM[i].instructions = opcodeValue;
                    IM[i].address = addressValue;
                    i++;

                }
                
            fclose(file);

            printf("Program Loaded.\nRun.\n");
            while (RUN) {
                fetch(); // Perform the fetch operation
                executeInstruction (IR.instructions,IR.address); // Execute the fetched instruction
                printf("PC = %d | A = %d | DM = [", PC, ACC);  // Debug output of current state
                for (int j = 0; j < DM_SIZE; j++) {
                    printf("%d%s", DM[j], (j < DM_SIZE - 1) ? ", " : "");
        }
        printf("]\n");
    }

    return 0;
        }

