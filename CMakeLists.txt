
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
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/external/sdl2-cmake-modules")

# options
option(EUI_BUILD_EXAMPLES "Build Example Applications" ON)
option(EUI_INSTALL_TARGET "Enable Install Target" ON)

# default compile options
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
	set(EUI_COMPILE_OPTIONS -std=c89 -pedantic -Wall -Wextra)
else()
	set(EUI_COMPILE_OPTIONS)
endif()

# default compile definitions
set(EUI_COMPILE_DEFINITIONS)

# print status
message(STATUS "EUI_COMPILE_OPTIONS: ${EUI_COMPILE_OPTIONS}")
message(STATUS "EUI_COMPILE_DEFINITIONS: ${EUI_COMPILE_DEFINITIONS}")

#
# library
#

add_library(eui
	${PROJECT_SOURCE_DIR}/source/eui/eui.c
	${PROJECT_SOURCE_DIR}/source/eui/eui_evnt.c
	${PROJECT_SOURCE_DIR}/source/eui/eui_widg.c)
target_compile_options(eui PRIVATE ${EUI_COMPILE_OPTIONS})
target_compile_definitions(eui PRIVATE ${EUI_COMPILE_DEFINITIONS})
target_include_directories(eui PUBLIC ${PROJECT_SOURCE_DIR}/source/eui)

#
# SDL2 helper library
#

find_package(SDL2)
if(SDL2_FOUND)
	add_library(eui_sdl2
			${PROJECT_SOURCE_DIR}/source/eui/eui_sdl2.c)
	target_compile_options(eui_sdl2 PRIVATE ${EUI_COMPILE_OPTIONS})
	target_compile_definitions(eui_sdl2 PRIVATE ${EUI_COMPILE_DEFINITIONS})
	target_include_directories(eui_sdl2 PUBLIC ${PROJECT_SOURCE_DIR}/source/eui)
	target_link_libraries(eui_sdl2 SDL2::Main eui)
endif()

#
# install target
#

if(EUI_INSTALL_TARGET)
	set(EUI_HEADERS ${PROJECT_SOURCE_DIR}/source/eui/eui.h)
	include(${PROJECT_SOURCE_DIR}/cmake/install.cmake)
endif()

#
# examples
#

