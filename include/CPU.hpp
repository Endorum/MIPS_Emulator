//
// Created by Alexander on 12.05.25.
//

#ifndef CPU_HPP
#define CPU_HPP
#include <cstdint>
#include <iostream>
#include <stdexcept>

#include "Memory.hpp"


typedef enum {
    R_ZERO, // always cointains 0

    R_AT, // reserved for assembler

    R_V0, // expression evaluation and function results
    R_V1,

    R_A0, // Arguments passed to procedures and functions
    R_A1,
    R_A2,
    R_A3,

    R_T0, // temporary storage - can be overwritten by called routines
    R_T1,
    R_T2,
    R_T3,
    R_T4,
    R_T5,
    R_T6,
    R_T7,

    R_S0, // variable storage - must be saved by called routines
    R_S1,
    R_S2,
    R_S3,
    R_S4,
    R_S5,
    R_S6,
    R_S7,

    R_T8, // more temporary storage
    R_T9,

    R_K0, // Reserved for OS use
    R_K1,

    R_GP, // global area pointer
    R_SP, // stack pointer
    R_FP, // frame pointer
    R_RA  // return address register


}REG_IDX;



typedef struct Instruction {
    u32 instr = 0;

    uint32_t opcode; // = (instr >> 26) & 0x3F;
    uint32_t rs; // = (instr >> 21) & 0x1F;
    uint32_t rt; // = (instr >> 16) & 0x1F;
    uint32_t rd; // = (instr >> 11) & 0x1F;
    uint32_t shamt; // = (instr >> 6)  & 0x1F;
    uint32_t funct; // = instr & 0x3F;
    uint32_t imm; // = instr & 0xFFFF;
    int16_t  simm; // = static_cast<int16_t>(imm);
    uint32_t addr; // = instr & 0x03FFFFFF;

    void print() const {
        printf("Instruction: %08X\n", instr);

        printf("opcode: %08X\n",opcode);
        printf("rs: %08X\n",rs);
        printf("rt: %08X\n",rt);
        printf("rd: %08X\n",rd);
        printf("shamt: %08X\n",shamt);
        printf("funct: %08X\n",funct);
        printf("imm: %08X=%d\n",imm,imm);
        printf("simm: %08X=%d\n",simm,simm);
        printf("addr: %08X\n",addr);
    }

    // 1D
    // 011 101

}Instruction;


class CPU {
public:


    CPU() {
        memory = new Memory();
    }

    ~CPU() {
        delete memory;
    }

    u32 heap_break = 0xF0000000;

    void loadROM(u32* rom, size_t size) {
        if(pc + size > memory->MEM_SIZE) {
            throw std::runtime_error("ERROR: pc + rom size out of bounds");
        }

        for(int i=0;i<size;i++) {
            memory->writeWord(i*4, rom[i]);
        }

    }


    void decode(u32 instr) {
        Instruction res;
        res.instr = instr;
        res.opcode = (instr >> 26) & 0x3F;
        res.rs     = (instr >> 21) & 0x1F;
        res.rt     = (instr >> 16) & 0x1F;
        res.rd     = (instr >> 11) & 0x1F;
        res.shamt  = (instr >> 6)  & 0x1F;
        res.funct  = instr & 0x3F;
        res.imm    = instr & 0xFFFF;
        res.simm   = static_cast<int16_t>(res.imm);
        res.addr   = instr & 0x03FFFFFF;
        current_instr = res;

        // current_instr.print();
    }

    void step() {
        u32 instr = memory->readWord(pc);
        decode(instr);
        execute();
        pc += 4;
    }

private:
    u32 reg_file[32] = {0};
    u32 pc = 0;
    u32 hi = 0;
    u32 lo = 0;

    Instruction current_instr = {0};

    Memory* memory;

    u32 readWordRegister(u8 idx) const {
        if (idx == 0) return 0;
        if(idx > R_RA) throw std::runtime_error("Register index out of bounds");
        return reg_file[idx];
    }

    u16 readHalfHighRegister(u8 idx) const {
        if (idx == 0) return 0;
        if(idx > R_RA) throw std::runtime_error("Register index out of bounds");
        return reg_file[idx] >> 16;
    }

    u16 readHalfLowRegister(u8 idx) const {
        if (idx == 0) return 0;
        if(idx > R_RA) throw std::runtime_error("Register index out of bounds");
        return reg_file[idx] & 0x0000FFFF;
    }

    void writeWordRegister(u8 idx, u32 value) {
        if (idx == 0) return;
        if(idx > R_RA) throw std::runtime_error("Register index out of bounds");
        reg_file[idx] = value;
    }

    void writeHalfHighRegister(u8 idx, u16 value) {
        if (idx == 0) return;
        if(idx > R_RA) throw std::runtime_error("Register index out of bounds");
        reg_file[idx] |= value << 16;
    }

    void writeHalfLowRegister(u8 idx, u16 value) {
        if (idx == 0) return;
        if(idx > R_RA) throw std::runtime_error("Register index out of bounds");
        reg_file[idx] |= value;
    }

    static u32 signExtend16(u16 imm) {
        return static_cast<u32>(static_cast<int16_t>(imm));
    }

    static u32 zeroExtend16(u16 imm) {
        return imm;
    }

