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
#define NEGATIVE_FLAG 0x80
#define OVERFLOW_FLAG 0x40
#define BREAK_FLAG 0x20
#define UNUSED_FLAG 0x10
#define DECIMAL_FLAG 0x08
#define INTERRUPT_FLAG 0x04
#define ZERO_FLAG 0x02
#define CARRY_FLAG 0x01

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

    //TODO  Get Mapper and pass to memory
    mem = new NesMEM();
    //Temporary starting point. Change later
    pc = 0;


    std::cout << "Loading " << romDir << std::endl;
    //TODO load rom

}

NesCPU::~NesCPU(void){
    std::cout << "NES CPU is being deleted" << std::endl;
    delete mem;
}

void NesCPU::run()
{
    // 1. Grab opcode
    uint8_t opcode = mem->read(pc);

    switch(opcode)
    {
        case 0x00:
            BRK();
            break;
        case 0x20:
            JSR();
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
        case 0x0A:
            ASL();
            break;
        case 0x2A:
            ROL();
            break;
        case 0x4A:
            LSR();
            break;
        case 0x6A:
            ROR();
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
    pc++;
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
        void (NesCPU::*optable[8])(uint16_t addr) = {NULL, BIT, JMP_ABS, JMP_IND, STY, LDY, CPY, CPX};
        (this->*optable[a])(addr);
    }
    if(c == 0x1 || 0x3)
    {
        //TODO get addr
        void (NesCPU::*optable[8])(uint16_t addr) = {ORA, AND, EOR, ADC, STA, LDA, CMP, SBC};
        (this->*optable[a])(addr);
    }
    if(c == 0x2 || 0x3)
    {
        //TODO get addr
        void (NesCPU::*optable[8])(uint16_t addr) = {ASL, ROL, LSR, ROR, STX, LDX, DEC, INC};
        (this->*optable[a])(addr);
    }
}

#define STACK_PAGE 0x10
void NesCPU::push(uint8_t val){
    mem->write(STACK_PAGE | S, val);
    S--;
}
uint8_t NesCPU::pull(){
    uint8_t val = mem->read(STACK_PAGE | S);
    S++;
    return val;
}


/***** OPCODES *****/
void NesCPU::ADC(uint16_t addr){}
void NesCPU::AND(uint16_t addr){
    uint8_t val = mem->read(addr);
    A = A & val;
    test_P((A == 0), ZERO_FLAG);
    test_P(((A & 0x80) != 0), NEGATIVE_FLAG);
}
void NesCPU::ASL(uint16_t addr){
    uint8_t val = mem->read(addr);
    uint8_t result = val << 1;
    mem->write(addr, result);
    test_P(((val & 0x80)), CARRY_FLAG);
    test_P((result == 0), ZERO_FLAG);
    test_P(((result & 0x80) != 0), NEGATIVE_FLAG);
}
//void NesCPU::BCC(uint16_t addr){}
//void NesCPU::BCS(uint16_t addr){}
//void NesCPU::BEQ(uint16_t addr){}
void NesCPU::BIT(uint16_t addr){
    uint8_t val = mem->read(addr);
    val = A & val;
    test_P((val == 0), ZERO_FLAG);
    test_P(((val & 0x80) != 0), NEGATIVE_FLAG);
    test_P(((val & 0x40) != 0), OVERFLOW_FLAG);
}
//void NesCPU::BMI(uint16_t addr){}
//void NesCPU::BNE(uint16_t addr){}
//void NesCPU::BPL(uint16_t addr){}
void NesCPU::BRK(void){}
//void NesCPU::BVC(uint16_t addr){}
void NesCPU::CLC(void){
    unset_P(CARRY_FLAG);
}
void NesCPU::CLD(void){
    unset_P(DECIMAL_FLAG);
}
void NesCPU::CLI(void){
    unset_P(INTERRUPT_FLAG);
}
void NesCPU::CLV(void){
    unset_P(OVERFLOW_FLAG);
}
void NesCPU::CMP(uint16_t addr){
    uint8_t val = mem->read(addr);
    uint8_t result = A - val;
    test_P((A >= val), CARRY_FLAG);
    test_P((A == val), ZERO_FLAG);
    test_P(((result & 0x80) != 0), NEGATIVE_FLAG);
}

void NesCPU::CPX(uint16_t addr){
    uint8_t val = mem->read(addr);
    uint8_t result = X - val;
    test_P((X >= val), CARRY_FLAG);
    test_P((X == val), ZERO_FLAG);
    test_P(((result & 0x80) != 0), NEGATIVE_FLAG);
}
void NesCPU::CPY(uint16_t addr){
    uint8_t val = mem->read(addr);
    uint8_t result = Y - val;
    test_P((Y >= val), CARRY_FLAG);
    test_P((Y == val), ZERO_FLAG);
    test_P(((result & 0x80) != 0), NEGATIVE_FLAG);
}
void NesCPU::DEC(uint16_t addr){
    uint8_t val = mem->read(addr);
    val = val - 1;
    
    test_P((val == 0), ZERO_FLAG);
    test_P(((val & 0x80) != 0), NEGATIVE_FLAG);
    mem->write(addr, val);
}

