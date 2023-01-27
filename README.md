# AHJOS：自己动手编写的操作系统
参考《30天自制操作系统》，学习操作系统内部原理，并动手编写属于自己的操作系统（暂且不要脸地命名为AHJOS吧hhhhh）
## 学习笔记
* [常用编译/反编译指令](markdown/sh_sample.md)
* [CPU寄存器](markdown/cpu_register.md)
* [BIOS程序指令](markdown/bios.md)

## 演化日志
### [**day01**，2023/1/26](day01/)
* 初次使用汇编语言编写程序
* 使用Bz.exe查看/编辑二进制文件
* 了解了如何制作FAT12格式启动区，并引导计算机启动

[helloos.img](day01/helloos.img)
![day01](markdown/imgs/log/day01.png)

### [**day02**，2023/1/26](day02/)
* 学习了部分CPU寄存器的使用方法
* 学习了Makefile的使用方法

[helloos02.2.img](day02/helloos02.2.img)
![day02](markdown/imgs/log/day02.png)

### [**day03**，2023/1/27](day03/)
* 制作了真正意义的IPL
* 学习了读取软盘至内存的方法，并读取至软盘的第10个柱面的第18个扇区
* 进入32位模式并导入C语言
* 控制VGA显卡，切换至320x200x8位彩色模式，并显示黑屏

[helloos03.img](day03/helloos03.img)
![day03](markdown/imgs/log/day03.png)

### [**day04**, 2023/1/27](day04/)
* 用C语言实现内存写入（显存）
* 编辑VGA显示调色板
* 显示器绘制矩形

[helloos04.img](day03/helloos04.img)
![day04](markdown/imgs/log/day04.png)