ipl.bin : ipl.nas Makefile
	nask ipl.nas ipl.bin ipl.lst

asmhead.bin : asmhead.nas Makefile
	nask asmhead.nas asmhead.bin asmhead.lst 

bootpack.gas : bootpack.c Makefile 
	cc1 -o bootpack.gas bootpack.c 

bootpack.nas : bootpack.gas Makefile 
	gas2nask bootpack.gas bootpack.nas 

bootpack.obj : bootpack.nas Makefile 
	nask bootpack.nas bootpack.obj bootpack.lst 

naskfunc.obj : naskfunc.nas Makefile 
	nask naskfunc.nas naskfunc.obj naskfunc.lst 

bootpack.bim : bootpack.obj naskfunc.obj Makefile
	obj2bim @../z_tools/haribote/haribote.rul \
		out:bootpack.bim stack:3136k map:bootpack.map \
		bootpack.obj naskfunc.obj 
# 3MB+64KB=3136KB

bootpack.hrb : bootpack.bim Makefile 
	bim2hrb bootpack.bim bootpack.hrb 0

haribote.sys : asmhead.bin bootpack.hrb Makefile 
	copy /B asmhead.bin+bootpack.hrb haribote.sys 

helloos04.img: ipl.bin haribote.sys Makefile
	edimg imgin:../z_tools/fdimg0at.tek \
		wbinimg src:ipl.bin len:512 from:0 to:0 \
		copy from:haribote.sys to:@: \
		imgout:helloos04.img

img:
	make -r helloos04.img

clean:
	-del *.bin 
	-del *.lst 
	-del *.gas 
	-del *.obj 
	-del bootpack.nas 
	-del bootpack.map 
	-del bootpack.bim 
	-del bootpack.hrb 
	-del haribote.sys
	