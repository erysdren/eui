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
 * EUI.C
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include "eui.h"

/*
 *
 * font8x8
 *
 */

static const unsigned char font8x8_basic[128][8] = {
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
 * xbm icons
 *
 */

/* checkbox border */
static const int checkbox_border_w = 11;
static const int checkbox_border_h = 11;
static unsigned char checkbox_border_bits[] = {
	0xff, 0x07, 0x01, 0x04, 0x01, 0x04, 0x01, 0x04, 0x01, 0x04, 0x01, 0x04,
	0x01, 0x04, 0x01, 0x04, 0x01, 0x04, 0x01, 0x04, 0xff, 0x07
};

/* checkbox x */
static const int checkbox_x_w = 11;
static const int checkbox_x_h = 11;
static unsigned char checkbox_x_bits[] = {
	0x00, 0x00, 0x00, 0x00, 0x04, 0x01, 0x88, 0x00, 0x50, 0x00, 0x20, 0x00,
	0x50, 0x00, 0x88, 0x00, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00
};

/*
 *
 * local types
 *
 */

/* frame */
typedef struct frame_t {
	eui_vec2_t pos;
	eui_vec2_t size;
	eui_vec2_t align;
} frame_t;

/*
 *
 * local variables
 *
 */

/* misc */
#ifndef sgn
#define sgn(x) ((x < 0) ? -1 : ((x > 0) ? 1 : 0))
#endif

/* frames */
#define MAX_FRAMES (64)
static frame_t frames[MAX_FRAMES] = {0};
static int frame_index = 0;

/* destination pixelmap */
static eui_pixelmap_t drawdest = {0};
#define PIXEL(pm, x, y) (pm).pixels[(y) * (pm).pitch + (x)]

/* event handling */
#define MAX_EVENTS (32)
static eui_event_t events[MAX_EVENTS] = {0};
static int num_events = 0;

/* input state */
static eui_vec2_t mouse = {0};
static int button = 0;

/* keyboard state */
#define MAX_KEYS (256)
#define KEY_BUFFER_SIZE (64)
#define KEY_BUFFER_ADVANCE(x) ((x) = ((x) + 1) & (KEY_BUFFER_SIZE - 1))
static bool keys[MAX_KEYS] = {0};
static int key_buffer[KEY_BUFFER_SIZE] = {0};
static int key_buffer_ridx = 0;
static int key_buffer_widx = 0;

/* configuration state */
#if (EUI_PIXEL_DEPTH == 8)
/* assumes vga palette */
static eui_config_t config = {
	{0, 15, 15, 0, 0, 15, 1} /* button */
};
#else
static eui_config_t config = {0};
#endif

/*
 *
 * local functions
 *
 */

/* draw font8x8 bitmap at pos */
static void eui_font8x8(eui_vec2_t pos, const unsigned char *bitmap, eui_color_t color)
{
	int x, y;
	int xx, yy;

	for (x = 0; x < 8; x++)
	{
		for (y = 0; y < 8; y++)
		{
			if (bitmap[x] & 1 << y)
			{
				xx = pos.x + y;
				yy = pos.y + x;

				if (xx < 0 || xx >= drawdest.w || yy < 0 || yy >= drawdest.h)
					continue;

				PIXEL(drawdest, xx, yy) = color;
			}
		}
	}
}

/*
 *
 * basic transforms
 *
 */

/* transform point to current frame, with alignment */
void eui_transform_point(eui_vec2_t *pos)
{
	switch (frames[frame_index].align.x)
	{
		case EUI_ALIGN_START:
			pos->x += frames[frame_index].pos.x;
			break;
		case EUI_ALIGN_MIDDLE:
			pos->x += frames[frame_index].pos.x + frames[frame_index].size.x / 2;
			break;
		case EUI_ALIGN_END:
			pos->x += frames[frame_index].pos.x + frames[frame_index].size.x;
			break;
		default:
			break;
	}

	switch (frames[frame_index].align.y)
	{
		case EUI_ALIGN_START:
			pos->y += frames[frame_index].pos.y;
			break;
		case EUI_ALIGN_MIDDLE:
			pos->y += frames[frame_index].pos.y + frames[frame_index].size.y / 2;
			break;
		case EUI_ALIGN_END:
			pos->y += frames[frame_index].pos.y + frames[frame_index].size.y;
			break;
		default:
			break;
	}
}

/* transform box to current frame, with alignment */
void eui_transform_box(eui_vec2_t *pos, eui_vec2_t size)
{
	switch (frames[frame_index].align.x)
	{
		case EUI_ALIGN_START:
			pos->x += frames[frame_index].pos.x;
			break;
		case EUI_ALIGN_MIDDLE:
			pos->x += frames[frame_index].pos.x + frames[frame_index].size.x / 2 - size.x / 2;
			break;
		case EUI_ALIGN_END:
			pos->x += frames[frame_index].pos.x + frames[frame_index].size.x - size.x;
			break;
		default:
			break;
	}

	switch (frames[frame_index].align.y)
	{
		case EUI_ALIGN_START:
			pos->y += frames[frame_index].pos.y;
			break;
		case EUI_ALIGN_MIDDLE:
			pos->y += frames[frame_index].pos.y + frames[frame_index].size.y / 2 - size.y / 2;
			break;
		case EUI_ALIGN_END:
			pos->y += frames[frame_index].pos.y + frames[frame_index].size.y - size.y;
			break;
		default:
			break;
	}
}

/* clip box to screen size, returns false if the shape will never be visible */
bool eui_clip_box(eui_vec2_t *pos, eui_vec2_t *size)
{
	/* it will never become visible */
	if (pos->x >= drawdest.w)
		return false;
	if (pos->y >= drawdest.h)
		return false;
	if (pos->x + size->x < 0)
		return false;
	if (pos->y + size->y < 0)
		return false;

	/* clip to top edge */
	if (pos->y < 0)
	{
		size->y += pos->y;
		pos->y = 0;
	}

	/* clip to bottom edge */
	if (pos->y + size->y >= drawdest.h)
	{
		size->y = drawdest.h - pos->y;
	}

	/* clip to left edge */
	if (pos->x < 0)
	{
		size->x += pos->x;
		pos->x = 0;
	}

	/* clip to right edge */
	if (pos->x + size->x >= drawdest.w)
	{
		size->x = drawdest.w - pos->x;
	}

	return true;
}

/*
 *
 * frame handling
 *
 */

/* go to subframe, transformed from current frame */
void eui_push_frame(eui_vec2_t pos, eui_vec2_t size)
{
	eui_transform_box(&pos, size);

	frame_index++;

	frames[frame_index].pos = pos;
	frames[frame_index].size = size;
	frames[frame_index].align.x = EUI_ALIGN_START;
	frames[frame_index].align.y = EUI_ALIGN_START;
}

/* return to parent frame */
void eui_pop_frame(void)
{
	if (frame_index)
		frame_index--;
}

/* reset all frame transforms */
void eui_reset_frame(void)
{
	frame_index = 0;
}

/* set current frame alignment */
void eui_set_align(int xalign, int yalign)
{
	frames[frame_index].align.x = xalign;
	frames[frame_index].align.y = yalign;
}

/*
 *
 * event handling
 *
 */

/* push event to the queue */
void eui_push_event(eui_event_t event)
{
	if (num_events == MAX_EVENTS - 1)
	{
		printf("EUI WARNING: Event queue exhausted!\n");
		return;
	}

	events[++num_events] = event;
}

/* pop event from the top of the queue */
int eui_pop_event(eui_event_t *out)
{
	if (!num_events)
	{
		*out = (eui_event_t){0};
		return 0;
	}

	*out = events[num_events];
	events[num_events] = (eui_event_t){0};
	num_events--;

	return num_events + 1;
}

/* push key to the queue */
void eui_push_key(int scancode)
{
	key_buffer[key_buffer_widx] = scancode;
	KEY_BUFFER_ADVANCE(key_buffer_widx);
	if (key_buffer_widx == key_buffer_ridx)
		KEY_BUFFER_ADVANCE(key_buffer_ridx);
}

/* pop key from the top of the queue */
int eui_pop_key(void)
{
	int res = -1;

	if (key_buffer_ridx == key_buffer_widx)
		return res;

	res = key_buffer[key_buffer_ridx];
	KEY_BUFFER_ADVANCE(key_buffer_ridx);

	return res;
}

/* reset keyboard queue */
static void eui_reset_key(void)
{
	key_buffer_ridx = key_buffer_widx = 0;
}

/*
 *
 * begin/end
 *
 */

/* begin eui with given pixelmap destination */
bool eui_begin(eui_pixelmap_t dest)
{
	eui_event_t event;

	/* sanity check */
	if (!dest.w || !dest.h || !dest.pitch || !dest.pixels)
		return false;

	/* set draw destination */
	drawdest = dest;

	/* reset keyboard queue */
	eui_reset_key();

	/* process event queue */
	while (eui_pop_event(&event))
	{
		switch (event.type)
		{
			case EUI_EVENT_KEY_DOWN:
				keys[event.key.scancode] = true;
				eui_push_key(event.key.scancode);
				break;

			case EUI_EVENT_KEY_UP:
				keys[event.key.scancode] = false;
				break;

			case EUI_EVENT_MOUSE:
				mouse.x = event.mouse.x;
				mouse.y = event.mouse.y;
				break;

			case EUI_EVENT_BUTTON_DOWN:
				button = 1;
				break;

			case EUI_EVENT_BUTTON_UP:
				button = 0;
				break;
		}
	}

	/* reset frame state */
	eui_reset_frame();

	/* push screen frame */
	eui_push_frame(EUI_VEC2(0, 0), EUI_VEC2(drawdest.w, drawdest.h));

	return true;
}

/* end eui */
void eui_end(void)
{

}

/*
 *
 * configuration
 *
 */

/* get modifiable config struct */
eui_config_t *eui_get_config(void)
{
	return &config;
}

/*
 *
 * utilities
 *
 */

/* get dimensions of text string, with newlines */
eui_vec2_t eui_get_text_size(char *s)
{
	int c;
	eui_vec2_t pos;
	eui_vec2_t size;
	int lastx = 0;

	pos.x = 0;
	pos.y = 0;

	/* find newlines in string */
	while ((c = *s++))
	{
		if (c == '\n')
		{
			pos.y += 1;
			lastx = pos.x;
			pos.x = 0;
		}
		else
		{
			pos.x += 1;
		}
	}

	size.x = lastx > pos.x ? lastx * 8 : pos.x * 8;
	size.y = (pos.y + 1) * 8;

	return size;
}

/* returns true if the mouse cursor is hovering over the given area */
bool eui_is_hovered(eui_vec2_t pos, eui_vec2_t size)
{
	eui_transform_box(&pos, size);

	if (mouse.x < pos.x || mouse.x > pos.x + size.x)
		return false;
	if (mouse.y < pos.y || mouse.y > pos.y + size.y)
		return false;
	return true;
}

/* clear screen with color */
void eui_clear(eui_color_t color)
{
	memset(drawdest.pixels, color, drawdest.h * drawdest.pitch);
}

/* draw built-in cursor */
void eui_cursor(eui_color_t color)
{
	eui_font8x8(EUI_VEC2(mouse.x - 3, mouse.y - 3), font8x8_basic['x'], color);
}

/*
 *
 * drawing primitives
 *
 */

/* draw filled box at pos, clipped but not transformed */
static void eui_filled_box_absolute(eui_vec2_t pos, eui_vec2_t size, eui_color_t color)
{
	int y;

	if (!eui_clip_box(&pos, &size))
		return;

	for (y = pos.y; y < pos.y + size.y; y++)
	{
		memset(&PIXEL(drawdest, pos.x, y), color, size.x * sizeof(eui_color_t));
	}
}

/* draw filled box at pos, transformed */
void eui_filled_box(eui_vec2_t pos, eui_vec2_t size, eui_color_t color)
{
	eui_transform_box(&pos, size);

	eui_filled_box_absolute(pos, size, color);
}

/* draw hollow box at pos, transformed */
void eui_border_box(eui_vec2_t pos, eui_vec2_t size, int width, eui_color_t color)
{
	eui_transform_box(&pos, size);

	/* top line */
	eui_filled_box_absolute(pos, EUI_VEC2(size.x, width), color);

	/* bottom line */
	eui_filled_box_absolute(EUI_VEC2(pos.x, pos.y + size.y - width), EUI_VEC2(size.x, width), color);

	/* left line */
	eui_filled_box_absolute(EUI_VEC2(pos.x, pos.y + width), EUI_VEC2(width, size.y - width * 2), color);

	/* right line */
	eui_filled_box_absolute(EUI_VEC2(pos.x + size.x - width, pos.y + width), EUI_VEC2(width, size.y - width * 2), color);
}

/* draw text at pos, transformed */
void eui_text(eui_vec2_t pos, eui_color_t color, char *s)
{
	eui_vec2_t size;
	int c;
	int start_x;
	size_t len = 0;
	char *ptr;

	/* get text size */
	size = eui_get_text_size(s);

	/* transform to size */
	eui_transform_box(&pos, size);

	/* draw string */
	start_x = pos.x;
	while ((c = *s++))
	{
		if (c == '\n')
		{
			switch (frames[frame_index].align.x)
			{
				case EUI_ALIGN_START:
					/* set next string position */
					pos.x = start_x;
					pos.y += 8;
					break;

				case EUI_ALIGN_MIDDLE:
					/* get length of next string chunk */
					ptr = s;
					while (*ptr && *ptr != '\n') ptr++;
					len = ptr - s;
					/* set next string position */
					pos.x = start_x + (size.x / 2) - ((len * 8) / 2);
					pos.y += 8;
					break;

				case EUI_ALIGN_END:
					/* get length of next string chunk */
					ptr = s;
					while (*ptr && *ptr != '\n') ptr++;
					len = ptr - s;
					/* set next string position */
					pos.x = start_x + size.x - (len * 8);
					pos.y += 8;
					break;
			}
		}
		else
		{
			eui_font8x8(pos, font8x8_basic[c], color);
			pos.x += 8;
		}
	}
}

/* draw formatted text at pos, transformed */
void eui_textf(eui_vec2_t pos, eui_color_t color, char *s, ...)
{
	static char text[1024];
	va_list args;

	va_start(args, s);
	vsnprintf(text, sizeof(text), s, args);
	va_end(args);

	eui_text(pos, color, text);
}

/* scan triangle edge and add to edge table */
static void eui_triangle_scan_edge(eui_vec2_t p0, eui_vec2_t p1, int edge_table[drawdest.h][2])
{
	int sx, sy, dx1, dy1, dx2, dy2, x, y, m, n, k, cnt;

	sx = p1.x - p0.x;
	sy = p1.y - p0.y;

	if (sx > 0)
		dx1 = 1;
	else if (sx < 0)
		dx1 = -1;
	else
		dx1 = 0;

	if (sy > 0)
		dy1 = 1;
	else if (sy < 0)
		dy1 = -1;
	else
		dy1 = 0;

	m = abs(sx);
	n = abs(sy);
	dx2 = dx1;
	dy2 = 0;

	if (m < n)
	{
		m = abs(sy);
		n = abs(sx);
		dx2 = 0;
		dy2 = dy1;
	}

	x = p0.x;
	y = p0.y;
	cnt = m + 1;
	k = n / 2;

	while (cnt--)
	{
		if (y >= 0 && y < drawdest.h)
		{
			if (x < edge_table[y][0])
				edge_table[y][0] = x;
			if (x > edge_table[y][1])
				edge_table[y][1] = x;
		}

		k += n;

		if (k < m)
		{
			x += dx2;
			y += dy2;
		}
		else
		{
			k -= m;
			x += dx1;
			y += dy1;
		}
	}
}

/* draw filled triangle with provided points, transformed */
void eui_filled_triangle(eui_vec2_t p0, eui_vec2_t p1, eui_vec2_t p2, eui_color_t color)
{
	int x, y, len;
	int edge_table[drawdest.h][2];

	/* init edge table */
	for (y = 0; y < drawdest.h; y++)
	{
		edge_table[y][0] = INT32_MAX;
		edge_table[y][1] = INT32_MIN;
	}

	/* transform points */
	eui_transform_point(&p0);
	eui_transform_point(&p1);
	eui_transform_point(&p2);

	/* scan triangle edges */
	eui_triangle_scan_edge(p0, p1, edge_table);
	eui_triangle_scan_edge(p1, p2, edge_table);
	eui_triangle_scan_edge(p2, p0, edge_table);

	for (y = 0; y < drawdest.h; y++)
	{
		if (edge_table[y][1] >= edge_table[y][0])
		{
			x = edge_table[y][0];
			len = 1 + edge_table[y][1] - edge_table[y][0];

			while (len--)
			{
				PIXEL(drawdest, x++, y) = color;
			}
		}
	}
}

/* draw line from p0 to p1, transformed */
void eui_line(eui_vec2_t p0, eui_vec2_t p1, eui_color_t color)
{
	int i, dx, dy, sdx, sdy, dxabs, dyabs, x, y, px, py;

	/* transform points */
	eui_transform_point(&p0);
	eui_transform_point(&p1);

	/* the horizontal distance of the line */
	dx = p1.x - p0.x;

	/* the vertical distance of the line */
	dy = p1.y - p0.y;

	dxabs = abs(dx);
	dyabs = abs(dy);

	sdx = sgn(dx);
	sdy = sgn(dy);

	x = dyabs >> 1;
	y = dxabs >> 1;

	px = p0.x;
	py = p0.y;

	if (px >= 0 && px < drawdest.w && py >= 0 && py < drawdest.h)
		PIXEL(drawdest, px, py) = color;

	if (dxabs >= dyabs)
	{
		/* the line is more horizontal than vertical */
		for (i = 0; i < dxabs; i++)
		{
			y += dyabs;

			if (y >= dxabs)
			{
				y -= dxabs;
				py += sdy;
			}

			px += sdx;

			if (px < 0 || px >= drawdest.w)
				continue;
			if (py < 0 || py >= drawdest.h)
				continue;

			PIXEL(drawdest, px, py) = color;
		}
	}
	else
	{
		/* the line is more vertical than horizontal */
		for (i = 0; i < dyabs; i++)
		{
			x += dxabs;

			if ( x >= dyabs)
			{
				x -= dyabs;
				px += sdx;
			}

			py += sdy;

			if (px < 0 || px >= drawdest.w)
				continue;
			if (py < 0 || py >= drawdest.h)
				continue;

			PIXEL(drawdest, px, py) = color;
		}
	}
}

/* draw pixelmap, transformed */
void eui_pixelmap(eui_vec2_t pos, eui_pixelmap_t pixelmap)
{
	int y, yy;
	eui_vec2_t size;
	eui_vec2_t ofs;

	/* transform */
	size = EUI_VEC2(pixelmap.w, pixelmap.h);
	eui_transform_box(&pos, size);

	/* save current pos */
	ofs = pos;

	/* clip */
	if (!eui_clip_box(&pos, &size))
		return;

	/* calculate pixelmap ofs */
	if (ofs.x < pos.x)
		ofs.x = pos.x - ofs.x;
	else
		ofs.x = 0;
	if (ofs.y < pos.y)
		ofs.y = pos.y - ofs.y;
	else
		ofs.y = 0;

	/* draw */
	for (y = ofs.y; y < size.y; y++)
	{
		yy = pos.y + y - ofs.y;
		memcpy(&PIXEL(drawdest, pos.x, yy), &PIXEL(pixelmap, ofs.x, y), size.x);
	}
}

/* draw xbm graphic, transformed */
void eui_xbm(eui_vec2_t pos, eui_color_t color, int w, int h, unsigned char *bitmap)
{
	int x, y, xx, yy;
	int pitch;

	/* transform */
	eui_transform_box(&pos, EUI_VEC2(w, h));

	/* draw graphic */
	pitch = w + (8 % w) - (w % 8);
	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			if (bitmap[(y * pitch + x) / 8] & 1 << (x % 8))
			{
				xx = pos.x + x;
				yy = pos.y + y;

				if (xx < 0 || xx >= drawdest.w || yy < 0 || yy >= drawdest.h)
					continue;

				PIXEL(drawdest, xx, yy) = color;
			}
		}
	}
}

