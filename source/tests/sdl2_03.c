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
 * SDL2_03.C
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "eui_sdl2.h"

#define WIDTH (512)
#define HEIGHT (342)

static SDL_Window *window;
static SDL_Surface *surface1;
static SDL_Surface *surface32;
static SDL_Renderer *renderer;
static SDL_Texture *texture;
static SDL_Rect blitrect;
static SDL_bool running;
static SDL_Event event;
SDL_Color colors[2];

#define mac_width 25
#define mac_height 32
static unsigned char mac_bits[] = {
	0xfc, 0xff, 0x7f, 0x00, 0x02, 0x00, 0x80, 0x00, 0x01, 0x00, 0x00, 0x01,
	0xf1, 0xff, 0x1f, 0x01, 0x09, 0x00, 0x20, 0x01, 0x09, 0x00, 0x20, 0x01,
	0x09, 0x00, 0x20, 0x01, 0x09, 0x91, 0x20, 0x01, 0x09, 0x91, 0x20, 0x01,
	0x09, 0x10, 0x20, 0x01, 0x09, 0x10, 0x20, 0x01, 0x09, 0x18, 0x20, 0x01,
	0x09, 0x00, 0x20, 0x01, 0x09, 0x42, 0x20, 0x01, 0x09, 0x3c, 0x20, 0x01,
	0x09, 0x00, 0x20, 0x01, 0x09, 0x00, 0x20, 0x01, 0xf1, 0xff, 0x1f, 0x01,
	0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
	0x01, 0x00, 0x00, 0x01, 0x01, 0x80, 0x1f, 0x01, 0x19, 0x00, 0x00, 0x01,
	0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
	0xfe, 0xff, 0xff, 0x00, 0x02, 0x00, 0x80, 0x00, 0x02, 0x00, 0x80, 0x00,
	0x02, 0x00, 0x80, 0x00, 0xfe, 0xff, 0xff, 0x00
};

/* button callback */
void my_cool_button_callback(void *user)
{
	EUI_UNUSED(user);
	printf("My cool button was pressed!\n");
}

/* main */
int main(int argc, char **argv)
{
	uint32_t format;
	unsigned int rmask, gmask, bmask, amask;
	int bpp;
	eui_vec2_t pos, size;

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
	surface1 = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 1, 0, 0, 0, 0);
	SDL_FillRect(surface1, NULL, 0);

	/* install palette */
	colors[0].r = 0;
	colors[0].g = 0;
	colors[0].b = 0;
	colors[1].r = 255;
	colors[1].g = 255;
	colors[1].b = 255;
	SDL_SetPaletteColors(surface1->format->palette, colors, 0, 2);

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

	/* xbm pos */
	pos.x = 0;
	pos.y = 0;

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
		if (eui_begin_sdl2(surface1))
		{
			/* clear */
			eui_clear(1);

			/* set alignment to center */
			eui_set_align(EUI_ALIGN_MIDDLE, EUI_ALIGN_MIDDLE);

			/* icon by susan kare, thank you <3 */
			pos.x = 0;
			pos.y = -48;
			eui_xbm(pos, 0, mac_width, mac_height, mac_bits);

			/* button */
			pos.x = 0;
			pos.y = 0;
			size.x = 128;
			size.y = 16;
			if (eui_button(pos, size, "My Cool Button", my_cool_button_callback, NULL))
			{
				pos.x = 0;
				pos.y = 24;
				eui_text(pos, 0, "Hovered");
			}

			/* end eui */
			eui_end();
		}

		/* blit to screen */
		SDL_BlitSurface(surface1, &blitrect, surface32, &blitrect);
		SDL_UpdateTexture(texture, NULL, surface32->pixels, surface32->pitch);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	/* quit */
	SDL_FreeSurface(surface1);
	SDL_FreeSurface(surface32);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}