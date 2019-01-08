cmake_minimum_required (VERSION 3.0)
project(net text V2)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_VERBOSE_MAKEFILE ON)
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

add_test(ts1 test_walouini test_is_edge_coordinates)
add_test(ts2 test_walouini test_is_edge)
add_test(ts3 test_walouini test_opposite_dir)
add_test(ts4 test_walouini test_copy_game)

add_test(ts5 test_avialar test_game_over)
add_test(ts6 test_avialar test_empty)
add_test(ts7 test_avialar test_game_width)
add_test(ts8 test_avialar test_rotate_piece_one)
add_test(ts9 test_avialar test_rotate_piece)
add_test(ts10 test_avialar test_set_piece_current_dir)

add_test(ts11 test_kleguen test_set_piece)
add_test(ts12 test_kleguen test_game_new_game)
add_test(ts13 test_kleguen test_shuffle_dir)
add_test(ts14 test_kleguen test_game_height)

add_test(ts15 test_mgendron test_delete_game)
add_test(ts16 test_mgendron test_get_piece)
add_test(ts17 test_mgendron test_get_current_dir)
add_test(ts18 test_mgendron test_restart_game)

set_tests_properties (ts1 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_is_edge_coordinates\"\n"SUCCESS ")
set_tests_properties (ts2 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_is_edge\"\n"SUCCESS ")
set_tests_properties (ts3 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_opposite_dir\"\n"SUCCESS ")
set_tests_properties (ts4 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_copy_game\"\n"SUCCESS ")
set_tests_properties (ts5 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_game_over\"\n"SUCCESS ")
set_tests_properties (ts6 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_empty\"\n"SUCCESS ")
set_tests_properties (ts7 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_game_width\"\n"SUCCESS ")
set_tests_properties (ts8 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_rotate_piece_one\"\n"SUCCESS ")
set_tests_properties (ts9 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_rotate_piece\"\n"SUCCESS ")
set_tests_properties (ts10 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_set_piece_current_dir\"\n"SUCCESS ")
set_tests_properties (ts11 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_set_piece\"\n"SUCCESS ")
set_tests_properties (ts12 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_game_new_game\"\n"SUCCESS ")
set_tests_properties (ts13 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_shuffle_dir\"\n"SUCCESS ")
set_tests_properties (ts14 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_game_height\"\n"SUCCESS ")
set_tests_properties (ts15 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_delete_game\"\n"SUCCESS ")
set_tests_properties (ts16 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_get_piece\"\n"SUCCESS ")
set_tests_properties (ts17 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_get_current_dir\"\n"SUCCESS ")
set_tests_properties (ts18 PROPERTIES PASS_REGULAR_EXPRESSION " => RUN TEST \"test_restart_game\"\n"SUCCESS ")


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
