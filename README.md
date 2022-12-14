# retrodos

This repo provides a high level guide on how to get started with retro programming on FreeDOS or MS-DOS platforms.

This guide expects that you're a power user - you should know how to install programs and virtual machines. You should know about the C programming ecosystem (how to compile, link, and build programs). And you should know your way around the command line.

## Why do this?

- You have direct access to the hardware
- Resources are constrained
- You learn a lot 
- Retro programming is fun


## Development Tech Stack

**Develop on FreeDOS**

Developing on FreeDOS can be fun if you want to feel what it was like develop on DOS in the early 90's.

1. Download [FreeDOS 1.3](https://www.freedos.org/download/), both the live CD and the bonus CD.

2. Install FreeDOS in a virtual machine.

3. After you can boot into FreeDOS, insert the bonus CD into the VM.

4. Install development tools with fdimples; specifically, you want Open Watcom, but you can install additional tools if you want.

5. Add the following text to your fdauto.bat file. This ensures the Open Watcom compiler can find all of its needed libraries, header files, and executables.

```
C:\DEVEL\WATCOMC\OWSETENV.BAT
set PATH=%PATH%;C:\DEVEL\WATCOMC\BINW\
```

6. Reboot the VM and try running `wcl.exe` - if it works, you are ready to write code.


**Develop on modern systems**

This is the reccomended development tech stack for serious development.

1. Install a code editor; I generally use Vim for retro programming but you can likely make this work with Visual Studio Code.

2. Install [OpenWatcom](https://github.com/open-watcom/open-watcom-v2/releases)

3. Add the OpenWatcom binaries to your path; for Linux, this should be: `open-watcom-v2/binl/`

4. Try running `wcl` - if it works, you are ready to write code.

5. Install DosBox for rapid testing.

## Compiling hello world

1. Create your source file:

```c
#include <stdio.h>

int main(void)
{
  printf("hello dos!\n");
  return 0;
}
```

2. Compile to EXE:

```
wcl main.c
```

3. If on DOS, you can run it direct.

4. If on Linux, you can quickly test your EXE on DosBOX:

```
# from Linux terminal
dosbox ./

# from DosBox prompt:
MAIN.EXE
```

## Debugging Code

1. Compile your app with debug symbols:

```
wcl -d3 main.c
```

2. Single step your app in the Watcom debugger:

```
wd main.exe
```

## Remote Debugging

You can also perform remote debugging using DosBox.

To do this, you must build DosBox Staging from source with the debugger features enabled.

https://github.com/dosbox-staging/dosbox-staging/blob/main/BUILD.md

You can then start your program in the debugger like so:

```
# from DosBox shell
debug YOUR_APP.exe
```

You can also invoke the debugger while the app is running by pressing the BREAK key (fn + b + alt on my Dell laptop, which doesn't have a break key)

Run: `fn + F5`

Step over: `fn + F10`

Breakpoints: `bp 01ED:0010`

It is difficult to find and break on your function.

One approach is to wrap your function in an infinite loop and then invoke the debugger while your program is looping.

```
while (1 == 1)
{
    // press BREAK to launch debugger while in this loop
    YourFunction();
}
```

## Compile a static library

1. Create your .h and .c file

```
# assume you wrote these two files:
gfx.c
gfx.h
```

2. Compile object code

```
wcc gfx.c
```

3. Package library

```
# wlib <library name> +<object file name>

wlib gfx +gfx
```

4. Link static lib to app

```
wcl main.c gfx.lib
```

## In-line assembly

1. Write a source file with in-line assembly:

```
int main(void)
{
  _asm{
    mox ax,0
    mov bx,0
    mov cx,0
  }
  return 0;
}
```

2. Compile with debug symbols:

```
wcl -d3 main.c
```

3. Single step your app in a debugger to confirm the ASM instructions are present:

```
wd main.exe
```

## Create a floppy disk on Linux

```bash

# create floppy disk image
head -c 1474560 /dev/zero > floppy.vfd

mkfs.vfat floppy.vfd

# mount floppy on Linux
sudo mkdir -p /media/dosdisk

sudo mount -o loop floppy.vfd /media/dosdisk/

# copy files to floppy as needed

# un-mount floppy disk from Linux
sudo umount /media/dosdisk/

# now you can insert the floppy.vfd image into FreeDOS via a VirtualBox floppy drive
```

## Have Fun

You now have the requisite skills to create non-trivial programs.

Have fun!
