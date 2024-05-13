#ifndef INCLUDE_PMM_H
#define INCLUDE_PMM_H

#include "multiboot.h"

// 内核文件在内存中的起始和结束位置
// 在连接器脚本中定义了

extern uint8_t kern_start[];
extern uint8_t kern_end[];

// 输出bios提供的物理内存布局
void show_memory_map();

#endif // INCLUDE