/*
MIT License

Copyright (c) 2023-2025 erysdren (it/its)

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
 * STANDALONE.C
 *
 */

#include "eui.h"
#include "examples.h"

void draw_titled_window(int x, int y, int w, int h, char *title, int focused)
{
	/* enter frame */
	eui_frame_push(x, y, w, h);

	/* offset z */
	if (focused)
		eui_frame_z_offset(8);

	/* center align */
	eui_frame_align_set(EUI_ALIGN_MIDDLE, EUI_ALIGN_MIDDLE);

	/* window background */
	eui_draw_box(0, 0, w, h, 0x08);

	/* outer 1px black border */
	eui_draw_box_border(0, 0, w, h, 1, 0x00);

	/* inner 1px black borders */
	eui_draw_box_border(0, 0, w - 6, h - 6, 1, 0x00);
	eui_frame_align_set(EUI_ALIGN_START, EUI_ALIGN_START);
	eui_draw_box(16, 0, 1, h, 0x00);
	eui_draw_box(w - 17, 0, 1, h, 0x00);
	eui_draw_box(0, 16, w, 1, 0x00);
	eui_frame_align_set(EUI_ALIGN_START, EUI_ALIGN_END);
	eui_draw_box(0, -16, w, 1, 0x00);

	/* redraw background */
	eui_frame_align_set(EUI_ALIGN_MIDDLE, EUI_ALIGN_START);
	eui_draw_box(0, 17, w - 8, h - 17 - 4, 0x0F);

	/* title */
	eui_frame_align_set(EUI_ALIGN_START, EUI_ALIGN_START);
	eui_draw_box(4, 4, 12, 12, 0x07);
	eui_frame_align_set(EUI_ALIGN_END, EUI_ALIGN_START);
	eui_draw_box(-4, 4, 12, 12, 0x07);
	eui_frame_align_set(EUI_ALIGN_MIDDLE, EUI_ALIGN_START);
	if (focused)
	{
		eui_draw_box(0, 4, w - 34, 12, 0x04);
		eui_draw_text(0, 6, 0x0F, title);
	}
	else
	{
		eui_draw_box(0, 4, w - 34, 12, 0x0F);
		eui_draw_text(0, 6, 0x00, title);
	}

	/* menu bar */
	eui_frame_align_set(EUI_ALIGN_START, EUI_ALIGN_START);
	eui_draw_text(8, 19, 0x00, "File");
	eui_draw_text(64, 19, 0x00, "Help");
	eui_frame_align_set(EUI_ALIGN_MIDDLE, EUI_ALIGN_START);
	eui_draw_box(0, 28, w - 8, 1, 0x00);

	/* exit frame */
	eui_frame_pop();
}

void example_standalone(void)
{
	/* draw a "standalone" window */
	draw_titled_window(0, 0, EXAMPLE_WIDTH, EXAMPLE_HEIGHT, "File Manager", EUI_TRUE);
}
