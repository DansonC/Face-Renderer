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
