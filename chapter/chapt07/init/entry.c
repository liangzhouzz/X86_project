#include "types.h"
#include "console.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"

int kern_entry(){
    init_debug();
    init_gdt();
    init_idt();

    console_clear();
	//console_write_color("Hello, OS kernel!\n", rc_black, rc_green);
    //panic("test");
    

    
    printk_color(rc_black, rc_green, "Hello OS!!!\n");
    // 人为触发中断
    asm volatile("int $0x3");
    asm volatile("int $0x4");
    return 0;
}