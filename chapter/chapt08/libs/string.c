#include "string.h"
#include "types.h"
//  字节复制
inline void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len){
    // 异常处理
    if (dest == NULL || src == NULL || len ==0) return;

    for(; len != 0; len--) {
        *dest++ = *src++;  // * 和 ++ 优先级相同但是 先根右边结合 d++ 然后再 *d
    }
}
// 复制指定的值
inline void memset(void *dest, uint8_t val, uint32_t len) {
    //if (dest == NULL || len == 0) return;

    uint8_t *dst = (uint8_t *) dest;  // 为什么    
    for (; len != 0; len--) {
        *dst++ = val;
    }
}

// 清零
inline void bzero(void *dest, uint32_t len){
    memset(dest, 0, len);
}

// 比较两个字符串
inline int strcmp(const char *str1, const char *str2){
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

// 将字符串复制到dest
inline char *strcpy(char *dest, const char *src){
    char *tmp = dest;
	// 当src 不为终止符的时候继续
	while (*src) {
	      *dest++ = *src++;
	}

	*dest = '\0'; // 终止符

	return tmp;
}

// 将字符串 src 连接到字符串 dest 的末尾，覆盖 dest 最后的 null 终止符，并在最后添加一个新的 null 终止符。
inline char *strcat(char *dest, const char *src){
    char *cp = dest;
	
	while (*cp) {
	      cp++;
	}

	while ((*cp++ = *src++))
	      ;

	return dest;
}

// 计算字符串长度 
inline int strlen(const char *src){
    const char *eos = src;

    while (*eos++)
	    ;

	return (eos - src - 1);
}