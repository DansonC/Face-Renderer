#include "cpu.hpp"

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdint>
#include <iostream>

//TODO
uint8_t NesCPU::get_opcode()
{
    return mem[pc];
}
void NesCPU::run()
{
    // 1. Grab opcode
    uint8_t opcode = get_opcode();
    // 2. Run function from table
    
    
}

void NesCPU::ADC(){}
void NesCPU::AND(){}
void NesCPU::ASL(){}
void NesCPU::BCC(){}
void NesCPU::BCS(){}
void NesCPU::BEQ(){}
void NesCPU::BIT(){}
void NesCPU::BMI(){}
void NesCPU::BNE(){}
void NesCPU::BPL(){}
void NesCPU::BRK(){}
void NesCPU::BVC(){}
void NesCPU::CLC(){}
void NesCPU::CLD(){}
void NesCPU::CLI(){}
void NesCPU::CLV(){}
void NesCPU::CMP(){}
void NesCPU::CPX(){}
void NesCPU::CPY(){}
void NesCPU::DEC(){}
void NesCPU::DEX(){}
void NesCPU::DEY(){}
void NesCPU::EOR(){}
void NesCPU::INC(){}
void NesCPU::INX(){}
void NesCPU::INY(){}
void NesCPU::JMP(){}
void NesCPU::JSR(){}
void NesCPU::LDA(){}
void NesCPU::LDX(){}
void NesCPU::LDY(){}
void NesCPU::LSR(){}

void NesCPU::NOP(){
    pc+= 1;
}

void NesCPU::ORA(){}
void NesCPU::PHA(){}
void NesCPU::PHP(){}
void NesCPU::PLA(){}
void NesCPU::PLP(){}
void NesCPU::ROL(){}
void NesCPU::ROR(){}
void NesCPU::RTI(){}
void NesCPU::RTS(){}
void NesCPU::SBC(){}
void NesCPU::SEC(){}
void NesCPU::SED(){}
void NesCPU::SEI(){}
void NesCPU::STA(){}
void NesCPU::STX(){}
void NesCPU::STY(){}
void NesCPU::TAX(){}
void NesCPU::TAY(){}
void NesCPU::TSX(){}
void NesCPU::TXA(){}
void NesCPU::TXS(){}
void NesCPU::TYA(){}
