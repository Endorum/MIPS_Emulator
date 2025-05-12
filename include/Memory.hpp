#include <vector>
#include <stdexcept>
#include <cstdint>

#define u32 uint32_t
#define u16 uint16_t
#define u8  uint8_t
#define s32 int32_t
#define s16 int16_t
#define s8  int8_t

class Memory {
public:
    static constexpr u32 MEM_SIZE = (1 << 20) - 1; // 64 MB for testing

    u8* data;

    Memory() {
        data = static_cast<uint8_t *>(malloc(MEM_SIZE));
        if(!data) throw std::runtime_error("Could not allocate data");
    }

    ~Memory() {
        free(data);
    }





    u32 readWord(u32 address) {
        if (address % 4 != 0) throw std::runtime_error("Address not word-aligned");
        if (address + 4 > MEM_SIZE) throw std::runtime_error("Memory read out of bounds " + std::to_string(address));

        u32 word = 0;
        for (int i = 0; i < 4; ++i)
            word |= data[address + i] << (24 - 8 * i);
        return word;
    }

    u16 readHalf(u32 address) {
        if (address % 2 != 0) throw std::runtime_error("Address not halfword-aligned");
        if (address + 2 > MEM_SIZE) throw std::runtime_error("Memory read out of bounds " + std::to_string(address));

        return (data[address] << 8) | data[address + 1];
    }

    u8 readByte(u32 address) {
        if (address > MEM_SIZE) throw std::runtime_error("Memory read out of bounds " + std::to_string(address));
        return data[address];
    }

    void writeWord(u32 address, u32 value) {
        if (address % 4 != 0) throw std::runtime_error("Address not word-aligned");
        if (address + 4 > MEM_SIZE) throw std::runtime_error("Memory write out of bounds " + std::to_string(address));

        for (int i = 0; i < 4; ++i)
            data[i] = (value >> (24 - 8 * i)) & 0xFF;
    }

    void writeHalf(u32 address, u16 value) {
        if (address % 2 != 0) throw std::runtime_error("Address not halfword-aligned");
        if (address + 2 > MEM_SIZE) throw std::runtime_error("Memory write out of bounds " + std::to_string(address));

        data[address] = (value >> 8) & 0xFF;
        data[address + 1] = value & 0xFF;
    }

    void writeByte(u32 address, u8 value) {
        if (address > MEM_SIZE) throw std::runtime_error("Memory write out of bounds " + std::to_string(address));
        data[address] = value;
    }
};
