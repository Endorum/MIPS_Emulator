| Opcode            | Name                            | Action                            | Opcode Bitfields  |  
|-------------------|---------------------------------|-----------------------------------|-------------------|
| ADD rd,rs,rt      | Add                             | rd=rs+rt                          | 000000            | rs | rt | rd | 00000 | 100000 |
| ADDI rt,rs,imm    | Add Immediate                   | rt=rs+imm                         | 001000            | rs | rt | imm |
| ADDIU rt,rs,imm   | Add Immediate Unsigned          | rt=rs+imm                         | 001001            | rs | rt | imm |
| ADDU rd,rs,rt     | Add Unsigned                    | rd=rs+rt                          | 000000            | rs | rt | rd | 00000 | 100001 |
| AND rd,rs,rt      | And                             | rd=rs&amp;rt                      | 000000            | rs | rt | rd | 00000 | 100100 |
| ANDI rt,rs,imm    | And Immediate                   | rt=rs&amp;imm                     | 001100            | rs | rt | imm |
| LUI rt,imm        | Load Upper Immediate            | rt=imm&lt;&lt;16                  | 001111            | rs | rt | imm |
| NOR rd,rs,rt      | Nor                             | rd=~(rs                           | rt)               | 000000                  | rs | rt | rd | 00000 | 100111 |
| OR rd,rs,rt       | Or                              | rd=rs                             | rt                |  000000 | rs | rt | rd | 00000 | 100101 |
| ORI rt,rs,imm     | Or Immediate                    | rt=rs                             | imm               |  001101 | rs | rt | imm |
| SLT rd,rs,rt      | Set On Less Than                | rd=rs&lt;rt                       | 000000            | rs | rt | rd | 00000 | 101010 |
| SLTI rt,rs,imm    | Set On Less Than Immediate      | rt=rs&lt;imm                      | 001010            | rs | rt | imm |
| SLTIU rt,rs,imm   | Set On &lt; Immediate Unsigned  | rt=rs&lt;imm                      | 001011            | rs | rt | imm |
| SLTU rd,rs,rt     | Set On Less Than Unsigned       | rd=rs&lt;rt                       | 000000            | rs | rt | rd | 00000 | 101011 |
| SUB rd,rs,rt      | Subtract                        | rd=rs-rt                          | 000000            | rs | rt | rd | 00000 | 100010 |
| SUBU rd,rs,rt     | Subtract Unsigned               | rd=rs-rt                          | 000000            | rs | rt | rd | 00000 | 100011 |
| XOR rd,rs,rt      | Exclusive Or                    | rd=rs^rt                          | 000000            | rs | rt | rd | 00000 | 100110 |
| XORI rt,rs,imm    | Exclusive Or Immediate          | rt=rs^imm                         | 001110            | rs | rt | imm |
| SLL rd,rt,sa      | Shift Left Logical              | rd=rt&lt;&lt;sa                   | 000000            | rs | rt | rd | sa | 000000 |
| SLLV rd,rt,rs     | Shift Left Logical Variable     | rd=rt&lt;&lt;rs                   | 000000            | rs | rt | rd | 00000 | 000100 |
| SRA rd,rt,sa      | Shift Right Arithmetic          | rd=rt&gt;&gt;sa                   | 000000            | 00000 | rt | rd | sa | 000011 |
| SRAV rd,rt,rs     | Shift Right Arithmetic Variable | rd=rt&gt;&gt;rs                   | 000000            | rs | rt | rd | 00000 | 000111 |
| SRL rd,rt,sa      | Shift Right Logical             | rd=rt&gt;&gt;sa                   | 000000            | rs | rt | rd | sa | 000010 |
| SRLV rd,rt,rs     | Shift Right Logical Variable    | rd=rt&gt;&gt;rs                   | 000000            | rs | rt | rd | 00000 | 000110 |
| DIV rs,rt         | Divide                          | HI=rs%rt; LO=rs/rt                | 000000            | rs | rt |<td colspan="2">0000000000 | 011010 |
| DIVU rs,rt        | Divide Unsigned                 | HI=rs%rt; LO=rs/rt                | 000000            | rs | rt |<td colspan="2">0000000000 | 011011 |
| MFHI rd           | Move From HI                    | rd=HI                             | 000000            |<td colspan="2">0000000000 | rd | 00000 | 010000 |
| MFLO rd           | Move From LO                    | rd=LO                             | 000000            |<td colspan="2">0000000000 | rd | 00000 | 010010 |
| MTHI rs           | Move To HI                      | HI=rs                             | 000000            | rs | 000000000000000 | 010001 |
| MTLO rs           | Move To LO                      | LO=rs                             | 000000            | rs | 000000000000000 | 010011 |
| MULT rs,rt        | Multiply                        | HI,LO=rs*rt                       | 000000            | rs | rt |<td colspan="2">0000000000 | 011000 |
| MULTU rs,rt       | Multiply Unsigned               | HI,LO=rs*rt                       | 000000            | rs | rt |<td colspan="2">0000000000 | 011001 |
| BEQ rs,rt,offset  | Branch On Equal                 | if(rs==rt) pc+=offset*4           | 000100            | rs | rt | offset |
| BGEZ rs,offset    | Branch On &gt;= 0               | if(rs&gt;=0) pc+=offset*4         | 000001            | rs | 00001 | offset |
| BGEZAL rs,offset  | Branch On &gt;= 0 And Link      | r31=pc; if(rs&gt;=0) pc+=offset*4 | 000001            | rs | 10001 | offset |
| BGTZ rs,offset    | Branch On &gt; 0                | if(rs&gt;0) pc+=offset*4          | 000111            | rs | 00000 | offset |
| BLEZ rs,offset    | Branch On                       | if(rs&lt;=0) pc+=offset*4         | 000110            | rs | 00000 | offset |
| BLTZ rs,offset    | Branch On &lt; 0                | if(rs&lt;0) pc+=offset*4          | 000001            | rs | 00000 | offset |
| BLTZAL rs,offset  | Branch On &lt; 0 And Link       | r31=pc; if(rs&lt;0) pc+=offset*4  | 000001            | rs | 10000 | offset |
| BNE rs,rt,offset  | Branch On Not Equal             | if(rs!=rt) pc+=offset*4           | 000101            | rs | rt | offset |
| BREAK             | Breakpoint                      | epc=pc; pc=0x3c                   | 000000            |<td colspan="4">code | 001101 |
| J target          | Jump                            | pc=pc_upper                       | (target&lt;&lt;2) |  000010 |<td colspan="5">target |
| JAL target        | Jump And Link                   | r31=pc; pc=target&lt;&lt;2        | 000011            |<td colspan="5">target |
| JALR rs           | Jump And Link Register          | rd=pc; pc=rs                      | 000000            | rs | 00000 | rd | 00000 | 001001 |
| JR rs             | Jump Register                   | pc=rs                             | 000000            | rs | 000000000000000 | 001000 |
| MFC0 rt,rd        | Move From Coprocessor           | rt=CPR[0,rd]                      | 010000            | 00000 | rt | rd |<td colspan="2">00000000000 |
| MTC0 rt,rd        | Move To Coprocessor             | CPR[0,rd]=rt                      | 010000            | 00100 | rt | rd |<td colspan="2">00000000000 |
| SYSCALL           | System Call                     | epc=pc; pc=0x3c                   | 000000            |<td colspan="4">00000000000000000000 | 001100 |
| LB rt,offset(rs)  | Load Byte                       | rt=*(char*)(offset+rs)            | 100000            | rs | rt | offset |
| LBU rt,offset(rs) | Load Byte Unsigned              | rt=*(Uchar*)(offset+rs)           | 100100            | rs | rt | offset |
| LH rt,offset(rs)  | Load Halfword                   | rt=*(short*)(offset+rs)           | 100001            | rs | rt | offset |
| LBU rt,offset(rs) | Load Halfword Unsigned          | rt=*(Ushort*)(offset+rs)          | 100101            | rs | rt | offset |
| LW rt,offset(rs)  | Load Word                       | rt=*(int*)(offset+rs)             | 100011            | rs | rt | offset |
| SB rt,offset(rs)  | Store Byte                      | *(char*)(offset+rs)=rt            | 101000            | rs | rt | offset |
| SH rt,offset(rs)  | Store Halfword                  | *(short*)(offset+rs)=rt           | 101001            | rs | rt | offset |
| SW rt,offset(rs)  | Store Word                      | *(int*)(offset+rs)=rt             | 101011            | rs | rt | offset |



