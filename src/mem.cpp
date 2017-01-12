#include "mem.h"

//Constructor
//TODO
NesMEM::NesMEM()
{
    
}

//Deconstructor
//TODO
NesMEM::~NesMEM()
{
    
}
/** Translates a NES memory address to a computer memory address
*/
void* NesMEM::get_mem_location(uint16_t addr)
{
    //TODO unimplemented
    return 0;
}
void NesMEM::write(uint16_t addr, uint8_t value)
{
    uint8_t* pointer = get_mem_location(addr);
    *pointer = value;
}

uint8_t NesMEM::read(uint16_t addr)
{
    uint8_t* pointer = get_mem_location(addr);
    return (*pointer);
}