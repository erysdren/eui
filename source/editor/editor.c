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
 * EDITOR.C
 *
 */

#include <stdio.h>
#include <stdint.h>

#include "tinyfiledialogs.h"

#include "eui_sdl2.h"

#define WIDTH (640)
#define HEIGHT (480)
#define PIXEL_WIDTH (7)
#define PIXEL_HEIGHT (7)
#define BITMAP_WIDTH (64)
#define BITMAP_HEIGHT (64)
#define ENTRY_WIDTH (11)
#define ENTRY_HEIGHT (11)
#define MAX_UNDOS (16)

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef CLAMP
#define CLAMP(a, min, max) MIN(MAX(a, min), max)
#endif

#ifndef SGN
#define SGN(x) ((x < 0) ? -1 : ((x > 0) ? 1 : 0))
#endif

/* palette */
unsigned char palette[768] = {
	0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x10, 0x10, 0x10, 0x18, 0x18, 0x18,
	0x20, 0x20, 0x20, 0x28, 0x28, 0x28, 0x30, 0x30, 0x30, 0x38, 0x38, 0x38,
	0x40, 0x40, 0x40, 0x48, 0x48, 0x48, 0x50, 0x50, 0x50, 0x58, 0x58, 0x58,
	0x60, 0x60, 0x60, 0x68, 0x68, 0x68, 0x70, 0x70, 0x70, 0x78, 0x78, 0x78,
	0x80, 0x80, 0x80, 0x88, 0x88, 0x88, 0x90, 0x90, 0x90, 0x98, 0x98, 0x98,
	0xa0, 0xa0, 0xa0, 0xa8, 0xa8, 0xa8, 0xb0, 0xb0, 0xb0, 0xb8, 0xb8, 0xb8,
	0xc0, 0xc0, 0xc0, 0xc8, 0xc8, 0xc8, 0xd0, 0xd0, 0xd0, 0xd8, 0xd8, 0xd8,
	0xe0, 0xe0, 0xe0, 0xe8, 0xe8, 0xe8, 0xf0, 0xf0, 0xf0, 0xfc, 0xfc, 0xfc,
	0x00, 0x00, 0x00, 0x04, 0x04, 0x08, 0x0c, 0x0c, 0x10, 0x10, 0x10, 0x18,
	0x18, 0x18, 0x20, 0x1c, 0x1c, 0x28, 0x24, 0x24, 0x30, 0x28, 0x28, 0x38,
	0x30, 0x30, 0x40, 0x34, 0x34, 0x48, 0x3c, 0x3c, 0x50, 0x44, 0x44, 0x58,
	0x48, 0x48, 0x60, 0x50, 0x50, 0x68, 0x54, 0x54, 0x70, 0x5c, 0x5c, 0x78,
	0x60, 0x60, 0x80, 0x68, 0x68, 0x88, 0x6c, 0x6c, 0x90, 0x74, 0x74, 0x98,
	0x78, 0x78, 0xa0, 0x80, 0x80, 0xa8, 0x88, 0x88, 0xb0, 0x8c, 0x8c, 0xb8,
	0x94, 0x94, 0xc0, 0x98, 0x98, 0xc8, 0xa0, 0xa0, 0xd0, 0xa4, 0xa4, 0xd8,
	0xac, 0xac, 0xe0, 0xb0, 0xb0, 0xe8, 0xb8, 0xb8, 0xf0, 0xc0, 0xc0, 0xfc,
	0x00, 0x00, 0x00, 0x08, 0x04, 0x04, 0x10, 0x0c, 0x08, 0x18, 0x10, 0x0c,
	0x20, 0x18, 0x10, 0x28, 0x1c, 0x14, 0x30, 0x24, 0x18, 0x38, 0x28, 0x1c,
	0x40, 0x30, 0x20, 0x48, 0x34, 0x24, 0x50, 0x3c, 0x28, 0x58, 0x44, 0x2c,
	0x60, 0x48, 0x30, 0x68, 0x50, 0x34, 0x70, 0x54, 0x38, 0x78, 0x5c, 0x3c,
	0x80, 0x60, 0x40, 0x88, 0x68, 0x44, 0x90, 0x6c, 0x48, 0x98, 0x74, 0x4c,
	0xa0, 0x78, 0x50, 0xa8, 0x80, 0x54, 0xb0, 0x88, 0x58, 0xb8, 0x8c, 0x5c,
	0xc0, 0x94, 0x60, 0xc8, 0x98, 0x64, 0xd0, 0xa0, 0x68, 0xd8, 0xa4, 0x6c,
	0xe0, 0xac, 0x70, 0xe8, 0xb0, 0x74, 0xf0, 0xb8, 0x78, 0xfc, 0xc0, 0x80,
	0x00, 0x00, 0x00, 0x08, 0x04, 0x00, 0x10, 0x08, 0x04, 0x18, 0x0c, 0x08,
	0x20, 0x10, 0x0c, 0x28, 0x14, 0x0c, 0x30, 0x18, 0x10, 0x38, 0x1c, 0x14,
	0x40, 0x20, 0x18, 0x48, 0x24, 0x18, 0x50, 0x28, 0x1c, 0x58, 0x2c, 0x20,
	0x60, 0x30, 0x24, 0x68, 0x34, 0x28, 0x70, 0x38, 0x28, 0x78, 0x3c, 0x2c,
	0x80, 0x40, 0x30, 0x88, 0x44, 0x34, 0x90, 0x48, 0x34, 0x98, 0x4c, 0x38,
	0xa0, 0x50, 0x3c, 0xa8, 0x54, 0x40, 0xb0, 0x58, 0x44, 0xb8, 0x5c, 0x44,
	0xc0, 0x60, 0x48, 0xc8, 0x64, 0x4c, 0xd0, 0x68, 0x50, 0xd8, 0x6c, 0x50,
	0xe0, 0x70, 0x54, 0xe8, 0x74, 0x58, 0xf0, 0x78, 0x5c, 0xfc, 0x80, 0x60,
	0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x10, 0x04, 0x04, 0x18, 0x08, 0x08,
	0x20, 0x0c, 0x0c, 0x28, 0x0c, 0x0c, 0x30, 0x10, 0x10, 0x38, 0x14, 0x14,
	0x40, 0x18, 0x18, 0x48, 0x18, 0x18, 0x50, 0x1c, 0x1c, 0x58, 0x20, 0x20,
	0x60, 0x24, 0x24, 0x68, 0x28, 0x28, 0x70, 0x28, 0x28, 0x78, 0x2c, 0x2c,
	0x80, 0x30, 0x30, 0x88, 0x34, 0x34, 0x90, 0x34, 0x34, 0x98, 0x38, 0x38,
	0xa0, 0x3c, 0x3c, 0xa8, 0x40, 0x40, 0xb0, 0x44, 0x44, 0xb8, 0x44, 0x44,
	0xc0, 0x48, 0x48, 0xc8, 0x4c, 0x4c, 0xd0, 0x50, 0x50, 0xd8, 0x50, 0x50,
	0xe0, 0x54, 0x54, 0xe8, 0x58, 0x58, 0xf0, 0x5c, 0x5c, 0xfc, 0x60, 0x60,
	0x00, 0x00, 0x00, 0x04, 0x04, 0x08, 0x08, 0x08, 0x10, 0x0c, 0x0c, 0x18,
	0x10, 0x10, 0x20, 0x14, 0x14, 0x28, 0x18, 0x18, 0x30, 0x1c, 0x1c, 0x38,
	0x20, 0x20, 0x40, 0x24, 0x24, 0x48, 0x28, 0x28, 0x50, 0x2c, 0x2c, 0x58,
	0x30, 0x30, 0x60, 0x34, 0x34, 0x68, 0x38, 0x38, 0x70, 0x3c, 0x3c, 0x78,
	0x40, 0x40, 0x80, 0x44, 0x44, 0x88, 0x48, 0x48, 0x90, 0x4c, 0x4c, 0x98,
	0x50, 0x50, 0xa0, 0x54, 0x54, 0xa8, 0x58, 0x58, 0xb0, 0x5c, 0x5c, 0xb8,
	0x60, 0x60, 0xc0, 0x64, 0x64, 0xc8, 0x68, 0x68, 0xd0, 0x6c, 0x6c, 0xd8,
	0x70, 0x70, 0xe0, 0x74, 0x74, 0xe8, 0x78, 0x78, 0xf0, 0x80, 0x80, 0xfc,
	0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x04, 0x10, 0x04, 0x08, 0x18, 0x08,
	0x0c, 0x20, 0x0c, 0x0c, 0x28, 0x0c, 0x10, 0x30, 0x10, 0x14, 0x38, 0x14,
	0x18, 0x40, 0x18, 0x18, 0x48, 0x18, 0x1c, 0x50, 0x1c, 0x20, 0x58, 0x20,
	0x24, 0x60, 0x24, 0x28, 0x68, 0x28, 0x28, 0x70, 0x28, 0x2c, 0x78, 0x2c,
	0x30, 0x80, 0x30, 0x34, 0x88, 0x34, 0x34, 0x90, 0x34, 0x38, 0x98, 0x38,
	0x3c, 0xa0, 0x3c, 0x40, 0xa8, 0x40, 0x44, 0xb0, 0x44, 0x44, 0xb8, 0x44,
	0x48, 0xc0, 0x48, 0x4c, 0xc8, 0x4c, 0x50, 0xd0, 0x50, 0x50, 0xd8, 0x50,
	0x54, 0xe0, 0x54, 0x58, 0xe8, 0x58, 0x5c, 0xf0, 0x5c, 0x60, 0xfc, 0x60,
	0x00, 0x00, 0x00, 0x08, 0x04, 0x08, 0x10, 0x08, 0x10, 0x18, 0x0c, 0x18,
	0x20, 0x10, 0x20, 0x28, 0x14, 0x28, 0x30, 0x18, 0x30, 0x38, 0x1c, 0x38,
	0x40, 0x20, 0x40, 0x48, 0x24, 0x48, 0x50, 0x28, 0x50, 0x58, 0x2c, 0x58,
	0x60, 0x30, 0x60, 0x68, 0x34, 0x68, 0x70, 0x38, 0x70, 0x78, 0x3c, 0x78,
	0x80, 0x40, 0x80, 0x88, 0x44, 0x88, 0x90, 0x48, 0x90, 0x98, 0x4c, 0x98,
	0xa0, 0x50, 0xa0, 0xa8, 0x54, 0xa8, 0xb0, 0x58, 0xb0, 0xb8, 0x5c, 0xb8,
	0xc0, 0x60, 0xc0, 0xc8, 0x64, 0xc8, 0xd0, 0x68, 0xd0, 0xd8, 0x6c, 0xd8,
	0xe0, 0x70, 0xe0, 0xe8, 0x74, 0xe8, 0xf0, 0x78, 0xf0, 0xfc, 0x80, 0xfc
};

