## 常用指令
### 1.NASM编译与反编译指令
* 编译指令
```sh
nasm boot.asm -o boot.bin
```
* 反编译指令
```sh
ndisasm -o 0x7c00 boot.bin >> disboot.asm
```
### 2.NASK编译指令
* 编译指令
```sh
nask helloos.nas helloos.img
```