
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

# compile options
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
	set(EUI_COMPILE_OPTIONS -std=c89 -pedantic -Wall -Wextra)
else()
	set(EUI_COMPILE_OPTIONS)
endif()

# compile definitions
set(EUI_COMPILE_DEFINITIONS EUI_PIXEL_DEPTH=8)

# status
message(STATUS "EUI_COMPILE_OPTIONS: ${EUI_COMPILE_OPTIONS}")
message(STATUS "EUI_COMPILE_DEFINITIONS: ${EUI_COMPILE_DEFINITIONS}")

# basic test
add_executable(test_basic
	${PROJECT_SOURCE_DIR}/source/tests/basic.c
	${PROJECT_SOURCE_DIR}/source/eui.c)
target_compile_definitions(test_basic PUBLIC ${EUI_COMPILE_DEFINITIONS})
target_compile_options(test_basic PUBLIC ${EUI_COMPILE_OPTIONS})
target_include_directories(test_basic PUBLIC ${PROJECT_SOURCE_DIR}/source)

# dos32 test
if(${CMAKE_SYSTEM_NAME} STREQUAL DOS AND NOT ${CMAKE_SYSTEM_PROCESSOR} STREQUAL I86)
	add_executable(test_dos32
		${PROJECT_SOURCE_DIR}/source/tests/dos32.c
		${PROJECT_SOURCE_DIR}/source/eui.c)
	target_compile_definitions(test_dos32 PUBLIC ${EUI_COMPILE_DEFINITIONS})
	target_compile_options(test_basic PUBLIC ${EUI_COMPILE_OPTIONS})
	target_include_directories(test_dos32 PUBLIC ${PROJECT_SOURCE_DIR}/source)
endif()

# sdl2 tests
find_package(SDL2)
if(SDL2_FOUND)
	add_executable(test_sdl2_01
		${PROJECT_SOURCE_DIR}/source/tests/sdl2_01.c
		${PROJECT_SOURCE_DIR}/source/eui.c
		${PROJECT_SOURCE_DIR}/source/eui_sdl2.c)
	target_link_libraries(test_sdl2_01 PUBLIC SDL2::Main)
	target_compile_definitions(test_sdl2_01 PUBLIC ${EUI_COMPILE_DEFINITIONS})
	target_compile_options(test_sdl2_01 PUBLIC ${EUI_COMPILE_OPTIONS})
	target_include_directories(test_sdl2_01 PUBLIC ${PROJECT_SOURCE_DIR}/source)

	add_executable(test_sdl2_02
		${PROJECT_SOURCE_DIR}/source/tests/sdl2_02.c
		${PROJECT_SOURCE_DIR}/source/eui.c
		${PROJECT_SOURCE_DIR}/source/eui_sdl2.c)
	target_link_libraries(test_sdl2_02 PUBLIC SDL2::Main)
	target_compile_definitions(test_sdl2_02 PUBLIC ${EUI_COMPILE_DEFINITIONS})
	target_compile_options(test_sdl2_02 PUBLIC ${EUI_COMPILE_OPTIONS})
	target_include_directories(test_sdl2_02 PUBLIC ${PROJECT_SOURCE_DIR}/source)

	add_executable(test_sdl2_03
		${PROJECT_SOURCE_DIR}/source/tests/sdl2_03.c
		${PROJECT_SOURCE_DIR}/source/eui.c
		${PROJECT_SOURCE_DIR}/source/eui_sdl2.c)
	target_link_libraries(test_sdl2_03 PUBLIC SDL2::Main)
	target_compile_definitions(test_sdl2_03 PUBLIC EUI_PIXEL_DEPTH=1)
	target_compile_options(test_sdl2_03 PUBLIC ${EUI_COMPILE_OPTIONS})
	target_include_directories(test_sdl2_03 PUBLIC ${PROJECT_SOURCE_DIR}/source)

	add_executable(test_sdl2_04
		${PROJECT_SOURCE_DIR}/source/tests/sdl2_04.c
		${PROJECT_SOURCE_DIR}/source/eui.c
		${PROJECT_SOURCE_DIR}/source/eui_sdl2.c)
	target_link_libraries(test_sdl2_04 PUBLIC SDL2::Main)
	target_compile_definitions(test_sdl2_04 PUBLIC EUI_PIXEL_DEPTH=4)
	target_compile_options(test_sdl2_04 PUBLIC ${EUI_COMPILE_OPTIONS})
	target_include_directories(test_sdl2_04 PUBLIC ${PROJECT_SOURCE_DIR}/source)

	configure_file(${PROJECT_SOURCE_DIR}/data/vga.pal ${PROJECT_BINARY_DIR}/vga.pal COPYONLY)
endif()

# editor example
if(SDL2_FOUND)
	add_executable(editor
		${PROJECT_SOURCE_DIR}/source/examples/editor.c
		${PROJECT_SOURCE_DIR}/source/eui.c
		${PROJECT_SOURCE_DIR}/source/eui_sdl2.c
		${PROJECT_SOURCE_DIR}/source/thirdparty/tinyfiledialogs.c)
	target_link_libraries(editor PUBLIC SDL2::Main)
	target_compile_definitions(editor PUBLIC ${EUI_COMPILE_DEFINITIONS})
	target_compile_options(editor PUBLIC ${EUI_COMPILE_OPTIONS})
	target_include_directories(editor PUBLIC ${PROJECT_SOURCE_DIR}/source)
	target_include_directories(editor PUBLIC ${PROJECT_SOURCE_DIR}/source/thirdparty)
endif()
