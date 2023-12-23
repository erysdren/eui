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
 * EUI_SDL2.C
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include "eui_sdl2.h"

static const int eui_scancode_from_sdl2[SDL_NUM_SCANCODES] = {
	[SDL_SCANCODE_ESCAPE] = EUI_SCANCODE_ESCAPE,
	[SDL_SCANCODE_1] = EUI_SCANCODE_1,
	[SDL_SCANCODE_2] = EUI_SCANCODE_2,
	[SDL_SCANCODE_3] = EUI_SCANCODE_3,
	[SDL_SCANCODE_4] = EUI_SCANCODE_4,
	[SDL_SCANCODE_5] = EUI_SCANCODE_5,
	[SDL_SCANCODE_6] = EUI_SCANCODE_6,
	[SDL_SCANCODE_7] = EUI_SCANCODE_7,
	[SDL_SCANCODE_8] = EUI_SCANCODE_8,
	[SDL_SCANCODE_9] = EUI_SCANCODE_9,
	[SDL_SCANCODE_0] = EUI_SCANCODE_0,
	[SDL_SCANCODE_MINUS] = EUI_SCANCODE_MINUS,
	[SDL_SCANCODE_EQUALS] = EUI_SCANCODE_EQUALS,
	[SDL_SCANCODE_BACKSPACE] = EUI_SCANCODE_BACKSPACE,
	[SDL_SCANCODE_TAB] = EUI_SCANCODE_TAB,
	[SDL_SCANCODE_Q] = EUI_SCANCODE_Q,
	[SDL_SCANCODE_W] = EUI_SCANCODE_W,
	[SDL_SCANCODE_E] = EUI_SCANCODE_E,
	[SDL_SCANCODE_R] = EUI_SCANCODE_R,
	[SDL_SCANCODE_T] = EUI_SCANCODE_T,
	[SDL_SCANCODE_Y] = EUI_SCANCODE_Y,
	[SDL_SCANCODE_U] = EUI_SCANCODE_U,
	[SDL_SCANCODE_I] = EUI_SCANCODE_I,
	[SDL_SCANCODE_O] = EUI_SCANCODE_O,
	[SDL_SCANCODE_P] = EUI_SCANCODE_P,
	[SDL_SCANCODE_LEFTBRACKET] = EUI_SCANCODE_LEFTBRACKET,
	[SDL_SCANCODE_RIGHTBRACKET] = EUI_SCANCODE_RIGHTBRACKET,
	[SDL_SCANCODE_RETURN] = EUI_SCANCODE_ENTER,
	[SDL_SCANCODE_LCTRL] = EUI_SCANCODE_CONTROL,
	[SDL_SCANCODE_RCTRL] = EUI_SCANCODE_CONTROL,
	[SDL_SCANCODE_A] = EUI_SCANCODE_A,
	[SDL_SCANCODE_S] = EUI_SCANCODE_S,
	[SDL_SCANCODE_D] = EUI_SCANCODE_D,
	[SDL_SCANCODE_F] = EUI_SCANCODE_F,
	[SDL_SCANCODE_G] = EUI_SCANCODE_G,
	[SDL_SCANCODE_H] = EUI_SCANCODE_H,
	[SDL_SCANCODE_J] = EUI_SCANCODE_J,
	[SDL_SCANCODE_K] = EUI_SCANCODE_K,
	[SDL_SCANCODE_L] = EUI_SCANCODE_L,
	[SDL_SCANCODE_SEMICOLON] = EUI_SCANCODE_SEMICOLON,
	[SDL_SCANCODE_APOSTROPHE] = EUI_SCANCODE_QUOTE,
	[SDL_SCANCODE_GRAVE] = EUI_SCANCODE_TILDE,
	[SDL_SCANCODE_LSHIFT] = EUI_SCANCODE_LSHIFT,
	[SDL_SCANCODE_BACKSLASH] = EUI_SCANCODE_BACKSLASH,
	[SDL_SCANCODE_Z] = EUI_SCANCODE_Z,
	[SDL_SCANCODE_X] = EUI_SCANCODE_X,
	[SDL_SCANCODE_C] = EUI_SCANCODE_C,
	[SDL_SCANCODE_V] = EUI_SCANCODE_V,
	[SDL_SCANCODE_B] = EUI_SCANCODE_B,
	[SDL_SCANCODE_N] = EUI_SCANCODE_N,
	[SDL_SCANCODE_M] = EUI_SCANCODE_M,
	[SDL_SCANCODE_COMMA] = EUI_SCANCODE_COMMA,
	[SDL_SCANCODE_PERIOD] = EUI_SCANCODE_PERIOD,
	[SDL_SCANCODE_SLASH] = EUI_SCANCODE_SLASH,
	[SDL_SCANCODE_RSHIFT] = EUI_SCANCODE_RSHIFT,
	[SDL_SCANCODE_KP_MULTIPLY] = EUI_SCANCODE_MULTIPLY,
	[SDL_SCANCODE_LALT] = EUI_SCANCODE_ALT,
	[SDL_SCANCODE_SPACE] = EUI_SCANCODE_SPACE,
	[SDL_SCANCODE_CAPSLOCK] = EUI_SCANCODE_CAPSLOCK,
	[SDL_SCANCODE_F1] = EUI_SCANCODE_F1,
	[SDL_SCANCODE_F2] = EUI_SCANCODE_F2,
	[SDL_SCANCODE_F3] = EUI_SCANCODE_F3,
	[SDL_SCANCODE_F4] = EUI_SCANCODE_F4,
	[SDL_SCANCODE_F5] = EUI_SCANCODE_F5,
	[SDL_SCANCODE_F6] = EUI_SCANCODE_F6,
	[SDL_SCANCODE_F7] = EUI_SCANCODE_F7,
	[SDL_SCANCODE_F8] = EUI_SCANCODE_F8,
	[SDL_SCANCODE_F9] = EUI_SCANCODE_F9,
	[SDL_SCANCODE_F10] = EUI_SCANCODE_F10,
	[SDL_SCANCODE_NUMLOCKCLEAR] = EUI_SCANCODE_NUMLOCK,
	[SDL_SCANCODE_SCROLLLOCK] = EUI_SCANCODE_SCROLLLOCK,
	[SDL_SCANCODE_HOME] = EUI_SCANCODE_HOME,
	[SDL_SCANCODE_UP] = EUI_SCANCODE_UP,
	[SDL_SCANCODE_PAGEUP] = EUI_SCANCODE_PAGEUP,
	[SDL_SCANCODE_LEFT] = EUI_SCANCODE_LEFT,
	[SDL_SCANCODE_RIGHT] = EUI_SCANCODE_RIGHT,
	[SDL_SCANCODE_KP_PLUS] = EUI_SCANCODE_PLUS,
	[SDL_SCANCODE_END] = EUI_SCANCODE_END,
	[SDL_SCANCODE_DOWN] = EUI_SCANCODE_DOWN,
	[SDL_SCANCODE_PAGEDOWN] = EUI_SCANCODE_PAGEDOWN,
	[SDL_SCANCODE_INSERT] = EUI_SCANCODE_INSERT,
	[SDL_SCANCODE_DELETE] = EUI_SCANCODE_DELETE,
	[SDL_SCANCODE_F11] = EUI_SCANCODE_F11,
	[SDL_SCANCODE_F12] = EUI_SCANCODE_F12
};

/* begin eui with given SDL_Surface destination */
bool eui_begin_sdl2(SDL_Surface *surface)
{
	eui_pixelmap_t dest;

	if (sizeof(eui_color_t) != surface->format->BytesPerPixel)
		return false;

	dest.w = surface->w;
	dest.h = surface->h;
	dest.pitch = surface->pitch;
	dest.pixels = (eui_color_t *)surface->pixels;

	return eui_begin(dest);
}

/* process and push SDL_Event */
void eui_push_event_sdl2(SDL_Event *event)
{
	eui_event_t eui_event;

	switch (event->type)
	{
		case SDL_KEYDOWN:
			if (eui_scancode_from_sdl2[event->key.keysym.scancode])
			{
				eui_event.type = EUI_EVENT_KEY_DOWN;
				eui_event.key.scancode = eui_scancode_from_sdl2[event->key.keysym.scancode];
				eui_push_event(eui_event);
			}
			break;

		case SDL_KEYUP:
			if (eui_scancode_from_sdl2[event->key.keysym.scancode])
			{
				eui_event.type = EUI_EVENT_KEY_UP;
				eui_event.key.scancode = eui_scancode_from_sdl2[event->key.keysym.scancode];
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
