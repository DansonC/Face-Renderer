#ifndef __NES_MEM__
#define __NES_MEM__

#include <cstdint>

class NesMEM
{
    public:
        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t value);
        void push(uint8_t val);
        uint8_t pull();
    private:
        void* get_mem_location(uint16_t addr);
};

#endif
