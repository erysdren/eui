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

#pragma once
#ifndef _EXAMPLES_H_
#define _EXAMPLES_H_
#ifdef __cplusplus
extern "C" {
#endif

#ifndef EXAMPLE_FUNC
#define EXAMPLE_FUNC example_hello
#endif

#ifndef EXAMPLE_TITLE
#define EXAMPLE_TITLE "EUI Example"
#endif

#ifndef EXAMPLE_WIDTH
#define EXAMPLE_WIDTH (640)
#endif

#ifndef EXAMPLE_HEIGHT
#define EXAMPLE_HEIGHT (480)
#endif

/* hello.c */
void example_hello(void);

/* order.c */
void example_order(void);

/* font.c */
void example_font(void);

/* windows.c */
void example_windows(void);

/* standalone.c */
void example_standalone(void);

/* cursor.c */
void example_cursor(void);

/* widgets.c */
void example_widgets(void);

/* bitmap.c */
void example_bitmap(void);

#ifdef __cplusplus
}
#endif
#endif /* _EXAMPLES_H_ */
