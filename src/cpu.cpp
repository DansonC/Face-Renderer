#include "cpu.h"

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdint>
#include <iostream>

/** flags P = NVBU DIZC
    to set negative flag: P = P | N,
    to unset negative flag: P = P & ~N,
    etc.
 **/
#define N 0x80 // negative
#define V 0x40 // overflow
#define B 0x20 // break
#define U 0x10 // unused
#define D 0x08 // decimal
#define I 0x04 // interrupt
#define Z 0x02 // zero
#define C 0x01 // carry

//TEMPORARY PROGRAMS TO TRY RUNNING
unsigned char noptest[3] = {0xea, 0xea, 0xea}; // NO OPS
unsigned char test1[7] = {0xa9, 0xc0, 0xaa, 0xe8, 0x69, 0xc4, 0x00};



void (NesCPU::*ops[151])(void) =  {
/* $00 */ NesCPU::NOP,
/* $01 */ NesCPU::NOP,
/* $02 */ NesCPU::NOP,
/* $03 */ NesCPU::NOP,
/* $04 */ NesCPU::NOP,
/* $05 */ NesCPU::NOP,
/* $06 */ NesCPU::NOP,
/* $07 */ NesCPU::NOP,
/* $08 */ NesCPU::NOP,
/* $09 */ NesCPU::NOP,
/* $0A */ NesCPU::NOP,
/* $0B */ NesCPU::NOP,
/* $0C */ NesCPU::NOP,
/* $0D */ NesCPU::NOP,
/* $0E */ NesCPU::NOP,
/* $0F */ NesCPU::NOP,
/* $10 */ NesCPU::NOP,
/* $11 */ NesCPU::NOP,
/* $12 */ NesCPU::NOP,
/* $13 */ NesCPU::NOP,
/* $14 */ NesCPU::NOP,
/* $15 */ NesCPU::NOP,
/* $16 */ NesCPU::NOP,
/* $17 */ NesCPU::NOP,
/* $18 */ NesCPU::NOP,
/* $19 */ NesCPU::NOP,
/* $1A */ NesCPU::NOP,
/* $1B */ NesCPU::NOP,
/* $1C */ NesCPU::NOP,
/* $1D */ NesCPU::NOP,
/* $1E */ NesCPU::NOP,
/* $1F */ NesCPU::NOP,
/* $20 */ NesCPU::NOP,
/* $21 */ NesCPU::NOP,
/* $22 */ NesCPU::NOP,
/* $23 */ NesCPU::NOP,
/* $24 */ NesCPU::NOP,
/* $25 */ NesCPU::NOP,
/* $26 */ NesCPU::NOP,
/* $27 */ NesCPU::NOP,
/* $28 */ NesCPU::NOP,
/* $29 */ NesCPU::NOP,
/* $2A */ NesCPU::NOP,
/* $2B */ NesCPU::NOP,
/* $2C */ NesCPU::NOP,
/* $2D */ NesCPU::NOP,
/* $2E */ NesCPU::NOP,
/* $2F */ NesCPU::NOP,
/* $30 */ NesCPU::NOP,
/* $31 */ NesCPU::NOP,
/* $32 */ NesCPU::NOP,
/* $33 */ NesCPU::NOP,
/* $34 */ NesCPU::NOP,
/* $35 */ NesCPU::NOP,
/* $36 */ NesCPU::NOP,
/* $37 */ NesCPU::NOP,
/* $38 */ NesCPU::NOP,
/* $39 */ NesCPU::NOP,
/* $3A */ NesCPU::NOP,
/* $3B */ NesCPU::NOP,
/* $3C */ NesCPU::NOP,
/* $3D */ NesCPU::NOP,
/* $3E */ NesCPU::NOP,
/* $3F */ NesCPU::NOP,
/* $40 */ NesCPU::NOP,
/* $41 */ NesCPU::NOP,
/* $42 */ NesCPU::NOP,
/* $43 */ NesCPU::NOP,
/* $44 */ NesCPU::NOP,
/* $45 */ NesCPU::NOP,
/* $46 */ NesCPU::NOP,
/* $47 */ NesCPU::NOP,
/* $48 */ NesCPU::NOP,
/* $49 */ NesCPU::NOP,
/* $4A */ NesCPU::NOP,
/* $4B */ NesCPU::NOP,
/* $4C */ NesCPU::NOP,
/* $4D */ NesCPU::NOP,
/* $4E */ NesCPU::NOP,
/* $4F */ NesCPU::NOP,
/* $50 */ NesCPU::NOP,
/* $51 */ NesCPU::NOP,
/* $52 */ NesCPU::NOP,
/* $53 */ NesCPU::NOP,
/* $54 */ NesCPU::NOP,
/* $55 */ NesCPU::NOP,
/* $56 */ NesCPU::NOP,
/* $57 */ NesCPU::NOP,
/* $58 */ NesCPU::NOP,
/* $59 */ NesCPU::NOP,
/* $5A */ NesCPU::NOP,
/* $5B */ NesCPU::NOP,
/* $5C */ NesCPU::NOP,
/* $5D */ NesCPU::NOP,
/* $5E */ NesCPU::NOP,
/* $5F */ NesCPU::NOP,
/* $60 */ NesCPU::NOP,
/* $61 */ NesCPU::NOP,
/* $62 */ NesCPU::NOP,
/* $63 */ NesCPU::NOP,
/* $64 */ NesCPU::NOP,
/* $65 */ NesCPU::NOP,
/* $66 */ NesCPU::NOP,
/* $67 */ NesCPU::NOP,
/* $68 */ NesCPU::NOP,
/* $69 */ NesCPU::NOP,
/* $6A */ NesCPU::NOP,
/* $6B */ NesCPU::NOP,
/* $6C */ NesCPU::NOP,
/* $6D */ NesCPU::NOP,
/* $6E */ NesCPU::NOP,
/* $6F */ NesCPU::NOP,
/* $70 */ NesCPU::NOP,
/* $71 */ NesCPU::NOP,
/* $72 */ NesCPU::NOP,
/* $73 */ NesCPU::NOP,
/* $74 */ NesCPU::NOP,
/* $75 */ NesCPU::NOP,
/* $76 */ NesCPU::NOP,
/* $77 */ NesCPU::NOP,
/* $78 */ NesCPU::NOP,
/* $79 */ NesCPU::NOP,
/* $7A */ NesCPU::NOP,
/* $7B */ NesCPU::NOP,
/* $7C */ NesCPU::NOP,
/* $7D */ NesCPU::NOP,
/* $7E */ NesCPU::NOP,
/* $7F */ NesCPU::NOP,
/* $80 */ NesCPU::NOP,
/* $81 */ NesCPU::NOP,
/* $82 */ NesCPU::NOP,
/* $83 */ NesCPU::NOP,
/* $84 */ NesCPU::NOP,
/* $85 */ NesCPU::NOP,
/* $86 */ NesCPU::NOP,
/* $87 */ NesCPU::NOP,
/* $88 */ NesCPU::NOP,
/* $89 */ NesCPU::NOP,
/* $8A */ NesCPU::NOP,
/* $8B */ NesCPU::NOP,
/* $8C */ NesCPU::NOP,
/* $8D */ NesCPU::NOP,
/* $8E */ NesCPU::NOP,
/* $8F */ NesCPU::NOP,
/* $90 */ NesCPU::NOP,
/* $91 */ NesCPU::NOP,
/* $92 */ NesCPU::NOP,
/* $93 */ NesCPU::NOP,
/* $94 */ NesCPU::NOP,
/* $95 */ NesCPU::NOP,
/* $96 */ NesCPU:: NOP
};


