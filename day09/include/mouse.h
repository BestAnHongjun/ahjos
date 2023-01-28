#ifndef __MOUSE_H__
#define __MOUSE_H__


#define KEYCMD_SENDTO_MOUSE		0xd4
#define MOUSECMD_ENABLE			0xf4

struct MOUSE_DEC {
	unsigned char buf[3], phase;
	int x, y, btn;
};

void enable_mouse(void);
int mouse_decode(struct MOUSE_DEC *mdec, unsigned char dat);
void inthandler2c(int *esp);

#endif // __MOUSE_H__
