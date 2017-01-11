#include "cpu.h"

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdint>
#include <iostream>

/** flags P = NVBU DIZC
    to set negative flag: P = P | NEGATIVE_FLAG,
    to unset negative flag: P = P & ~NEGATIVE_FLAG,
    etc.
 **/
#define NEGATIVE_FLAG 0x80 // negative
#define OVERFLOW_FLAG 0x40 // overflow
#define BREAK_FLAG 0x20 // break
#define UNUSED_FLAG 0x10 // unused
#define DECIMAL_FLAG 0x08 // decimal
#define INTERRUPT_FLAG 0x04 // interrupt
#define ZERO_FLAG 0x02 // zero
#define CARRY_FLAG 0x01 // carry

//TEMPORARY PROGRAMS TO TRY RUNNING
unsigned char noptest[3] = {0xea, 0xea, 0xea}; // NO OPS
unsigned char test1[7] = {0xa9, 0xc0, 0xaa, 0xe8, 0x69, 0xc4, 0x00};



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

    switch(opcode)
    {
        case 0x00:
            BRK();
            break;
        case 0x20: //Special case for JSR absolute
            NOP(); //TODO
            break;
        case 0x40:
            RTI();
            break;
        case 0x60:
            RTS();
            break;
        case 0x08:
            PHP();
            break;
        case 0x28:
            PLP();
            break;
        case 0x48:
            PHA();
            break;
        case 0x68:
            PLA();
            break;
        case 0x88:
            DEY();
            break;
        case 0xA8:
            TAY();
            break;
        case 0xC8:
            INY();
            break;
        case 0xE8:
            INX();
            break;
        case 0x18:
            CLC();
            break;
        case 0x38:
            SEC();
            break;
        case 0x58:
            CLI();
            break;
        case 0x78:
            SEI();
            break;
        case 0x98:
            TYA();
            break;
        case 0xB8:
            CLV();
            break;
        case 0xD8:
            CLD();
            break;
        case 0xF8:
            SED();
            break;
        case 0x8A:
            TXA();
            break;
        case 0x9A:
            TXS();
            break;
        case 0xAA:
            TAX();
            break;
        case 0xBA:
            TSX();
            break;
        case 0xCA:
            DEX();
            break;
        case 0xEA:
            NOP();
            break;
        default:
         // If opcode follows the form xxy10000, then its a branch
            if((opcode & (~0xE0)) == 0x10)
            {
                //TODO branch code
            } else
            {
                process_ops(opcode);
            }
            break;
    }
}

void NesCPU::process_ops(uint8_t opcode)
{
    //Opcodes follow the form aaabbbcc
    uint8_t a = (opcode >> 5) & (~0x7);
    uint8_t b = (opcode >> 2) & (~0x7);
    uint8_t c = opcode & (~0x3);


    uint16_t addr;

    if(c == 0x0)
    {
        //TODO get address
        switch(a)
        {
            case 0x0:
                // ASSERT(0); // Should never reach
            case 0x1:
                BIT(addr);
                break;
            case 0x2:
                JMP(addr); //TODO figure this out
                break;
            case 0x3:
                JMP(addr); //TODO figure this out
                break;
            case 0x4:
                STY(addr);
                break;
            case 0x5:
                LDY(addr);
                break;
            case 0x6:
                CPY(addr);
            case 0x7:
                CPX(addr);
        }
    }
    if(c == 0x1 || 0x3)
    {
        //TODO get addr
        switch(a)
        {
           case 0x0:
                ORA(addr);
                break;
            case 0x1:
                AND(addr);
                break;
            case 0x2:
                EOR(addr);
                break;
            case 0x3:
                ADC(addr);
                break;
            case 0x4:
                STA(addr);
                break;
            case 0x5:
                LDA(addr);
                break;
            case 0x6:
                CMP(addr);
                break;
            case 0x7:
                SBC(addr);
                break;
        }
    }
    if(c == 0x2 || 0x3)
    {
        //TODO get addr
        switch(a)
        {
            case 0x0:
                ASL(addr);
                break;
            case 0x1:
                ROL(addr);
                break;
            case 0x2:
                LSR(addr);
                break;
            case 0x3:
                ROR(addr);
                break;
            case 0x4:
                STX(addr);
                break;
            case 0x5:
                LDX(addr);
                break;
            case 0x6:
                DEC(addr);
                break;
            case 0x7:
                INC(addr);
                break;
        }
    }
}

