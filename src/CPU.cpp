//
// Created by Alexander on 12.05.25.
//

#include "../include/CPU.hpp"

#include <iostream>

void CPU::_none(CPU& cpu){
    printf("none\n");
    cpu.current_instr.print();
    throw std::runtime_error("ERROR: somethings messed up");
}
void CPU::_add(CPU& cpu) {
    printf("add\n");
    auto a = static_cast<int32_t>(cpu.rs());
    auto b = static_cast<int32_t>(cpu.rt());
    int32_t result = a + b;
    if (((a > 0) && (b > 0) && (result < 0)) || ((a < 0) && (b < 0) && (result > 0))) {
        throw std::overflow_error("add overflow");
    }
    cpu.writeWordRegister(cpu.current_instr.rd, result);
}

void CPU::_addu(CPU& cpu){
    printf("addu\n");
    cpu.writeWordRegister(cpu.current_instr.rd, cpu.rs() + cpu.rt());
}
void CPU::_addi(CPU& cpu) {
    printf("addi\n");
    auto a = static_cast<int32_t>(cpu.rs());
    int32_t b = static_cast<int16_t>(cpu.current_instr.imm); // Sign-extend!
    int32_t result = a + b;
    if (((a > 0) && (b > 0) && (result < 0)) || ((a < 0) && (b < 0) && (result > 0))) {
        throw std::overflow_error("addi overflow");
    }
    cpu.writeWordRegister(cpu.current_instr.rt, result); // RT is destination for ADDI
}

void CPU::_addiu(CPU& cpu) {
    printf("addiu\n");
    int32_t imm = static_cast<int16_t>(cpu.current_instr.imm); // sign-extend
    cpu.writeWordRegister(cpu.current_instr.rt, cpu.rs() + imm); // rt is destination
}

void CPU::_and(CPU& cpu){
    printf("and\n");
    cpu.writeWordRegister(cpu.current_instr.rd, cpu.rs() & cpu.rt());
}
void CPU::_andi(CPU& cpu){
    printf("andi\n");
    cpu.writeWordRegister(cpu.current_instr.rt, cpu.rs() & cpu.current_instr.imm);
}
void CPU::_div(CPU& cpu){
    printf("div\n");
    cpu.hi = static_cast<int32_t>(cpu.rs()) % static_cast<int32_t>(cpu.rt());
    cpu.lo = static_cast<int32_t>(cpu.rs()) / static_cast<int32_t>(cpu.rt());
}
void CPU::_divu(CPU& cpu){
    printf("divu\n");
    cpu.hi = cpu.readWordRegister(cpu.rs()) % cpu.rt();
    cpu.lo = cpu.readWordRegister(cpu.rs()) / cpu.rt();

}
void CPU::_mult(CPU& cpu){
    printf("mult\n");

    uint64_t result = static_cast<int64_t>(cpu.rs()) * static_cast<int64_t>(cpu.rt());

    cpu.lo = static_cast<uint32_t>(result & 0xFFFFFFFF);       // lower 32 bits
    cpu.hi = static_cast<uint32_t>((result >> 32) & 0xFFFFFFFF); // upper 32 bits
}
void CPU::_multu(CPU& cpu){
    printf("multu\n");

    uint64_t result = static_cast<uint64_t>(cpu.rs()) * static_cast<uint64_t>(cpu.rt());

    cpu.lo = static_cast<uint32_t>(result & 0xFFFFFFFF);       // lower 32 bits
    cpu.hi = static_cast<uint32_t>((result >> 32) & 0xFFFFFFFF); // upper 32 bits

}
void CPU::_nor(CPU& cpu){
    printf("nor\n");
    cpu.writeWordRegister(cpu.current_instr.rd, ~(cpu.rs() | cpu.rt()));
}
void CPU::_or(CPU& cpu){
    printf("or\n");
    cpu.writeWordRegister(cpu.current_instr.rd, cpu.rs() | cpu.rt());
}
void CPU::_ori(CPU& cpu){
    printf("ori\n");
    cpu.writeWordRegister(cpu.current_instr.rt, cpu.rs() | cpu.current_instr.imm);
}
void CPU::_ssl(CPU& cpu) {
    printf("ssl\n");
    // SLL: Logical shift left (rd = rt << shamt)
    cpu.writeWordRegister(cpu.current_instr.rd, cpu.readWordRegister(cpu.current_instr.rt) << cpu.current_instr.shamt);
}

