/*
MIT License

Copyright (c) 2018 shpuld
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
 * TEST_WATCOM.C
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <dos.h>
#include <conio.h>

#include "eui.h"

#define VGA_MEMORY (0xA0000)
static uint8_t backbuffer[320 * 200];
static bool running;

/* button callback */
void quit_callback(void *user)
{
	running = false;
}

/* main */
int main(int argc, char **argv)
{
	int old_mode;
	eui_pixelmap_t dest;
	eui_event_t event;
	union REGS regs;
	eui_vec2_t pos, size;

	/* get old mode */
	regs.h.ah = 0x0f;
	int386(0x10, &regs, &regs);
	old_mode = regs.h.al;

	/* set video mode to 13h */
	regs.w.ax = 0x13;
	int386(0x10, &regs, &regs);

	/* enable mouse */
	regs.w.ax = 0x00;
	int386(0x33, &regs, &regs);

	/* hide mouse */
	regs.w.ax = 0x02;
	int386(0x33, &regs, &regs);

	/* setup pixelmap */
	dest.w = 320;
	dest.h = 200;
	dest.pitch = 320;
	dest.pixels = (eui_color_t *)backbuffer;

	/* main loop */
	running = true;
	while (running)
	{
		/* read mouse */
		regs.w.ax = 0x03;
		int386(0x33, &regs, &regs);

		/* mouse move event */
		event.type = EUI_EVENT_MOUSE;
		event.mouse.x = regs.w.cx;
		event.mouse.y = regs.w.dx;
		event.mouse.xrel = 0;
		event.mouse.yrel = 0;
		eui_push_event(event);

		/* mouse button event */
		if (regs.w.bx)
		{
			event.type = EUI_EVENT_BUTTON_DOWN;
			event.button.x = regs.w.cx;
			event.button.y = regs.w.dx;
			event.button.button = EUI_BUTTON_LEFT;
			eui_push_event(event);
		}
		else
		{
			event.type = EUI_EVENT_BUTTON_UP;
			event.button.x = regs.w.cx;
			event.button.y = regs.w.dx;
			event.button.button = EUI_BUTTON_LEFT;
			eui_push_event(event);
		}

		/* do eui */
		if (eui_begin(dest));
		{
			/* clear */
			eui_clear(18);

			/* set alignment to center */
			eui_set_align(EUI_ALIGN_MIDDLE, EUI_ALIGN_MIDDLE);

			/* button */
			pos.x = 0;
			pos.y = 0;
			size.x = 48;
			size.y = 16;
			eui_button(pos, size, "Quit", quit_callback, NULL);

			/* mouse pos */
			pos.x = 0;
			pos.y = 32;
			eui_textf(pos, 15, "x=%d y=%d", regs.w.cx, regs.w.dx);

			/* draw cursor */
			eui_cursor(5);

			/* end eui */
			eui_end();
		}

		/* copy to screen */
		memcpy((void *)VGA_MEMORY, (void *)backbuffer, sizeof(backbuffer));
	}

	/* reset video mode */
	regs.w.ax = old_mode;
	int386(0x10, &regs, &regs);

	return 0;
}