First, Second ->
|
v
(opcode field)

|     | 000  | 001   | 010  | 011   | 100  | 101 | 110  | 111  |
|-----|------|-------|------|-------|------|-----|------|------|
| 000 | REG  |       | J    | JAL   | BEQ  | BNE | BLEZ | BGTZ |
| 001 | ADDI | ADDIU | SLTI | SLTIU | ANDI | ORI | XORI |      |
| 010 |      |       |      |       |      |     |      |      |
| 011 | LLO  | LHI   | TRAP |       |      |     |      |      |
| 100 | LB   | LH    |      | LW    | LBU  | LHU |      |      |
| 101 | SB   | SH    |      | SW    |      |     |      |      |
| 110 |      |       |      |       |      |     |      |      |
| 111 |      |       |      |       |      |     |      |      |

REG: (function code field)

|     | 000  | 001   | 010  | 011  | 100  | 101 | 110  | 111  |
|-----|------|-------|------|------|------|-----|------|------|
| 000 | SSL  |       | SRL  | SRA  | SLLV |     | SRLV | SRAV |
| 001 | JR   | JALR  |      |      |      |     |      |      |
| 010 | MFHI | MTHI  | MFLO | MTLO |      |     |      |      |
| 011 | MULT | MULTU | DIV  | DIVU |      |     |      |      |
| 100 | ADD  | ADDU  | SUB  | SUBU | AND  | OR  | XOR  | NOR  |
| 101 |      |       | SLT  | SLTU |      |     |      |      |
| 110 |      |       |      |      |      |     |      |      |
| 111 |      |       |      |      |      |     |      |      |

https://student.cs.uwaterloo.ca/~isg/res/mips/opcodes