    void branchIf(bool condition, s16 offset) {
        if (condition) {
            // Offset is shifted left by 2 (word-aligned)
            pc += static_cast<s32>(offset) << 2;
        }
    }

    u32 rs() const { return readWordRegister(current_instr.rs); }
    u32 rt() const { return readWordRegister(current_instr.rt); }
    u32 rd() const { return current_instr.rd; }

    void trap(const std::string& msg) {
        throw std::runtime_error("CPU Trap: " + msg);
    }



    using InstrHandler = void(*)(CPU&);

    static void _none(CPU& cpu); // should happen -> exit and error

    // Arithmetic
    static void _add(CPU& cpu);
    static void _addu(CPU& cpu);
    static void _addi(CPU& cpu);
    static void _addiu(CPU& cpu);
    static void _and(CPU& cpu);
    static void _andi(CPU& cpu);
    static void _div(CPU& cpu);
    static void _divu(CPU& cpu);
    static void _mult(CPU& cpu);
    static void _multu(CPU& cpu);
    static void _nor(CPU& cpu);
    static void _or(CPU& cpu);
    static void _ori(CPU& cpu);
    static void _ssl(CPU& cpu);
    static void _sllv(CPU& cpu);
    static void _sra(CPU& cpu);
    static void _srav(CPU& cpu);
    static void _srl(CPU& cpu);
    static void _srlv(CPU& cpu);
    static void _sub(CPU& cpu);
    static void _subu(CPU& cpu);
    static void _xor(CPU& cpu);
    static void _xori(CPU& cpu);

    // Constant-Manipulating
    static void _lhi(CPU& cpu);
    static void _llo(CPU& cpu);

    // Comparison
    static void _slt(CPU& cpu);
    static void _sltu(CPU& cpu);
    static void _slti(CPU& cpu);
    static void _sltiu(CPU& cpu);

    // Branch
    static void _beq(CPU& cpu);
    static void _bgtz(CPU& cpu);
    static void _blez(CPU& cpu);
    static void _bne(CPU& cpu);

    // Jump
    static void _jmp(CPU& cpu);
    static void _jal(CPU& cpu);
    static void _jalr(CPU& cpu);
    static void _jr(CPU& cpu);

    // Load
    static void _lb(CPU& cpu);
    static void _lbu(CPU& cpu);
    static void _lh(CPU& cpu);
    static void _lhu(CPU& cpu);
    static void _lw(CPU& cpu);

    // Store
    static void _sb(CPU& cpu);
    static void _sh(CPU& cpu);
    static void _sw(CPU& cpu);

    // Data movement
    static void _mfhi(CPU& cpu);
    static void _mflo(CPU& cpu);
    static void _mthi(CPU& cpu);
    static void _mtlo(CPU& cpu);

    // Exception and interript
    static void _trap(CPU& cpu);

    static void print_int(CPU &cpu);
    static void print_float(CPU &cpu);
    static void print_double(CPU &cpu);
    static void print_string(CPU &cpu);
    static void read_int(CPU &cpu);
    static void read_float(CPU &cpu);
    static void read_double(CPU &cpu);
    static void read_string(CPU &cpu);
    static void sbrk(CPU &cpu);
    static void print_byte(CPU &cpu);
    static void read_byte(CPU &cpu);

    static inline InstrHandler instr_table[] = {
        _none, _none,  _jmp,  _jal,   _beq,  _bne,  _blez, _bgtz,
        _addi, _addiu, _slti, _sltiu, _andi, _ori,  _xori, _none,
        _none, _none,  _none, _none,  _none, _none, _none, _none,
        _llo,  _lhi,   _trap, _none,  _none, _none, _none, _none,
        _lb,   _lh,    _none, _lw,    _lbu,  _lhu,  _none, _none,
        _sb,   _sh,    _none, _sw,    _none, _none, _none, _none,
        _none, _none,  _none, _none,  _none, _none, _none, _none,
        _none, _none,  _none, _none,  _none, _none, _none, _none,
    };

    static inline InstrHandler reg_table[] = {
        _ssl,  _none,  _srl,  _sra,  _sllv, _none, _srlv, _srav,
        _jr,   _jalr,  _none, _none, _trap, _none, _none, _none,
        _mfhi, _mthi,  _mflo, _mtlo, _none, _none, _none, _none,
        _mult, _multu, _div,  _divu, _none, _none, _none, _none,
        _add,  _addu,  _sub,  _subu, _and,  _or,   _xor,  _nor,
        _none, _none,  _slt,  _sltu, _none, _none, _none, _none,
        _none, _none,  _none, _none, _none, _none, _none, _none,
        _none, _none,  _none, _none, _none, _none, _none, _none,
    };

    void execute() {
        std::cout << "Executing opcode: 0x" << std::hex << static_cast<int>(current_instr.opcode) << ": ";


        u8 opcode = current_instr.opcode;
        if (opcode >= 64) {
            throw std::runtime_error("Invalid opcode");
        }

        if(opcode == 0x0) {
            if (current_instr.funct >= 64) {
                throw std::runtime_error("Invalid funct");
            }
            reg_table[current_instr.funct](*this);
        }else {
            instr_table[opcode](*this); // calling the function with this
        }


    }







};

#endif //CPU_HPP
