#include "types.h"
#include "console.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "pmm.h"

int kern_entry(){
    init_debug();
    init_gdt();
    init_idt();

    console_clear();
	//console_write_color("Hello, OS kernel!\n", rc_black, rc_green);
    //panic("test");
    

    
    printk_color(rc_black, rc_green, "Hello OS!!!\n");
    
    init_timer(200);
    
    // `sti` 指令的作用是设置中断标志（Set Interrupt Flag）
    // asm volatile("sti");
    
    // 显示物理内存布局
    printk("kernel in memory start: 0x%08X\n", kern_start);
    printk("kernel in memory end: 0x%08X\n", kern_end);
    printk("kernel in memory used: %d KB\n\n", (kern_end - kern_start + 1023) / 1024); // 换算成kb

    show_memory_map();
    return 0;
}