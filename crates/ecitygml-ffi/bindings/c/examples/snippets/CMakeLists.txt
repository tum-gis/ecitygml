# Builds the C snippets (`<name>.c`, short programs giving a first impression of the
# bindings) and registers a CTest case for every expected output shared by all languages: for
# `tests/expected/snippets/<snippet>/<fixture>.txt` (at the repository root), the snippet runs on `<FIXTURES>/<fixture>.gml` and must print that text
# (see ../../cmake/compare_output.cmake). Added by ../../CMakeLists.txt (`add_subdirectory`); expects
# REPOSITORY_ROOT, ECITYGML_FFI, ECITYGML_FFI_LIBRARY_DIR and FIXTURES.

set(EXPECTED_SNIPPETS_DIR "${REPOSITORY_ROOT}/tests/expected/snippets")
# Snippets that write a file, and its extension; the file is the snippet's second argument.
set(OUTPUT_EXTENSION_translate_to_local_coordinates ".gml")

file(GLOB snippet_sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
foreach(source ${snippet_sources})
    get_filename_component(snippet "${source}" NAME_WE)
    set(target snippet_${snippet})
    add_executable(${target} "${source}")
    target_include_directories(${target} PRIVATE "${PROJECT_SOURCE_DIR}/include")
    target_link_libraries(${target} PRIVATE "${ECITYGML_FFI}")
    target_compile_options(${target} PRIVATE -Wall -Wextra -Werror)
    # Find libecitygml_ffi at runtime (Linux doesn't search its directory otherwise).
    set_target_properties(${target} PROPERTIES BUILD_RPATH "${ECITYGML_FFI_LIBRARY_DIR}")

    file(GLOB cases CONFIGURE_DEPENDS "${EXPECTED_SNIPPETS_DIR}/${snippet}/*.txt")
    if(NOT cases)
        message(FATAL_ERROR "No expected output for ${snippet} in ${EXPECTED_SNIPPETS_DIR}/${snippet}")
    endif()
    foreach(case ${cases})
        get_filename_component(fixture "${case}" NAME_WLE)
        set(output_arguments "")
        if(DEFINED OUTPUT_EXTENSION_${snippet})
            set(extension "${OUTPUT_EXTENSION_${snippet}}")
            set(output_arguments
                "-DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/snippet-output/${snippet}-${fixture}${extension}"
                "-DEXPECTED_OUTPUT=${EXPECTED_SNIPPETS_DIR}/${snippet}/${fixture}${extension}")
        endif()
        add_test(NAME ${target}_${fixture}
            COMMAND ${CMAKE_COMMAND} -DEXAMPLE=$<TARGET_FILE:${target}> "-DINPUT=${FIXTURES}/${fixture}.gml"
                "-DEXPECTED=${case}" ${output_arguments} -P "${PROJECT_SOURCE_DIR}/cmake/compare_output.cmake")
    endforeach()
endforeach()
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/snippet-output")
