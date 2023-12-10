cmake_minimum_required(VERSION 3.12)
project(Botb2Testes)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_include_directories(${PROJECT_NAME}  PUBLIC
    ../
)

target_link_libraries(${PROJECT_NAME}  PUBLIC
    botb2
)