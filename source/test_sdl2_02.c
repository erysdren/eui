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
 * TEST_SDL2_02.C
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "eui_sdl2.h"

#define WIDTH (640)
#define HEIGHT (480)

static SDL_Window *window;
static SDL_Surface *surface8;
static SDL_Surface *surface32;
static SDL_Renderer *renderer;
static SDL_Texture *texture;
static SDL_Rect blitrect;
static SDL_bool running;
static SDL_Event event;

/* button callback */
void quit_callback(void *user)
{
	EUI_UNUSED(user);
	running = SDL_FALSE;
}

/* install palette to SDL_Surface */
void install_palette(const char *filename, SDL_Surface *surface)
{
	FILE *file;
	int i;
	SDL_Color colors[256];

	file = fopen(filename, "rb");
	if (!file)
		return;

	for (i = 0; i < 256; i++)
	{
		colors[i].r = fgetc(file);
		colors[i].g = fgetc(file);
		colors[i].b = fgetc(file);
	}

	SDL_SetPaletteColors(surface->format->palette, colors, 0, 256);

	fclose(file);
}

/* main */
int main(int argc, char **argv)
{
	uint32_t format;
	unsigned int rmask, gmask, bmask, amask;
	int bpp;
	eui_config_t *eui_config;

	EUI_UNUSED(argc);
	EUI_UNUSED(argv);

	/* init */
	SDL_Init(SDL_INIT_VIDEO);

	/* create window */
	window = SDL_CreateWindow("eui",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
	);

	/* set window borderless */
	SDL_SetWindowBordered(window, SDL_FALSE);

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

	/* install palette */
	install_palette("pal_vga.dat", surface8);

	/* create display surface */
	format = SDL_GetWindowPixelFormat(window);
	SDL_PixelFormatEnumToMasks(format, &bpp, &rmask, &gmask, &bmask, &amask);
	surface32 = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, bpp, rmask, gmask, bmask, amask);
	texture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

	/* make sure relative mouse mode is disabled */
	SDL_SetRelativeMouseMode(SDL_FALSE);

	/* setup blit rect */
	blitrect.x = 0;
	blitrect.y = 0;
	blitrect.w = WIDTH;
	blitrect.h = HEIGHT;

	/* configure eui */
	eui_config = eui_get_config();

	eui_config->button.text_color = 0;
	eui_config->button.text_color_hover = 15;

	eui_config->button.bg_color = 15;
	eui_config->button.bg_color_hover = 0;

	eui_config->button.border_color = 0;
	eui_config->button.border_color_hover = 15;

	eui_config->button.border_width = 1;

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
			eui_clear(15);

			/* border */
			eui_border_box(EUI_VEC2(0, 0), EUI_VEC2(WIDTH, HEIGHT), 2, 0);

			/* title */
			eui_border_box(EUI_VEC2(0, 0), EUI_VEC2(WIDTH, 18), 2, 0);
			eui_push_frame(EUI_VEC2(0, 0), EUI_VEC2(WIDTH, 18));
			eui_set_align(EUI_ALIGN_MIDDLE, EUI_ALIGN_MIDDLE);
			eui_text(EUI_VEC2(0, 0), 0, "eui");
			eui_pop_frame();

			/* quit button */
			eui_set_align(EUI_ALIGN_MIDDLE, EUI_ALIGN_MIDDLE);
			eui_button(EUI_VEC2(0, 0), EUI_VEC2(48, 16), "Quit", quit_callback, NULL);

			/* end eui */
			eui_end();
		}

		/* blit to screen */
		SDL_BlitSurface(surface8, &blitrect, surface32, &blitrect);
		SDL_UpdateTexture(texture, NULL, surface32->pixels, surface32->pitch);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	/* quit */
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface8);
	SDL_FreeSurface(surface32);
	SDL_Quit();

	return 0;
}