/* pen icon */
#define pen_width 16
#define pen_height 16
static unsigned char pen_bits[] = {
	0xff, 0xff, 0x01, 0x80, 0x01, 0x80, 0x01, 0x82, 0x01, 0x87, 0x01, 0x8e,
	0x81, 0x9c, 0xc1, 0x89, 0xe1, 0x83, 0xf1, 0x81, 0xf1, 0x80, 0x79, 0x80,
	0x19, 0x80, 0x01, 0x80, 0x01, 0x80, 0xff, 0xff
};

/* selected pen icon */
#define pen_selected_width 16
#define pen_selected_height 16
static unsigned char pen_selected_bits[] = {
	0x00, 0x00, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7d, 0xfe, 0x78, 0xfe, 0x71,
	0x7e, 0x63, 0x3e, 0x76, 0x1e, 0x7c, 0x0e, 0x7e, 0x0e, 0x7f, 0x86, 0x7f,
	0xe6, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0x00, 0x00
};

/* bucket icon */
#define bucket_width 16
#define bucket_height 16
static unsigned char bucket_bits[] = {
	0xff, 0xff, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x89, 0x81, 0xd1, 0x83,
	0x61, 0x9e, 0x71, 0xa4, 0x99, 0xa4, 0x0d, 0xae, 0x19, 0xab, 0xb1, 0xb9,
	0xe1, 0x90, 0x41, 0x80, 0x01, 0x80, 0xff, 0xff
};

