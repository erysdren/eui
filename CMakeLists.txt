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

add_library(eui)

target_sources(eui PRIVATE
	${PROJECT_SOURCE_DIR}/source/eui.c
	${PROJECT_SOURCE_DIR}/source/eui_evnt.c
	${PROJECT_SOURCE_DIR}/source/eui_widg.c
)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
	target_compile_options(eui PRIVATE -pedantic -Wall -Wextra)
endif()

set_target_properties(eui PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)

target_include_directories(eui PUBLIC ${PROJECT_SOURCE_DIR}/include)

# sdl2 bridge library
find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
if(SDL2_FOUND)
	add_library(eui_sdl2)

	target_sources(eui_sdl2 PRIVATE
		${PROJECT_SOURCE_DIR}/source/eui_sdl2.c
	)

	if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
		target_compile_options(eui_sdl2 PRIVATE -pedantic -Wall -Wextra)
	endif()

	set_target_properties(eui_sdl2 PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)

	target_link_libraries(eui_sdl2 PUBLIC eui SDL2::SDL2)
endif()

# sdl3 bridge library
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
if(SDL2_FOUND)
	add_library(eui_sdl3)

	target_sources(eui_sdl3 PRIVATE
		${PROJECT_SOURCE_DIR}/source/eui_sdl3.c
	)

	if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
		target_compile_options(eui_sdl3 PRIVATE -pedantic -Wall -Wextra)
	endif()

	set_target_properties(eui_sdl3 PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON)

	target_link_libraries(eui_sdl3 PUBLIC eui SDL3::SDL3)
endif()

# examples

if(EUI_BUILD_EXAMPLES)

	set(examples hello order font windows standalone)
	set(examples_interactive cursor widgets)
	set(examples_8bpp bitmap)

	# sdl2
	if(SDL2_FOUND)
		# 8bpp
		foreach(example IN LISTS examples examples_interactive examples_8bpp)
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
		foreach(example IN LISTS examples examples_interactive)
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

	# sdl3
	if(SDL3_FOUND)
		# 8bpp
		foreach(example IN LISTS examples examples_interactive examples_8bpp)
			add_executable(${example}_sdl3)
			target_sources(${example}_sdl3 PUBLIC
				${PROJECT_SOURCE_DIR}/examples/harness_sdl3.c
				${PROJECT_SOURCE_DIR}/examples/${example}.c
			)
			target_compile_definitions(${example}_sdl3 PUBLIC EXAMPLE_FUNC=example_${example})
			if(${example} STREQUAL "standalone")
				target_compile_definitions(${example}_sdl3 PUBLIC EXAMPLE_STANDALONE=1)
			endif()
			target_link_libraries(${example}_sdl3 eui_sdl3)
		endforeach()

		# 4bpp
		foreach(example IN LISTS examples examples_interactive)
			add_executable(${example}_sdl3_4bpp)
			target_sources(${example}_sdl3_4bpp PUBLIC
				${PROJECT_SOURCE_DIR}/examples/harness_sdl3_4bpp.c
				${PROJECT_SOURCE_DIR}/examples/${example}.c
			)
			target_compile_definitions(${example}_sdl3_4bpp PUBLIC EXAMPLE_FUNC=example_${example})
			if(${example} STREQUAL "standalone")
				target_compile_definitions(${example}_sdl3_4bpp PUBLIC EXAMPLE_STANDALONE=1)
			endif()
			target_link_libraries(${example}_sdl3_4bpp eui_sdl3)
		endforeach()
	endif()

	# dos
	if(CMAKE_SYSTEM_NAME STREQUAL "DOS")
		foreach(example IN LISTS examples)
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
