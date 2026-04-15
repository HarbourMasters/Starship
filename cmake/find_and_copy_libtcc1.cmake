# cmake/find_and_copy_libtcc1.cmake
# Called at build time via cmake -P.
# Variables passed in:
#   SEARCH_DIR           - primary recursive search root (e.g. CMAKE_BINARY_DIR)
#   DEST_DIR             - destination directory to copy libtcc1.a into
#   SYSTEM_FALLBACK_DIRS - (optional) semicolon-separated list of system dirs to
#                          check if not found under SEARCH_DIR (e.g. /usr/lib)

file(GLOB_RECURSE LIBTCC1_CANDIDATES "${SEARCH_DIR}/libtcc1.a")

if(LIBTCC1_CANDIDATES)
    list(GET LIBTCC1_CANDIDATES 0 LIBTCC1_PATH)
    message(STATUS "Found libtcc1.a at: ${LIBTCC1_PATH}")
    file(COPY "${LIBTCC1_PATH}" DESTINATION "${DEST_DIR}")
else()
    # Fall back to system-installed locations if provided
    set(FOUND_IN_SYSTEM FALSE)
    if(DEFINED SYSTEM_FALLBACK_DIRS)
        foreach(SYSDIR ${SYSTEM_FALLBACK_DIRS})
            if(EXISTS "${SYSDIR}/libtcc1.a")
                message(STATUS "Found libtcc1.a in system path: ${SYSDIR}/libtcc1.a")
                file(COPY "${SYSDIR}/libtcc1.a" DESTINATION "${DEST_DIR}")
                set(FOUND_IN_SYSTEM TRUE)
                break()
            endif()
        endforeach()
    endif()

    if(NOT FOUND_IN_SYSTEM)
        message(WARNING "libtcc1.a was not found under '${SEARCH_DIR}' or in any system fallback path. Skipping copy.")
    endif()
endif()