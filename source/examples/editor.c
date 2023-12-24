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
 * EDITOR.C
 *
 */

#include <stdio.h>
#include <stdint.h>

#include "tinyfiledialogs.h"

#include "eui_sdl2.h"

#define WIDTH (640)
#define HEIGHT (480)
#define TILE_WIDTH (7)
#define TILE_HEIGHT (7)
#define MAP_WIDTH (64)
#define MAP_HEIGHT (64)
#define ENTRY_WIDTH (11)
#define ENTRY_HEIGHT (11)

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

static struct {
	uint16_t walls[MAP_HEIGHT][MAP_WIDTH];
	uint16_t objects[MAP_HEIGHT][MAP_WIDTH];
} tilemap;

/* temp layer */
int templayer[MAP_HEIGHT][MAP_WIDTH];

enum {
	TOOL_PEN,
	TOOL_FILL,
	TOOL_RECT
};

static int current_tool = TOOL_PEN;

static int current_layer = 0;
static eui_color_t current_color = 63;

static SDL_Window *window;
static SDL_Surface *surface8;
static SDL_Surface *surface32;
static SDL_Renderer *renderer;
static SDL_Texture *texture;
static SDL_Rect blit_rect;
static SDL_bool running;
static SDL_Color colors[256];

/* clear button */
void button_clear(void *user)
{
	EUI_UNUSED(user);

	memset(&tilemap, 0, sizeof(tilemap));
	memset(templayer, -1, sizeof(templayer));
}

/* save button */
void button_save(void *user)
{
	char *filename;
	FILE *file;

	EUI_UNUSED(user);

	filename = tinyfd_saveFileDialog("Save Map", "map.dat", 0, NULL, NULL);

	if (filename == NULL)
		return;

	file = fopen(filename, "wb");
	fwrite(&tilemap, sizeof(tilemap), 1, file);
	fclose(file);
}

/* load button */
void button_load(void *user)
{
	char *filename;
	FILE *file;

	EUI_UNUSED(user);

	filename = tinyfd_openFileDialog("Load Map", "map.dat", 0, NULL, NULL, 0);

	if (filename == NULL)
		return;

	file = fopen(filename, "rb");
	fread(&tilemap, sizeof(tilemap), 1, file);
	fclose(file);
}


/* flood fill part of tilemap */
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
	static eui_vec2_t stack[MAP_WIDTH * MAP_HEIGHT * 4];
	int stack_count;
	eui_color_t seed;
	eui_color_t read;
	static int clicked;

	if (!eui_get_button())
	{
		clicked = EUI_FALSE;
		return;
	}

	if (eui_get_button() & EUI_BUTTON_RIGHT)
		color = 0;

	if (clicked)
		return;

	/* get seed color */
	seed = tilemap.walls[y][x];

	if (seed == color)
		return;

	/* push first value to stack */
	stack_count = 0;
	PUSH(x, y);

	/* do flood fill */
	while (stack_count)
	{
		POP(x, y);

		/* out of bounds */
		if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
			continue;

		/* read color */
		read = tilemap.walls[y][x];

		/* it's a match */
		if (read == seed)
		{
			tilemap.walls[y][x] = color;

			PUSH(x + 1, y);
			PUSH(x - 1, y);
			PUSH(x, y + 1);
			PUSH(x, y - 1);
		}
	}

	clicked = EUI_TRUE;
}
#undef PUSH
#undef POP

/* plot color on tilemap */
void tool_pen(int x, int y, eui_color_t color)
{
	if (!eui_get_button())
		return;

	if (eui_get_button() & EUI_BUTTON_RIGHT)
		color = 0;

	/* plot color */
	tilemap.walls[y][x] = color;
}

