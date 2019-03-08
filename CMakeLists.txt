cmake_minimum_required (VERSION 3.7)
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

add_executable(net_solve net_solve.c)
target_link_libraries(net_solve game )

enable_testing()
include (CTest)


add_test(test_is_edge_coordinates test_walouini is_edge_coordinates) # test
add_test(test_is_edge test_walouini is_edge)
add_test(test_opposite_dir test_walouini opposite_dir)
add_test(test_copy_game test_walouini copy_game)

add_test(test_is_game_over test_avialar is_game_over)
add_test(test_empty test_avialar empty)
add_test(test_game_width test_avialar game_width)
add_test(test_rotate_piece_one test_avialar rotate_piece_one)
add_test(test_rotate_piece test_avialar rotate_piece)
add_test(test_set_piece_current_dir test_avialar set_piece_current_dir)

add_test(test_set_piece test_kleguen set_piece)
add_test(test_new_game test_kleguen game_new_game)
add_test(test_shuffle_dir test_kleguen shuffle_dir)
add_test(test_game_height test_kleguen game_height)
add_test(test_is_wrapping test_kleguen is_wrapping)
add_test(test_new_game_ext test_kleguen new_game_ext)
add_test(test_new_game_empty_ext test_kleguen new_game_empty_ext)


add_test(test_delete test_mgendron delete)
add_test(test_get_piece test_mgendron get_piece)
add_test(test_current_dir test_mgendron current_dir)
add_test(test_restart test_mgendron restart)


set_tests_properties (test_is_edge_coordinates PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (test_is_edge PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (test_opposite_dir PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (test_copy_game PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")

set_tests_properties (test_is_game_over PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (test_empty PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (test_game_width PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (test_rotate_piece_one PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (test_rotate_piece PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (test_set_piece_current_dir PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")

set_tests_properties (test_set_piece PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (test_new_game PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (test_shuffle_dir PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (test_game_height PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (test_is_wrapping PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (test_new_game_ext PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (test_new_game_empty_ext PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")

set_tests_properties (test_delete PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (test_get_piece PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (test_current_dir PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
set_tests_properties (test_restart PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")


set_tests_properties (test_is_edge_coordinates PROPERTIES TIMEOUT 3)
set_tests_properties (test_is_edge PROPERTIES TIMEOUT 3)
set_tests_properties (test_opposite_dir PROPERTIES TIMEOUT 3)
set_tests_properties (test_copy_game PROPERTIES TIMEOUT 3)

set_tests_properties (test_is_game_over PROPERTIES TIMEOUT 3)
set_tests_properties (test_empty PROPERTIES TIMEOUT 3)
set_tests_properties (test_game_width PROPERTIES TIMEOUT 3)
set_tests_properties (test_rotate_piece_one PROPERTIES TIMEOUT 3)
set_tests_properties (test_rotate_piece PROPERTIES TIMEOUT 3)
set_tests_properties (test_set_piece_current_dir PROPERTIES TIMEOUT 3)

set_tests_properties (test_set_piece PROPERTIES TIMEOUT 3)
set_tests_properties (test_new_game PROPERTIES TIMEOUT 3)
set_tests_properties (test_shuffle_dir PROPERTIES TIMEOUT 3)
set_tests_properties (test_game_height PROPERTIES TIMEOUT 3)
set_tests_properties (test_is_wrapping PROPERTIES TIMEOUT 3)
set_tests_properties (test_new_game_ext PROPERTIES TIMEOUT 3)
set_tests_properties (test_new_game_empty_ext PROPERTIES TIMEOUT 3)


set_tests_properties (test_delete PROPERTIES TIMEOUT 3)
set_tests_properties (test_get_piece PROPERTIES TIMEOUT 3)
set_tests_properties (test_current_dir PROPERTIES TIMEOUT 3)
set_tests_properties (test_restart PROPERTIES TIMEOUT 3)


add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
