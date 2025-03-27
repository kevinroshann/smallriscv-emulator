#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <vector>

class CPU {
public:
    uint32_t registers[32]; // 32 registers (x0 - x31)
    uint32_t pc;            // Program Counter
    std::vector<uint8_t> memory; // RAM

    CPU();  // Constructor
    void loadProgram(const std::vector<uint8_t>& program);
    void executeInstruction();
};

#endif
