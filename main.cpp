#include <iostream>

#include "include/CPU.hpp"

int main() {


    CPU cpu;

    // 0x24
    // 001001 00

    /// 00 00 00 0c
    /// opc     src1  src2  dest  shamt  func = 0C = 001 100
    /// 000000  00000 00000 00000 00000  001 100
    ///


    u32 rom[] = {
        0x2408001e,
        0x24090014,
        0x01092020,
        0x24020001,
        0x0000000c, // syscall :
        0x240400c0,
        0x00042400,
        0x24840000,
        0x24020004,
        0x0000000c,
        0x24020000,
        0x03e00008,
        0x0a48656c,
        0x6c6f2057,
        0x6f726c64,
        0x210a0000,
    };

    cpu.loadROM(rom, sizeof(rom));

    cpu.step();
    cpu.step();
    cpu.step();
    cpu.step();
    cpu.step();
    cpu.step();
    cpu.step();
    cpu.step();
    cpu.step();
    cpu.step();
    cpu.step();
    cpu.step();
    cpu.step();




    return 0;
}
