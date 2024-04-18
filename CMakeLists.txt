cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

# Set the project version and language
project(Lylat64 VERSION 0.1.0 LANGUAGES C CXX ASM)

if(APPLE)
  enable_language(OBJCXX)
endif()

# Set the minimum version of CMake and the deployment target for macOS
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum OS X deployment version")

# Set the C++ standard and enable the MSVC parallel build option
set(CMAKE_CXX_STANDARD 20 CACHE STRING "The C++ standard to use")
set(CMAKE_C_STANDARD 11 CACHE STRING "The C standard to use")
#add_compile_options(-fsanitize=address)
#add_link_options(-fsanitize=address)

# Add a custom module path to locate additional CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
include(FindFontconfig)

if (WIN32)
include(cmake/automate-vcpkg.cmake)
# Forced to use MSVC
set(MSVC ON)

if(MSVC)
set(VCPKG_TRIPLET x64-windows-static)
set(VCPKG_TARGET_TRIPLET x64-windows-static)
else()
set(VCPKG_TRIPLET x64-mingw-static)
set(VCPKG_TARGET_TRIPLET x64-mingw-static)
endif()

vcpkg_bootstrap()
vcpkg_install_packages(fontconfig sdl2 zlib bzip2 libzip libpng getopt dirent libusb pthread glew glfw3)
endif()

if (MSVC)
set(CPP "${CMAKE_C_COMPILER}" "/EP")
else()
set(CPP "${CMAKE_C_COMPILER}" "-E" "-P" "-Wno-trigraphs" "-x" "c")
endif()

# Set game compilation version
set(VERSION us)
set(USE_NETWORKING OFF)
set(SKIP_XCODE_VERSION_CHECK ON)

# Add compile definitions for the target
add_compile_definitions(
    VERSION_US=1
    ENABLE_RUMBLE=1
    F3DEX_GBI=1
    _LANGUAGE_C
    _USE_MATH_DEFINES
    CIMGUI_DEFINE_ENUMS_AND_STRUCTS
    NON_MATCHING=1
    NON_EQUIVALENT=1
	AVOID_UB=1
)

# Find necessary libraries
if (UNIX AND NOT APPLE)
find_package(OpenGL REQUIRED)
endif()

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Collect source files to build the executable
file(GLOB_RECURSE ALL_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    # "src/assets/*.c"
    "src/audio/*.c"
    "src/audio/*.h"
    "src/engine/*.c"
    "src/engine/*.h"
    "src/libultra/io/aisetfreq.c"
    "src/libultra/gu/sqrtf.c"
    "src/libultra/gu/mtxutil.c"
    "src/libultra/gu/ortho.c"
    "src/overlays/*.c"
    "src/overlays/*.h"
    "src/port/*.h"
    "src/port/*.c"
    "src/port/*.cpp"
    "src/sys/*.c"
    "src/sys/*.h"
    "src/1FA60.c"
    "src/buffers.c"
    "src/dmatable.c"
    "src/libc_math64.c"
    "src/libc_sprintf.c"
)

# Exclude specific files from the ALL_FILES list
list(FILTER ALL_FILES EXCLUDE REGEX ".*.inc.c")

list(FILTER ALL_FILES EXCLUDE REGEX "src/engine/fox_A4290_colheaders.c")
list(FILTER ALL_FILES EXCLUDE REGEX "src/engine/fox_edata_info.c")
list(FILTER ALL_FILES EXCLUDE REGEX "src/engine/fox_rcp_setup.c")
list(FILTER ALL_FILES EXCLUDE REGEX "src/engine/fox_load_inits.c")
list(FILTER ALL_FILES EXCLUDE REGEX "src/overlays/ovl_ending/fox_end2_data.c")
list(FILTER ALL_FILES EXCLUDE REGEX "src/sys/sys_timer.c")
list(FILTER ALL_FILES EXCLUDE REGEX "src/sys/sys_fault.c")

add_executable(${PROJECT_NAME} ${ALL_FILES} ${GENERATED_SOURCES}
		src/port/resource/importers/ResourceUtil.h)

################################################################################
# MSVC runtime library
################################################################################
if (MSVC)
  if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	  get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
	  if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
		  string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
			  $<$<CONFIG:Debug>:
                MultiThreadedDebug
			  >
			  $<$<CONFIG:Release>:
                MultiThreaded
			  >
			  $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
		  )
	  elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
		  string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
			  $<$<CONFIG:Debug>:
				  MultiThreadedDebug
			  >
			  $<$<CONFIG:Release>:
				  MultiThreaded
			  >
			  $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
		  )
	  endif()
	  set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})
  endif()
endif()

