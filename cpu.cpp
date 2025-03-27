#include "cpu.h"
#include <iostream>

CPU::CPU() {
    pc = 0;  // Set PC to 0
    memory.resize(1024 * 1024); // 1MB RAM
}

void CPU::loadProgram(const std::vector<uint8_t>& program) {
    for (size_t i = 0; i < program.size(); i++) {
        memory[i] = program[i]; // Copy program into memory
    }
}

void CPU::executeInstruction() {
    uint32_t instruction = memory[pc] | (memory[pc+1] << 8) | (memory[pc+2] << 16) | (memory[pc+3] << 24);
    pc += 4;

    uint32_t opcode = instruction & 0x7F;
    uint32_t rd = (instruction >> 7) & 0x1F;
    uint32_t funct3 = (instruction >> 12) & 0x7;
    uint32_t rs1 = (instruction >> 15) & 0x1F;
    uint32_t rs2 = (instruction >> 20) & 0x1F;
    uint32_t funct7 = (instruction >> 25);

    switch (opcode) {
        case 0x33: // R-type instructions
            if (funct3 == 0 && funct7 == 0) {
                registers[rd] = registers[rs1] + registers[rs2]; // ADD
            } else if (funct3 == 0 && funct7 == 0x20) {
                registers[rd] = registers[rs1] - registers[rs2]; // SUB
            }
            break;

        case 0x13: // I-type instructions
            if (funct3 == 0) {
                registers[rd] = registers[rs1] + (instruction >> 20); // ADDI
            }
            break;

        case 0x63: // Branch instructions
            if (funct3 == 0) { // BEQ
                if (registers[rs1] == registers[rs2]) {
                    pc += ((instruction >> 7) & 0x1E); // Relative jump
                }
            }
            break;

        default:
            std::cout << "Unknown instruction: " << std::hex << instruction << "\n";
    }
}

