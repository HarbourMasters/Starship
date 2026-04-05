cmake_minimum_required(VERSION 3.10)
project(ModTemplate)

find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PARENT_DIR}
    ${PARENT_DIR}/include
    ${PARENT_DIR}/src
    ${PARENT_DIR}/libultraship/src
    ${PARENT_DIR}/libultraship/include
    ${PARENT_DIR}/libultraship/include/libultraship
)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

set(BUILD_GEN ${CMAKE_CURRENT_SOURCE_DIR}/output/build.gen)
get_filename_component(OUTPUT_DIR ${BUILD_GEN} DIRECTORY)
file(MAKE_DIRECTORY ${OUTPUT_DIR})

set(INTERMEDIATE_OUTPUTS "")
set(DIST_OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/output/dist)

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

string(REPLACE ";" "\n" FORMATTED_FILE_LIST "${INTERMEDIATE_OUTPUTS}")
string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/output/" "" FORMATTED_FILE_LIST "${FORMATTED_FILE_LIST}")
file(WRITE ${BUILD_GEN} "${FORMATTED_FILE_LIST}\n")

add_custom_target(generate_packaged_mod ALL DEPENDS ${INTERMEDIATE_OUTPUTS})