void NesCPU::ADC(uint16_t addr){}
void NesCPU::AND(uint16_t addr){}
void NesCPU::ASL(uint16_t addr){}
void NesCPU::BCC(uint16_t addr){}
void NesCPU::BCS(uint16_t addr){}
void NesCPU::BEQ(uint16_t addr){}
void NesCPU::BIT(uint16_t addr){}
void NesCPU::BMI(uint16_t addr){}
void NesCPU::BNE(uint16_t addr){}
void NesCPU::BPL(uint16_t addr){}
void NesCPU::BRK(void){}
void NesCPU::BVC(uint16_t addr){}
void NesCPU::CLC(void){}
void NesCPU::CLD(void){}
void NesCPU::CLI(void){}
void NesCPU::CLV(void){}
void NesCPU::CMP(uint16_t addr){}
void NesCPU::CPX(uint16_t addr){}
void NesCPU::CPY(uint16_t addr){}
void NesCPU::DEC(uint16_t addr){}

void NesCPU::DEX(void){
    pc+= 1;
    X-= 1;

    if (X == 0) P = P | ZERO_FLAG;

    if ((X & 0x80) != 0) P = P | NEGATIVE_FLAG;
}

void NesCPU::DEY(void){
    pc+= 1;
    Y-= 1;

    if (Y == 0) P = P | ZERO_FLAG;

    if ((Y & 0x80) != 0) P = P | NEGATIVE_FLAG;
}

void NesCPU::EOR(uint16_t addr){}
void NesCPU::INC(uint16_t addr){}
void NesCPU::INX(void){
    pc+= 1;
    X+= 1;

    if (X == 0) P = P | ZERO_FLAG;

    if ((X & 0x80) != 0) P = P | NEGATIVE_FLAG;
}

void NesCPU::INY(void){
    pc+= 1;
    Y+= 1;

    if (Y == 0) P = P | ZERO_FLAG;

    if ((Y & 0x80) != 0) P = P | NEGATIVE_FLAG;
}

void NesCPU::JMP(uint16_t addr){}
void NesCPU::JSR(uint16_t addr){}
void NesCPU::LDA(uint16_t addr){}
void NesCPU::LDX(uint16_t addr){}
void NesCPU::LDY(uint16_t addr){}
void NesCPU::LSR(uint16_t addr){}
void NesCPU::NOP(){
    pc += 1;
}
void NesCPU::ORA(uint16_t addr){}
void NesCPU::PHA(void){}
void NesCPU::PHP(void){}
void NesCPU::PLA(void){}
void NesCPU::PLP(void){}
void NesCPU::ROL(uint16_t addr){}
void NesCPU::ROR(uint16_t addr){}
void NesCPU::RTI(void){}
void NesCPU::RTS(void){}
void NesCPU::SBC(uint16_t addr){}
void NesCPU::SEC(void){}
void NesCPU::SED(void){}
void NesCPU::SEI(void){}
void NesCPU::STA(uint16_t addr){}
void NesCPU::STX(uint16_t addr){}
void NesCPU::STY(uint16_t addr){}

void NesCPU::TAX(void){
    pc+= 1;
    X = A;

    if (X == 0) P = P | ZERO_FLAG;

    if ((X & 0x80) != 0) P = P | NEGATIVE_FLAG;
}

void NesCPU::TAY(void){
    pc+= 1;
    Y = A;

    if (Y == 0) P = P | ZERO_FLAG;

    if ((Y & 0x80) != 0) P = P | NEGATIVE_FLAG;
}

void NesCPU::TSX(void){}

void NesCPU::TXA(void){
    pc+= 1;
    A = X;

    if (A == 0) P = P | ZERO_FLAG;

    if ((A & 0x80) != 0) P = P | NEGATIVE_FLAG;
}

void NesCPU::TXS(void){}
void NesCPU::TYA(void){
    pc+= 1;
    A = Y;

    if (A == 0) P = P | ZERO_FLAG;

    if ((A & 0x80) != 0) P = P | NEGATIVE_FLAG;
}

