# Runs an example and compares its standard output with the expected output shared by all
# languages (tests/expected at the repository root). Used by the C CTest suite:
#   cmake -DEXAMPLE=<executable> -DINPUT=<fixture> -DEXPECTED=<file>
#         [-DOUTPUT=<path> [-DEXPECTED_OUTPUT=<file>]] -P compare_output.cmake
# OUTPUT is passed as the example's second argument (for examples that write a file); if
# EXPECTED_OUTPUT exists, the written file must match it.
set(arguments "${INPUT}")
if(DEFINED OUTPUT)
    list(APPEND arguments "${OUTPUT}")
endif()
execute_process(
    COMMAND "${EXAMPLE}" ${arguments}
    OUTPUT_VARIABLE actual
    ERROR_VARIABLE errors
    RESULT_VARIABLE exit_code)
if(NOT exit_code EQUAL 0)
    message(FATAL_ERROR "${EXAMPLE} exited with ${exit_code}: ${errors}")
endif()
file(READ "${EXPECTED}" expected)
if(NOT actual STREQUAL expected)
    message(FATAL_ERROR "Output of ${EXAMPLE} differs from ${EXPECTED}:\n${actual}")
endif()
if(DEFINED EXPECTED_OUTPUT AND EXISTS "${EXPECTED_OUTPUT}")
    file(READ "${OUTPUT}" actual_file)
    file(READ "${EXPECTED_OUTPUT}" expected_file)
    if(NOT actual_file STREQUAL expected_file)
        message(FATAL_ERROR "${OUTPUT} differs from ${EXPECTED_OUTPUT}")
    endif()
endif()