NesCPU::NesCPU(const std::string romDir){
    std::cout << "NES CPU is being created" << std::endl;

    /** INITIALIZING POWERUP STATE **/
    P = 0x34;
    A = 0;
    X = 0;
    Y = 0;
    S = 0xFD;

    //TODO init memory
    //Temporary starting point. Change later
    pc = 0;


    std::cout << "Loading " << romDir << std::endl;
    //TODO load rom

}

NesCPU::~NesCPU(void){
    std::cout << "NES CPU is being deleted" << std::endl;
}

//TODO
uint8_t NesCPU::get_opcode()
{
    return 0;
}
void NesCPU::run()
{
    // 1. Grab opcode
    uint8_t opcode = this->get_opcode();
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

void NesCPU::DEX(){
//TODO $CA
}

void NesCPU::DEY(){
//TODO $88
}

void NesCPU::EOR(){}
void NesCPU::INC(){}

void NesCPU::INX(){
//TODO $E8
}

void NesCPU::INY(){
//TODO $C8
}

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

void NesCPU::TAX(){
//TODO $AA
    X = A;
    if (X == 0){

    }
}

void NesCPU::TAY(){
//TODO $A8
}

void NesCPU::TSX(){}

void NesCPU::TXA(){
//TODO $8A
}

void NesCPU::TXS(){}

void NesCPU::TYA(){
//TODO $98
}