#==============================================================================#
# Libultraship Integration                                                            #
#==============================================================================#

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/include
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/include/libultraship
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/log
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/debug
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/menu
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/utils
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/utils/binarytools
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/config
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/resource
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/resource/type
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/resource/factory
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/audio
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/window
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/window/gui
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/config
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/public
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/public/libultra
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/public/bridge
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/extern
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/extern/tinyxml2
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/libultraship/Lib/
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/libultraship/Lib/libjpeg/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/libultraship/Lib/spdlog/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/graphic/Fast3D/U64/PR
  ${CMAKE_CURRENT_SOURCE_DIR}/libultraship/src/graphic
  ${SDL2_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
		target_compile_definitions(${PROJECT_NAME} PRIVATE
			"$<$<CONFIG:Debug>:"
				"_DEBUG;"
				"_CRT_SECURE_NO_WARNINGS;"
				"ENABLE_DX11;"
			">"
			"$<$<CONFIG:Release>:"
				"NDEBUG"
			">"
			"INCLUDE_GAME_PRINTF;"
			"UNICODE;"
			"_UNICODE"
			STORMLIB_NO_AUTO_LINK
			"_CRT_SECURE_NO_WARNINGS;"
            "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS;"
		)
	elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
		target_compile_definitions(${PROJECT_NAME} PRIVATE
			"$<$<CONFIG:Debug>:"
				"NOINCLUDE_GAME_PRINTF;"
				"_DEBUG;"
				"_CRT_SECURE_NO_WARNINGS;"
				"ENABLE_OPENGL"
			">"
			"$<$<CONFIG:Release>:"
				"NDEBUG;"
			">"
			"INCLUDE_GAME_PRINTF;"
			"WIN32;"
			"UNICODE;"
			"_UNICODE"
			STORMLIB_NO_AUTO_LINK
            "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS;"
		)
	endif()
elseif (CMAKE_SYSTEM_NAME STREQUAL "CafeOS")
	target_compile_definitions(${PROJECT_NAME} PRIVATE
		"$<$<CONFIG:Debug>:"
			"_DEBUG"
		">"
		"$<$<CONFIG:Release>:"
			"NDEBUG"
		">"
        "SPDLOG_ACTIVE_LEVEL=3;"
		"SPDLOG_NO_THREAD_ID;"
        "SPDLOG_NO_TLS;"
		"STBI_NO_THREAD_LOCALS;"
	)
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU|Clang|AppleClang")
	target_compile_definitions(${PROJECT_NAME} PRIVATE
		"$<$<CONFIG:Debug>:"
			"_DEBUG"
		">"
		"$<$<CONFIG:Release>:"
			"NDEBUG"
		">"
        "$<$<BOOL:${BUILD_CROWD_CONTROL}>:ENABLE_CROWD_CONTROL>"
		"SPDLOG_ACTIVE_LEVEL=0;"
		"_CONSOLE;"
		"_CRT_SECURE_NO_WARNINGS;"
		"ENABLE_OPENGL;"
		"UNICODE;"
		"_UNICODE"
	)
endif()

add_subdirectory(libultraship ${CMAKE_CURRENT_SOURCE_DIR}/libultraship)

add_dependencies(${PROJECT_NAME} libultraship)
target_link_libraries(${PROJECT_NAME} PRIVATE libultraship)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<BOOL:${USE_NETWORKING}>:SDL2_net::SDL2_net-static>"
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "NintendoSwitch")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        -lglad
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "CafeOS")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:-Wl,--wrap=abort>"
    )
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${DEVKITPRO}/portlibs/wiiu/include/
    )
else()
 	set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<BOOL:${USE_NETWORKING}>:SDL2_net::SDL2_net>"
	)
endif()

