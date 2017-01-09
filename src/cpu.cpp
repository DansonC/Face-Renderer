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
void (NesCPU::*ops[151])(void) =  {
/* $00 */ NOP, 
/* $01 */ NOP,
/* $02 */ NOP,
/* $03 */ NOP,
/* $04 */ NOP,
/* $05 */ NOP,
/* $06 */ NOP,
/* $07 */ NOP,
/* $08 */ NOP,
/* $09 */ NOP,
/* $0A */ NOP,
/* $0B */ NOP,
/* $0C */ NOP,
/* $0D */ NOP,
/* $0E */ NOP,
/* $0F */ NOP,
/* $10 */ NOP,
/* $11 */ NOP,
/* $12 */ NOP,
/* $13 */ NOP,
/* $14 */ NOP,
/* $15 */ NOP,
/* $16 */ NOP,
/* $17 */ NOP,
/* $18 */ NOP,
/* $19 */ NOP,
/* $1A */ NOP,
/* $1B */ NOP,
/* $1C */ NOP,
/* $1D */ NOP,
/* $1E */ NOP,
/* $1F */ NOP,
/* $20 */ NOP,
/* $21 */ NOP,
/* $22 */ NOP,
/* $23 */ NOP,
/* $24 */ NOP,
/* $25 */ NOP,
/* $26 */ NOP,
/* $27 */ NOP,
/* $28 */ NOP,
/* $29 */ NOP,
/* $2A */ NOP,
/* $2B */ NOP,
/* $2C */ NOP,
/* $2D */ NOP,
/* $2E */ NOP,
/* $2F */ NOP,
/* $30 */ NOP,
/* $31 */ NOP,
/* $32 */ NOP,
/* $33 */ NOP,
/* $34 */ NOP,
/* $35 */ NOP,
/* $36 */ NOP,
/* $37 */ NOP,
/* $38 */ NOP,
/* $39 */ NOP,
/* $3A */ NOP,
/* $3B */ NOP,
/* $3C */ NOP,
/* $3D */ NOP,
/* $3E */ NOP,
/* $3F */ NOP,
/* $40 */ NOP,
/* $41 */ NOP,
/* $42 */ NOP,
/* $43 */ NOP,
/* $44 */ NOP,
/* $45 */ NOP,
/* $46 */ NOP,
/* $47 */ NOP,
/* $48 */ NOP,
/* $49 */ NOP,
/* $4A */ NOP,
/* $4B */ NOP,
/* $4C */ NOP,
/* $4D */ NOP,
/* $4E */ NOP,
/* $4F */ NOP,
/* $50 */ NOP,
/* $51 */ NOP,
/* $52 */ NOP,
/* $53 */ NOP,
/* $54 */ NOP,
/* $55 */ NOP,
/* $56 */ NOP,
/* $57 */ NOP,
/* $58 */ NOP,
/* $59 */ NOP,
/* $5A */ NOP,
/* $5B */ NOP,
/* $5C */ NOP,
/* $5D */ NOP,
/* $5E */ NOP,
/* $5F */ NOP,
/* $60 */ NOP,
/* $61 */ NOP,
/* $62 */ NOP,
/* $63 */ NOP,
/* $64 */ NOP,
/* $65 */ NOP,
/* $66 */ NOP,
/* $67 */ NOP,
/* $68 */ NOP,
/* $69 */ NOP,
/* $6A */ NOP,
/* $6B */ NOP,
/* $6C */ NOP,
/* $6D */ NOP,
/* $6E */ NOP,
/* $6F */ NOP,
/* $70 */ NOP,
/* $71 */ NOP,
/* $72 */ NOP,
/* $73 */ NOP,
/* $74 */ NOP,
/* $75 */ NOP,
/* $76 */ NOP,
/* $77 */ NOP,
/* $78 */ NOP,
/* $79 */ NOP,
/* $7A */ NOP,
/* $7B */ NOP,
/* $7C */ NOP,
/* $7D */ NOP,
/* $7E */ NOP,
/* $7F */ NOP,
/* $80 */ NOP,
/* $81 */ NOP,
/* $82 */ NOP,
/* $83 */ NOP,
/* $84 */ NOP,
/* $85 */ NOP,
/* $86 */ NOP,
/* $87 */ NOP,
/* $88 */ NOP,
/* $89 */ NOP,
/* $8A */ NOP,
/* $8B */ NOP,
/* $8C */ NOP,
/* $8D */ NOP,
/* $8E */ NOP,
/* $8F */ NOP,
/* $90 */ NOP,
/* $91 */ NOP,
/* $92 */ NOP,
/* $93 */ NOP,
/* $94 */ NOP,
/* $95 */ NOP,
/* $96 */ NOP
};
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
