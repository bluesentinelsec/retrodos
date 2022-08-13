/*
  This program demonstrates how to 
  set the VGA card to mode 13h
  for 320x200 resolution at 256
  colors. Mode 13h is useful for
  game programming because it
  provides one continguous region
  of video memory from:
  A000:0000h - A000:F9FFh
*/

#include <conio.h>		/* for kbhit  */
#include <dos.h>		/* for int86  */

#define VGA256	    0x13
#define TEXT_MODE   0x03

/*
  Set_Video_Mode sets the VGA card
  to an alternate graphics mode.
  This demo shows how to se the
  video mode to 13h or the 
  default text mode.
*/

void
Set_Video_Mode (int mode)
{
  /* used to place bytes in CPU registers */
  union REGS inregs, outregs;

  /* set AX register */
  inregs.h.ah = 0;
  inregs.h.al = (unsigned char) mode;

  /* invoke interupt */
  int86 (0x10, &inregs, &outregs);
}

int
main (void)
{
  /* set VGA card to mode 13h */
  Set_Video_Mode (VGA256);

  /* wait for a key press */
  while (!kbhit ())
    {
    }

  /* set VGA card to text mode */
  Set_Video_Mode (TEXT_MODE);

  return 0;
}
