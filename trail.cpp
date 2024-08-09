#include<iostream>
#include<stdlib.h>
#include<vector>

using namespace std;

class InstructionFetch {
public:
    uint32_t fetchInstruction(uint32_t pc, const vector<uint8_t>& memory) {
        
        uint32_t instruction = memory[pc] << 24 | memory[pc + 1] << 16 | memory[pc + 2] << 8 | memory[pc + 3];
        return instruction;
    }
};

class InstructionDecode {
public:
    struct DecodedInstruction {
        std::string operation;
        uint32_t address;
    };

    DecodedInstruction decode(uint32_t instruction) {
        uint8_t opcode = instruction >> 24;
        uint32_t address = instruction & 0x00FFFFFF;

        std::string operation;
        if (opcode == 0x01) {
            operation = "LOAD";
        }

        return { operation, address };
    }
};


class Execute {
public:
    void execute(const std::string& operation, uint32_t& address) {
        if (operation == "LOAD") {
        }
    }
};


class MemoryAccess {
public:
    bool accessMemory(uint32_t address, Cache& cache, std::vector<uint8_t>& memory, uint8_t& value) {
        if (cache.access(address, value)) {
            std::cout << "Cache Hit\n";
            return true;
        } else {
            std::cout << "Cache Miss\n";
            cache.load(address, memory);
            value = memory[address];
            return false;
        }
    }
};

class WriteBack {
public:
    void writeBack(uint8_t value, uint32_t& registerR1) {
        registerR1 = value;
    }
};



int main()
{
    

}