cmake_minimum_required(VERSION 3.13)
project(fp02)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(../cute_lib)

add_executable(fp02
        src/cute/cute.h
        src/cute/cute_base.h
        src/cute/cute_counting_listener.h
        src/cute/cute_data_driven.h
        src/cute/cute_demangle.h
        src/cute/cute_deprecated.h
        src/cute/cute_determine_library.h
        src/cute/cute_determine_traits.h
        src/cute/cute_determine_version.h
        src/cute/cute_diff_values.h
        src/cute/cute_equals.h
        src/cute/cute_integer_sequence.h
        src/cute/cute_listener.h
        src/cute/cute_range.h
        src/cute/cute_relops.h
        src/cute/cute_repeated_test.h
        src/cute/cute_runner.h
        src/cute/cute_suite.h
        src/cute/cute_suite_test.h
        src/cute/cute_test.h
        src/cute/cute_test_incarnate.h
        src/cute/cute_testmember.h
        src/cute/cute_throws.h
        src/cute/cute_to_string.h
        src/cute/cute_version.h
        src/cute/cute_xml_file.h
        src/cute/ide_listener.h
        src/cute/ostream_listener.h
        src/cute/tap_listener.h
        src/cute/xml_listener.h
        src/Labirinth.cpp
        src/Labirinth.h
        src/Sudoku.cpp
        src/Sudoku.h
        src/Test.cpp)
