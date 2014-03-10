void reboot(){
    asm volatile("cli");
	asm volatile("mov $0xFE, %al");
	asm volatile("out %al, $0x64");
	asm volatile("halt:jmp halt");
}

void shutdown(){
	monitor_write("This feature is not avaible yet.");
}