/*
 *
 * widgets
 *
 */

/* fires callback function if pressed and returns true if hovered */
bool eui_button(eui_vec2_t pos, eui_vec2_t size, char *text, eui_callback callback, void *user)
{
	static bool clicked;
	bool hovered;

	hovered = eui_is_hovered(pos, size);

	if (hovered)
	{
		eui_filled_box(pos, size, config.button.bg_color_hover);
		eui_border_box(pos, size, config.button.border_width, config.button.border_color_hover);
		eui_push_frame(pos, size);
		eui_set_align(EUI_ALIGN_MIDDLE, EUI_ALIGN_MIDDLE);
		eui_text(EUI_VEC2(0, 0), config.button.text_color_hover, text);
		eui_pop_frame();
	}
	else
	{
		eui_filled_box(pos, size, config.button.bg_color);
		eui_border_box(pos, size, config.button.border_width, config.button.border_color);
		eui_push_frame(pos, size);
		eui_set_align(EUI_ALIGN_MIDDLE, EUI_ALIGN_MIDDLE);
		eui_text(EUI_VEC2(0, 0), config.button.text_color, text);
		eui_pop_frame();
	}

	if (hovered && button && !clicked)
	{
		callback(user);
		clicked = true;
	}

	if (!button)
		clicked = false;

	return hovered;
}

/* bool checkbox */
void eui_checkbox(eui_vec2_t pos, char *label, eui_color_t color, bool *value)
{
	static bool clicked;
	bool hovered;
	eui_vec2_t size;

	if (!value)
		return;

	/* box border */
	size = EUI_VEC2(11, 11);
	eui_xbm(pos, color, checkbox_border_w, checkbox_border_h, checkbox_border_bits);

	/* toggle on click */
	hovered = eui_is_hovered(pos, size);
	if (hovered && button && !clicked)
	{
		*value = !*value;
		clicked = true;
	}
	if (!button)
		clicked = false;

	/* draw x */
	if (*value)
		eui_xbm(pos, color, checkbox_x_w, checkbox_x_h, checkbox_x_bits);

	/* label */
	eui_text(EUI_VEC2(pos.x + 13, pos.y + 2), color, label);
}
