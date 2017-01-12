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

#include "mem.h"

class NesCPU
{
    private:
    /** Initialize Registers **/
        uint16_t pc;
        uint8_t S, A, X, Y;
        uint8_t P;
        
        uint8_t get_opcode();
        void process_ops(uint8_t opcode);
        void push(uint8_t val);
        uint8_t pull();
        
        NesMEM* mem;
        
        void set_P(uint8_t flag){
            P = P | flag;
        }
        
        void unset_P(uint8_t flag){
            P = P & (~flag);
        }
        
        void test_P(bool test, uint8_t flag)
        {
            if(test)
                P = P | flag;
            else
                P = P & (~flag);
        }
        
        //Note duplicate function declarations for several functions
        void ADC(uint16_t addr);
        void AND(uint16_t addr);
        void ASL(uint16_t addr);
        void ASL(void);
        void BCC(uint16_t addr);
        void BCS(uint16_t addr);
        void BEQ(uint16_t addr);
        void BIT(uint16_t addr);
        void BMI(uint16_t addr);
        void BNE(uint16_t addr);
        void BPL(uint16_t addr);
        void BRK(void);
        void BVC(uint16_t addr);
        void CLC(void);
        void CLD(void);
        void CLI(void);
        void CLV(void);
        void CMP(uint16_t addr);
        void CPX(uint16_t addr);
        void CPY(uint16_t addr);
        void DEC(uint16_t addr);
        void DEX(void);
        void DEY(void);
        void EOR(uint16_t addr);
        void INC(uint16_t addr);
        void INX(void);
        void INY(void);
        void JMP(uint16_t addr);
        void JSR(uint16_t addr);
        void LDA(uint16_t addr);
        void LDX(uint16_t addr);
        void LDY(uint16_t addr);
        void LSR(uint16_t addr);
        void LSR(void);
        void NOP();
        void ORA(uint16_t addr);
        void PHA(void);
        void PHP(void);
        void PLA(void);
        void PLP(void);
        void ROL(uint16_t addr);
        void ROL(void);
        void ROR(uint16_t addr);
        void ROR(void);
        void RTI(void);
        void RTS(void);
        void SBC(uint16_t addr);
        void SEC(void);
        void SED(void);
        void SEI(void);
        void STA(uint16_t addr);
        void STX(uint16_t addr);
        void STY(uint16_t addr);
        void TAX(void);
        void TAY(void);
        void TSX(void);
        void TXA(void);
        void TXS(void);
        void TYA(void);
        
        
        

    public:
        void run();
        NesCPU(const std::string romDir); // constructor
        ~NesCPU(); // destructor
        
        
};


#endif
