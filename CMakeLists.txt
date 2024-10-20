cmake_minimum_required(VERSION 3.28)
project(eui
	DESCRIPTION "UI and drawing library with a small footprint written in C89"
	HOMEPAGE_URL "https://github.com/erysdren/eui"
	LANGUAGES C
	VERSION 0.0.2
)

# options

option(EUI_BUILD_EXAMPLES "Build EUI Examples" ON)

# library

add_library(eui STATIC)

target_sources(eui PRIVATE
	${PROJECT_SOURCE_DIR}/source/eui.c
	${PROJECT_SOURCE_DIR}/source/eui_evnt.c
	${PROJECT_SOURCE_DIR}/source/eui_widg.c
)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
	target_compile_options(eui PRIVATE -std=c89 -pedantic -Wall -Wextra)
endif()

target_include_directories(eui PUBLIC ${PROJECT_SOURCE_DIR}/include)

# sdl2 bridge library
find_package(SDL2)
if(SDL2_FOUND)
	add_library(eui_sdl2 STATIC)

	target_sources(eui_sdl2 PRIVATE
		${PROJECT_SOURCE_DIR}/source/eui_sdl2.c
	)

	if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
		target_compile_options(eui_sdl2 PRIVATE -std=c89 -pedantic -Wall -Wextra)
	endif()

	target_link_libraries(eui_sdl2 PUBLIC eui SDL2::SDL2)
endif()

# examples

if(EUI_BUILD_EXAMPLES)

	# sdl2
	if(SDL2_FOUND)
		# 8bpp
		foreach(example hello order font windows standalone cursor widgets bitmap)
			add_executable(${example}_sdl2)
			target_sources(${example}_sdl2 PUBLIC
				${PROJECT_SOURCE_DIR}/examples/harness_sdl2.c
				${PROJECT_SOURCE_DIR}/examples/${example}.c
			)
			target_compile_definitions(${example}_sdl2 PUBLIC EXAMPLE_FUNC=example_${example})
			if(${example} STREQUAL "standalone")
				target_compile_definitions(${example}_sdl2 PUBLIC EXAMPLE_STANDALONE=1)
			endif()
			target_link_libraries(${example}_sdl2 eui_sdl2)
		endforeach()

		# 4bpp
		foreach(example hello order font windows standalone cursor widgets)
			add_executable(${example}_sdl2_4bpp)
			target_sources(${example}_sdl2_4bpp PUBLIC
				${PROJECT_SOURCE_DIR}/examples/harness_sdl2_4bpp.c
				${PROJECT_SOURCE_DIR}/examples/${example}.c
			)
			target_compile_definitions(${example}_sdl2_4bpp PUBLIC EXAMPLE_FUNC=example_${example})
			if(${example} STREQUAL "standalone")
				target_compile_definitions(${example}_sdl2_4bpp PUBLIC EXAMPLE_STANDALONE=1)
			endif()
			target_link_libraries(${example}_sdl2_4bpp eui_sdl2)
		endforeach()
	endif()

	# dos
	if(${CMAKE_SYSTEM_NAME} STREQUAL DOS)
		foreach(example hello order font windows standalone)
			add_executable(${example}_dos)
			target_sources(${example}_dos PUBLIC
				${PROJECT_SOURCE_DIR}/examples/harness_dos.c
				${PROJECT_SOURCE_DIR}/examples/${example}.c
			)
			target_compile_definitions(${example}_dos PUBLIC EXAMPLE_FUNC=example_${example})
			if(${example} STREQUAL "standalone")
				target_compile_definitions(${example}_dos PUBLIC EXAMPLE_STANDALONE=1)
			endif()
			target_link_libraries(${example}_dos eui)
		endforeach()
	endif()

endif()
