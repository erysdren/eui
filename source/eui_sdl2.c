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
 * EUI_SDL2.C
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include "eui_sdl2.h"

static int scancode_table_initialized = EUI_FALSE;
static int scancode_table[SDL_NUM_SCANCODES];

static void initialize_scancode_table(void)
{
	if (scancode_table_initialized)
		return;

	scancode_table[SDL_SCANCODE_ESCAPE] = EUI_SCANCODE_ESCAPE;
	scancode_table[SDL_SCANCODE_1] = EUI_SCANCODE_1;
	scancode_table[SDL_SCANCODE_2] = EUI_SCANCODE_2;
	scancode_table[SDL_SCANCODE_3] = EUI_SCANCODE_3;
	scancode_table[SDL_SCANCODE_4] = EUI_SCANCODE_4;
	scancode_table[SDL_SCANCODE_5] = EUI_SCANCODE_5;
	scancode_table[SDL_SCANCODE_6] = EUI_SCANCODE_6;
	scancode_table[SDL_SCANCODE_7] = EUI_SCANCODE_7;
	scancode_table[SDL_SCANCODE_8] = EUI_SCANCODE_8;
	scancode_table[SDL_SCANCODE_9] = EUI_SCANCODE_9;
	scancode_table[SDL_SCANCODE_0] = EUI_SCANCODE_0;
	scancode_table[SDL_SCANCODE_MINUS] = EUI_SCANCODE_MINUS;
	scancode_table[SDL_SCANCODE_EQUALS] = EUI_SCANCODE_EQUALS;
	scancode_table[SDL_SCANCODE_BACKSPACE] = EUI_SCANCODE_BACKSPACE;
	scancode_table[SDL_SCANCODE_TAB] = EUI_SCANCODE_TAB;
	scancode_table[SDL_SCANCODE_Q] = EUI_SCANCODE_Q;
	scancode_table[SDL_SCANCODE_W] = EUI_SCANCODE_W;
	scancode_table[SDL_SCANCODE_E] = EUI_SCANCODE_E;
	scancode_table[SDL_SCANCODE_R] = EUI_SCANCODE_R;
	scancode_table[SDL_SCANCODE_T] = EUI_SCANCODE_T;
	scancode_table[SDL_SCANCODE_Y] = EUI_SCANCODE_Y;
	scancode_table[SDL_SCANCODE_U] = EUI_SCANCODE_U;
	scancode_table[SDL_SCANCODE_I] = EUI_SCANCODE_I;
	scancode_table[SDL_SCANCODE_O] = EUI_SCANCODE_O;
	scancode_table[SDL_SCANCODE_P] = EUI_SCANCODE_P;
	scancode_table[SDL_SCANCODE_LEFTBRACKET] = EUI_SCANCODE_LEFTBRACKET;
	scancode_table[SDL_SCANCODE_RIGHTBRACKET] = EUI_SCANCODE_RIGHTBRACKET;
	scancode_table[SDL_SCANCODE_RETURN] = EUI_SCANCODE_ENTER;
	scancode_table[SDL_SCANCODE_LCTRL] = EUI_SCANCODE_CONTROL;
	scancode_table[SDL_SCANCODE_RCTRL] = EUI_SCANCODE_CONTROL;
	scancode_table[SDL_SCANCODE_A] = EUI_SCANCODE_A;
	scancode_table[SDL_SCANCODE_S] = EUI_SCANCODE_S;
	scancode_table[SDL_SCANCODE_D] = EUI_SCANCODE_D;
	scancode_table[SDL_SCANCODE_F] = EUI_SCANCODE_F;
	scancode_table[SDL_SCANCODE_G] = EUI_SCANCODE_G;
	scancode_table[SDL_SCANCODE_H] = EUI_SCANCODE_H;
	scancode_table[SDL_SCANCODE_J] = EUI_SCANCODE_J;
	scancode_table[SDL_SCANCODE_K] = EUI_SCANCODE_K;
	scancode_table[SDL_SCANCODE_L] = EUI_SCANCODE_L;
	scancode_table[SDL_SCANCODE_SEMICOLON] = EUI_SCANCODE_SEMICOLON;
	scancode_table[SDL_SCANCODE_APOSTROPHE] = EUI_SCANCODE_QUOTE;
	scancode_table[SDL_SCANCODE_GRAVE] = EUI_SCANCODE_TILDE;
	scancode_table[SDL_SCANCODE_LSHIFT] = EUI_SCANCODE_LSHIFT;
	scancode_table[SDL_SCANCODE_BACKSLASH] = EUI_SCANCODE_BACKSLASH;
	scancode_table[SDL_SCANCODE_Z] = EUI_SCANCODE_Z;
	scancode_table[SDL_SCANCODE_X] = EUI_SCANCODE_X;
	scancode_table[SDL_SCANCODE_C] = EUI_SCANCODE_C;
	scancode_table[SDL_SCANCODE_V] = EUI_SCANCODE_V;
	scancode_table[SDL_SCANCODE_B] = EUI_SCANCODE_B;
	scancode_table[SDL_SCANCODE_N] = EUI_SCANCODE_N;
	scancode_table[SDL_SCANCODE_M] = EUI_SCANCODE_M;
	scancode_table[SDL_SCANCODE_COMMA] = EUI_SCANCODE_COMMA;
	scancode_table[SDL_SCANCODE_PERIOD] = EUI_SCANCODE_PERIOD;
	scancode_table[SDL_SCANCODE_SLASH] = EUI_SCANCODE_SLASH;
	scancode_table[SDL_SCANCODE_RSHIFT] = EUI_SCANCODE_RSHIFT;
	scancode_table[SDL_SCANCODE_KP_MULTIPLY] = EUI_SCANCODE_MULTIPLY;
	scancode_table[SDL_SCANCODE_LALT] = EUI_SCANCODE_ALT;
	scancode_table[SDL_SCANCODE_SPACE] = EUI_SCANCODE_SPACE;
	scancode_table[SDL_SCANCODE_CAPSLOCK] = EUI_SCANCODE_CAPSLOCK;
	scancode_table[SDL_SCANCODE_F1] = EUI_SCANCODE_F1;
	scancode_table[SDL_SCANCODE_F2] = EUI_SCANCODE_F2;
	scancode_table[SDL_SCANCODE_F3] = EUI_SCANCODE_F3;
	scancode_table[SDL_SCANCODE_F4] = EUI_SCANCODE_F4;
	scancode_table[SDL_SCANCODE_F5] = EUI_SCANCODE_F5;
	scancode_table[SDL_SCANCODE_F6] = EUI_SCANCODE_F6;
	scancode_table[SDL_SCANCODE_F7] = EUI_SCANCODE_F7;
	scancode_table[SDL_SCANCODE_F8] = EUI_SCANCODE_F8;
	scancode_table[SDL_SCANCODE_F9] = EUI_SCANCODE_F9;
	scancode_table[SDL_SCANCODE_F10] = EUI_SCANCODE_F10;
	scancode_table[SDL_SCANCODE_NUMLOCKCLEAR] = EUI_SCANCODE_NUMLOCK;
	scancode_table[SDL_SCANCODE_SCROLLLOCK] = EUI_SCANCODE_SCROLLLOCK;
	scancode_table[SDL_SCANCODE_HOME] = EUI_SCANCODE_HOME;
	scancode_table[SDL_SCANCODE_UP] = EUI_SCANCODE_UP;
	scancode_table[SDL_SCANCODE_PAGEUP] = EUI_SCANCODE_PAGEUP;
	scancode_table[SDL_SCANCODE_LEFT] = EUI_SCANCODE_LEFT;
	scancode_table[SDL_SCANCODE_RIGHT] = EUI_SCANCODE_RIGHT;
	scancode_table[SDL_SCANCODE_KP_PLUS] = EUI_SCANCODE_PLUS;
	scancode_table[SDL_SCANCODE_END] = EUI_SCANCODE_END;
	scancode_table[SDL_SCANCODE_DOWN] = EUI_SCANCODE_DOWN;
	scancode_table[SDL_SCANCODE_PAGEDOWN] = EUI_SCANCODE_PAGEDOWN;
	scancode_table[SDL_SCANCODE_INSERT] = EUI_SCANCODE_INSERT;
	scancode_table[SDL_SCANCODE_DELETE] = EUI_SCANCODE_DELETE;
	scancode_table[SDL_SCANCODE_F11] = EUI_SCANCODE_F11;
	scancode_table[SDL_SCANCODE_F12] = EUI_SCANCODE_F12;

	scancode_table_initialized = EUI_TRUE;
}