/* selected bucket icon */
#define bucket_selected_width 16
#define bucket_selected_height 16
static unsigned char bucket_selected_bits[] = {
	0x00, 0x00, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0x76, 0x7e, 0x2e, 0x7c,
	0x9e, 0x61, 0x8e, 0x5b, 0x66, 0x5b, 0xf2, 0x51, 0xe6, 0x54, 0x4e, 0x46,
	0x1e, 0x6f, 0xbe, 0x7f, 0xfe, 0x7f, 0x00, 0x00
};

/* rect icon */
#define rect_width 16
#define rect_height 16
static unsigned char rect_bits[] = {
	0xff, 0xff, 0x01, 0x80, 0x01, 0x80, 0xf9, 0x9f, 0x09, 0x90, 0x09, 0x90,
	0x09, 0x90, 0x09, 0x90, 0x09, 0x90, 0x09, 0x90, 0x09, 0x90, 0x09, 0x90,
	0xf9, 0x9f, 0x01, 0x80, 0x01, 0x80, 0xff, 0xff
};

/* selected rect icon */
#define rect_selected_width 16
#define rect_selected_height 16
static unsigned char rect_selected_bits[] = {
	0x00, 0x00, 0xfe, 0x7f, 0xfe, 0x7f, 0x06, 0x60, 0xf6, 0x6f, 0xf6, 0x6f,
	0xf6, 0x6f, 0xf6, 0x6f, 0xf6, 0x6f, 0xf6, 0x6f, 0xf6, 0x6f, 0xf6, 0x6f,
	0x06, 0x60, 0xfe, 0x7f, 0xfe, 0x7f, 0x00, 0x00
};

/* filled rect icon */
#define filled_rect_width 16
#define filled_rect_height 16
static unsigned char filled_rect_bits[] = {
	0xff, 0xff, 0x01, 0x80, 0x01, 0x80, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f,
	0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f,
	0xf9, 0x9f, 0x01, 0x80, 0x01, 0x80, 0xff, 0xff
};

/* selected filled rect icon */
#define filled_rect_selected_width 16
#define filled_rect_selected_height 16
static unsigned char filled_rect_selected_bits[] = {
	0x00, 0x00, 0xfe, 0x7f, 0xfe, 0x7f, 0x06, 0x60, 0x06, 0x60, 0x06, 0x60,
	0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x06, 0x60,
	0x06, 0x60, 0xfe, 0x7f, 0xfe, 0x7f, 0x00, 0x00
};

/* bitmap */
static uint8_t bitmap[BITMAP_HEIGHT][BITMAP_WIDTH];
static uint8_t bitmap_history[MAX_UNDOS][BITMAP_HEIGHT][BITMAP_WIDTH];
static int current_bitmap = 0;
static int top_bitmap = 1;

/* temp layer */
int templayer[BITMAP_HEIGHT][BITMAP_WIDTH];

