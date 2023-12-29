/*
MIT License

Copyright (c) 2023 erysdren (it/she/they)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
 *
 * HARNESS_DOS.C
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <dos.h>
#include <conio.h>

#ifdef __DJGPP__
#include <dpmi.h>
#include <go32.h>
#include <sys/nearptr.h>
#include <sys/farptr.h>
#define VGA_MEMORY (0xA0000 + __djgpp_conventional_base)
#else
#define VGA_MEMORY (0xA0000)
#endif

#include "eui.h"
#include "examples.h"

static uint8_t screen[320 * 200];

/* main */
int main(int argc, char **argv)
{
	int old_mode;
	union REGS regs;

	EUI_UNUSED(argc);
	EUI_UNUSED(argv);

	/* get old video mode */
	regs.h.ah = 0x0f;
	int386(0x10, &regs, &regs);
	old_mode = regs.h.al;

	/* set video mode to 0x13 */
	regs.w.ax = 0x13;
	int386(0x10, &regs, &regs);

	/* init eui */
	eui_init(320, 200, 8, 320, (void *)screen);

	/* main loop */
	while (!kbhit())
	{
		/* run eui context */
		if (eui_context_begin())
		{
			/* run example func */
			EXAMPLE_FUNC();

			/* end eui context */
			eui_context_end();
		}

		/* copy to screen */
		memcpy((void *)VGA_MEMORY, (void *)screen, sizeof(screen));
	}

	/* quit */
	eui_quit();

	/* reset video mode */
	regs.w.ax = old_mode;
	int386(0x10, &regs, &regs);

	return 0;
}
