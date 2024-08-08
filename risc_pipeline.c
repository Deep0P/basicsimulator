#include <stdio.h>
#include <stdlib.h>

#define NUM_INSTRUCTIONS 10

// Define the stages of the pipeline
typedef enum {
    IF,     // Instruction Fetch
    ID,     // Instruction Decode
    EX,     // Execute
    MEM,    // Memory Access
    WB      // Write-back
} PipelineStage;

// Define the RISC instruction structure
typedef struct {
    char opcode;
    int src1;
    int src2;
    int dest;
    int buffer;
} Instruction;

// Define the pipeline registers
Instruction if_id, id_ex, ex_mem, mem_wb;

// Simulated memory
int memory[256] = {0};

// Simulated register file
int registers[32] = {0};

// ADD=00
// SUB=01
// MUL=10
// DIV=11

// Simulated program counter
int pc = 0;

int ins_order[4][4]={
    {10,1,2,3},
    {00,4,5,6},
    {11,7,8,9},
    {01,10,11,12}
};


// Fetch the next instruction
Instruction fetch(int pc) {
    Instruction inst;
    inst.opcode = ins_order[pc][0]; 
    
    inst.src1 = ins_order[pc][1];    
    inst.src2 = ins_order[pc][2];    
    inst.dest = ins_order[pc][3]; 
    inst.buffer=0;   
    return inst;
}

// Simulate the execution of an instruction
Instruction execute(Instruction inst) {
    switch (inst.opcode) {
        case 00:
            inst.buffer = registers[ inst.src1] + registers[ inst.src2]; 
            break;
        case 01:
            inst.buffer = registers[ inst.src1] - registers[ inst.src2]; 
            break;
        case 10:
            inst.buffer= registers[ inst.src1] * registers[ inst.src2];
            break;
        case 11:
            inst.buffer = registers[ inst.src1] / registers[ inst.src2]; 
            break;
        default:
            break;
    }
    return inst;
}

// Simulate the memory access stage
Instruction memoryAccess(Instruction inst) {
    switch (inst.opcode) {
        case 100:
            inst.buffer = registers[ inst.src1]; 
            break;
        case 110:
            registers[ inst.src1]=inst.buffer; 
            break;
        default:
            break;
    }
    return inst;
}

// Simulate the write-back stage
void writeBack(Instruction inst) {
    
    registers[inst.dest]=inst.buffer;
}

// Display the contents of pipeline registers and registers
void printPipelineState(int cycle) {
    printf("Cycle %d:\n", cycle);
    printf("IF/ID: Opcode=%d, Src1=%d, Src2=%d, Dest=%d\n", if_id.opcode, if_id.src1, if_id.src2, if_id.dest);
    printf("ID/EX: Opcode=%d, Src1=%d, Src2=%d, Dest=%d\n", id_ex.opcode, id_ex.src1, id_ex.src2, id_ex.dest);
    printf("EX/MEM: Opcode=%d, Src1=%d, Src2=%d, Dest=%d\n", ex_mem.opcode, ex_mem.src1, ex_mem.src2, ex_mem.dest);
    printf("MEM/WB: Opcode=%d, Src1=%d, Src2=%d, Dest=%d\n", mem_wb.opcode, mem_wb.src1, mem_wb.src2, mem_wb.dest);
    printf("Registers: ");
    for (int i = 0; i < 32; i++) {
        printf("R%d=%d ", i, registers[i]);
    }
    printf("\n\n");
}

int main() {
    int cycle = 0;
    int instructions_executed = 0;
    int i;
    for(i=0;i<32;i++)
    {
        registers[i]= (rand() % 100) + 1;
    }   

    while (instructions_executed < NUM_INSTRUCTIONS) {
        // Execute the pipeline stages in reverse order
        mem_wb = ex_mem;
        ex_mem = id_ex;
        id_ex = if_id;
        if_id = fetch(pc);

        id_ex=execute(id_ex);
        ex_mem=memoryAccess(ex_mem);
        writeBack(mem_wb);

        printPipelineState(cycle);
        
        pc += 1; // Simulate incrementing the program counter
        cycle++;
        instructions_executed++;

    }

    return 0;
}
