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

#pragma once
#ifndef _EUI_H_
#define _EUI_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/* element alignment */
enum {
	EUI_ALIGN_START,
	EUI_ALIGN_MIDDLE,
	EUI_ALIGN_END
};

/* true/false/unset */
enum {
	EUI_FALSE = 0,
	EUI_TRUE = 1
};

/* button type */
enum {
	EUI_BUTTON_LEFT,
	EUI_BUTTON_RIGHT
};

/* event type */
enum {
	EUI_EVENT_NONE,
	EUI_EVENT_KEY_DOWN,
	EUI_EVENT_KEY_UP,
	EUI_EVENT_MOUSE,
	EUI_EVENT_BUTTON_DOWN,
	EUI_EVENT_BUTTON_UP
};

/* keyboard scancodes */
enum {
	EUI_SCANCODE_ESCAPE = 0x01,
	EUI_SCANCODE_1 = 0x02,
	EUI_SCANCODE_2 = 0x03,
	EUI_SCANCODE_3 = 0x04,
	EUI_SCANCODE_4 = 0x05,
	EUI_SCANCODE_5 = 0x06,
	EUI_SCANCODE_6 = 0x07,
	EUI_SCANCODE_7 = 0x08,
	EUI_SCANCODE_8 = 0x09,
	EUI_SCANCODE_9 = 0x0A,
	EUI_SCANCODE_0 = 0x0B,
	EUI_SCANCODE_MINUS = 0x0C,
	EUI_SCANCODE_EQUALS = 0x0D,
	EUI_SCANCODE_BACKSPACE = 0x0E,
	EUI_SCANCODE_TAB = 0x0F,
	EUI_SCANCODE_Q = 0x10,
	EUI_SCANCODE_W = 0x11,
	EUI_SCANCODE_E = 0x12,
	EUI_SCANCODE_R = 0x13,
	EUI_SCANCODE_T = 0x14,
	EUI_SCANCODE_Y = 0x15,
	EUI_SCANCODE_U = 0x16,
	EUI_SCANCODE_I = 0x17,
	EUI_SCANCODE_O = 0x18,
	EUI_SCANCODE_P = 0x19,
	EUI_SCANCODE_LEFTBRACKET = 0x1A,
	EUI_SCANCODE_RIGHTBRACKET = 0x1B,
	EUI_SCANCODE_ENTER = 0x1C,
	EUI_SCANCODE_CONTROL = 0x1D,
	EUI_SCANCODE_A = 0x1E,
	EUI_SCANCODE_S = 0x1F,
	EUI_SCANCODE_D = 0x20,
	EUI_SCANCODE_F = 0x21,
	EUI_SCANCODE_G = 0x22,
	EUI_SCANCODE_H = 0x23,
	EUI_SCANCODE_J = 0x24,
	EUI_SCANCODE_K = 0x25,
	EUI_SCANCODE_L = 0x26,
	EUI_SCANCODE_SEMICOLON = 0x27,
	EUI_SCANCODE_QUOTE = 0x28,
	EUI_SCANCODE_TILDE = 0x29,
	EUI_SCANCODE_LSHIFT = 0x2A,
	EUI_SCANCODE_BACKSLASH = 0x2B,
	EUI_SCANCODE_Z = 0x2C,
	EUI_SCANCODE_X = 0x2D,
	EUI_SCANCODE_C = 0x2E,
	EUI_SCANCODE_V = 0x2F,
	EUI_SCANCODE_B = 0x30,
	EUI_SCANCODE_N = 0x31,
	EUI_SCANCODE_M = 0x32,
	EUI_SCANCODE_COMMA = 0x33,
	EUI_SCANCODE_PERIOD = 0x34,
	EUI_SCANCODE_SLASH = 0x35,
	EUI_SCANCODE_RSHIFT = 0x36,
	EUI_SCANCODE_MULTIPLY = 0x37,
	EUI_SCANCODE_ALT = 0x38,
	EUI_SCANCODE_SPACE = 0x39,
	EUI_SCANCODE_CAPSLOCK = 0x3A,
	EUI_SCANCODE_F1 = 0x3B,
	EUI_SCANCODE_F2 = 0x3C,
	EUI_SCANCODE_F3 = 0x3D,
	EUI_SCANCODE_F4 = 0x3E,
	EUI_SCANCODE_F5 = 0x3F,
	EUI_SCANCODE_F6 = 0x40,
	EUI_SCANCODE_F7 = 0x41,
	EUI_SCANCODE_F8 = 0x42,
	EUI_SCANCODE_F9 = 0x43,
	EUI_SCANCODE_F10 = 0x44,
	EUI_SCANCODE_NUMLOCK = 0x45,
	EUI_SCANCODE_SCROLLLOCK = 0x46,
	EUI_SCANCODE_HOME = 0x47,
	EUI_SCANCODE_UP = 0x48,
	EUI_SCANCODE_PAGEUP = 0x49,
	EUI_SCANCODE_LEFT = 0x4B,
	EUI_SCANCODE_RIGHT = 0x4D,
	EUI_SCANCODE_PLUS = 0x4E,
	EUI_SCANCODE_END = 0x4F,
	EUI_SCANCODE_DOWN = 0x50,
	EUI_SCANCODE_PAGEDOWN = 0x51,
	EUI_SCANCODE_INSERT = 0x52,
	EUI_SCANCODE_DELETE = 0x53,
	EUI_SCANCODE_F11 = 0x57,
	EUI_SCANCODE_F12 = 0x58
};