/* draw hollow rectangle on tilemap */
void tool_rect(int x, int y, eui_color_t color)
{
	static eui_vec2_t startpos;
	static eui_vec2_t endpos;
	static int started;
	int xx, yy;
	int xsgn, ysgn;

	if (!eui_get_button())
	{
		/* write changes */
		if (started)
		{
			for (yy = 0; yy < MAP_HEIGHT; yy++)
			{
				for (xx = 0; xx < MAP_WIDTH; xx++)
				{
					if (templayer[yy][xx] >= 0)
						tilemap.walls[yy][xx] = templayer[yy][xx];
				}
			}

			started = EUI_FALSE;
		}

		return;
	}

	if (eui_get_button() & EUI_BUTTON_RIGHT)
		color = 0;

	if (started)
	{
		endpos.x = x;
		endpos.y = y;

		xsgn = SGN(endpos.x - startpos.x);
		ysgn = SGN(endpos.y - startpos.y);

		memset(templayer, -1, sizeof(templayer));

		/* vertical lines */
		for (yy = startpos.y; yy != endpos.y; yy += ysgn)
		{
			if (yy < 0 || yy >= MAP_HEIGHT)
				break;
			templayer[yy][startpos.x] = color;
			templayer[yy][endpos.x] = color;
		}

		/* horizontal lines */
		for (xx = startpos.x; xx != endpos.x; xx += xsgn)
		{
			if (xx < 0 || xx >= MAP_WIDTH)
				break;
			templayer[startpos.y][xx] = color;
			templayer[endpos.y][xx] = color;
		}

		/* fill last point */
		templayer[endpos.y][endpos.x] = color;
	}
	else
	{
		startpos.x = x;
		startpos.y = y;
		started = EUI_TRUE;
	}
}