void NesCPU::DEX(void){
    X-= 1;

    test_P((X == 0), ZERO_FLAG);
    test_P(((X & 0x80) != 0), NEGATIVE_FLAG);
}

void NesCPU::DEY(void){
    Y-= 1;

    test_P((Y == 0), ZERO_FLAG);
    test_P(((Y & 0x80) != 0), NEGATIVE_FLAG);
}

void NesCPU::EOR(uint16_t addr){
    uint8_t val = mem->read(addr);
    A = A^val;
    test_P((A == 0), ZERO_FLAG);
    test_P(((A & 0x80) != 0), NEGATIVE_FLAG);
}
void NesCPU::INC(uint16_t addr){
    uint8_t val = mem->read(addr);
    val = val + 1;
    test_P((val == 0), ZERO_FLAG);
    test_P(((val & 0x80) != 0), NEGATIVE_FLAG);
    mem->write(addr, val);
}
void NesCPU::INX(void){
    X+= 1;

    test_P((X == 0), ZERO_FLAG);
    test_P(((X & 0x80) != 0), NEGATIVE_FLAG);
}

void NesCPU::INY(void){
    Y+= 1;

    test_P((Y == 0), ZERO_FLAG);
    test_P(((Y & 0x80) != 0), NEGATIVE_FLAG);
}
void NesCPU::JSR(void){
    //TODO
    /*
    push(pc + 2); // push (ret address - 1) onto stack
    pc = abs_addr() - 1;
    */
}
void NesCPU::LDA(uint16_t addr){
    A = mem->read(addr);
    test_P((A == 0), ZERO_FLAG);
    test_P(((A & 0x80) != 0), NEGATIVE_FLAG);
}
void NesCPU::LDX(uint16_t addr){
    X = mem->read(addr);
    test_P((X == 0), ZERO_FLAG);
    test_P(((X & 0x80) != 0), NEGATIVE_FLAG);
}
void NesCPU::LDY(uint16_t addr){
    Y = mem->read(addr);
    test_P((Y == 0), ZERO_FLAG);
    test_P(((Y & 0x80) != 0), NEGATIVE_FLAG);
}
void NesCPU::LSR(uint16_t addr){}
void NesCPU::NOP(){
    //DOES NOTHING
}
void NesCPU::ORA(uint16_t addr){
    uint8_t val = mem->read(addr);
    A = A | val;
    test_P((A == 0), ZERO_FLAG);
    test_P(((A & 0x80) != 0), NEGATIVE_FLAG);
}
void NesCPU::PHA(void){
    push(A);
}
void NesCPU::PHP(void){
    push(P);
}
void NesCPU::PLA(void){
    A = pull();
    
    test_P((A == 0), ZERO_FLAG);
    test_P(((A & 0x80) != 0), NEGATIVE_FLAG);
}
void NesCPU::PLP(void){
    P = pull();
}
void NesCPU::ROL(uint16_t addr){}
void NesCPU::ROR(uint16_t addr){}
void NesCPU::RTI(void){}
void NesCPU::RTS(void){}
void NesCPU::SBC(uint16_t addr){}
void NesCPU::SEC(void){
    set_P(CARRY_FLAG);
}
void NesCPU::SED(void){
    set_P(DECIMAL_FLAG);
}
void NesCPU::SEI(void){
    set_P(INTERRUPT_FLAG);
}
void NesCPU::STA(uint16_t addr){
    mem->write(addr, A);
}
void NesCPU::STX(uint16_t addr){
    mem->write(addr, X);
}
void NesCPU::STY(uint16_t addr){
    mem->write(addr, Y);
}

void NesCPU::TAX(void){
    X = A;

    test_P((X == 0), ZERO_FLAG);
    test_P(((X & 0x80) != 0), NEGATIVE_FLAG);
}

void NesCPU::TAY(void){
    Y = A;

    test_P((Y == 0), ZERO_FLAG);
    test_P(((Y & 0x80) != 0), NEGATIVE_FLAG);
}

void NesCPU::TSX(void){
    X = S;
    
    test_P((X == 0), ZERO_FLAG);
    test_P(((X & 0x80) != 0), NEGATIVE_FLAG);
}

void NesCPU::TXA(void){
    A = X;

    test_P((A == 0), ZERO_FLAG);
    test_P(((A & 0x80) != 0), NEGATIVE_FLAG);
}

void NesCPU::TXS(void){
    S = X;
}
void NesCPU::TYA(void){
    A = Y;

    test_P((A == 0), ZERO_FLAG);
    test_P(((A & 0x80) != 0), NEGATIVE_FLAG);
}

//JUMP
void NesCPU::JMP_ABS(uint16_t addr){
    pc = addr - 1; // Gets incremented later
}
void NesCPU::JMP_IND(uint16_t addr){
    //TODO
    //Special case
}

//Accumulator Addressing
void NesCPU::ASL(void){
    test_P(((A & 0x80)), CARRY_FLAG);
    A = A << 1;
    test_P((A == 0), ZERO_FLAG);
    test_P(((A & 0x80) != 0), NEGATIVE_FLAG);
}
void NesCPU::ROL(void){}
void NesCPU::LSR(void){}
void NesCPU::ROR(void){}

