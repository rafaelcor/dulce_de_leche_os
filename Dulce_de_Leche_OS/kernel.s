.code16
.text
.org 0x00

.global _start
_start:
 jmp init

gdtr:
 .word gdt_end-gdt-1 # Length of the gdt
 .int gdt # physical address of gdt
gdt:
.equ nullsel, .-gdt # .->current location,so nullsel = 0h
gdt0: # Null descriptor,as per convention gdt0 is 0
 .int 0 # Each gdt entry is 8 bytes, so at 08h it is CS
 .int 0 # In all the segment descriptor is 64 bits

.equ codesel, .-gdt # This is 8h,ie 2nd descriptor in gdt
code_gdt: # Code descriptor 4Gb flat segment at 0000:0000h
 .word 0xFFFF # Limit 4Gb bits 0-15 of segment descriptor
 .word 0x0000 # Base 0h bits 16-31 of segment descriptor (sd)
 .byte 0x00 # Base addr of seg 16-23 of 32bit a.intr,32-39 of sd 
 .byte 0x9A 
 .byte 0xCF
 .byte 0x00 # Base addr of seg 24-31 of 32bit addr,56-63 of sd

.equ datasel, .-gdt # ie 10h, beginning of next 8 bytes for data sd
data_gdt: # Data descriptor 4Gb flat seg at 0000:0000h
 .word 0xFFFF # Limit 4Gb
 .word 0x0000 # Base 0000:0000h
 .byte 0x00 # Descriptor format same as above
 .byte 0x92
 .byte 0x0cf
 .byte 0x00

.equ videosel, .-gdt # ie 18h,next gdt entry
 .word 3999 # Limit 80*25*2-1
 .word 0x8000 # Base 0xb8000
 .byte 0x0B
 .byte 0x92 # present,ring 0,data,expand-up,writable
 .byte 0x00 # byte granularity 16 bit
 .byte 0x00
gdt_end:

message:
 lodsb
 or %al, %al
 jz done
 mov $0x0E, %ah
 mov $1, %bl
 int $0x10
 jmp message

done:
 ret

topm: .ascii "Pasando al Modo Protegido...\n\r\0"

init:
 call check_a20
 mov %ax, %bx
 mov $topm, %si
 call message
 cli
 lgdt gdtr
 mov %cr0, %eax
 or $0x01, %al
 mov %eax, %cr0
 ljmp $codesel, $go_pm

.code32
go_pm:
 mov $_stack, %esp
 mov $datasel, %ax
 mov %ax, %ds # Initialise ds & es to data segment
 mov %ax, %es
 cmp $0x00, %bx
 je enable_A20
 call main
 jmp .

.code16
 
# Function: check_a20
#
# Purpose: to check the status of the a20 line in a completely self-contained state-preserving way.
# The function can be modified as necessary by removing push's at the beginning and their
# respective pop's at the end if complete self-containment is not required.
#
# Returns: 0 in ax if the a20 line is disabled (memory wraps around)
# 1 in ax if the a20 line is enabled (memory does not wrap around)
 
check_a20:
 pushf
 push %ds
 push %es
 push %di
 push %si
 
 #cli
 
 xor %ax, %ax
 mov %ax, %es
 
 not %ax # ax = 0xFFFF
 mov %ax, %ds
 
 mov $0x0500, %di
 mov $0x0510, %si

 movb %es:(%di), %al
 push %ax

 movb  %es:(%di), %al
 push %ax

 movb $0x00, %es:(%di)
 movb $0xFF, %ds:(%si)

 cmpb $0xFF, %es:(%di)

 pop %ax
 movb %al, %ds:(%si)

 pop %ax
 movb %al, %es:(%di)

 mov $0x00, %ax
 je check_a20__exit

 mov $0x01, %ax
 
check_a20__exit:
 pop %si
 pop %di
 pop %es
 pop %ds
 popf
 
 ret

.code32

enable_A20:
 #cli

 call a20wait
 mov $0xAD, %al
 out %al, $0x64

 call a20wait
 mov $0xD0, %al
 out %al, $0x64

 call a20wait2
 in $0x60, %al
 push %eax

 call a20wait
 mov $0xD1, %al
 out %al, $0x64

 call a20wait
 pop %eax
 or $0x02, %al
 out %al, $0x60

 call a20wait
 mov $0xAE, %al
 out %al, $0x64

 call a20wait
 #sti
 ret

a20wait:
 in $0x64, %al
 test $0x02, %al
 jnz a20wait
 ret

a20wait2:
 in $0x64, %al
 test $0x01, %al
 jz a20wait2
 ret

stack:
 .org .+4096
_stack:
