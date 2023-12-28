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
 * HELLO.C
 *
 */

#include "eui.h"

void example_hello(void)
{
	/* clear screen */
	eui_screen_clear(0x01);

	/* center alignment */
	eui_frame_align_set(EUI_ALIGN_MIDDLE, EUI_ALIGN_MIDDLE);

	/* left aligned text */
	eui_draw_box(0, -80, 192, 64, 0x0F);
	eui_draw_box_border(0, -80, 192, 64, 2, 0x02);

	eui_frame_push(0, -80, 176, 48);
	eui_frame_align_set(EUI_ALIGN_START, EUI_ALIGN_MIDDLE);
	eui_draw_text(0, 0, 0x00, "Left aligned text\nwith a newline!");
	eui_frame_pop();

	/* center aligned text */
	eui_draw_box(0, 0, 192, 64, 0x0F);
	eui_draw_box_border(0, 0, 192, 64, 2, 0x02);

	eui_frame_push(0, 0, 192, 64);
	eui_frame_align_set(EUI_ALIGN_MIDDLE, EUI_ALIGN_MIDDLE);
	eui_draw_text(0, 0, 0x00, "Center aligned text\nwith a newline!");
	eui_frame_pop();

	/* right aligned text */
	eui_draw_box(0, 80, 192, 64, 0x0F);
	eui_draw_box_border(0, 80, 192, 64, 2, 0x02);

	eui_frame_push(0, 80, 176, 48);
	eui_frame_align_set(EUI_ALIGN_END, EUI_ALIGN_MIDDLE);
	eui_draw_text(0, 0, 0x00, "Right aligned text\nwith a newline!");
	eui_frame_pop();
}
