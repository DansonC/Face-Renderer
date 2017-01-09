#ifndef __NES_CPU__
#define __NES_CPU__


// TODO make status flags into a Union?
/** Status Flags **/
#define STATUS_NEG 0x80
#define STATUS_OVERFLOW 0x40
#define STATUS_S 0x20
#define STATUS S2 0x10
#define STATUS_DECIMAL 0x08
#define STATUS_INT 0x04
#define STATUS_ZERO 0x02
#define STATUS_CARRY 0x01

#include <string>
#include <cstdint>
#include <iostream>

class NesCPU
{
    private:
    /** Initialize Registers **/
        uint16_t pc;
        uint8_t S, A, X, Y;
        uint8_t P;
        
        void ADC();
        void AND();
        void ASL();
        void BCC();
        void BCS();
        void BEQ();
        void BIT();
        void BMI();
        void BNE();
        void BPL();
        void BRK();
        void BVC();
        void CLC();
        void CLD();
        void CLI();
        void CLV();
        void CMP();
        void CPX();
        void CPY();
        void DEC();
        void DEX();
        void DEY();
        void EOR();
        void INC();
        void INX();
        void INY();
        void JMP();
        void JSR();
        void LDA();
        void LDX();
        void LDY();
        void LSR();
        void NOP();
        void ORA();
        void PHA();
        void PHP();
        void PLA();
        void PLP();
        void ROL();
        void ROR();
        void RTI();
        void RTS();
        void SBC();
        void SEC();
        void SED();
        void SEI();
        void STA();
        void STX();
        void STY();
        void TAX();
        void TAY();
        void TSX();
        void TXA();
        void TXS();
        void TYA();
        
        
        

    public:
        void run();
        NesCPU(const std::string romDir); // constructor
        ~NesCPU(); // destructor
};


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

#endif