void CPU::_sllv(CPU& cpu) {
    printf("sllv\n");
    // SLLV: Logical shift left variable (rd = rt << rs)
    u8 shift = cpu.rs() & 0x1F;
    cpu.writeWordRegister(cpu.current_instr.rd, cpu.rt() << shift);
}

void CPU::_sra(CPU& cpu) {
    printf("sra\n");
    // SRA: Arithmetic shift right (preserves sign bit)
    auto val = static_cast<int32_t>(cpu.rt());
    cpu.writeWordRegister(cpu.current_instr.rd, val >> cpu.current_instr.shamt);
}

void CPU::_srav(CPU& cpu) {
    printf("srav\n");
    // SRAV: Arithmetic shift right variable
    u8 shift = cpu.rs() & 0x1F;
    auto val = static_cast<int32_t>(cpu.rt());
    cpu.writeWordRegister(cpu.current_instr.rd, val >> shift);
}

void CPU::_srl(CPU& cpu) {
    printf("srl\n");
    // SRL: Logical shift right (fills with zeros)
    u32 val = cpu.rt();
    cpu.writeWordRegister(cpu.current_instr.rd, val >> cpu.current_instr.shamt);
}

void CPU::_srlv(CPU& cpu) {
    printf("srlv\n");
    // SRLV: Logical shift right variable
    u8 shift = cpu.rs() & 0x1F;
    u32 val = cpu.rt();
    cpu.writeWordRegister(cpu.current_instr.rd, val >> shift);
}

void CPU::_sub(CPU& cpu){
    printf("sub\n");
    auto a = static_cast<int32_t>(cpu.rs());
    auto b = static_cast<int32_t>(cpu.rt());
    int32_t result = a - b;
    if (((a < 0) && (b > 0) && (result > 0)) || ((a > 0) && (b < 0) && (result < 0))) {
        throw std::overflow_error("sub overflow");
    }
    cpu.writeWordRegister(cpu.current_instr.rd, result);
}
void CPU::_subu(CPU& cpu){
    printf("subu\n");
    cpu.writeWordRegister(cpu.current_instr.rd, cpu.rs() - cpu.rt());
}
void CPU::_xor(CPU& cpu){
    printf("xor\n");
    cpu.writeWordRegister(cpu.current_instr.rd, cpu.rs() ^ cpu.rt());
}
void CPU::_xori(CPU& cpu){
    printf("xori\n");
    cpu.writeWordRegister(cpu.current_instr.rt, cpu.rs() ^ cpu.current_instr.imm);
}
void CPU::_lhi(CPU& cpu){
    printf("lhi\n");
    cpu.hi = cpu.current_instr.imm;
}
void CPU::_llo(CPU& cpu){
    printf("llo\n");
    cpu.lo = cpu.current_instr.imm;
}
void CPU::_slt(CPU& cpu) {
    printf("slt\n");
    cpu.writeWordRegister(cpu.current_instr.rd,
        static_cast<int32_t>(cpu.rs()) < static_cast<int32_t>(cpu.rt()) ? 1 : 0);
}

void CPU::_sltu(CPU& cpu) {
    printf("sltu\n");
    cpu.writeWordRegister(cpu.current_instr.rd,
        cpu.rs() < cpu.rt() ? 1 : 0);
}

void CPU::_slti(CPU& cpu) {
    printf("slti\n");
    cpu.writeWordRegister(cpu.current_instr.rt,
        static_cast<int32_t>(cpu.rs()) < static_cast<int32_t>(cpu.current_instr.imm) ? 1 : 0);
}

void CPU::_sltiu(CPU& cpu) {
    printf("sltiu\n");
    cpu.writeWordRegister(cpu.current_instr.rt,
        cpu.rs() < cpu.current_instr.imm ? 1 : 0);
}

void CPU::_beq(CPU& cpu) {
    printf("beq\n");
    cpu.branchIf(cpu.rs() == cpu.rt(), cpu.current_instr.imm);
}

void CPU::_bgtz(CPU& cpu){
    printf("bgtz\n");
    cpu.branchIf(static_cast<int32_t>(cpu.rs()) > 0, cpu.current_instr.imm);
}
void CPU::_blez(CPU& cpu){
    printf("blez\n");
    cpu.branchIf(static_cast<int32_t>(cpu.rs()) <= 0, cpu.current_instr.imm);
}
void CPU::_bne(CPU& cpu){
    printf("bne\n");
    cpu.branchIf(cpu.rs() != cpu.rt(), cpu.current_instr.imm);
}
void CPU::_jmp(CPU& cpu) {
    printf("jmp\n");
    // Form the target address
    u32 target = (cpu.pc & 0xF0000000) | (cpu.current_instr.addr << 2);
    cpu.pc = target;
}

