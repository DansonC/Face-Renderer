#ifndef __NES_CPU__
#define __NES_CPU__

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
        uint8_t sp, A, X, Y;
        uint8_t P;

    public:
        void run();
        NesCPU(const std::string romDir); // constructor
        ~NesCPU(); // destructor
};

NesCPU::NesCPU(const std::string romDir){
    std::cout << "NES CPU is being created" << std::endl;
    std::cout << "Loading " << romDir << std::endl;
}

NesCPU::~NesCPU(void){
    std::cout << "NES CPU is being deleted" << std::endl;
}

#endif
