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

#pragma once
#ifndef _EUI_H_
#define _EUI_H_
#ifdef __cplusplus
extern "C" {
#endif

/*
 *
 * macros
 *
 */

#ifndef EUI_MAX_FRAMES
#define EUI_MAX_FRAMES (128)
#endif

#ifndef EUI_MAX_DRAWCMDS
#define EUI_MAX_DRAWCMDS (1024)
#endif

#define EUI_UNUSED(x) ((void)(x))

/*
 *
 * enums
 *
 */

/* element alignment */
enum {
	EUI_ALIGN_START,
	EUI_ALIGN_MIDDLE,
	EUI_ALIGN_END
};

/* true/false */
enum {
	EUI_FALSE,
	EUI_TRUE
};

/* font */
enum {
	EUI_FONT_8X8,
	EUI_FONT_8X14
};

/*
 *
 * function prototypes
 *
 */

/*
 * init/quit
 */

/* initialize library with writeable destination buffer */
/* returns EUI_FALSE on failure */
int eui_init(int w, int h, int bpp, int pitch, void *buffer);

/* shutdown library and clear state */
void eui_quit(void);

/*
 * context handling
 */

/* begin new eui context and create root frame */
/* returns EUI_FALSE on failure */
int eui_context_begin(void);

/* end current eui context and destroy root frame */
void eui_context_end(void);

/*
 * frame handling
 */

/* create and enter new child frame, transformed from the current frame */
/* returns EUI_FALSE on failure */
int eui_frame_push(int x, int y, int w, int h);

/* return to parent frame */
void eui_frame_pop(void);

/* set alignment for elements in the current frame */
void eui_frame_align_set(int align_x, int align_y);

/* get alignment for elements in the current frame */
void eui_frame_align_get(int *align_x, int *align_y);

/* if set to EUI_TRUE, elements will be clipped to the current frame edges */
void eui_frame_clip_set(int clip);

/* returns EUI_TRUE if clipping is enabled for this frame  */
int eui_frame_clip_get(void);

/* offset z value of current frame */
void eui_frame_z_offset(int z);

/* set z value of current frame */
void eui_frame_z_set(int z);

/* get z value of current frame */
int eui_frame_z_get(void);

/*
 * font handling
 */

/* set font */
void eui_font_set(int font);

/* get font */
int eui_font_get(void);

/*
 * utilities
 */

/* clear screen with color */
void eui_screen_clear(unsigned int color);

/* get cell dimensions of text, with newline and alignment handling */
/* returns EUI_FALSE on failure */
int eui_get_text_dimensions(int *w, int *h, char *s);

/* convert error code to printable string */
const char *eui_error_string(int code);

/*
 * drawing primitives
 */

/* draw box */
void eui_draw_box(int x, int y, int w, int h, unsigned int color);

/* draw box border */
void eui_draw_box_border(int x, int y, int w, int h, int width, unsigned int color);

/* draw text */
void eui_draw_text(int x, int y, unsigned int color, char *s);

/* draw formatted text */
void eui_draw_textf(int x, int y, unsigned int color, char *s, ...);

#ifdef __cplusplus
}
#endif
#endif /* _EUI_H_ */