enum {
	TOOL_PEN,
	TOOL_FILL,
	TOOL_RECT,
	TOOL_FILLED_RECT
};

static int current_tool = TOOL_PEN;
static eui_color_t current_color = 0;

/* filter patterns for save/load dialogs */
static const char *filter_patterns[1] = {"*.bmp"};

static SDL_Window *window;
static SDL_Surface *surface8;
static SDL_Surface *surface32;
static SDL_Renderer *renderer;
static SDL_Texture *texture;
static SDL_Rect blit_rect;
static SDL_bool running;
static SDL_Color colors[256];

/* push bitmap to stack */
void bitmap_push(int redo)
{
	int i;

	/* it's a redo, not an edit */
	if (redo)
	{
		/* already at the top of the stack */
		if (current_bitmap >= top_bitmap)
			return;

		/* move to next bitmap */
		current_bitmap++;
		return;
	}

	if (current_bitmap == MAX_UNDOS - 1)
	{
		/* move bitmap stack down */
		for (i = 0; i < current_bitmap; i++)
		{
			memcpy(&bitmap_history[i], &bitmap_history[i + 1], sizeof(bitmap_history[i]));
		}
	}
	else
	{
		/* move to next bitmap */
		current_bitmap++;

		/* clear upper bitmap stack */
		for (i = current_bitmap; i < MAX_UNDOS; i++)
		{
			memset(&bitmap_history[i], 0, sizeof(bitmap_history[i]));
		}
	}

	/* copy current bitmap to next in stack */
	top_bitmap = current_bitmap;
	memcpy(&bitmap_history[current_bitmap], bitmap, sizeof(bitmap));
}

/* pop bitmap from stack */
void bitmap_pop(void)
{
	if (!current_bitmap)
		return;

	current_bitmap--;}

/* undo button */
void button_undo(void *user)
{
	EUI_UNUSED(user);
	bitmap_pop();
	memcpy(bitmap, &bitmap_history[current_bitmap], sizeof(bitmap));
}

/* redo button */
void button_redo(void *user)
{
	EUI_UNUSED(user);
	bitmap_push(EUI_TRUE);
	memcpy(bitmap, &bitmap_history[current_bitmap], sizeof(bitmap));
}

/* clear button */
void button_clear(void *user)
{
	EUI_UNUSED(user);

	memset(&bitmap, 0, sizeof(bitmap));
	memset(templayer, -1, sizeof(templayer));

	bitmap_push(EUI_FALSE);
}

/* save button */
void button_save(void *user)
{
	char *filename;
	int y;
	SDL_Surface *bmp;
	uint8_t *ptr;

	EUI_UNUSED(user);

	filename = tinyfd_saveFileDialog("Save BMP", "image.bmp", 1, filter_patterns, "BMP Files");

	SDL_PumpEvents();
	SDL_FlushEvents(SDL_MOUSEMOTION, SDL_MOUSEWHEEL);
	eui_clear_events();

	if (filename == NULL)
		return;

	/* create bmp surface */
	bmp = SDL_CreateRGBSurface(0, BITMAP_WIDTH, BITMAP_HEIGHT, 8, 0, 0, 0, 0);
	if (bmp == NULL)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", SDL_GetError(), NULL);
		return;
	}

	/* set palette */
	SDL_SetPaletteColors(bmp->format->palette, colors, 0, 256);

	/* copy in bitmap */
	ptr = (uint8_t *)bmp->pixels;
	for (y = 0; y < bmp->h; y++)
	{
		memcpy(ptr, &bitmap[y][0], bmp->w * sizeof(eui_color_t));
		ptr += bmp->pitch;
	}

	/* save bmp to disk */
	if (SDL_SaveBMP(bmp, filename) != 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", SDL_GetError(), NULL);
	}

	SDL_FreeSurface(bmp);
}

/* load button */
void button_load(void *user)
{
	char *filename;
	SDL_Surface *bmp;
	int y;
	uint8_t *ptr;

	EUI_UNUSED(user);

	filename = tinyfd_openFileDialog("Load BMP", "image.bmp", 1, filter_patterns, "BMP Files", 0);

	SDL_PumpEvents();
	SDL_FlushEvents(SDL_MOUSEMOTION, SDL_MOUSEWHEEL);
	eui_clear_events();

	if (filename == NULL)
		return;

	bmp = SDL_LoadBMP(filename);

	if (bmp == NULL)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", SDL_GetError(), NULL);
		return;
	}

	if (bmp->format->BytesPerPixel != sizeof(eui_color_t))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Editor Error", "Image does not have the correct color depth", NULL);
		return;
	}

	if (bmp->w != BITMAP_WIDTH || bmp->h != BITMAP_HEIGHT)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Editor Error", "Image does not have the correct dimensions", NULL);
		return;
	}

	ptr = (uint8_t *)bmp->pixels;
	for (y = 0; y < bmp->h; y++)
	{
		memcpy(&bitmap[y][0], ptr, bmp->w * sizeof(eui_color_t));
		ptr += bmp->pitch;
	}

	SDL_FreeSurface(bmp);
}


/* flood fill part of bitmap */
#define PUSH(_x, _y) \
	{ \
		stack_count++; \
		stack[stack_count].x = _x; \
		stack[stack_count].y = _y; \
	}
