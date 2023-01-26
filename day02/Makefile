ipl.bin : ipl.nas Makefile
	nask ipl.nas ipl.bin ipl.lst

helloos02.2.img: ipl.bin Makefile
	edimg imgin:../tolset/z_tools/fdimg0at.tek \
		wbinimg src:ipl.bin len:512 from:0 to:0 \
		imgout:helloos02.2.img

img:
	make -r ipl.bin
	make -r helloos02.2.img
	