if(EUI_BUILD_EXAMPLES)

	#
	# SDL2 examples
	#

	if(SDL2_FOUND)

		# hello
		add_executable(hello_sdl2
			${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2.c
			${PROJECT_SOURCE_DIR}/source/examples/hello.c)
		target_compile_definitions(hello_sdl2 PUBLIC
			EXAMPLE_FUNC=example_hello)
		target_link_libraries(hello_sdl2 SDL2::Main eui eui_sdl2)

		# hello (4bpp)
		add_executable(hello_sdl2_4bpp
			${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2_4bpp.c
			${PROJECT_SOURCE_DIR}/source/examples/hello.c)
		target_compile_definitions(hello_sdl2_4bpp PUBLIC
			EXAMPLE_FUNC=example_hello)
		target_link_libraries(hello_sdl2_4bpp eui_sdl2)

		# order
		add_executable(order_sdl2
			${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2.c
			${PROJECT_SOURCE_DIR}/source/examples/order.c)
		target_compile_definitions(order_sdl2 PUBLIC
			EXAMPLE_FUNC=example_order)
		target_link_libraries(order_sdl2 eui_sdl2)

		# order (4bpp)
		add_executable(order_sdl2_4bpp
			${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2_4bpp.c
			${PROJECT_SOURCE_DIR}/source/examples/order.c)
		target_compile_definitions(order_sdl2_4bpp PUBLIC
			EXAMPLE_FUNC=example_order)
		target_link_libraries(order_sdl2_4bpp eui_sdl2)

		# font
		add_executable(font_sdl2
			${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2.c
			${PROJECT_SOURCE_DIR}/source/examples/font.c)
		target_compile_definitions(font_sdl2 PUBLIC
			EXAMPLE_FUNC=example_font)
		target_link_libraries(font_sdl2 eui_sdl2)

		# font (4bpp)
		add_executable(font_sdl2_4bpp
			${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2_4bpp.c
			${PROJECT_SOURCE_DIR}/source/examples/font.c)
		target_compile_definitions(font_sdl2_4bpp PUBLIC
			EXAMPLE_FUNC=example_font)
		target_link_libraries(font_sdl2_4bpp eui_sdl2)

		# windows
		add_executable(windows_sdl2
			${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2.c
			${PROJECT_SOURCE_DIR}/source/examples/windows.c)
		target_compile_definitions(windows_sdl2 PUBLIC
			EXAMPLE_FUNC=example_windows)
		target_link_libraries(windows_sdl2 eui_sdl2)

		# windows (4bpp)
		add_executable(windows_sdl2_4bpp
			${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2_4bpp.c
			${PROJECT_SOURCE_DIR}/source/examples/windows.c)
		target_compile_definitions(windows_sdl2_4bpp PUBLIC
			EXAMPLE_FUNC=example_windows)
		target_link_libraries(windows_sdl2_4bpp eui_sdl2)

		# standalone
		add_executable(standalone_sdl2
			${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2.c
			${PROJECT_SOURCE_DIR}/source/examples/standalone.c)
		target_compile_definitions(standalone_sdl2 PUBLIC
			EXAMPLE_FUNC=example_standalone
			EXAMPLE_STANDALONE=1)
		target_link_libraries(standalone_sdl2 eui_sdl2)

		# standalone (4bpp)
		add_executable(standalone_sdl2_4bpp
			${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2_4bpp.c
			${PROJECT_SOURCE_DIR}/source/examples/standalone.c)
		target_compile_definitions(standalone_sdl2_4bpp PUBLIC
			EXAMPLE_FUNC=example_standalone
			EXAMPLE_STANDALONE=1)
		target_link_libraries(standalone_sdl2_4bpp eui_sdl2)

		# cursor
		add_executable(cursor_sdl2
			${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2.c
			${PROJECT_SOURCE_DIR}/source/examples/cursor.c)
		target_compile_definitions(cursor_sdl2 PUBLIC
			EXAMPLE_FUNC=example_cursor)
		target_link_libraries(cursor_sdl2 eui_sdl2)

		# cursor (4bpp)
		add_executable(cursor_sdl2_4bpp
			${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2_4bpp.c
			${PROJECT_SOURCE_DIR}/source/examples/cursor.c)
		target_compile_definitions(cursor_sdl2_4bpp PUBLIC
			EXAMPLE_FUNC=example_cursor)
		target_link_libraries(cursor_sdl2_4bpp eui_sdl2)

		# widgets
		add_executable(widgets_sdl2
			${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2.c
			${PROJECT_SOURCE_DIR}/source/examples/widgets.c)
		target_compile_definitions(widgets_sdl2 PUBLIC
			EXAMPLE_FUNC=example_widgets)
		target_link_libraries(widgets_sdl2 eui_sdl2)

		# widgets (4bpp)
		add_executable(widgets_sdl2_4bpp
			${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2_4bpp.c
			${PROJECT_SOURCE_DIR}/source/examples/widgets.c)
		target_compile_definitions(widgets_sdl2_4bpp PUBLIC
			EXAMPLE_FUNC=example_widgets)
		target_link_libraries(widgets_sdl2_4bpp eui_sdl2)

		# bitmap
		add_executable(bitmap_sdl2
			${PROJECT_SOURCE_DIR}/source/examples/harness_sdl2.c
			${PROJECT_SOURCE_DIR}/source/examples/bitmap.c)
		target_compile_definitions(bitmap_sdl2 PUBLIC
			EXAMPLE_FUNC=example_bitmap)
		target_link_libraries(bitmap_sdl2 eui_sdl2)

	endif()

	#
	# DOS examples
	#

	if(${CMAKE_SYSTEM_NAME} STREQUAL DOS)

		# hello
		add_executable(hello_dos
			${PROJECT_SOURCE_DIR}/source/examples/harness_dos.c
			${PROJECT_SOURCE_DIR}/source/examples/hello.c)
		target_compile_definitions(hello_dos PUBLIC
			EXAMPLE_FUNC=example_hello)
		target_link_libraries(hello_dos eui)

		# order
		add_executable(order_dos
			${PROJECT_SOURCE_DIR}/source/examples/harness_dos.c
			${PROJECT_SOURCE_DIR}/source/examples/order.c)
		target_compile_definitions(order_dos PUBLIC
			EXAMPLE_FUNC=example_order)
		target_link_libraries(order_dos eui)

		# font
		add_executable(font_dos
			${PROJECT_SOURCE_DIR}/source/examples/harness_dos.c
			${PROJECT_SOURCE_DIR}/source/examples/font.c)
		target_compile_definitions(font_dos PUBLIC
			EXAMPLE_FUNC=example_font)
		target_link_libraries(font_dos eui)

		# windows
		add_executable(windows_dos
			${PROJECT_SOURCE_DIR}/source/examples/harness_dos.c
			${PROJECT_SOURCE_DIR}/source/examples/windows.c)
		target_compile_definitions(windows_dos PUBLIC
			EXAMPLE_FUNC=example_windows)
		target_link_libraries(windows_dos eui)

		# standalone
		add_executable(standalone_dos
			${PROJECT_SOURCE_DIR}/source/examples/harness_dos.c
			${PROJECT_SOURCE_DIR}/source/examples/standalone.c)
		target_compile_definitions(standalone_dos PUBLIC
			EXAMPLE_FUNC=example_standalone
			EXAMPLE_STANDALONE=1)
		target_link_libraries(standalone_dos eui)

	endif()

endif()
