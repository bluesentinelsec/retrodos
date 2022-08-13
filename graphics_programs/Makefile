

video_mode:
	indent vmode.c
	wcl -d3 vmode.c

make_floppy:
	head -c 1474560 /dev/zero > floppy.vfd
	mkfs.vfat floppy.vfd
	sudo mkdir -p /media/dosdisk
	sudo mount -o loop floppy.vfd /media/dosdisk/
clean:
	rm -f *.o
	rm -f *.c~
	rm -f *.exe
	rm -f *.err
