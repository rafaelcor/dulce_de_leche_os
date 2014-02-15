.code16
.text
.org 0x00

.global _start
_start:
 mov $0x00, %ax
 mov %ax, %ds
 mov $bootmesg, %si
 call message

ReadFloppy:
 mov $disk, %si
 call message

 mov $0x80, %dl # Drive 0x80 = hard disk 1
 mov $0x00, %dh # Head (0=base)
 mov $0x00, %ch # Track/cylinder
 mov $0x02, %cl # Sector (1=bootloader, apparently sectors starts counting at 1 instead of 0)
 mov $0x7E0, %bx # Place in RAM for kernel - I suppose randomly chosen on examples
 mov %bx, %es # Place BX in pointer ES
 mov $0x00, %bx # Back to zero - also has something to do with RAM position
 mov $0x02, %ah
 mov $0x40, %al
 int $0x13

 jc ReadFloppy # If it went wrong, try again

 mov $tokernel, %si
 call message

 jmp $0x7E0, $0x0

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

bootmesg: .ascii "Dulce de Leche esta iniciando...\n\r\0"
disk: .ascii "Cargando el kernel...\n\r\0"
tokernel: .ascii "Pasando el control al Kernel...\n\r\0"

.org 510
.word 0xAA55