if(USE_NETWORKING)
    if(MSVC)
        vcpkg_install_packages(sdl2-net)
    endif()
    find_package(SDL2_net REQUIRED)
    include_directories(${SDL2_NET_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_net::SDL2_net)
    target_compile_definitions(${PROJECT_NAME} PRIVATE USE_NETWORKING)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if(CMAKE_SYSTEM_NAME MATCHES "NintendoSwitch")

nx_generate_nacp(Lylat.nacp
   NAME "Lylat64"
   AUTHOR "${PROJECT_TEAM}"
   VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
)

nx_create_nro(${PROJECT_NAME}
    NACP Lylat.nacp
)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/lylat64.nro DESTINATION . COMPONENT ${PROJECT_NAME})
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
  if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
      target_compile_options(${PROJECT_NAME} PRIVATE
          $<$<CONFIG:Debug>:
              /w;
              /Od;
              /MTd
          >
          $<$<CONFIG:Release>:
              /Oi;
              /Gy;
              /W3;
              /MT
          >
          /permissive-;
          /MP;
          ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
          ${DEFAULT_CXX_EXCEPTION_HANDLING}
      )
      target_compile_options(${PROJECT_NAME} PRIVATE  $<$<CONFIG:Debug>:/ZI;>)
  elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
      target_compile_options(${PROJECT_NAME} PRIVATE
          $<$<CONFIG:Debug>:
              /MTd
          >
          $<$<CONFIG:Release>:
              /O2;
              /Oi;
              /Gy;
              /MT
          >
          /permissive-;
          /MP;
          /w;
          ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
          ${DEFAULT_CXX_EXCEPTION_HANDLING}
      )
  endif()
  if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
      target_link_options(${PROJECT_NAME} PRIVATE
          $<$<CONFIG:Debug>:
              /INCREMENTAL
          >
          $<$<CONFIG:Release>:
              /OPT:REF;
              /OPT:ICF;
              /INCREMENTAL:NO;
              /FORCE:MULTIPLE
          >
          /MANIFEST:NO;
          /DEBUG;
          /SUBSYSTEM:WINDOWS
      )
  elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
      target_link_options(${PROJECT_NAME} PRIVATE
          $<$<CONFIG:Debug>:
              /STACK:8777216
          >
          $<$<CONFIG:Release>:
              /OPT:REF;
              /OPT:ICF;
              /INCREMENTAL:NO;
              /FORCE:MULTIPLE
          >
          /MANIFEST:NO;
          /DEBUG;
          /SUBSYSTEM:WINDOWS
      )
  endif()

  # Remove /RTC from msvc flags
  foreach (fentry
    CMAKE_C_FLAGS
    CMAKE_CXX_FLAGS
  )
    string (REGEX REPLACE "/RTC(su|[1su])" "" ${fentry} "${${fentry}}")
  endforeach(fentry)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
  if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
      target_compile_options(${PROJECT_NAME} PRIVATE
          -Wall -Wextra -Wno-error
          -Wno-return-type
          -Wno-unused-parameter
          -Wno-unused-function
          -Wno-unused-variable
          -Wno-missing-field-initializers
          -Wno-parentheses
          -Wno-narrowing
          -Wno-missing-braces
          -Wno-int-conversion
          $<$<COMPILE_LANGUAGE:C>:
              -Werror-implicit-function-declaration
              -Wno-incompatible-pointer-types
              -fpermissive
          >
          $<$<COMPILE_LANGUAGE:CXX>:-fpermissive>
          $<$<COMPILE_LANGUAGE:CXX>:
              -Wno-c++11-narrowing
              -Wno-deprecated-enum-enum-conversion
          >
          -pthread
      )

      target_link_options(${PROJECT_NAME} PRIVATE
          -pthread
      )
  elseif (CMAKE_SYSTEM_NAME STREQUAL "NintendoSwitch")
      target_compile_options(${PROJECT_NAME} PRIVATE
          -Wall -Wextra -Wno-error
          -Wno-return-type
          -Wno-unused-parameter
          -Wno-unused-function
          -Wno-unused-variable
          -Wno-missing-field-initializers
          -Wno-parentheses
          -Wno-narrowing
          -Wno-missing-braces
          -Wno-int-conversion
          $<$<COMPILE_LANGUAGE:C>:
              -Werror-implicit-function-declaration
              -Wno-incompatible-pointer-types
              -fpermissive
          >
          $<$<COMPILE_LANGUAGE:CXX>:-fpermissive>
          $<$<COMPILE_LANGUAGE:CXX>:
              -Wno-c++11-narrowing
              -Wno-deprecated-enum-enum-conversion
          >
          -pthread
      )

      target_link_options(${PROJECT_NAME} PRIVATE
          -pthread
      )
  elseif (CMAKE_SYSTEM_NAME STREQUAL "CafeOS")
      target_compile_options(${PROJECT_NAME} PRIVATE
          -O2

          # disable some warnings to not clutter output
          -Wno-multichar
          -Wno-return-type
          -Wno-narrowing
          -Wno-switch-outside-range
          $<$<COMPILE_LANGUAGE:C>:
              -Werror-implicit-function-declaration
              -Wno-incompatible-pointer-types
              -Wno-discarded-array-qualifiers
              -Wno-discarded-qualifiers
              -Wno-int-conversion
              -Wno-builtin-declaration-mismatch
              -Wno-switch-unreachable
              -Wno-stringop-overflow
          >
      )
  else()
      if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
  set(CPU_OPTION -msse2 -mfpmath=sse)
      endif()

      target_compile_options(${PROJECT_NAME} PRIVATE
          -Wall -Wextra -Wno-error
          -Wno-unused-parameter
          -Wno-unused-function
          -Wno-unused-variable
          -Wno-missing-field-initializers
          -Wno-parentheses
          -Wno-narrowing
          -Wno-missing-braces
          -Wno-int-conversion
          $<$<COMPILE_LANGUAGE:C>:
              -Werror-implicit-function-declaration
              -Wno-incompatible-pointer-types
              -fpermissive
          >
          $<$<COMPILE_LANGUAGE:CXX>:-fpermissive>
          $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-enum-conversion>
          -pthread
    ${CPU_OPTION}
      )

      target_link_options(${PROJECT_NAME} PRIVATE
          -pthread
          -Wl,-export-dynamic
      )
  endif()
endif()