void CPU::_jal(CPU& cpu) {
    printf("jal\n");
    // Store the return address (current PC + 4) into R_RA
    cpu.writeWordRegister(R_RA, cpu.pc + 4);

    // Form the target address for the jump
    u32 target = (cpu.pc & 0xF0000000) | (cpu.current_instr.addr << 2);
    cpu.pc = target;
}

void CPU::_jalr(CPU& cpu){
    printf("jalr\n");
    cpu.writeWordRegister(R_RA, cpu.pc + 4);

    u32 target = cpu.rs() << 2;
    cpu.pc = target;
}
void CPU::_jr(CPU& cpu){
    printf("jr\n");

    u32 target = cpu.rs() << 2;
    cpu.pc = target;
}
void CPU::_lb(CPU& cpu) {
    printf("lb\n");

    // Calculate the memory address where the byte will be read from
    u32 address = cpu.rs() + static_cast<s16>(cpu.current_instr.imm); // rs + sign-extended imm

    // Read the byte from memory
    u8 byte = cpu.memory->readByte(address);

    // Sign-extend the byte to a 32-bit value
    s32 sign_extended_value = static_cast<s8>(byte); // Load as signed byte and sign-extend

    // Write the result into the target register (rt)
    cpu.writeWordRegister(cpu.current_instr.rt, sign_extended_value);
}

void CPU::_lbu(CPU& cpu) {
    printf("lbu\n");

    // Calculate the memory address where the byte will be read from
    u32 address = cpu.rs() + static_cast<s16>(cpu.current_instr.imm); // rs + sign-extended imm

    // Read the byte from memory
    u8 byte = cpu.memory->readByte(address);

    // Zero-extend the byte to a 32-bit value (unsigned extension)
    u32 zero_extended_value = static_cast<u32>(byte); // Zero-extend the byte to 32 bits

    // Write the result into the target register (rt)
    cpu.writeWordRegister(cpu.current_instr.rt, zero_extended_value);
}

void CPU::_lh(CPU& cpu){
    printf("lh\n");

    // Calculate the memory address where the byte will be read from
    u32 address = cpu.rs() + static_cast<s16>(cpu.current_instr.imm); // rs + sign-extended imm

    // Read the byte from memory
    u16 halfword = cpu.memory->readHalf(address);

    // Sign-extend the half word to a 32-bit value
    s32 sign_extended_value = static_cast<s16>(halfword); // Load as signed byte and sign-extend

    // Write the result into the target register (rt)
    cpu.writeWordRegister(cpu.current_instr.rt, sign_extended_value);
}
void CPU::_lhu(CPU& cpu){
    printf("lhu\n");

    // Calculate the memory address where the byte will be read from
    u32 address = cpu.rs() + static_cast<s16>(cpu.current_instr.imm); // rs + sign-extended imm

    u16 halfword = cpu.memory->readHalf(address);

    // Write the result into the target register (rt)
    cpu.writeWordRegister(cpu.current_instr.rt, halfword);
}
void CPU::_lw(CPU& cpu){
    printf("lw\n");

    // Calculate the memory address where the word will be read from
    u32 address = cpu.rs() + static_cast<s16>(cpu.current_instr.imm); // rs + sign-extended imm

    // Read the word from memory (this will read 4 bytes, i.e., a 32-bit word)
    u32 word = cpu.memory->readWord(address);

    // Write the result into the target register (rt)
    cpu.writeWordRegister(cpu.current_instr.rt, word);
}

void CPU::_sb(CPU& cpu){
    printf("sb\n");

    u32 address = cpu.rs() + static_cast<s16>(cpu.current_instr.imm);

    u8 byte = static_cast<u8>(cpu.rt() & 0x000000FF);
    cpu.memory->writeByte(address, byte);
}
void CPU::_sh(CPU& cpu){
    printf("sh\n");

    u32 address = cpu.rs() + static_cast<s16>(cpu.current_instr.imm);

    u16 halfWord = static_cast<u16>(cpu.rt() & 0x0000FFFF);
    cpu.memory->writeHalf(address, halfWord);
}
void CPU::_sw(CPU& cpu){
    printf("sw\n");

    u32 address = cpu.rs() + static_cast<s16>(cpu.current_instr.imm);

    u32 word = static_cast<u32>(cpu.rt());
    cpu.memory->writeHalf(address, word);
}
void CPU::_mfhi(CPU& cpu){
    printf("mfhi\n");
    cpu.writeWordRegister(cpu.current_instr.rd, cpu.hi);
}
void CPU::_mflo(CPU& cpu){
    printf("mflo\n");
    cpu.writeWordRegister(cpu.current_instr.rd, cpu.lo);
}
void CPU::_mthi(CPU& cpu){
    printf("mthi\n");
    cpu.hi = cpu.rs();
}
void CPU::_mtlo(CPU& cpu){
    printf("mtlo\n");
    cpu.lo = cpu.rs();
}


