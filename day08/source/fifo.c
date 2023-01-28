#include "../include/bootpack.h"


void fifo8_init(struct FIFO8 *fifo, int size, unsigned char *buf)
{
    fifo->size = size;
    fifo->buf = buf;
    fifo->free = size;  // 缓冲区的大小
    fifo->flags = 0;
    fifo->next_r = 0;
    fifo->next_w = 0;
    return;
}

int fifo8_put(struct FIFO8 *fifo, unsigned char data)
{
    if (fifo->free == 0)
    {   // 无空余，溢出
        fifo->flags |= FLAGS_OVERRUN;
        return -1;
    }
    fifo->buf[fifo->next_w] = data;
    fifo->next_w++;
    if (fifo->next_w == fifo->size)
    {
        fifo->next_w = 0;
    }
    fifo->free--;
    return 0;
}

int fifo8_get(struct FIFO8 *fifo)
{
    int data;
    if (fifo->free == fifo->size)
    {   // 缓冲区为空
        return -1;
    }
    data = fifo->buf[fifo->next_r];
    fifo->next_r++;
    if (fifo->next_r == fifo->size)
    {
        fifo->next_r = 0;
    }
    fifo->free++;
    return data;
}

int fifo8_status(struct FIFO8 *fifo)
{
    return fifo->size - fifo->free;
}