
![EUI Example](./.github/eui.png "EUI Example")

# EUI

EUI is a small UI and drawing library designed for homebrew games, debug UIs, embedded systems, and low resolution or low color depth displays.

The main EUI library is only two files, [`eui.c`](./source/eui.c) and [`eui.h`](./source/eui.h). To add EUI to your project, just clone the files into your source tree and compile.

## Source Code Guide

- [`eui.c`](./source/eui.c) & [`eui.h`](./source/eui.h): Main platform agnostic EUI library.
- [`eui_sdl2.c`](./source/eui_sdl2.c) & [`eui_sdl2.h`](./source/eui_sdl2.h): Helper functions for integration with SDL2.

## Credits

- EUI uses [Daniel Hepper's font8x8](https://github.com/dhepper/font8x8/) (License: Public Domain).
- EUI uses code ported from [Shpuld's SUI](https://github.com/shpuld/sui-qc/) (License: MIT).

## License

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
