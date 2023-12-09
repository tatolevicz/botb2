cmake_minimum_required(VERSION 3.12)

project(botb2 VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        botb2.h
        Common/Utils.h
        Processor/Ticker.h
        Processor/Ticker.cpp
        Processor/Tickable.h
        Processor/Tickable.cpp
        Types/Interval.h
        )

add_library(${PROJECT_NAME} STATIC ${SOURCES})

set(INCLUDES
        Processor
        Common
        Types
        fmt/include
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${INCLUDES}
        )