void CPU::_trap(CPU& cpu){
    printf("trap\n");

    u8 trapCode = static_cast<uint8_t>(cpu.readWordRegister(R_V0)); // trap code in v0

    switch (trapCode) {
        default: throw std::runtime_error("ERROR: Unrecognized trap code: " + std::to_string(trapCode));
        case 1: print_int(cpu); break;
        case 2: print_float(cpu); break;
        case 3: print_double(cpu); break;
        case 4: print_string(cpu); break;
        case 5: read_int(cpu); break;
        case 6: print_float(cpu); break;
        case 7: print_double(cpu); break;
        case 8: print_string(cpu); break;
        case 9: sbrk(cpu); break;
        case 10: exit(0);
        case 12: print_int(cpu); break;
        case 101: print_byte(cpu);
        case 102: read_byte(cpu);
    }

}

void CPU::print_int(CPU& cpu) {
    printf("%d\n",cpu.readWordRegister(R_A0));
}

void CPU::print_float(CPU &cpu) {
    printf("%f",static_cast<float>(cpu.readWordRegister(R_A0)));
}

void CPU::print_double(CPU &cpu) {
    uint64_t value = static_cast<uint64_t>(cpu.readWordRegister(R_A0)) << 32 | static_cast<uint64_t>(cpu.readWordRegister(R_A1));
    printf("%f",static_cast<double>(value));
}

void CPU::print_string(CPU &cpu) {
    u32 str_addr = cpu.readWordRegister(R_A0); // address is in virtual memory
    u8 c;
    std::string str;
    do {
        c = cpu.memory->readByte(str_addr++);
        str += c;
    }while(c != '\0');
    printf("%s",str.c_str());
}


void CPU::read_int(CPU &cpu) {
    // Variable to hold the input integer
    int input;

    // Read the integer from the user
    scanf("%d", &input);  // Read a signed decimal integer

    // Store the value in the $2 register (rt) - the second operand register in the instruction
    cpu.writeWordRegister(cpu.current_instr.rt, static_cast<u32>(input));
}

void CPU::read_float(CPU &cpu) {
    float input;

    scanf("%f",&input);

    cpu.writeWordRegister(cpu.current_instr.rt, static_cast<u32>(input));
}

void CPU::read_double(CPU &cpu) {
    double input;

    scanf("%f",&input);

    cpu.writeWordRegister(cpu.current_instr.rs, static_cast<uint64_t>(input) << 32);
    cpu.writeWordRegister(cpu.current_instr.rt, static_cast<u32>(input));
}

void CPU::read_string(CPU &cpu) {
    std::string str;
    scanf("%s", &str);
    u32 str_addr = cpu.rs();

    for(int i=0;i<str.size();i++) {
        cpu.memory->writeByte(str_addr, str.at(i));
    }
    cpu.memory->writeByte(str_addr, '\0');

    cpu.writeWordRegister(cpu.current_instr.rt, str.size());
}

void CPU::sbrk(CPU &cpu) {
    // rs holds the number of bytes to allocate (or deallocate)
    s32 bytes_requested = static_cast<s32>(cpu.readWordRegister(cpu.current_instr.rs));

    // rd will hold the starting address of the allocated memory
    u32 allocated_address = cpu.heap_break; // Current "break" of the heap

    // Allocate or deallocate memory by adjusting the heap_break
    cpu.heap_break += bytes_requested;

    // Store the allocated address in the rd register
    cpu.writeWordRegister(cpu.current_instr.rd, allocated_address);
}


void CPU::print_byte(CPU &cpu) {
    u8 byte = cpu.rs();
    printf("%c",byte);
}

void CPU::read_byte(CPU &cpu) {
    u8 byte;
    scanf("%c",&byte);
    cpu.writeWordRegister(cpu.current_instr.rd, byte);
}

