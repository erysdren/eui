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
 * EUI_EVNT.C
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>

#include "eui_evnt.h"

/*
 *
 * state
 *
 */

/* keyboard state */
static unsigned char keys[256] = {0};

/* key buffer */
#define KEY_BUFFER_SIZE (64)
#define KEY_BUFFER_ADVANCE(x) ((x) = ((x) + 1) & (KEY_BUFFER_SIZE - 1))
static int key_buffer[KEY_BUFFER_SIZE] = {0};
static int key_buffer_ridx = 0;
static int key_buffer_widx = 0;

/* cursor state */
static int cursor_x = 0;
static int cursor_y = 0;

/* button state */
static int button = 0;

/* event queue */
static eui_event_t events[EUI_MAX_EVENTS] = {0};
static int num_events = 0;

/*
 *
 * public functions
 *
 */

/*
 * input reading
 */

/* read cursor position */
void eui_cursor_read(int *x, int *y)
{
	if (x)
		*x = cursor_x;

	if (y)
		*y = cursor_y;
}

/* read button state */
int eui_button_read(void)
{
	return button;
}

/*
 * utilities
 */

/* returns EUI_TRUE if the cursor is hovering over the given box */
int eui_cursor_hovering(int x, int y, int w, int h)
{
	int cursor_x, cursor_y;

	eui_cursor_read(&cursor_x, &cursor_y);

	eui_transform_box(&x, &y, w, h);

	if (cursor_x < x || cursor_x > x + w)
		return EUI_FALSE;
	if (cursor_y < y || cursor_y > y + h)
		return EUI_FALSE;

	return EUI_TRUE;
}

/*
 * keyboard handling
 */

/* get pointer to array of chars defining what keys are currently pressed */
const unsigned char *eui_key_state_get(int *num_keys)
{
	if (num_keys)
		*num_keys = 256;
	return (const unsigned char *)keys;
}

/* push key to the queue */
void eui_key_push(int scancode)
{
	key_buffer[key_buffer_widx] = scancode;
	KEY_BUFFER_ADVANCE(key_buffer_widx);
	if (key_buffer_widx == key_buffer_ridx)
		KEY_BUFFER_ADVANCE(key_buffer_ridx);
}

/* pop key from the top of the queue */
int eui_key_pop(void)
{
	int res = -1;

	if (key_buffer_ridx == key_buffer_widx)
		return res;

	res = key_buffer[key_buffer_ridx];
	KEY_BUFFER_ADVANCE(key_buffer_ridx);

	return res;
}

/*
 * event handling
 */

/* process all queued events */
/* returns EUI_FALSE on failure */
int eui_event_queue_process(void)
{
	eui_event_t event;

	/* process event queue */
	while (eui_event_pop(&event))
	{
		switch (event.type)
		{
			case EUI_EVENT_KEY_DOWN:
				keys[event.key.scancode] = EUI_TRUE;
				eui_key_push(event.key.scancode);
				break;

			case EUI_EVENT_KEY_UP:
				keys[event.key.scancode] = EUI_FALSE;
				break;

			case EUI_EVENT_CURSOR:
				cursor_x = event.cursor.x;
				cursor_y = event.cursor.y;
				break;

			case EUI_EVENT_BUTTON_DOWN:
				button |= event.button.button;
				break;

			case EUI_EVENT_BUTTON_UP:
				button &= ~event.button.button;
				break;

			default:
				return EUI_FALSE;
		}
	}

	return EUI_TRUE;
}

/* clear event queue and state */
void eui_event_queue_clear(void)
{
	num_events = 0;
	memset(events, 0, sizeof(events));
	cursor_x = 0;
	cursor_y = 0;
	button = 0;
	memset(keys, 0, sizeof(keys));
}

/* push event to the queue */
/* returns EUI_FALSE on failure */
int eui_event_push(eui_event_t *event)
{
	/* early out */
	if (num_events == EUI_MAX_EVENTS - 1)
		return EUI_FALSE;

	/* increment and copy event in */
	memcpy(&events[++num_events], event, sizeof(eui_event_t));

	return EUI_TRUE;
}

/* pop event from the top of the queue */
/* returns the number of events left in the queue */
int eui_event_pop(eui_event_t *event)
{
	/* early out */
	if (!num_events)
		return 0;

	/* pop top event */
	memcpy(event, &events[num_events], sizeof(eui_event_t));

	/* clear top event */
	memset(&events[num_events], 0, sizeof(eui_event_t));

	/* decrement */
	return num_events--;
}