/* begin eui with given SDL_Surface destination */
int eui_begin_sdl2(SDL_Surface *surface)
{
	eui_pixelmap_t dest;

	if (sizeof(eui_color_t) != surface->format->BytesPerPixel)
		return EUI_FALSE;

	dest.w = surface->w;
	dest.h = surface->h;
	dest.pitch = surface->pitch;
	dest.pixels = (eui_color_t *)surface->pixels;

	initialize_scancode_table();

	return eui_begin(dest);
}

/* process and push SDL_Event */
void eui_push_event_sdl2(SDL_Event *event)
{
	eui_event_t eui_event;

	initialize_scancode_table();

	switch (event->type)
	{
		case SDL_KEYDOWN:
			if (scancode_table[event->key.keysym.scancode])
			{
				eui_event.type = EUI_EVENT_KEY_DOWN;
				eui_event.key.scancode = scancode_table[event->key.keysym.scancode];
				eui_push_event(eui_event);
			}
			break;

		case SDL_KEYUP:
			if (scancode_table[event->key.keysym.scancode])
			{
				eui_event.type = EUI_EVENT_KEY_UP;
				eui_event.key.scancode = scancode_table[event->key.keysym.scancode];
				eui_push_event(eui_event);
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (event->button.button)
			{
				case SDL_BUTTON_LEFT:
					eui_event.type = EUI_EVENT_BUTTON_DOWN;
					eui_event.button.x = event->button.x;
					eui_event.button.y = event->button.y;
					eui_event.button.button = EUI_BUTTON_LEFT;
					eui_push_event(eui_event);
					break;

				case SDL_BUTTON_RIGHT:
					eui_event.type = EUI_EVENT_BUTTON_DOWN;
					eui_event.button.x = event->button.x;
					eui_event.button.y = event->button.y;
					eui_event.button.button = EUI_BUTTON_RIGHT;
					eui_push_event(eui_event);
					break;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			switch (event->button.button)
			{
				case SDL_BUTTON_LEFT:
					eui_event.type = EUI_EVENT_BUTTON_UP;
					eui_event.button.x = event->button.x;
					eui_event.button.y = event->button.y;
					eui_event.button.button = EUI_BUTTON_LEFT;
					eui_push_event(eui_event);
					break;

				case SDL_BUTTON_RIGHT:
					eui_event.type = EUI_EVENT_BUTTON_UP;
					eui_event.button.x = event->button.x;
					eui_event.button.y = event->button.y;
					eui_event.button.button = EUI_BUTTON_RIGHT;
					eui_push_event(eui_event);
					break;
			}
			break;

		case SDL_MOUSEMOTION:
			eui_event.type = EUI_EVENT_MOUSE;
			eui_event.mouse.x = event->motion.x;
			eui_event.mouse.y = event->motion.y;
			eui_event.mouse.xrel = event->motion.xrel;
			eui_event.mouse.yrel = event->motion.yrel;
			eui_push_event(eui_event);
			break;

		default:
			break;
	}
}

/* draw SDL_Surface, transformed */
void eui_pixelmap_sdl2(eui_vec2_t pos, SDL_Surface *surface)
{
	eui_pixelmap_t pm;

	if (sizeof(eui_color_t) != surface->format->BytesPerPixel)
		return;

	pm.w = surface->w;
	pm.h = surface->h;
	pm.pitch = surface->pitch;
	pm.pixels = (eui_color_t *)surface->pixels;

	eui_pixelmap(pos, pm);
}
