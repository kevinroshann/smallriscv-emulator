.section .text
.globl _start

_start:
    # Load the address of the UART output register
    li a0, 0x10000000  # UART base address
    la a1, message     # Load address of the string

print_loop:
    lbu a2, (a1)       # Load byte from message
    beqz a2, done      # If null terminator, stop
    sb a2, (a0)        # Store byte to UART
    addi a1, a1, 1     # Move to next byte
    j print_loop

done:
    j done             # Infinite loop (halt)

.section .data
message:
    .asciz "Hello, RISC-V!\n"
