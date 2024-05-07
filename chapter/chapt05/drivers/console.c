#include "console.h"
#include "common.h"
// VGA 的显示缓冲的起点 0xB8000
static uint16_t *video_memory = (uint16_t *)0xB8000;

// 屏幕光标的坐标   static 限定 作用域
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

// 屏幕输入光标的移动
static void move_cursor() {
    // 屏幕80 字节宽
    uint16_t cursorLocation = cursor_y * 80 + cursor_x;

    outb(0x3D4, 14);                    // VGA 我们要设置光标的高字节
    outb(0x3D5, cursorLocation >> 8);   // 发送高8位
    outb(0x3D4, 15);                    // 低字节
    outb(0x3D5, cursorLocation);        // 发送低8位
}

// 清屏操作  实际上就是利用白底黑字的空格 覆盖
void console_clear() {
    uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
    uint16_t blank = 0x20 | (attribute_byte << 8);

    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i] = blank;
    }

    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

// 屏幕滚动 就是将后24行的数据全部向上挪动一行 最后一行清空
static void scroll() {
    // attrbute_byte 被构造出一个黑底白字的描述格式
    uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
    uint16_t blank = 0x20 | (attribute_byte << 8);   // space 是 0x20

    // cursor_y 到25的时候就该换行；
    if (cursor_y >= 25) {
        // 将所有的行显示数据复制到上一行 ，第一行永远消失
        for (int i = 0 * 80; i < 24 * 80; i++) {
            video_memory[i] = video_memory[i + 80];
        }

        // 最后一行填充数据
        for (int i = 24* 80; i < 25* 80; i++) {
            video_memory[i] = blank;
        }
        // 向上移动一行 所以cursor_y = 24
        cursor_y = 24;

    } 


}

// 显示字符串
// 先实现一个字符
void console_putc_color(char c, real_color_t back, real_color_t fore) {
    uint8_t back_color = (uint8_t)back;
    uint8_t fore_color = (uint8_t)fore;

    uint8_t attribute_byte = (back_color << 4) | (fore_color & 0x0F);
    uint16_t attribute = attribute_byte << 8;

    // 0x08 是退格的ASCII
    // 0x09 是tab
    if (c == 0x08 && cursor_x) {
        cursor_x--; // 退格
    } else if (c == 0x09) {
        cursor_x = (cursor_x + 8) & ~(8 - 1);
    } else if (c == '\r') {
        cursor_x = 0; // 
    } else if (c == '\n') {
        cursor_x = 0;
        cursor_y++; // 换行
    } else if (c >= ' ') {
        video_memory[cursor_y* 80 + cursor_x] = c | attribute;
        cursor_x++;
    }
    // 超过80 换行
    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }

    scroll();

    move_cursor();
}     

// yijuhua
void console_write(char*cstr) {
    while(*cstr) {
        console_putc_color(*cstr++, rc_black, rc_white);
    }
}


// 带颜色
void console_write_color(char *cstr, real_color_t back, real_color_t fore) {
    while(*cstr) {
        console_putc_color(*cstr++, back, fore);
    }
}

// 16 nums
void console_write_hex(uint32_t n, real_color_t back, real_color_t fore) {
    int tmp;
	char noZeroes = 1;

	console_write_color("0x", back, fore); // 先打印出0x

	// 16进制转换
	for (int i = 28; i >= 0; i -= 4) {
		tmp = (n >> i) & 0xF;
		if (tmp == 0 && noZeroes != 0) {
		      continue;
		}
		noZeroes = 0;
		if (tmp >= 0xA) {
		      console_putc_color(tmp-0xA+'a', back, fore);
		} else {
		      console_putc_color(tmp+'0', back, fore);
		}
	}
}

// 10 nums
void console_write_dec(uint32_t n, real_color_t back, real_color_t fore){
    if (n == 0) {
		console_putc_color('0', back, fore);
		return;
	}

	uint32_t acc = n;
	char c[32];
	int i = 0;
	while (acc > 0) {
		c[i] = '0' + acc % 10;
		acc /= 10;
		i++;
	}
	c[i] = 0;

	char c2[32];
	c2[i--] = 0;

	int j = 0;
	while(i >= 0) {
	      c2[i--] = c[j++];
	}

	console_write_color(c2, back, fore);
}