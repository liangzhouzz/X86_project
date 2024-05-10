#include "types.h"
#include "console.h"
#include "debug.h"
#include "gdt.h"

int kern_entry(){
    init_debug();
    init_gdt();
    
    console_clear();
	//console_write_color("Hello, OS kernel!\n", rc_black, rc_green);
    //panic("test");
    
    printk_color(rc_blue, rc_red, "Hello OS!!!\n");
    return 0;
}