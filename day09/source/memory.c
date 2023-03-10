#include "../include/bootpack.h"


void memman_init(struct MEMMAN *man)
{
    man->frees = 0;     // 可用信息数目
    man->maxfrees = 0;  // 用于观察可用状况
    man->lostsize = 0;  // 释放失败的内存的大小总和
    man->losts = 0;     // 释放失败次数
    return;
}

unsigned int memman_total(struct MEMMAN *man)
{   // 报告空闲内存大小
    unsigned int i, t = 0;
    for (i = 0; i < man->frees; i++)
    {
        t += man->free[i].size;
    }
    return t;
}

unsigned int memman_alloc(struct MEMMAN *man, unsigned int size)
{   // 分配内存
    unsigned int i, a;
    for (i = 0; i < man->frees; i++)
    {
        if (man->free[i].size >= size)
        {   // 找到了足够大的内存
            a = man->free[i].addr;
            man->free[i].size -= size;
            if (man->free[i].size == 0)
            {
                man->frees--;
                for (; i < man->frees; i++)
                {
                    man->free[i] = man->free[i + 1];
                }
            }
            return a;
        }
    }
    return 0;
}

int memman_free(struct MEMMAN *man, unsigned int addr, unsigned int size)
{   // 释放内存
    int i, j;
    // 为方便管理内存，将free[]按照addr的顺序排列
    for (i = 0; i < man->frees; i++)
    {
        if (man->free[i].addr > addr)
        {
            break;
        }
    }
    // free[i-1].addr < addr < free[i].addr
    if (i > 0)
    {   // 前面有可用内存
        if (man->free[i - 1].addr + man->free[i - 1].size == addr)
        {   // 可以和前面的可用内存归纳到一起
            man->free[i - 1].size += size;
            if (i < man->frees)
            {   // 后面也有
                if (addr + size == man->free[i].addr)
                {   // 也可以和后面的可用内存归纳到一起
                    man->free[i - 1].size += man->free[i].size;
                    // man->free[i]删除，free[i]变0后归纳到前面去
                    man->frees--;
                    for (; i < man->frees; i++)
                    {
                        man->free[i] = man->free[i + 1];
                    }
                }
            }
            return 0;
        }
    }
    if (i < man->frees)
    {   // 不能与前面的可用内存归纳到一起
        if (addr + size == man->free[i].addr)
        {   // 可以和后面的内容归纳到一起
            man->free[i].addr = addr;
            man->free[i].size += size;
            return 0;
        }
    }
    if (man->frees < MEMMAN_FREES)
    {
        // 既不能与前面归纳，也不能与后面归纳
        for (j = man->frees; j > i; j--)
        {
            man->free[j] = man->free[j - 1];
        }
        man->frees++;
        if (man->maxfrees < man->frees)
        {
            man->maxfrees = man->frees; // 更新最大值
        }
        man->free[i].addr = addr;
        man->free[i].size = size;
        return 0;
    }

    // 不能往后移动
    man->losts++;
    man->lostsize += size;
    return -1;
}

unsigned int memtest(unsigned int start, unsigned int end)
{
    char flg486 = 0;
    unsigned int eflg, cr0, i;

    /* 确认CPU是386还是486以上 */
    eflg = io_load_eflags();
    eflg |= EFLAGS_AC_BIT;
    io_store_eflags(eflg);
    eflg = io_load_eflags();
    if ((eflg & EFLAGS_AC_BIT) != 0)
    { // 如果是386，即使设定AC=1，也会自动回0
        flg486 = 1;
    }
    eflg &= ~EFLAGS_AC_BIT;
    io_store_eflags(eflg);

    if (flg486 != 0)
    {
        cr0 = load_cr0();
        cr0 |= CR0_CACHE_DISABLE; // 禁止缓存
        store_cr0(cr0);
    }

    i = memtest_sub(start, end);

    if (flg486 != 0)
    {
        cr0 = load_cr0();
        cr0 &= ~CR0_CACHE_DISABLE; // 允许缓存
        store_cr0(cr0);
    }

    return i;
}
