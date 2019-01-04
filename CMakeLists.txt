cmake_minimum_required (VERSION 3.0)
project(V2)
add_definitions(-std=c99 -g -Wall)

set(EXECUTABLE_OUTPUT_PATH .)
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
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

