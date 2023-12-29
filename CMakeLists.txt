
# cmake settings
cmake_minimum_required(VERSION 3.5)
project(EUI
	DESCRIPTION "UI and drawing library with a small footprint written in C89"
	HOMEPAGE_URL "https://github.com/erysdren/eui/"
	LANGUAGES C
	VERSION 0.0.1
)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# default compile options
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
	set(EUI_COMPILE_OPTIONS -std=c89 -pedantic -Wall -Wextra)
else()
	set(EUI_COMPILE_OPTIONS)
endif()

# default compile definitions
set(EUI_COMPILE_DEFINITIONS EUI_PIXEL_DEPTH=8)

# print status
message(STATUS "EUI_COMPILE_OPTIONS: ${EUI_COMPILE_OPTIONS}")
message(STATUS "EUI_COMPILE_DEFINITIONS: ${EUI_COMPILE_DEFINITIONS}")

#
# SDL2 examples
#

find_package(SDL2)
if(SDL2_FOUND)

	# hello
	add_executable(hello_sdl2
		${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2.c
		${PROJECT_SOURCE_DIR}/source/examples/hello.c
		${PROJECT_SOURCE_DIR}/source/eui/eui.c)
	target_compile_options(hello_sdl2 PUBLIC ${EUI_COMPILE_OPTIONS})
	target_compile_definitions(hello_sdl2 PUBLIC ${EUI_COMPILE_DEFINITIONS})
	target_include_directories(hello_sdl2 PUBLIC ${PROJECT_SOURCE_DIR}/source/eui)
	target_link_libraries(hello_sdl2 SDL2::Main)

	# hello (4bpp)
	add_executable(hello_sdl2_4bpp
		${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2_4bpp.c
		${PROJECT_SOURCE_DIR}/source/examples/hello.c
		${PROJECT_SOURCE_DIR}/source/eui/eui.c)
	target_compile_options(hello_sdl2_4bpp PUBLIC ${EUI_COMPILE_OPTIONS})
	target_compile_definitions(hello_sdl2_4bpp PUBLIC ${EUI_COMPILE_DEFINITIONS})
	target_include_directories(hello_sdl2_4bpp PUBLIC ${PROJECT_SOURCE_DIR}/source/eui)
	target_link_libraries(hello_sdl2_4bpp SDL2::Main)

	# order
	add_executable(order_sdl2
		${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2.c
		${PROJECT_SOURCE_DIR}/source/examples/order.c
		${PROJECT_SOURCE_DIR}/source/eui/eui.c)
	target_compile_options(order_sdl2 PUBLIC ${EUI_COMPILE_OPTIONS})
	target_compile_definitions(order_sdl2 PUBLIC ${EUI_COMPILE_DEFINITIONS} EXAMPLE_FUNC=example_order)
	target_include_directories(order_sdl2 PUBLIC ${PROJECT_SOURCE_DIR}/source/eui)
	target_link_libraries(order_sdl2 SDL2::Main)

	# order (4bpp)
	add_executable(order_sdl2_4bpp
		${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2_4bpp.c
		${PROJECT_SOURCE_DIR}/source/examples/order.c
		${PROJECT_SOURCE_DIR}/source/eui/eui.c)
	target_compile_options(order_sdl2_4bpp PUBLIC ${EUI_COMPILE_OPTIONS})
	target_compile_definitions(order_sdl2_4bpp PUBLIC ${EUI_COMPILE_DEFINITIONS} EXAMPLE_FUNC=example_order)
	target_include_directories(order_sdl2_4bpp PUBLIC ${PROJECT_SOURCE_DIR}/source/eui)
	target_link_libraries(order_sdl2_4bpp SDL2::Main)

	# font
	add_executable(font_sdl2
		${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2.c
		${PROJECT_SOURCE_DIR}/source/examples/font.c
		${PROJECT_SOURCE_DIR}/source/eui/eui.c)
	target_compile_options(font_sdl2 PUBLIC ${EUI_COMPILE_OPTIONS})
	target_compile_definitions(font_sdl2 PUBLIC ${EUI_COMPILE_DEFINITIONS} EXAMPLE_FUNC=example_font)
	target_include_directories(font_sdl2 PUBLIC ${PROJECT_SOURCE_DIR}/source/eui)
	target_link_libraries(font_sdl2 SDL2::Main)

	# font (4bpp)
	add_executable(font_sdl2_4bpp
		${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2_4bpp.c
		${PROJECT_SOURCE_DIR}/source/examples/font.c
		${PROJECT_SOURCE_DIR}/source/eui/eui.c)
	target_compile_options(font_sdl2_4bpp PUBLIC ${EUI_COMPILE_OPTIONS})
	target_compile_definitions(font_sdl2_4bpp PUBLIC ${EUI_COMPILE_DEFINITIONS} EXAMPLE_FUNC=example_font)
	target_include_directories(font_sdl2_4bpp PUBLIC ${PROJECT_SOURCE_DIR}/source/eui)
	target_link_libraries(font_sdl2_4bpp SDL2::Main)

endif()

#
# DOS examples
#

if(${CMAKE_SYSTEM_NAME} STREQUAL DOS)

	# hello
	add_executable(hello_dos
		${PROJECT_SOURCE_DIR}/source/examples/harness_dos.c
		${PROJECT_SOURCE_DIR}/source/examples/hello.c
		${PROJECT_SOURCE_DIR}/source/eui/eui.c)
	target_compile_options(hello_dos PUBLIC ${EUI_COMPILE_OPTIONS})
	target_compile_definitions(hello_dos PUBLIC ${EUI_COMPILE_DEFINITIONS})
	target_include_directories(hello_dos PUBLIC ${PROJECT_SOURCE_DIR}/source/eui)

	# order
	add_executable(order_dos
		${PROJECT_SOURCE_DIR}/source/examples/harness_dos.c
		${PROJECT_SOURCE_DIR}/source/examples/order.c
		${PROJECT_SOURCE_DIR}/source/eui/eui.c)
	target_compile_options(order_dos PUBLIC ${EUI_COMPILE_OPTIONS})
	target_compile_definitions(order_dos PUBLIC ${EUI_COMPILE_DEFINITIONS} EXAMPLE_FUNC=example_order)
	target_include_directories(order_dos PUBLIC ${PROJECT_SOURCE_DIR}/source/eui)

endif()
