#ifndef __NES_MEM__
#define __NES_MEM__

class NesMEM
{
    public:
        uint8_t read(uint16_t addr);
        uint8_t write(uint16_t addr, uint8_t value);
        void push(uint8_t val);
        uint8_t pull();
    private:
};

#endif
