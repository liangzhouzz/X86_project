/*
 首先 声明了内核程序的入口 地址是 符号 “start”
 这个用于告诉ld。如何构造内核映像文件
 然后声明了 .text段 ---代码段  以及它的起始地质 0x100000 （1MB）
 接着就是 已初始化段 .data 和 未初始化数据段 .bss   页对其 采用 4096
*/

ENTRY(start)
SECTIONS
{
	. = 0x100000;
	PROVIDE( kern_start = . );
	.text :
	{
		*(.text)
		. = ALIGN(4096);
	}
	.data :
	{
		*(.data)
		*(.rodata)
		. = ALIGN(4096);
	}
	.bss :
	{
		*(.bss)
		. = ALIGN(4096);
	}
	.stab :
	{
		*(.stab)
		. = ALIGN(4096);
	}
	.stabstr :
	{
		*(.stabstr)
	 	. = ALIGN(4096);
	}
	PROVIDE( kern_end = . );
	/DISCARD/ : { *(.comment) *(.eh_frame) }
}
