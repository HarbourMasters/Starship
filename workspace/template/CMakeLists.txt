cmake_minimum_required(VERSION 3.10)
project(ModTemplate)

find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(LOCAL_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(INCLUDE_DIRS
    ${LOCAL_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${PARENT_DIR}
    ${PARENT_DIR}/include
    ${PARENT_DIR}/src
    ${PARENT_DIR}/libultraship/src
    ${PARENT_DIR}/libultraship/include
    ${PARENT_DIR}/libultraship/include/libultraship
)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
list(FILTER SRC_FILES EXCLUDE REGEX ".*.inc.c")

set(BUILD_GEN ${CMAKE_CURRENT_SOURCE_DIR}/output/build.gen)
get_filename_component(OUTPUT_DIR ${BUILD_GEN} DIRECTORY)
file(MAKE_DIRECTORY ${OUTPUT_DIR})

set(INTERMEDIATE_OUTPUTS "")
set(COPY_OUTPUTS "")
set(DIST_OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/output/dist)

# Generate preprocessed source file (Leaves sources in output/dist)
foreach(SOURCE_FILE ${SRC_FILES})
    file(RELATIVE_PATH RELATIVE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src ${SOURCE_FILE})
    set(OUTPUT_FILE ${DIST_OUTPUT}/${RELATIVE_FILE})
    get_filename_component(INTERMEDIATE_DIR ${OUTPUT_FILE} DIRECTORY)

    add_custom_command(
        OUTPUT ${OUTPUT_FILE}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${INTERMEDIATE_DIR}
        COMMAND Python3::Interpreter ${PARENT_DIR}/tools/merge.py 
                --out ${OUTPUT_FILE} 
                --includes ${INCLUDE_DIRS}
                --src ${SOURCE_FILE}
        DEPENDS ${SOURCE_FILE} ${PARENT_DIR}/tools/merge.py
        VERBATIM
    )

    list(APPEND INTERMEDIATE_OUTPUTS ${OUTPUT_FILE})
endforeach()

# Copy headers into output folder
foreach(INCLUDE_DIR ${LOCAL_INCLUDE_DIRS})
    file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "${INCLUDE_DIR}/*.h")
    foreach(HEADER_FILE ${HEADER_FILES})
        file(RELATIVE_PATH RELATIVE_HEADER ${INCLUDE_DIR} ${HEADER_FILE})

        set(OUTPUT_HEADER ${OUTPUT_DIR}/include/${RELATIVE_HEADER})

        get_filename_component(HEADER_OUTPUT_DIR ${OUTPUT_HEADER} DIRECTORY)

        add_custom_command(
            OUTPUT ${OUTPUT_HEADER}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${HEADER_OUTPUT_DIR}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${HEADER_FILE} ${OUTPUT_HEADER}
            DEPENDS ${HEADER_FILE}
            VERBATIM
        )

        list(APPEND COPY_OUTPUTS ${OUTPUT_HEADER})
    endforeach()
endforeach()

# Copy assets into output folder
file(GLOB_RECURSE ASSET_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets/*")
foreach(ASSET_FILE ${ASSET_FILES})
    file(RELATIVE_PATH RELATIVE_ASSET ${CMAKE_CURRENT_SOURCE_DIR}/assets ${ASSET_FILE})

    set(OUTPUT_ASSET ${OUTPUT_DIR}/${RELATIVE_ASSET})

    get_filename_component(ASSET_OUTPUT_DIR ${OUTPUT_ASSET} DIRECTORY)

    add_custom_command(
        OUTPUT ${OUTPUT_ASSET}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${ASSET_OUTPUT_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ASSET_FILE} ${OUTPUT_ASSET}
        DEPENDS ${ASSET_FILE}
        VERBATIM
    )

    list(APPEND COPY_OUTPUTS ${OUTPUT_ASSET})
endforeach()

# Copy manifest into output folder
set(MANIFEST_FILE ${CMAKE_CURRENT_SOURCE_DIR}/manifest.json)

set(OUTPUT_MANIFEST ${OUTPUT_DIR}/manifest.json)

get_filename_component(MANIFEST_OUTPUT_DIR ${OUTPUT_MANIFEST} DIRECTORY)
add_custom_command(
    OUTPUT ${OUTPUT_MANIFEST}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${MANIFEST_OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MANIFEST_FILE} ${OUTPUT_MANIFEST}
    DEPENDS ${MANIFEST_FILE}
    VERBATIM
)
list(APPEND COPY_OUTPUTS ${OUTPUT_MANIFEST})

string(REPLACE ";" "\n" FORMATTED_FILE_LIST "${INTERMEDIATE_OUTPUTS}")
string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/output/" "" FORMATTED_FILE_LIST "${FORMATTED_FILE_LIST}")
file(WRITE ${BUILD_GEN} "${FORMATTED_FILE_LIST}\n")

add_custom_target(generate_packaged_mod ALL DEPENDS ${INTERMEDIATE_OUTPUTS} ${COPY_OUTPUTS})