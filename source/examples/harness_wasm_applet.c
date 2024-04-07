/*
MIT License
Copyright (c) 2023-2024 erysdren (it/she/they)
Copyright (c) 2023 Ada <ada@thingvellir.net>

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

/* WebAssembly Applet API frontend for EUI
 * spec: <https://thingvellir.net/log/2024-01-01.html>
 */
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "eui.h"
#include "eui_evnt.h"
#include "examples.h"
#include "palette_vga.h"

/* required libc functions that aren't available on freestanding */
void *memset(void *raw, int c, size_t n)
{
	size_t i;
	char *ptr = raw;

	for (i = 0; i < n; i++)
		ptr[i] = c;

	return ptr;
}

void *memcpy(void *dest, const void *src, size_t n)
{
	size_t i;
	const char *in = (const char *)src;
	char *out = (char *)dest;

	for (i = 0; i < n; i++)
		out[i] = in[i];

	return (void *)out;
}

size_t strlen(const char *ptr)
{
	size_t len = 0;

	while (*ptr++)
		len++;

	return len;
}

/* not needed? */
#if 0
extern char __heap_base; /* provided by clang */
static intptr_t heap_ptr = &__heap_base;

void *malloc(size_t len)
{
	intptr_t ptr = heap_ptr;

	/* TODO: alignment */
	heap_ptr += len;

	return (void *)ptr;
}

void free(void *ptr)
{
	EUI_UNUSED(ptr);
}
#endif


#if !defined(__clang__)
#error "WebAssembly Applet frontend requires clang-specific attributes"
#endif

#define IMPORT(ns, sym) __attribute__((import_module((ns)), import_name((sym))))
#define EXPORT(name) __attribute__((visibility("default"), export_name((name))))

#define DISPLAY_WIDTH  320
#define DISPLAY_HEIGHT 240

static uint8_t fb_8bit[DISPLAY_WIDTH * DISPLAY_HEIGHT];

static uint32_t fb_palette[256];
static uint32_t fb_32bit[DISPLAY_WIDTH * DISPLAY_HEIGHT];

/* unused by this harness, but allows writing out text */
IMPORT("Applet", "Write")
extern void AppletWrite(const char *ptr, size_t len);

EXPORT("AppletDisplayWidth")
int AppletDisplayWidth(void)
{
	return DISPLAY_WIDTH;
}

EXPORT("AppletDisplayHeight")
int AppletDisplayHeight(void)
{
	return DISPLAY_HEIGHT;
}

EXPORT("AppletDisplayPtr")
uint32_t *AppletDisplayPtr(void)
{
	return fb_32bit;
}

EXPORT("AppletStart")
void AppletStart(void)
{
	size_t i, j;

	for (i = 0, j = 0; i < 256; i++, j += 3)
	{
		/* html5 canvas expects RGBA8888 and wasm is
		 * little-endian, so encode the palette as XBGR */
		fb_palette[i] =
			0xff000000
			| (palette_vga[j + 2] << 16)
			| (palette_vga[j + 1] << 8)
			| (palette_vga[j + 0] << 0);
	}

	eui_init(
		DISPLAY_WIDTH,
		DISPLAY_HEIGHT,
		8,
		DISPLAY_WIDTH,
		(void *)fb_8bit
	);
}

EXPORT("AppletQuit")
void AppletQuit(void)
{
	eui_quit();
}

EXPORT("AppletRender")
void AppletRender(void)
{
	size_t i;

	if (eui_context_begin())
	{
		EXAMPLE_FUNC();
		eui_context_end();

		for (i = 0; i < (DISPLAY_WIDTH * DISPLAY_HEIGHT); i++)
		{
			/* convert 8bit paletted to rgba8888 */
			fb_32bit[i] = fb_palette[fb_8bit[i]];
		}
	}
}

EXPORT("AppletEvent")
int AppletEvent(int kind, int arg_1, int arg_2, int arg_3)
{
	eui_event_t e;

	switch (kind) {
		case 0x00: /* key down */
			e.type = EUI_EVENT_KEY_DOWN;
			e.key.scancode = arg_1;
			break;

		case 0x01: /* key up */
			e.type = EUI_EVENT_KEY_UP;
			e.key.scancode = arg_1;
			break;

		case 0x02: /* mouse click */
			e.type = EUI_EVENT_BUTTON_DOWN;
			e.button.x = (int)arg_1;
			e.button.y = (int)arg_2;
			e.button.button = arg_3;
			break;

		case 0x03: /* mouse unclick */
			e.type = EUI_EVENT_BUTTON_UP;
			e.button.x = (int)arg_1;
			e.button.y = (int)arg_2;
			e.button.button = arg_3;
			break;

		case 0x04: /* absolute mouse movement */
			e.type = EUI_EVENT_CURSOR;
			e.cursor.x = (int)arg_1;
			e.cursor.y = (int)arg_2;
			break;

		case 0x05: /* relative mouse movement */
			e.type = EUI_EVENT_CURSOR;
			e.cursor.xrel = (int)arg_1;
			e.cursor.yrel = (int)arg_2;
			break;

		/* event left unhandled */
		default:
			return 0;
	}

	eui_event_push(&e);

	/* event was handled */
	return 1;
}
