TOOLPATH = ../z_tools/
INCPATH  = ../z_tools/haribote/ include/

BUILD_PATH = build/
LOG_PATH = $(BUILD_PATH)log/
ASM_PATH = asm/
C_PATH = source/

OBJS_BOOTPACK = $(BUILD_PATH)bootpack.obj $(BUILD_PATH)naskfunc.obj \
	$(BUILD_PATH)hankaku.obj $(BUILD_PATH)graphic.obj $(BUILD_PATH)dsctbl.obj \
	$(BUILD_PATH)int.obj $(BUILD_PATH)fifo.obj $(BUILD_PATH)keyboard.obj \
	$(BUILD_PATH)mouse.obj $(BUILD_PATH)memory.obj $(BUILD_PATH)sheet.obj

MAKE     = $(TOOLPATH)make.exe -r
NASK     = $(TOOLPATH)nask.exe
CC1      = $(TOOLPATH)cc1.exe -I$(INCPATH) -Os -Wall -quiet
GAS2NASK = $(TOOLPATH)gas2nask.exe -a
OBJ2BIM  = $(TOOLPATH)obj2bim.exe
MAKEFONT = $(TOOLPATH)makefont.exe
BIN2OBJ  = $(TOOLPATH)bin2obj.exe
BIM2HRB  = $(TOOLPATH)bim2hrb.exe
RULEFILE = $(TOOLPATH)haribote/haribote.rul
EDIMG    = $(TOOLPATH)edimg.exe
IMGTOL   = $(TOOLPATH)imgtol.com
COPY     = copy
DEL      = del /Q

# 默认动作

default :
	$(MAKE) img

# 镜像文件生成

$(BUILD_PATH)ipl.bin : $(ASM_PATH)ipl.nas Makefile
	$(NASK) $(ASM_PATH)ipl.nas $(BUILD_PATH)ipl.bin $(LOG_PATH)ipl.lst

asmhead.bin : $(ASM_PATH)asmhead.nas Makefile
	$(NASK) $(ASM_PATH)asmhead.nas asmhead.bin $(LOG_PATH)asmhead.lst

$(BUILD_PATH)%.gas : $(C_PATH)%.c Makefile
	$(CC1) -o $(BUILD_PATH)$*.gas $(C_PATH)$*.c

$(BUILD_PATH)%.nas : $(BUILD_PATH)%.gas Makefile
	$(GAS2NASK) $(BUILD_PATH)$*.gas $(BUILD_PATH)$*.nas

$(BUILD_PATH)%.obj : $(BUILD_PATH)%.nas Makefile
	$(NASK) $(BUILD_PATH)$*.nas $(BUILD_PATH)$*.obj $(LOG_PATH)$*.lst

$(BUILD_PATH)naskfunc.obj : $(ASM_PATH)naskfunc.nas Makefile
	$(NASK) $(ASM_PATH)naskfunc.nas $(BUILD_PATH)naskfunc.obj $(LOG_PATH)naskfunc.lst

$(BUILD_PATH)hankaku.bin : shared/fonts/hankaku.txt Makefile
	$(MAKEFONT) shared/fonts/hankaku.txt $(BUILD_PATH)hankaku.bin

$(BUILD_PATH)hankaku.obj : $(BUILD_PATH)hankaku.bin Makefile
	$(BIN2OBJ) $(BUILD_PATH)hankaku.bin $(BUILD_PATH)hankaku.obj _hankaku

$(BUILD_PATH)bootpack.bim : $(OBJS_BOOTPACK) Makefile
	$(OBJ2BIM) @$(RULEFILE) out:$(BUILD_PATH)bootpack.bim stack:3136k map:$(BUILD_PATH)bootpack.map \
		$(OBJS_BOOTPACK)
# 3MB+64KB=3136KB

bootpack.hrb : $(BUILD_PATH)bootpack.bim Makefile
	$(BIM2HRB) $(BUILD_PATH)bootpack.bim bootpack.hrb 0

ahjos.sys : asmhead.bin bootpack.hrb Makefile
	copy /B asmhead.bin+bootpack.hrb ahjos.sys

ahjos10.img : $(BUILD_PATH)ipl.bin ahjos.sys Makefile
	$(EDIMG)   imgin:../z_tools/fdimg0at.tek \
		wbinimg src:$(BUILD_PATH)ipl.bin len:512 from:0 to:0 \
		copy from:ahjos.sys to:@: \
		imgout:ahjos10.img

# 其他指令

img :
	$(MAKE) ahjos10.img
	$(MAKE) clean

clean :
	-$(DEL) "$(BUILD_PATH)"
	-$(DEL) "$(LOG_PATH)"
	-$(DEL) asmhead.bin
	-$(DEL) bootpack.hrb 
	-$(DEL) ahjos.sys

