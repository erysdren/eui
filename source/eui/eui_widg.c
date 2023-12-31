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
 * EUI_WIDG.C
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>

#include "eui_widg.h"

/*
 *
 * public functions
 *
 */

/* draw button widget and handle state */
/* returns EUI_TRUE if hovered and fires callback if clicked */
int eui_widget_button(int x, int y, int w, int h, char *label, void (*callback)(void *), void *user)
{
	static int clicked;
	int button;
	int hovered;

	hovered = eui_cursor_hovering(x, y, w, h);

	button = eui_button_read();

	if (hovered)
	{
		eui_frame_push(x, y, w, h);
		eui_frame_align_set(EUI_ALIGN_MIDDLE, EUI_ALIGN_MIDDLE);

		eui_draw_box(0, 0, w, h, 0x00);
		eui_draw_box_border(0, 0, w, h, 1, 0x0F);
		eui_draw_text(0, 0, 0x0F, label);

		eui_frame_pop();
	}
	else
	{
		eui_frame_push(x, y, w, h);
		eui_frame_align_set(EUI_ALIGN_MIDDLE, EUI_ALIGN_MIDDLE);

		eui_draw_box(0, 0, w, h, 0x0F);
		eui_draw_box_border(0, 0, w, h, 1, 0x00);
		eui_draw_text(0, 0, 0x00, label);

		eui_frame_pop();
	}

	if (hovered && button && !clicked)
	{
		if (callback != NULL)
			callback(user);

		clicked = EUI_TRUE;
	}

	if (!button)
		clicked = EUI_FALSE;

	return hovered;
}
