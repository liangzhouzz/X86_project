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
    // 初始化物理内存管理
    init_pmm();

    printk_color(rc_black, rc_red, "\nThe Count of Physical Memory Page is: %u\n\n", phy_page_count); // 栈中分配的物理也的大小
    uint32_t allc_addr = NULL;
    printk_color(rc_black, rc_light_brown , "Test Physical Memory Alloc :\n");
    
    allc_addr = pmm_alloc_page(); // 分配一个页 物理内存
    printk_color(rc_black, rc_light_brown , "Alloc Physical Addr: 0x%08X\n",allc_addr);
    allc_addr = pmm_alloc_page();
    printk_color(rc_black, rc_light_brown , "Alloc Physical Addr: 0x%08X\n",allc_addr);
    allc_addr = pmm_alloc_page();
    printk_color(rc_black, rc_light_brown , "Alloc Physical Addr: 0x%08X\n",allc_addr);
    allc_addr = pmm_alloc_page();
    printk_color(rc_black, rc_light_brown , "Alloc Physical Addr: 0x%08X\n",allc_addr);



    return 0;
}