#define POP(_x, _y) \
	{ \
		_x = stack[stack_count].x; \
		_y = stack[stack_count].y; \
		stack[stack_count].x = 0; \
		stack[stack_count].y = 0; \
		stack_count--; \
	}
void tool_fill(int x, int y, eui_color_t color)
{
	static eui_vec2_t stack[BITMAP_WIDTH * BITMAP_HEIGHT * 4];
	static int started;
	int stack_count;
	eui_color_t seed;
	eui_color_t read;

	/* user is not pressing any buttons */
	if (!eui_get_button())
	{
		if (started)
		{
			/* push bitmap stack for undo/redo */
			bitmap_push(EUI_FALSE);

			/* turn off started flag */
			started = EUI_FALSE;
		}

		return;
	}

	/* right click erases */
	if (eui_get_button() & EUI_BUTTON_RIGHT)
		color = 0;

	/* already doing it, don't do it again */
	if (started)
		return;

	/* get seed color */
	seed = bitmap[y][x];

	/* prevent stack overflow */
	if (seed == color)
		return;

	/* push first position to stack */
	stack_count = 0;
	PUSH(x, y);

	/* do flood fill */
	while (stack_count)
	{
		/* read stack value */
		POP(x, y);

		/* out of bounds */
		if (x < 0 || x >= BITMAP_WIDTH || y < 0 || y >= BITMAP_HEIGHT)
			continue;

		/* read pixel */
		read = bitmap[y][x];

		/* it's a match */
		if (read == seed)
		{
			/* set pixel */
			bitmap[y][x] = color;

			/* add neighboring pixel positions */
			PUSH(x + 1, y);
			PUSH(x - 1, y);
			PUSH(x, y + 1);
			PUSH(x, y - 1);
		}
	}

	/* we're doing it */
	started = EUI_TRUE;
}
#undef PUSH
#undef POP

/* plot pixel on bitmap */
void tool_pen(int x, int y, eui_color_t color)
{
	static int started;

	/* user is not pressing any buttons */
	if (!eui_get_button())
	{
		if (started)
		{
			/* push bitmap stack for undo/redo */
			bitmap_push(EUI_FALSE);

			/* turn off started flag */
			started = EUI_FALSE;
		}

		return;
	}

	/* right click erases */
	if (eui_get_button() & EUI_BUTTON_RIGHT)
		color = 0;

	/* plot pixel */
	bitmap[y][x] = color;

	/* we're doing it */
	started = EUI_TRUE;
}

/* draw hollow rectangle on bitmap */
void tool_rect(int x, int y, eui_color_t color)
{
	static eui_vec2_t startpos;
	static eui_vec2_t endpos;
	static int started;
	int xx, yy;
	int xsgn, ysgn;

	/* user is not pressing a button */
	if (!eui_get_button())
	{
		/* we've already staretd drawing, so write changes */
		if (started)
		{
			/* write changes to bitmap */
			for (yy = 0; yy < BITMAP_HEIGHT; yy++)
			{
				for (xx = 0; xx < BITMAP_WIDTH; xx++)
				{
					if (templayer[yy][xx] >= 0)
						bitmap[yy][xx] = templayer[yy][xx];
				}
			}

			/* push bitmap stack for undo/redo */
			bitmap_push(EUI_FALSE);

			/* turn off started flag */
			started = EUI_FALSE;
		}

		/* clear temp layer */
		memset(templayer, -1, sizeof(templayer));
		return;
	}

	/* right click erases */
	if (eui_get_button() & EUI_BUTTON_RIGHT)
		color = 0;

	/* already started drawing */
	if (started)
	{
		/* set endpos */
		endpos.x = x;
		endpos.y = y;

		/* get draw direction for lines */
		xsgn = SGN(endpos.x - startpos.x);
		ysgn = SGN(endpos.y - startpos.y);

		/* clear temp layer */
		memset(templayer, -1, sizeof(templayer));

		/* vertical lines */
		for (yy = startpos.y; yy != endpos.y; yy += ysgn)
		{
			if (yy < 0 || yy >= BITMAP_HEIGHT)
				break;
			templayer[yy][startpos.x] = color;
			templayer[yy][endpos.x] = color;
		}

		/* horizontal lines */
		for (xx = startpos.x; xx != endpos.x; xx += xsgn)
		{
			if (xx < 0 || xx >= BITMAP_WIDTH)
				break;
			templayer[startpos.y][xx] = color;
			templayer[endpos.y][xx] = color;
		}

		/* fill last point */
		templayer[endpos.y][endpos.x] = color;
	}
	else
	{
		/* set startpos */
		startpos.x = x;
		startpos.y = y;

		/* user started drawing */
		started = EUI_TRUE;
	}
}
/* draw filled rectangle on bitmap */
void tool_filled_rect(int x, int y, eui_color_t color)
{
	static eui_vec2_t startpos;
	static eui_vec2_t endpos;
	static int started;
	int xx, yy;
	int xsgn, ysgn;

	/* user is not pressing a button */
	if (!eui_get_button())
	{
		/* we've already staretd drawing, so write changes */
		if (started)
		{
			/* write changes to bitmap */
			for (yy = 0; yy < BITMAP_HEIGHT; yy++)
			{
				for (xx = 0; xx < BITMAP_WIDTH; xx++)
				{
					if (templayer[yy][xx] >= 0)
						bitmap[yy][xx] = templayer[yy][xx];
				}
			}

			/* push bitmap stack for undo/redo */
			bitmap_push(EUI_FALSE);

			/* turn off started flag */
			started = EUI_FALSE;
		}

		/* clear temp layer */
		memset(templayer, -1, sizeof(templayer));
		return;
	}

	/* right click erases */
	if (eui_get_button() & EUI_BUTTON_RIGHT)
		color = 0;

	/* already started drawing */
	if (started)
	{
		/* set endpos */
		endpos.x = x;
		endpos.y = y;

		/* get draw direction for lines */
		xsgn = SGN(endpos.x - startpos.x);
		ysgn = SGN(endpos.y - startpos.y);

		/* clear temp layer */
		memset(templayer, -1, sizeof(templayer));

		/* vertical lines */
		for (yy = startpos.y; yy != endpos.y; yy += ysgn)
		{
			if (yy < 0 || yy >= BITMAP_HEIGHT)
				break;
			templayer[yy][startpos.x] = color;
			templayer[yy][endpos.x] = color;
		}

		/* horizontal lines */
		for (xx = startpos.x; xx != endpos.x; xx += xsgn)
		{
			if (xx < 0 || xx >= BITMAP_WIDTH)
				break;
			templayer[startpos.y][xx] = color;
			templayer[endpos.y][xx] = color;
		}

		/* filling */
		for (yy = startpos.y; yy != endpos.y; yy += ysgn)
		{
			if (yy < 0 || yy >= BITMAP_HEIGHT || xx < 0 || xx >= BITMAP_WIDTH)
				break;

			for (xx = startpos.x; xx != endpos.x; xx += xsgn)
			{
				templayer[yy][xx] = color;
			}
		}

		/* fill last point */
		templayer[endpos.y][endpos.x] = color;
	}
	else
	{
		/* set startpos */
		startpos.x = x;
		startpos.y = y;

		/* user started drawing */
		started = EUI_TRUE;
	}
}

