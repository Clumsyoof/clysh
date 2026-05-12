cmake_minimum_required(VERSION 3.31.11)
project(shell)
add_library(${PROJECT_NAME} STATIC shell.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER shell.h)
install(TARGETS shell DESTINATION lib
        PUBLIC_HEADER DESTINATION include
        )
