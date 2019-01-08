cmake_minimum_required (VERSION 3.0)
#project(net text V2)
project(net_text_V2)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(EXECUTABLE_OUTPUT_PATH .)
set(CMAKE_C_FLAGS"-std=c99 -Wall -g")

#include_directories(source_v2)

set(SRCS
    game.c
    game_io.c
    )
    
set(HEADERS
    game.h
    game_io.h
    )

add_library(game ${SRCS} ${HEADERS})
    

add_executable(net_text net_text.c)
target_link_libraries(net_text game )

add_executable(test_kleguen test_kleguen.c)
target_link_libraries(test_kleguen game )

add_executable(test_avialar test_avialar.c)
target_link_libraries(test_avialar game )

add_executable(test_walouini test_walouini.c)
target_link_libraries(test_walouini game )

add_executable(test_mgendron test_mgendron.c)
target_link_libraries(test_mgendron game )

enable_testing()

add_test(ts1 test_walouini is_edge_coordinates)
add_test(ts2 test_walouini is_edge)
add_test(ts3 test_walouini opposite_dir)
add_test(ts4 test_walouini copy_game)

add_test(ts5 test_avialar is_game_over)
add_test(ts6 test_avialar empty)
add_test(ts7 test_avialar game_width)
add_test(ts8 test_avialar rotate_piece_one)
add_test(ts9 test_avialar rotate_piece)
add_test(ts10 test_avialar set_piece_current_dir)

add_test(ts11 test_kleguen set_piece)
add_test(ts12 test_kleguen game_new_game)
add_test(ts13 test_kleguen shuffle_dir)
add_test(ts14 test_kleguen game_height)

add_test(ts15 test_mgendron delete)
add_test(ts16 test_mgendron get_piece)
add_test(ts17 test_mgendron current_dir)
add_test(ts18 test_mgendron restart)

set_tests_properties (ts1 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (ts2 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (ts3 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (ts4 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (ts5 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (ts6 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (ts7 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (ts8 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (ts9 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (ts10 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (ts11 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (ts12 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (ts13 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (ts14 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (ts15 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (ts16 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (ts17 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (ts18 PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")


set_tests_properties (ts1 PROPERTIES TIMEOUT 3)
set_tests_properties (ts2 PROPERTIES TIMEOUT 3)
set_tests_properties (ts3 PROPERTIES TIMEOUT 3)
set_tests_properties (ts4 PROPERTIES TIMEOUT 3)
set_tests_properties (ts5 PROPERTIES TIMEOUT 3)
set_tests_properties (ts6 PROPERTIES TIMEOUT 3)
set_tests_properties (ts7 PROPERTIES TIMEOUT 3)
set_tests_properties (ts8 PROPERTIES TIMEOUT 3)
set_tests_properties (ts9 PROPERTIES TIMEOUT 3)
set_tests_properties (ts10 PROPERTIES TIMEOUT 3)
set_tests_properties (ts11 PROPERTIES TIMEOUT 3)
set_tests_properties (ts12 PROPERTIES TIMEOUT 3)
set_tests_properties (ts13 PROPERTIES TIMEOUT 3)
set_tests_properties (ts14 PROPERTIES TIMEOUT 3)
set_tests_properties (ts15 PROPERTIES TIMEOUT 3)
set_tests_properties (ts16 PROPERTIES TIMEOUT 3)
set_tests_properties (ts17 PROPERTIES TIMEOUT 3)
set_tests_properties (ts18 PROPERTIES TIMEOUT 3)


add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
