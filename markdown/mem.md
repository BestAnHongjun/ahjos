# AHJOS内存分布图
[返回首页](../README.md)
* 0x00000000-0x000fffff：在启动中会多次使用，但之后就变空（当然，还有BIOS，VRAM等内容）
* 0x00100000-0x00267fff：用于保存软盘的内容（1440KB）
* 0x00268000-0x0026f7ff：空（30KB）
* 0x0026f800-0x0026ffff：IDT（2KB）
* 0x00270000-0x0027ffff：GDT（64KB）
* 0x00280000-0x002fffff：bootpack.hrb（512KB）
* 0x00300000-0x003fffff：栈及其他（1MB）
* 0x00400000-          ：空