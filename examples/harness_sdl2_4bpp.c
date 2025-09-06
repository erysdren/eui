/*
MIT License

Copyright (c) 2023-2025 erysdren (it/its)

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
 * HARNESS_SDL2_4BPP.C
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "SDL.h"

#include "eui_sdl2.h"
#include "examples.h"

#include "palette_windows.h"

/* SDL2 state */
static SDL_Window *window;
static SDL_Surface *surface4;
static SDL_Surface *surface32;
static SDL_Renderer *renderer;
static SDL_Texture *texture;
static SDL_Rect rect;
static SDL_Color colors[16];
static SDL_Event event;

#ifdef EXAMPLE_STANDALONE
#define MOUSE_GRAB_PADDING (10)
SDL_HitTestResult hit_test(SDL_Window *window, const SDL_Point *point, void *user)
{
	EUI_UNUSED(window);
	EUI_UNUSED(user);

	if (point->y <= 16)
		return SDL_HITTEST_DRAGGABLE;
	else
		return SDL_HITTEST_NORMAL;
}
#endif

/* main */
int main(int argc, char **argv)
{
	uint32_t format;
	unsigned int rmask, gmask, bmask, amask;
	int bpp;
	int i;

	EUI_UNUSED(argc);
	EUI_UNUSED(argv);

	/* init */
	SDL_Init(SDL_INIT_VIDEO);

	/* create window */
	window = SDL_CreateWindow(EXAMPLE_TITLE,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		EXAMPLE_WIDTH, EXAMPLE_HEIGHT,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
	);

	/* create renderer */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(renderer, EXAMPLE_WIDTH, EXAMPLE_HEIGHT);
	SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
	SDL_SetWindowMinimumSize(window, EXAMPLE_WIDTH, EXAMPLE_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

#ifdef EXAMPLE_STANDALONE
	SDL_SetWindowBordered(window, SDL_FALSE);
	SDL_SetWindowHitTest(window, hit_test, 0);
#endif

	/* create our render surface */
	surface4 = SDL_CreateRGBSurface(0, EXAMPLE_WIDTH, EXAMPLE_HEIGHT, 4, 0, 0, 0, 0);
	SDL_FillRect(surface4, NULL, 0);

	/* init palette */
	for (i = 0; i < 16; i++)
	{
		colors[i].r = palette_windows[i * 3];
		colors[i].g = palette_windows[i * 3 + 1];
		colors[i].b = palette_windows[i * 3 + 2];
	}

	/* install palette */
	SDL_SetPaletteColors(surface4->format->palette, colors, 0, 16);

	/* create display surface */
	format = SDL_GetWindowPixelFormat(window);
	SDL_PixelFormatEnumToMasks(format, &bpp, &rmask, &gmask, &bmask, &amask);
	surface32 = SDL_CreateRGBSurface(0, EXAMPLE_WIDTH, EXAMPLE_HEIGHT, bpp, rmask, gmask, bmask, amask);
	texture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_STREAMING, EXAMPLE_WIDTH, EXAMPLE_HEIGHT);

	/* make sure relative mouse mode is disabled */
	SDL_SetRelativeMouseMode(SDL_FALSE);

	/* setup blit rect */
	rect.x = 0;
	rect.y = 0;
	rect.w = EXAMPLE_WIDTH;
	rect.h = EXAMPLE_HEIGHT;

	/* init eui */
	eui_init(surface4->w, surface4->h, surface4->format->BitsPerPixel, surface4->pitch, surface4->pixels);

	/* main loop */
	while (!SDL_QuitRequested())
	{
		/* push events */
		while (SDL_PollEvent(&event))
			eui_sdl2_event_push(&event);

		/* process events */
		eui_event_queue_process();

		/* clear screen */
		SDL_FillRect(surface4, NULL, 0x00);

		/* run eui context */
		if (eui_context_begin())
		{
			/* run example func */
			EXAMPLE_FUNC();

			/* end eui context */
			eui_context_end();
		}

		/* copy to screen */
		SDL_BlitSurface(surface4, &rect, surface32, &rect);
		SDL_UpdateTexture(texture, NULL, surface32->pixels, surface32->pitch);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	/* quit */
	eui_quit();
	SDL_FreeSurface(surface4);
	SDL_FreeSurface(surface32);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
