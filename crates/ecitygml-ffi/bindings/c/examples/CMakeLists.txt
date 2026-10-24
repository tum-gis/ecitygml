# Builds the C examples (`NN_<name>.c`) and registers a
# CTest case for every expected output shared by all languages: for
# `tests/expected/examples/<example>/<dataset>/<fixture>.txt` (at the repository root), the example runs on `<FIXTURES>/<dataset>/<fixture>.gml` and must print
# that text (see ../cmake/compare_output.cmake). Added by ../CMakeLists.txt (`add_subdirectory`); expects
# REPOSITORY_ROOT, ECITYGML_FFI, ECITYGML_FFI_LIBRARY_DIR and FIXTURES.

set(EXPECTED_EXAMPLES_DIR "${REPOSITORY_ROOT}/tests/expected/examples")
# Examples that write a file, and its extension; the file is the example's second argument.
set(OUTPUT_EXTENSION_06_export_obj ".obj")
set(OUTPUT_EXTENSION_07_convert ".gml.gz")

file(GLOB example_sources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/[0-9][0-9]_*.c")
foreach(source ${example_sources})
    get_filename_component(example "${source}" NAME_WE)
    add_executable(${example} "${source}")
    target_include_directories(${example} PRIVATE "${PROJECT_SOURCE_DIR}/include")
    target_link_libraries(${example} PRIVATE "${ECITYGML_FFI}")
    target_compile_options(${example} PRIVATE -Wall -Wextra -Werror)
    # Find libecitygml_ffi at runtime (Linux doesn't search its directory otherwise).
    set_target_properties(${example} PROPERTIES BUILD_RPATH "${ECITYGML_FFI_LIBRARY_DIR}")

    file(GLOB cases CONFIGURE_DEPENDS "${EXPECTED_EXAMPLES_DIR}/${example}/*/*.txt")
    if(NOT cases)
        message(FATAL_ERROR "No expected output for ${example} in ${EXPECTED_EXAMPLES_DIR}/${example}")
    endif()
    foreach(case ${cases})
        # `<dataset>/<fixture>.txt` -> the fixture `<dataset>/<fixture>.gml`.
        get_filename_component(stem "${case}" NAME_WLE)
        get_filename_component(case_dir "${case}" DIRECTORY)
        get_filename_component(dataset "${case_dir}" NAME)
        set(output_arguments "")
        if(DEFINED OUTPUT_EXTENSION_${example})
            set(extension "${OUTPUT_EXTENSION_${example}}")
            set(output_arguments
                "-DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/example-output/${example}-${dataset}-${stem}${extension}"
                "-DEXPECTED_OUTPUT=${case_dir}/${stem}${extension}")
        endif()
        add_test(NAME example_${example}_${dataset}_${stem}
            COMMAND ${CMAKE_COMMAND} -DEXAMPLE=$<TARGET_FILE:${example}> "-DINPUT=${FIXTURES}/${dataset}/${stem}.gml"
                "-DEXPECTED=${case}" ${output_arguments} -P "${PROJECT_SOURCE_DIR}/cmake/compare_output.cmake")
    endforeach()
endforeach()
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/example-output")

add_test(NAME example_missing_file COMMAND 01_read_city_model "${FIXTURES}/does-not-exist.gml")
set_tests_properties(example_missing_file PROPERTIES WILL_FAIL TRUE)