/* main */
int main(int argc, char **argv)
{
	uint32_t format;
	unsigned int rmask, gmask, bmask, amask;
	int bpp;
	eui_vec2_t bitmap_pos, bitmap_size;
	eui_vec2_t cursor_pos;
	eui_vec2_t selected_pixel;
	eui_vec2_t current_color_pos;
	eui_vec2_t current_color_size;
	eui_vec2_t pixel_pos, pixel_size;
	eui_vec2_t palette_pos, palette_size, palette_entry_size;
	eui_vec2_t pos, size;
	SDL_Event event;
	int i;
	int x, y;

	EUI_UNUSED(argc);
	EUI_UNUSED(argv);

	/* init */
	SDL_Init(SDL_INIT_VIDEO);

	/* create window */
	window = SDL_CreateWindow("editor",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
	);

	/* create renderer */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
	SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
	SDL_SetWindowMinimumSize(window, WIDTH, HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

	/* create our render surface */
	surface8 = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 8, 0, 0, 0, 0);
	SDL_FillRect(surface8, NULL, 0);

	/* generate palette table */
	for (i = 0; i < 256; i++)
	{
		colors[i].r = palette[i * 3];
		colors[i].g = palette[i * 3 + 1];
		colors[i].b = palette[i * 3 + 2];
	}

	/* install palette */
	SDL_SetPaletteColors(surface8->format->palette, colors, 0, 256);

	/* create display surface */
	format = SDL_GetWindowPixelFormat(window);
	SDL_PixelFormatEnumToMasks(format, &bpp, &rmask, &gmask, &bmask, &amask);
	surface32 = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, bpp, rmask, gmask, bmask, amask);
	texture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

	/* make sure relative mouse mode is disabled */
	SDL_SetRelativeMouseMode(SDL_FALSE);

	/* setup blit rect */
	blit_rect.x = 0;
	blit_rect.y = 0;
	blit_rect.w = WIDTH;
	blit_rect.h = HEIGHT;

	/* clear bitmap */
	memset(&bitmap, 0, sizeof(bitmap));
	memset(templayer, -1, sizeof(templayer));

	/* set default color */
	current_color = 63;

	/* main loop */
	running = SDL_TRUE;
	while (running)
	{
		/* parse sdl events */
		while (SDL_PollEvent(&event))
		{
			eui_push_event_sdl2(&event);

			switch (event.type)
			{
				case SDL_QUIT:
					running = SDL_FALSE;
					break;
			}
		}

		/* do eui */
		if (eui_begin_sdl2(surface8))
		{
			/* clear */
			eui_clear(4);

			/* grid background */
			bitmap_size.x = PIXEL_WIDTH * BITMAP_WIDTH;
			bitmap_size.y = PIXEL_HEIGHT * BITMAP_HEIGHT;
			bitmap_pos.x = WIDTH - bitmap_size.x;
			bitmap_pos.y = HEIGHT - bitmap_size.y;
			eui_filled_box(bitmap_pos, bitmap_size, 0);

			/* get cursor pos */
			cursor_pos = eui_get_cursor_pos();

			/* draw palette */
			palette_entry_size.x = ENTRY_WIDTH;
			palette_entry_size.y = ENTRY_HEIGHT;
			palette_size.x = palette_entry_size.x * 16;
			palette_size.y = palette_entry_size.y * 16;
			palette_pos.x = (bitmap_pos.x / 2) - (palette_size.x / 2);
			palette_pos.y = bitmap_pos.y;
			for (y = 0; y < 16; y++)
			{
				for (x = 0; x < 16; x++)
				{
					eui_vec2_t pos;

					pos.x = palette_pos.x + (x * palette_entry_size.x);
					pos.y = palette_pos.y + (y * palette_entry_size.y);

					/* draw palette entry */
					eui_filled_box(pos, palette_entry_size, y * 16 + x);
				}
			}

			/* draw selected color */
			pos.x = palette_pos.x;
			pos.y = palette_pos.y - 10;
			eui_textf(pos, 31, "color=%03d", current_color);
			current_color_pos.x = ((current_color % 16) * palette_entry_size.x) + palette_pos.x - 1;
			current_color_pos.y = ((current_color / 16) * palette_entry_size.y) + palette_pos.y - 1;
			current_color_size.x = palette_entry_size.x + 2;
			current_color_size.y = palette_entry_size.y + 2;
			eui_border_box(current_color_pos, current_color_size, 1, 255);

			/* do color interaction */
			if (eui_is_hovered(palette_pos, palette_size))
			{
				eui_vec2_t entry_pos, entry_size, selected_color;

				entry_pos.x = cursor_pos.x - palette_pos.x;
				entry_pos.y = cursor_pos.y - palette_pos.y;

				selected_color.x = (entry_pos.x - (entry_pos.x % ENTRY_WIDTH)) / ENTRY_WIDTH;
				selected_color.y = (entry_pos.y - (entry_pos.y % ENTRY_HEIGHT)) / ENTRY_HEIGHT;

				selected_color.x = CLAMP(selected_color.x, 0, 15);
				selected_color.y = CLAMP(selected_color.y, 0, 15);

				entry_pos.x = (selected_color.x * ENTRY_WIDTH) + palette_pos.x;
				entry_pos.y = (selected_color.y * ENTRY_HEIGHT) + palette_pos.y;

				entry_pos.x -= 1;
				entry_pos.y -= 1;

				entry_size.x = palette_entry_size.x + 2;
				entry_size.y = palette_entry_size.y + 2;

				/* draw color outline */
				eui_border_box(entry_pos, entry_size, 1, 255);

				if (eui_get_button() & EUI_BUTTON_LEFT)
				{
					current_color = selected_color.y * 16 + selected_color.x;
				}
			}

			/* draw bitmap */
			pixel_size.x = PIXEL_WIDTH;
			pixel_size.y = PIXEL_HEIGHT;
			for (y = 0; y < BITMAP_HEIGHT; y++)
			{
				for (x = 0; x < BITMAP_WIDTH; x++)
				{
					/* pixel pos */
					pixel_pos.x = bitmap_pos.x + (x * PIXEL_WIDTH);
					pixel_pos.y = bitmap_pos.y + (y * PIXEL_HEIGHT);

					/* draw pixel */
					eui_filled_box(pixel_pos, pixel_size, bitmap[y][x]);

					/* temp layer value */
					if (templayer[y][x] >= 0)
						eui_filled_box(pixel_pos, pixel_size, templayer[y][x]);
				}
			}

			/* draw selected pixel */
			if (eui_is_hovered(bitmap_pos, bitmap_size))
			{
				/* pixel size */
				pixel_size.x = PIXEL_WIDTH + 2;
				pixel_size.y = PIXEL_HEIGHT + 2;

				/* pixel pos */
				pixel_pos.x = cursor_pos.x - bitmap_pos.x;
				pixel_pos.y = cursor_pos.y - bitmap_pos.y;

				/* selected pixel */
				selected_pixel.x = (pixel_pos.x - (pixel_pos.x % PIXEL_WIDTH)) / PIXEL_WIDTH;
				selected_pixel.y = (pixel_pos.y - (pixel_pos.y % PIXEL_HEIGHT)) / PIXEL_HEIGHT;

				selected_pixel.x = CLAMP(selected_pixel.x, 0, BITMAP_WIDTH - 1);
				selected_pixel.y = CLAMP(selected_pixel.y, 0, BITMAP_HEIGHT - 1);

				pixel_pos.x = (selected_pixel.x * PIXEL_WIDTH) + bitmap_pos.x;
				pixel_pos.y = (selected_pixel.y * PIXEL_HEIGHT) + bitmap_pos.y;

				pixel_pos.x -= 1;
				pixel_pos.y -= 1;

				/* draw pixel outline */
				eui_border_box(pixel_pos, pixel_size, 1, 255);

				/* draw help text */
				pos.x = bitmap_pos.x;
				pos.y = bitmap_pos.y - 20;
				eui_textf(pos, 31, "pixel=%02dx%02d", selected_pixel.x, selected_pixel.y);
				pos.x = bitmap_pos.x;
				pos.y = bitmap_pos.y - 10;
				eui_textf(pos, 31, "color=%03d", bitmap[selected_pixel.y][selected_pixel.x]);

				/* do pixel interaction */
				switch (current_tool)
				{
					case TOOL_PEN:
						tool_pen(selected_pixel.x, selected_pixel.y, current_color);
						break;

					case TOOL_FILL:
						tool_fill(selected_pixel.x, selected_pixel.y, current_color);
						break;

					case TOOL_RECT:
						tool_rect(selected_pixel.x, selected_pixel.y, current_color);
						break;

					case TOOL_FILLED_RECT:
						tool_filled_rect(selected_pixel.x, selected_pixel.y, current_color);
						break;
				}
			}
			else
			{
				/* draw help text */
				pos.x = bitmap_pos.x;
				pos.y = bitmap_pos.y - 20;
				eui_text(pos, 31, "pixel=--x--");
				pos.x = bitmap_pos.x;
				pos.y = bitmap_pos.y - 10;
				eui_text(pos, 31, "color=---");

				/* clear temp layer */
				memset(templayer, -1, sizeof(templayer));
			}

			/* move to top left alignment */
			eui_set_align(EUI_ALIGN_END, EUI_ALIGN_START);

			/* filled rect button */
			pos.x = -4;
			pos.y = (bitmap_pos.y / 2) - (filled_rect_height / 2);
			size.x = filled_rect_width;
			size.y = filled_rect_height;
			if (current_tool == TOOL_FILLED_RECT)
				eui_xbm(pos, 31, filled_rect_selected_width, filled_rect_selected_height, filled_rect_selected_bits);
			else
				eui_xbm(pos, 31, filled_rect_width, filled_rect_height, filled_rect_bits);

			/* select filled rect */
			if (eui_is_hovered(pos, size) && eui_get_button())
				current_tool = TOOL_FILLED_RECT;

			/* rect button */
			pos.x = -1 * rect_width - 8;
			pos.y = (bitmap_pos.y / 2) - (rect_height / 2);
			size.x = rect_width;
			size.y = rect_height;
			if (current_tool == TOOL_RECT)
				eui_xbm(pos, 31, rect_selected_width, rect_selected_height, rect_selected_bits);
			else
				eui_xbm(pos, 31, rect_width, rect_height, rect_bits);

			/* select rect */
			if (eui_is_hovered(pos, size) && eui_get_button())
				current_tool = TOOL_RECT;

			/* bucket button */
			pos.x = -1 * (bucket_width * 2) - 12;
			pos.y = (bitmap_pos.y / 2) - (pen_height / 2);
			size.x = bucket_width;
			size.y = bucket_height;
			if (current_tool == TOOL_FILL)
				eui_xbm(pos, 31, bucket_selected_width, bucket_selected_height, bucket_selected_bits);
			else
				eui_xbm(pos, 31, bucket_width, bucket_height, bucket_bits);

			/* select bucket */
			if (eui_is_hovered(pos, size) && eui_get_button())
				current_tool = TOOL_FILL;

			/* pen button */
			pos.x = -1 * (pen_width * 3) - 16;
			pos.y = (bitmap_pos.y / 2) - (pen_height / 2);
			size.x = pen_width;
			size.y = pen_height;
			if (current_tool == TOOL_PEN)
				eui_xbm(pos, 31, pen_selected_width, pen_selected_height, pen_selected_bits);
			else
				eui_xbm(pos, 31, pen_width, pen_height, pen_bits);

			/* select pen */
			if (eui_is_hovered(pos, size) && eui_get_button())
				current_tool = TOOL_PEN;

			/* move to bottom alignment */
			eui_set_align(EUI_ALIGN_START, EUI_ALIGN_END);

			/* undo button */
			pos.x = 0;
			pos.y = -48;
			size.x = bitmap_pos.x / 2;
			size.y = 24;
			eui_button(pos, size, "Undo", button_undo, NULL);

			/* redo button */
			pos.x = bitmap_pos.x - size.x;
			pos.y = -48;
			eui_button(pos, size, "Redo", button_redo, NULL);

			/* clear button */
			pos.x = 0;
			pos.y = -24;
			size.x = bitmap_pos.x;
			size.y = 24;
			eui_button(pos, size, "Clear", button_clear, NULL);

			/* save button */
			pos.x = 0;
			pos.y = 0;
			size.x = bitmap_pos.x / 2;
			size.y = 24;
			eui_button(pos, size, "Save", button_save, NULL);

			/* load button */
			pos.x = bitmap_pos.x - size.x;
			pos.y = 0;
			eui_button(pos, size, "Load", button_load, NULL);

			/* end eui */
			eui_end();
		}

		/* blit to screen */
		SDL_BlitSurface(surface8, &blit_rect, surface32, &blit_rect);
		SDL_UpdateTexture(texture, NULL, surface32->pixels, surface32->pitch);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	/* quit */
	SDL_FreeSurface(surface8);
	SDL_FreeSurface(surface32);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}