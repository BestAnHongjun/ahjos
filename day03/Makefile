ipl.bin : ipl.nas Makefile
	nask ipl.nas ipl.bin ipl.lst

hanbote.sys : haribote.nas Makefile
	nask haribote.nas haribote.sys haribote.lst

helloos03.img: ipl.bin Makefile
	edimg imgin:../tolset/z_tools/fdimg0at.tek \
		wbinimg src:ipl.bin len:512 from:0 to:0 \
		copy from:haribote.sys to:@:\
		imgout:helloos03.img

img:
	make -r ipl.bin
	make -r hanbote.sys
	make -r helloos03.img
	