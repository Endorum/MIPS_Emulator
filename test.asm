    .data
    input:  .word 10       # Store integer 10 in memory at label "input"
    output: .word 0        # Store result at label "output"

    .text
    .globl main
main:
    # Load integer from memory (input)
    lw   $t0, input        # Load word from address "input" into $t0

    # Add 5 to the value in $t0
    addi $t0, $t0, 5       # $t0 = $t0 + 5

    # Store the result into the "output" memory location
    sw   $t0, output       # Store word in $t0 into "output"

    # Exit the program (using a syscall to terminate)
    li   $v0, 10           # Syscall for exit
    syscall