/* main */
int main(int argc, char **argv)
{
	uint32_t format;
	unsigned int rmask, gmask, bmask, amask;
	int bpp;
	eui_vec2_t tilemap_pos, tilemap_size;
	eui_vec2_t cursor_pos;
	eui_vec2_t selected_tile;
	eui_vec2_t tile_pos, tile_size;
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

	/* set window size */
	SDL_SetWindowMinimumSize(window, WIDTH, HEIGHT);

	/* create renderer */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
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

	/* clear tilemap */
	button_clear(NULL);

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

			/* tile grid background */
			tilemap_size.x = TILE_WIDTH * MAP_WIDTH;
			tilemap_size.y = TILE_HEIGHT * MAP_HEIGHT;
			tilemap_pos.x = WIDTH - tilemap_size.x;
			tilemap_pos.y = HEIGHT - tilemap_size.y;
			eui_filled_box(tilemap_pos, tilemap_size, 0);

			/* get cursor pos */
			cursor_pos = eui_get_cursor_pos();

			/* draw palette */
			palette_entry_size.x = ENTRY_WIDTH;
			palette_entry_size.y = ENTRY_HEIGHT;
			palette_size.x = palette_entry_size.x * 16;
			palette_size.y = palette_entry_size.y * 16;
			palette_pos.x = (tilemap_pos.x / 2) - (palette_size.x / 2);
			palette_pos.y = tilemap_pos.y;
			for (y = 0; y < 16; y++)
			{
				for (x = 0; x < 16; x++)
				{
					eui_vec2_t pos;

					pos.x = palette_pos.x + (x * palette_entry_size.x);
					pos.y = palette_pos.y + (y * palette_entry_size.y);

					/* draw tile entry */
					eui_filled_box(pos, palette_entry_size, y * 16 + x);
				}
			}

			/* draw selected color */
			eui_textf(EUI_VEC2(palette_pos.x, palette_pos.y - 10), 31, "color=%03d", current_color);

			/* do color interaction */
			if (eui_is_hovered(palette_pos, palette_size))
			{
				eui_vec2_t entry_pos, entry_size, selected_color;

				entry_pos.x = cursor_pos.x - palette_pos.x;
				entry_pos.y = cursor_pos.y - palette_pos.y;

				selected_color.x = (entry_pos.x - (entry_pos.x % ENTRY_WIDTH)) / ENTRY_WIDTH;
				selected_color.y = (entry_pos.y - (entry_pos.y % ENTRY_HEIGHT)) / ENTRY_HEIGHT;

				entry_pos.x = (selected_color.x * ENTRY_WIDTH) + palette_pos.x;
				entry_pos.y = (selected_color.y * ENTRY_HEIGHT) + palette_pos.y;

				entry_pos.x -= 1;
				entry_pos.y -= 1;

				entry_size.x = palette_entry_size.x + 2;
				entry_size.y = palette_entry_size.y + 2;

				/* draw tile outline */
				eui_border_box(entry_pos, entry_size, 1, 255);

				if (eui_get_button() & EUI_BUTTON_LEFT)
				{
					current_color = selected_color.y * 16 + selected_color.x;
				}
			}

			/* draw tilemap */
			tile_size.x = TILE_WIDTH;
			tile_size.y = TILE_HEIGHT;
			for (y = 0; y < MAP_HEIGHT; y++)
			{
				for (x = 0; x < MAP_WIDTH; x++)
				{
					/* tile pos */
					tile_pos.x = tilemap_pos.x + (x * TILE_WIDTH);
					tile_pos.y = tilemap_pos.y + (y * TILE_HEIGHT);

					/* draw tile */
					eui_filled_box(tile_pos, tile_size, tilemap.walls[y][x]);

					/* temp layer value */
					if (templayer[y][x] >= 0)
						eui_filled_box(tile_pos, tile_size, templayer[y][x]);
				}
			}

			/* draw selected tile */
			if (eui_is_hovered(tilemap_pos, tilemap_size))
			{
				/* tile size */
				tile_size.x = TILE_WIDTH + 2;
				tile_size.y = TILE_HEIGHT + 2;

				/* tile pos */
				tile_pos.x = cursor_pos.x - tilemap_pos.x;
				tile_pos.y = cursor_pos.y - tilemap_pos.y;

				/* selected tile */
				selected_tile.x = (tile_pos.x - (tile_pos.x % TILE_WIDTH)) / TILE_WIDTH;
				selected_tile.y = (tile_pos.y - (tile_pos.y % TILE_HEIGHT)) / TILE_HEIGHT;

				selected_tile.x = CLAMP(selected_tile.x, 0, MAP_WIDTH - 1);
				selected_tile.y = CLAMP(selected_tile.y, 0, MAP_HEIGHT - 1);

				tile_pos.x = (selected_tile.x * TILE_WIDTH) + tilemap_pos.x;
				tile_pos.y = (selected_tile.y * TILE_HEIGHT) + tilemap_pos.y;

				tile_pos.x -= 1;
				tile_pos.y -= 1;

				/* draw tile outline */
				eui_border_box(tile_pos, tile_size, 1, 255);

				/* draw selected tile */
				eui_textf(EUI_VEC2(tilemap_pos.x, tilemap_pos.y - 20), 31, "tile=%02dx%02d", selected_tile.x, selected_tile.y);
				eui_textf(EUI_VEC2(tilemap_pos.x, tilemap_pos.y - 10), 31, "color=%03d", tilemap.walls[selected_tile.y][selected_tile.x]);

				/* do tile interaction */
				switch (current_tool)
				{
					case TOOL_PEN:
						tool_pen(selected_tile.x, selected_tile.y, current_color);
						break;

					case TOOL_FILL:
						tool_fill(selected_tile.x, selected_tile.y, current_color);
						break;

					case TOOL_RECT:
						tool_rect(selected_tile.x, selected_tile.y, current_color);
						break;
				}
			}
			else
			{
				/* draw selected tile */
				eui_text(EUI_VEC2(tilemap_pos.x, tilemap_pos.y - 20), 31, "tile=--x--");
				eui_text(EUI_VEC2(tilemap_pos.x, tilemap_pos.y - 10), 31, "color=---");
			}

			/* move to top left alignment */
			eui_set_align(EUI_ALIGN_END, EUI_ALIGN_START);

			/* rect button */
			pos.x = -4;
			pos.y = (tilemap_pos.y / 2) - (rect_height / 2);
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
			pos.x = -1 * bucket_width - 8;
			pos.y = (tilemap_pos.y / 2) - (pen_height / 2);
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
			pos.x = -1 * (pen_width * 2) - 12;
			pos.y = (tilemap_pos.y / 2) - (pen_height / 2);
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

			/* clear button */
			pos.x = 0;
			pos.y = -24;
			size.x = tilemap_pos.x;
			size.y = 24;
			eui_button(pos, size, "Clear", button_clear, NULL);

			/* save button */
			pos.x = 0;
			pos.y = 0;
			size.x = tilemap_pos.x / 2;
			size.y = 24;
			eui_button(pos, size, "Save", button_save, NULL);

			/* load button */
			pos.x = tilemap_pos.x - size.x;
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
