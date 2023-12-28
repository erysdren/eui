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
 * EUI.C
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>

#include "eui.h"

/*
 *
 * font8x8
 *
 */

static unsigned char font8x8_basic[128][8] = {
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0000 (nul) */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0001 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0002 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0003 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0004 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0005 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0006 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0007 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0008 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0009 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+000A */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+000B */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+000C */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+000D */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+000E */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+000F */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0010 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0011 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0012 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0013 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0014 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0015 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0016 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0017 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0018 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0019 */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+001A */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+001B */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+001C */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+001D */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+001E */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+001F */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0020 (space) */
	{ 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00 }, /* U+0021 (!) */
	{ 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0022 (") */
	{ 0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00 }, /* U+0023 (#) */
	{ 0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00 }, /* U+0024 ($) */
	{ 0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00 }, /* U+0025 (%) */
	{ 0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00 }, /* U+0026 (&) */
	{ 0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0027 (') */
	{ 0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00 }, /* U+0028 (() */
	{ 0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00 }, /* U+0029 ()) */
	{ 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00 }, /* U+002A (*) */
	{ 0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00 }, /* U+002B (+) */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06 }, /* U+002C (,) */
	{ 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00 }, /* U+002D (-) */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00 }, /* U+002E (.) */
	{ 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00 }, /* U+002F (/) */
	{ 0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00 }, /* U+0030 (0) */
	{ 0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00 }, /* U+0031 (1) */
	{ 0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00 }, /* U+0032 (2) */
	{ 0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00 }, /* U+0033 (3) */
	{ 0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00 }, /* U+0034 (4) */
	{ 0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00 }, /* U+0035 (5) */
	{ 0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00 }, /* U+0036 (6) */
	{ 0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00 }, /* U+0037 (7) */
	{ 0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00 }, /* U+0038 (8) */
	{ 0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00 }, /* U+0039 (9) */
	{ 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00 }, /* U+003A (:) */
	{ 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06 }, /* U+003B (;) */
	{ 0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00 }, /* U+003C (<) */
	{ 0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00 }, /* U+003D (=) */
	{ 0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00 }, /* U+003E (>) */
	{ 0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00 }, /* U+003F (?) */
	{ 0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00 }, /* U+0040 (@) */
	{ 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00 }, /* U+0041 (A) */
	{ 0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00 }, /* U+0042 (B) */
	{ 0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00 }, /* U+0043 (C) */
	{ 0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00 }, /* U+0044 (D) */
	{ 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00 }, /* U+0045 (E) */
	{ 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00 }, /* U+0046 (F) */
	{ 0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00 }, /* U+0047 (G) */
	{ 0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00 }, /* U+0048 (H) */
	{ 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00 }, /* U+0049 (I) */
	{ 0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00 }, /* U+004A (J) */
	{ 0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00 }, /* U+004B (K) */
	{ 0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00 }, /* U+004C (L) */
	{ 0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00 }, /* U+004D (M) */
	{ 0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00 }, /* U+004E (N) */
	{ 0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00 }, /* U+004F (O) */
	{ 0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00 }, /* U+0050 (P) */
	{ 0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00 }, /* U+0051 (Q) */
	{ 0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00 }, /* U+0052 (R) */
	{ 0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00 }, /* U+0053 (S) */
	{ 0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00 }, /* U+0054 (T) */
	{ 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00 }, /* U+0055 (U) */
	{ 0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00 }, /* U+0056 (V) */
	{ 0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00 }, /* U+0057 (W) */
	{ 0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00 }, /* U+0058 (X) */
	{ 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00 }, /* U+0059 (Y) */
	{ 0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00 }, /* U+005A (Z) */
	{ 0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00 }, /* U+005B ([) */
	{ 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00 }, /* U+005C (\) */
	{ 0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00 }, /* U+005D (]) */
	{ 0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00 }, /* U+005E (^) */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF }, /* U+005F (_) */
	{ 0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+0060 (`) */
	{ 0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00 }, /* U+0061 (a) */
	{ 0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00 }, /* U+0062 (b) */
	{ 0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00 }, /* U+0063 (c) */
	{ 0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6E, 0x00 }, /* U+0064 (d) */
	{ 0x00, 0x00, 0x1E, 0x33, 0x3f, 0x03, 0x1E, 0x00 }, /* U+0065 (e) */
	{ 0x1C, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0F, 0x00 }, /* U+0066 (f) */
	{ 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F }, /* U+0067 (g) */
	{ 0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00 }, /* U+0068 (h) */
	{ 0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00 }, /* U+0069 (i) */
	{ 0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E }, /* U+006A (j) */
	{ 0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00 }, /* U+006B (k) */
	{ 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00 }, /* U+006C (l) */
	{ 0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00 }, /* U+006D (m) */
	{ 0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00 }, /* U+006E (n) */
	{ 0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00 }, /* U+006F (o) */
	{ 0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F }, /* U+0070 (p) */
	{ 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78 }, /* U+0071 (q) */
	{ 0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00 }, /* U+0072 (r) */
	{ 0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00 }, /* U+0073 (s) */
	{ 0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00 }, /* U+0074 (t) */
	{ 0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00 }, /* U+0075 (u) */
	{ 0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00 }, /* U+0076 (v) */
	{ 0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00 }, /* U+0077 (w) */
	{ 0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00 }, /* U+0078 (x) */
	{ 0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F }, /* U+0079 (y) */
	{ 0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00 }, /* U+007A (z) */
	{ 0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00 }, /* U+007B ({) */
	{ 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00 }, /* U+007C (|) */
	{ 0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00 }, /* U+007D (}) */
	{ 0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* U+007E (~) */
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } /* U+007F */
};

/*
 *
 * limits
 *
 */

#ifndef EUI_MAX_FRAMES
#define EUI_MAX_FRAMES (64)
#endif

/*
 *
 * types
 *
 */

/* frame */
typedef struct frame_t {
	int x, y;
	int w, h;
	struct {
		int x, y;
	} align;
	int clip;
} frame_t;

/*
 *
 * state
 *
 */

static struct {
	frame_t frames[EUI_MAX_FRAMES];
	int frame_index;
	int w;
	int h;
	int bpp;
	int pitch;
	void *buffer;
	int glyph_w;
	int glyph_h;
	void (*set_pixel)(int x, int y, unsigned int color);
	void (*set_box)(int x, int y, int w, int h, unsigned int color);
	void (*set_glyph)(int x, int y, unsigned int glyph, unsigned int color);
} state;

/*
 *
 * private functions
 *
 */

static void set_pixel_1(int x, int y, unsigned int color)
{
	unsigned char *ofs;
	unsigned int shift, mask;

	/* get buffer offset */
	ofs = &((unsigned char *)state.buffer)[y * state.pitch + (x >> 3)];

	/* get shift and mask */
	shift = ~x & 7;
	mask = 0x1 << shift;

	/* OR the color in at ofs */
	*ofs = (*ofs & ~mask) | ((color & 0x1) << shift);
}

static void set_box_1(int x, int y, int w, int h, unsigned int color)
{
	int xx, yy;
	void *ptr;

	for (yy = y; yy < y + h; yy++)
	{
		if (x % 8 || w % 8)
		{
			/* not aligned */
			for (xx = x; xx < x + w; xx++)
				state.set_pixel(xx, yy, color);
		}
		else
		{
			/* aligned */
			ptr = &((unsigned char *)state.buffer)[yy * state.pitch + (x >> 3)];
			if (color)
				memset(ptr, 0xFF, w / 8);
			else
				memset(ptr, 0x00, w / 8);
		}
	}
}

static void set_pixel_2(int x, int y, unsigned int color)
{
	unsigned char *ofs;
	unsigned int shift, mask;

	/* get buffer offset */
	ofs = &((unsigned char *)state.buffer)[y * state.pitch + (x >> 2)];

	/* get shift and mask */
	shift = 6 - (2 * (x % 4));
	mask = 0x3 << shift;

	/* OR the color in at ofs */
	*ofs = (*ofs & ~mask) | ((color & 0x3) << shift);
}

static void set_box_2(int x, int y, int w, int h, unsigned int color)
{
	int xx, yy;
	void *ptr;

	for (yy = y; yy < y + h; yy++)
	{
		if (x % 4 || w % 4)
		{
			/* not aligned */
			for (xx = x; xx < x + w; xx++)
				state.set_pixel(xx, yy, color);
		}
		else
		{
			/* aligned */
			ptr = &((unsigned char *)state.buffer)[yy * state.pitch + (x >> 2)];
			color = color << 6 | color << 4 | color << 2 | color;
			memset(ptr, color, w / 4);
		}
	}
}

static void set_pixel_4(int x, int y, unsigned int color)
{
	unsigned char *ofs;
	unsigned int shift, mask;

	/* get buffer offset */
	ofs = &((unsigned char *)state.buffer)[y * state.pitch + (x >> 1)];

	/* get shift and mask */
	shift = 4 - (4 * (x % 2));
	mask = 0xF << shift;

	/* OR the color in at ofs */
	*ofs = (*ofs & ~mask) | ((color & 0xF) << shift);
}

static void set_box_4(int x, int y, int w, int h, unsigned int color)
{
	int xx, yy;
	void *ptr;

	for (yy = y; yy < y + h; yy++)
	{
		if (x % 2 || w % 2)
		{
			/* not aligned */
			for (xx = x; xx < x + w; xx++)
				state.set_pixel(xx, yy, color);
		}
		else
		{
			/* aligned */
			ptr = &((unsigned char *)state.buffer)[yy * state.pitch + (x >> 1)];
			color = color << 4 | color;
			memset(ptr, color, w / 2);
		}
	}
}

static void set_pixel_8(int x, int y, unsigned int color)
{
	((unsigned char *)state.buffer)[y * state.pitch + x] = color;
}

static void set_box_8(int x, int y, int w, int h, unsigned int color)
{
	int yy;

	for (yy = y; yy < y + h; yy++)
	{
		memset(&((unsigned char *)state.buffer)[yy * state.pitch + x], color, w);
	}
}

static void set_pixel_16(int x, int y, unsigned int color)
{
	unsigned short *ofs;
	ofs = (unsigned short *)((char *)state.buffer + (y * state.pitch) + (x * 2));
	*ofs = color;
}

static void set_box_16(int x, int y, int w, int h, unsigned int color)
{
	int xx, yy;
	unsigned short *ofs;

	for (yy = y; yy < y + h; yy++)
	{
		for (xx = x; xx < x + w; xx++)
		{
			ofs = (unsigned short *)((char *)state.buffer + (yy * state.pitch) + (xx * 2));
			*ofs = color;
		}
	}
}

static void set_pixel_32(int x, int y, unsigned int color)
{
	unsigned int *ofs;
	ofs = (unsigned int *)((char *)state.buffer + (y * state.pitch) + (x * 4));
	*ofs = color;
}

static void set_box_32(int x, int y, int w, int h, unsigned int color)
{
	int xx, yy;
	unsigned int *ofs;

	for (yy = y; yy < y + h; yy++)
	{
		for (xx = x; xx < x + w; xx++)
		{
			ofs = (unsigned int *)((char *)state.buffer + (yy * state.pitch) + (xx * 4));
			*ofs = color;
		}
	}
}

static void set_glyph_font8x8(int x, int y, unsigned int glyph, unsigned int color)
{
	int xx, yy, xxx, yyy;
	unsigned char *bitmap;

	if (glyph >= 128)
		return;

	bitmap = font8x8_basic[glyph];

	for (xx = 0; xx < 8; xx++)
	{
		for (yy = 0; yy < 8; yy++)
		{
			if (bitmap[xx] & 1 << yy)
			{
				xxx = x + yy;
				yyy = y + xx;

				if (xxx < 0 || xxx >= state.w)
					continue;
				if (yyy < 0 || yyy >= state.h)
					continue;

				state.set_pixel(xxx, yyy, color);
			}
		}
	}
}

/* transform box to current frame, with alignment */
static void eui_transform_box(int *x, int *y, int w, int h)
{
	switch (state.frames[state.frame_index].align.x)
	{
		case EUI_ALIGN_START:
			*x += state.frames[state.frame_index].x;
			break;
		case EUI_ALIGN_MIDDLE:
			*x += state.frames[state.frame_index].x + state.frames[state.frame_index].w / 2 - w / 2;
			break;
		case EUI_ALIGN_END:
			*x += state.frames[state.frame_index].x + state.frames[state.frame_index].w - w;
			break;
		default:
			break;
	}

	switch (state.frames[state.frame_index].align.y)
	{
		case EUI_ALIGN_START:
			*y += state.frames[state.frame_index].y;
			break;
		case EUI_ALIGN_MIDDLE:
			*y += state.frames[state.frame_index].y + state.frames[state.frame_index].h / 2 - h / 2;
			break;
		case EUI_ALIGN_END:
			*y += state.frames[state.frame_index].y + state.frames[state.frame_index].h - h;
			break;
		default:
			break;
	}
}

/* clip box to arbitrary size, returns EUI_FALSE if the shape will never be visible */
static int eui_clip_box_lower(int *x, int *y, int *w, int *h, int cx, int cy, int cw, int ch)
{
	int start_x, start_y, end_x, end_y;

	start_x = cx;
	start_y = cy;
	end_x = cx + cw;
	end_y = cy + ch;

	/* it will never become visible */
	if (*x >= end_x)
		return EUI_FALSE;
	if (*y >= end_y)
		return EUI_FALSE;
	if (*x + *w < start_x)
		return EUI_FALSE;
	if (*y + *h < start_y)
		return EUI_FALSE;

	/* clip to top edge */
	if (*y < start_y)
	{
		*h += *y - start_y;
		*y = start_y;
	}

	/* clip to bottom edge */
	if (*y + *h >= end_y)
	{
		*h = end_y - *y;
	}

	/* clip to left edge */
	if (*x < start_x)
	{
		*w += *x - start_x;
		*x = start_x;
	}

	/* clip to right edge */
	if (*x + *w >= end_x)
	{
		*w = end_x - *x;
	}

	return EUI_TRUE;
}

/* clip box to screen size, returns EUI_FALSE if the shape will never be visible */
static int eui_clip_box(int *x, int *y, int *w, int *h)
{
	if (state.frames[state.frame_index].clip)
	{
		int frame_x, frame_y, frame_w, frame_h;

		/* save frame coordinates */
		frame_x = state.frames[state.frame_index].x;
		frame_y = state.frames[state.frame_index].y;
		frame_w = state.frames[state.frame_index].w;
		frame_h = state.frames[state.frame_index].h;

		/* clip frame to screen */
		if (!eui_clip_box_lower(&frame_x, &frame_y, &frame_w, &frame_h, 0, 0, state.w, state.h))
			return EUI_FALSE;

		/* clip shape to frame */
		return eui_clip_box_lower(x, y, w, h, frame_x, frame_y, frame_w, frame_h);
	}
	else
	{
		/* clip shape to screen */
		return eui_clip_box_lower(x, y, w, h, 0, 0, state.w, state.h);
	}
}

/*
 *
 * public functions
 *
 */

/*
 * init/quit
 */

/* initialize library with writeable destination buffer */
/* returns EUI_FALSE on failure */
int eui_init(int w, int h, int bpp, int pitch, void *buffer)
{
	if (!w || !h || !bpp || !pitch || !buffer)
		return EUI_FALSE;

	/* set base functions */
	switch (bpp)
	{
		case 1:
			state.set_pixel = set_pixel_1;
			state.set_box = set_box_1;
			break;

		case 2:
			state.set_pixel = set_pixel_2;
			state.set_box = set_box_2;
			break;

		case 4:
			state.set_pixel = set_pixel_4;
			state.set_box = set_box_4;
			break;

		case 8:
			state.set_pixel = set_pixel_8;
			state.set_box = set_box_8;
			break;

		case 16:
			state.set_pixel = set_pixel_16;
			state.set_box = set_box_16;
			break;

		case 32:
			state.set_pixel = set_pixel_32;
			state.set_box = set_box_32;
			break;

		default:
			return EUI_FALSE;
	}

	/* set state values */
	state.w = w;
	state.h = h;
	state.bpp = bpp;
	state.pitch = pitch;
	state.buffer = buffer;
	state.glyph_w = 8;
	state.glyph_h = 8;
	state.set_glyph = set_glyph_font8x8;

	return EUI_TRUE;
}

/* shutdown library and clear state */
void eui_quit(void)
{
	memset(&state, 0, sizeof(state));
}

/*
 * context handling
 */

/* begin new eui context and create root frame */
/* returns EUI_FALSE on failure */
int eui_context_begin(void)
{
	state.frame_index = 0;
	if (!eui_frame_push(0, 0, state.w, state.h))
		return EUI_FALSE;

	return EUI_TRUE;
}

/* end current eui context and destroy root frame */
void eui_context_end(void)
{

}

/*
 * frame handling
 */

/* create and enter new child frame, transformed from the current frame */
/* returns EUI_FALSE on failure */
int eui_frame_push(int x, int y, int w, int h)
{
	if (state.frame_index == EUI_MAX_FRAMES - 1)
		return EUI_FALSE;

	eui_transform_box(&x, &y, w, h);

	state.frame_index++;

	state.frames[state.frame_index].x = x;
	state.frames[state.frame_index].y = y;
	state.frames[state.frame_index].w = w;
	state.frames[state.frame_index].h = h;
	state.frames[state.frame_index].align.x = EUI_ALIGN_START;
	state.frames[state.frame_index].align.y = EUI_ALIGN_START;
	state.frames[state.frame_index].clip = EUI_FALSE;

	return EUI_TRUE;
}

/* return to parent frame */
void eui_frame_pop(void)
{
	if (state.frame_index)
		state.frame_index--;
}

/* set alignment for elements in the current frame */
void eui_frame_align_set(int align_x, int align_y)
{
	state.frames[state.frame_index].align.x = align_x;
	state.frames[state.frame_index].align.y = align_y;
}

/* get alignment for elements in the current frame */
void eui_frame_align_get(int *align_x, int *align_y)
{
	if (align_x)
		*align_x = state.frames[state.frame_index].align.x;

	if (align_y)
		*align_y = state.frames[state.frame_index].align.y;
}

/* if set to EUI_TRUE, elements will be clipped to the current frame edges */
void eui_frame_clip_set(int clip)
{
	state.frames[state.frame_index].clip = clip ? EUI_TRUE : EUI_FALSE;
}

/* returns EUI_TRUE if clipping is enabled for this frame  */
int eui_frame_clip_get(void)
{
	return state.frames[state.frame_index].clip ? EUI_TRUE : EUI_FALSE;
}

/*
 * utilities
 */

/* clear screen with color */
void eui_screen_clear(unsigned int color)
{
	memset(state.buffer, color, state.h * state.pitch);
}

/* get cell dimensions of text, with newline and alignment handling */
/* returns EUI_FALSE on failure */
int eui_get_text_dimensions(int *w, int *h, char *s)
{
	int c, x, y;
	int lastx = 0;

	if (!s)
		return EUI_FALSE;

	x = 0;
	y = 0;

	/* find newlines in string */
	while ((c = *s++))
	{
		if (c == '\n')
		{
			y += 1;
			lastx = x;
			x = 0;
		}
		else
		{
			x += 1;
		}
	}

	if (w)
		*w = lastx > x ? lastx * state.glyph_w : x * state.glyph_w;

	if (h)
		*h = (y + 1) * state.glyph_h;

	return EUI_TRUE;;
}

/* convert error code to printable string */
const char *eui_error_string(int code)
{
	EUI_UNUSED(code);
	return NULL;
}

/*
 * drawing primitives
 */

/* draw box */
void eui_draw_box(int x, int y, int w, int h, unsigned int color)
{
	eui_transform_box(&x, &y, w, h);

	if (eui_clip_box(&x, &y, &w, &h))
		state.set_box(x, y, w, h, color);
}

/* draw box border */
void eui_draw_box_border(int x, int y, int w, int h, int t, unsigned int color)
{
	int lx, ly, lw, lh;
	eui_transform_box(&x, &y, w, h);

	/* top line */
	lx = x;
	ly = y;
	lw = w;
	lh = t;
	if (eui_clip_box(&lx, &ly, &lw, &lh))
		state.set_box(lx, ly, lw, lh, color);

	/* bottom line */
	lx = x;
	ly = y + h - t;
	lw = w;
	lh = t;
	if (eui_clip_box(&lx, &ly, &lw, &lh))
		state.set_box(lx, ly, lw, lh, color);

	/* left line */
	lx = x;
	ly = y + t;
	lw = t;
	lh = h - t * 2;
	if (eui_clip_box(&lx, &ly, &lw, &lh))
		state.set_box(lx, ly, lw, lh, color);

	/* right line */
	lx = x + w - t;
	ly = y + t;
	lw = t;
	lh = h - t * 2;
	if (eui_clip_box(&lx, &ly, &lw, &lh))
		state.set_box(lx, ly, lw, lh, color);
}

/* draw text */
void eui_draw_text(int x, int y, unsigned int color, char *s)
{
	int c;
	int start_x;
	char *ptr;
	int w, h;
	unsigned int len = 0;

	/* get text size */
	if (!eui_get_text_dimensions(&w, &h, s))
		return;

	/* transform to size */
	eui_transform_box(&x, &y, w, h);

	/* draw string */
	start_x = x;
	while ((c = *s++))
	{
		if (c == '\n')
		{
			switch (state.frames[state.frame_index].align.x)
			{
				case EUI_ALIGN_START:
					/* set next string position */
					x = start_x;
					y += state.glyph_h;
					break;

				case EUI_ALIGN_MIDDLE:
					/* get length of next string chunk */
					ptr = s;
					while (*ptr && *ptr != '\n') ptr++;
					len = ptr - s;
					/* set next string position */
					x = start_x + (w / 2) - ((len * state.glyph_w) / 2);
					y += state.glyph_h;
					break;

				case EUI_ALIGN_END:
					/* get length of next string chunk */
					ptr = s;
					while (*ptr && *ptr != '\n') ptr++;
					len = ptr - s;
					/* set next string position */
					x = start_x + w - (len * state.glyph_w);
					y += state.glyph_h;
					break;
			}
		}
		else
		{
			state.set_glyph(x, y, c, color);
			x += state.glyph_w;
		}
	}
}

/* draw formatted text */
void eui_draw_textf(int x, int y, unsigned int color, char *s, ...)
{
	static char buffer[1024];
	va_list args;

	va_start(args, s);
	vsprintf(buffer, s, args);
	va_end(args);

	eui_draw_text(x, y, color, buffer);
}
