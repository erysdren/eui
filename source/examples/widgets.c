/*
MIT License

Copyright (c) 2023-2024 erysdren (it/she/they)

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
 * WIDGETS.C
 *
 */

#include <stdio.h>
#include <stddef.h>

#include "eui_widg.h"

void button_callback(void *user)
{
	EUI_UNUSED(user);
	printf("Button pressed!\n");
}

void example_widgets(void)
{
	/* clear screen */
	eui_screen_clear(0x01);

	/* set alignment to the center of the frame */
	eui_frame_align_set(EUI_ALIGN_MIDDLE, EUI_ALIGN_MIDDLE);

	/* draw 192x64 box and draw a 2px border */
	eui_draw_box(0, 0, 192, 96, 0x0F);
	eui_draw_box_border(0, 0, 192, 96, 2, 0x02);

	/* create child frame with 8 pixels of padding on each side */
	eui_frame_push(0, 0, 176, 80);

	/* set child frame alignment to top-left */
	eui_frame_align_set(EUI_ALIGN_START, EUI_ALIGN_START);

	/* draw a string with the default 8x8 font */
	if (eui_widget_button(0, 0, 64, 24, "Button", button_callback, NULL))
	{
		eui_draw_text(0, 32, 0x00, "A simple button.");
	}

	/* destroy child frame */
	eui_frame_pop();
}
