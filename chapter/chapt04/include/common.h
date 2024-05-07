#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_
#include "typers.h"

//端口写一个字节
void outb(uint16_t port, uint8_t value);

// 读一个字节
uint8_t inb(uint16_t port);

// 读一个字
uint16_t inw(uint16_t port); 

#endif // include