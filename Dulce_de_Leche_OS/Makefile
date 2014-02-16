SOURCES=kernel.o main.o common.o monitor.o idt.o idt_asm.o isr.o irq.o timer.o kb.o string.o
CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS=--oformat binary -melf_i386

all: $(SOURCES) link 
	dd if=/dev/zero of=ddl.img bs=512 count=65
	dd if=boot.bin of=ddl.img bs=512 count=1 conv=notrunc
	dd if=kernel.bin of=ddl.img bs=512 count=64 seek=1 conv=notrunc
	mv *.o *.bin temps


clean:
	rm temps/*

link:
	ld -Ttext 0x7C00 $(LDFLAGS) -o boot.bin boot.o
	ld -Ttext 0x7E00 $(LDFLAGS) -o kernel.bin $(SOURCES)

.s.o:
	as -32 boot.s -o boot.o
	as -32 $< -o $@
