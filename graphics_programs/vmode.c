#include <stdio.h>
#include <dos.h>
#include <conio.h>

#define VGA256 0x13
#define TEXT_MODE 0x03

void
Set_Video_Mode (int mode)
{
  union REGS inregs, outregs;

  inregs.h.ah = 0;
  inregs.h.al = (unsigned char) mode;

  int86 (0x10, &inregs, &outregs);
}

int
main (void)
{
  Set_Video_Mode (VGA256);

  while (!kbhit ())
    {
    }

  Set_Video_Mode (TEXT_MODE);

  return 0;
}
