#ifndef __ASMHEAD_H__
#define __ASMHEAD_H__


struct BOOTINFO {       /* 0x0ff0-0x0fff */
	char cyls;          /* 启动区读磁盘读到此为止 */
	char leds;          /* 启动时键盘的LED的状态 */
	char vmode;         /* 显卡模式为多少位彩色 */
	char reserve;
	short scrnx, scrny; /* 画面分辨率 */
	char *vram;
};
#define ADR_BOOTINFO	0x00000ff0

#endif // __ASMHEAD_H__