/*
 *
 * eui types
 *
 */

/* default pixel depth is 8bpp */
#ifndef EUI_PIXEL_DEPTH
#define EUI_PIXEL_DEPTH (8)
#endif

/* pixel color type */
#if (EUI_PIXEL_DEPTH == 8)
typedef uint8_t eui_color_t;
#elif (EUI_PIXEL_DEPTH == 16)
typedef uint16_t eui_color_t;
#elif (EUI_PIXEL_DEPTH == 32)
typedef uint32_t eui_color_t;
#else
#error Unsupported pixel depth!
#endif

/* vec2 */
typedef struct eui_vec2_t {
	int x, y;
} eui_vec2_t;

/* event */
typedef union eui_event_t {
	int type;
	struct { int type; int scancode; } key;
	struct { int type; int x; int y; int xrel; int yrel; } mouse;
	struct { int type; int x; int y; int button; } button;
} eui_event_t;

/* pixelmap */
typedef struct eui_pixelmap_t {
	int w;
	int h;
	int pitch;
	eui_color_t *pixels;
} eui_pixelmap_t;

/* general callback function */
typedef void eui_callback(void *user);

/*
 *
 * helper macros
 *
 */

/* create vec2 */
#define EUI_VEC2(x, y) (eui_vec2_t){(x), (y)}

/* create pixelmap */
#define EUI_PIXELMAP(w, h, pitch, pixels) (eui_pixelmap_t){(w), (h), (pitch), (pixels)}

/*
 *
 * basic transforms
 *
 */

/* transform point to current frame, with alignment */
void eui_transform_point(eui_vec2_t *pos);

/* transform box to current frame, with alignment */
void eui_transform_box(eui_vec2_t *pos, eui_vec2_t size);

/* clip box to screen size, returns false if the shape will never be visible */
bool eui_clip_box(eui_vec2_t *pos, eui_vec2_t *size);

/*
 *
 * frame handling
 *
 */

/* go to subframe, transformed from current frame */
void eui_push_frame(eui_vec2_t pos, eui_vec2_t size);

/* return to parent frame */
void eui_pop_frame(void);

/* reset all frame transforms */
void eui_reset_frame(void);

/* set current frame alignment */
void eui_set_align(int xalign, int yalign);

/*
 *
 * event handling
 *
 */

/* push event to the queue */
void eui_push_event(eui_event_t event);

/* pop event from the top of the queue */
int eui_pop_event(eui_event_t *out);

/*
 *
 * begin/end
 *
 */

/* begin eui with given pixelmap destination */
bool eui_begin(eui_pixelmap_t dest);

/* end eui */
void eui_end(void);

/*
 *
 * utilities
 *
 */

/* get dimensions of text string, with newlines */
eui_vec2_t eui_get_text_size(char *s);

/* returns true if the mouse cursor is hovering over the given area */
bool eui_is_hovered(eui_vec2_t pos, eui_vec2_t size);

/* clear screen with color */
void eui_clear(eui_color_t color);

/* draw built-in cursor */
void eui_cursor(eui_color_t color);

/*
 *
 * drawing primitives
 *
 */

/* draw filled box at pos, transformed */
void eui_filled_box(eui_vec2_t pos, eui_vec2_t size, eui_color_t color);

/* draw hollow box at pos, transformed */
void eui_border_box(eui_vec2_t pos, eui_vec2_t size, int width, eui_color_t color);

/* draw text at pos, transformed */
void eui_text(eui_vec2_t pos, eui_color_t color, char *s);

/* draw formatted text at pos, transformed */
void eui_textf(eui_vec2_t pos, eui_color_t color, char *s, ...);

/* draw filled triangle with provided points, transformed */
void eui_filled_triangle(eui_vec2_t p0, eui_vec2_t p1, eui_vec2_t p2, eui_color_t color);

/* draw line from p0 to p1, transformed */
void eui_line(eui_vec2_t p0, eui_vec2_t p1, eui_color_t color);

/* draw pixelmap, transformed */
void eui_pixelmap(eui_vec2_t pos, eui_pixelmap_t pixelmap);

/* draw xbm graphic, transformed */
void eui_xbm(eui_vec2_t pos, eui_color_t color, int w, int h, char *bits);

/*
 *
 * widgets
 *
 */

/* fires callback function if pressed and returns true if hovered */
bool eui_button(eui_vec2_t pos, eui_vec2_t size, char *text, eui_callback callback, void *user);

/* bool checkbox */
void eui_checkbox(eui_vec2_t pos, char *label, eui_color_t color, bool *value);

#ifdef __cplusplus
}
#endif
#endif /* _EUI_H_ */
