#define PIT_CHANNEL0      0x40  //PIT Channel 0's Data Register Port
#define PIT_CHANNEL1      0x41  //PIT Channels 1's Data Register Port, we wont be using this here
#define PIT_CHANNEL2     0x42  //PIT Channels 2's Data Register Port
#define PIT_CMDREG        0x43  //PIT Chip's Command Register Port
/*void generate_tone(){		
	monitor_write("hello\n");	
	asm volatile("pusha");
	monitor_write("hello1\n");	
	asm volatile("movw %ax, %cx");
	monitor_write("hello2\n");	
	asm volatile("movb $182, %al");
	monitor_write("hello3\n");	
	asm volatile("outb %al, $0x43");
	monitor_write("hello4\n");	
	asm volatile("movw %cx, %ax");	
	monitor_write("hello5\n");	
	asm volatile("outb %al, $0x42");
	monitor_write("hello6\n");	
	asm volatile("movb %ah, %al");
	monitor_write("hello7\n");	
	asm volatile("outb %al, $0x42");
	monitor_write("hello8\n");	
	asm volatile("inb $0x61, %al");			
	monitor_write("hello9\n");	
	asm volatile("orb $0x03, %al");
	monitor_write("hello10\n");	
	asm volatile("outb %al, $0x61");
	monitor_write("hello11\n");	
	asm volatile("popa");
	monitor_write("hello12\n");	
	asm volatile("ret");
	monitor_write("hello13\n");	
	
}*/

void speaker_set(int hz)
{
    int divisor = 1193180 / hz;
    outb(PIT_CMDREG, 0xB6);
    outb(PIT_CHANNEL2, (unsigned char) (divisor) );
    outb(PIT_CHANNEL2, (unsigned char) (divisor >> 8));	
}
void beep(unsigned int wait_time,unsigned int times ) 
{
     unsigned char tempA =inb(0x61);
     unsigned char tempB = (inb(0x61) & 0xFC);
     unsigned int count;

    for(count = 0; count < times; count++) 
    {
         if(tempA != (tempA | 3)) 
         {
              outb(0x61, tempA | 3);
         }
        timer_wait(wait_time);
        outb(0x61, tempB);        timer_wait(1);
   }
}
