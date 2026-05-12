cmake_minimum_required(VERSION 3.31.11)
project(cmd)
add_library(${PROJECT_NAME} cmd.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE shell)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER cmd.h)
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include
        )
