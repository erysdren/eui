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
 * TEST_WATCOM16.C
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static uint8_t screen[160 * 100];

#include "eui.h"

/* main */
int main(int argc, char **argv)
{
	eui_pixelmap_t dest;
	eui_vec2_t pos, size;
	FILE *file;

	EUI_UNUSED(argc);
	EUI_UNUSED(argv);

	/* setup pixelmap */
	dest.w = 160;
	dest.h = 100;
	dest.pitch = 160;
	dest.pixels = (eui_color_t *)screen;

	/* do eui */
	if (eui_begin(dest))
	{
		/* clear */
		eui_clear(18);

		/* set alignment to center */
		eui_set_align(EUI_ALIGN_MIDDLE, EUI_ALIGN_MIDDLE);

		/* button */
		pos.x = 0;
		pos.y = 0;
		size.x = 128;
		size.y = 16;
		if (eui_button(pos, size, "My Cool Button", NULL, NULL))
		{
			pos.x = 0;
			pos.y = 24;
			eui_text(pos, 15, "Hovered");
		}

		/* end eui */
		eui_end();
	}

	/* dump screen buffer */
	file = fopen("screen.dat", "wb");
	fwrite(screen, 160 * 100, 1, file);
	fclose(file);

	return 0;
}
