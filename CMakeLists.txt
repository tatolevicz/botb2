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
        Processor/BarAggregator.cpp Processor/BarAggregator.h Types/TickData.h Types/BarData.h Types/TimeValue.h)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

add_subdirectory(dependencies/fmt)
add_subdirectory(dependencies/rapidcsv)

# Defina o caminho onde o header do Catch2 será armazenado
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/catch)
set(CATCH_HEADER ${CATCH_INCLUDE_DIR}/catch.hpp)

# Verifique se o header do Catch2 já está baixado
if(NOT EXISTS ${CATCH_HEADER})
    # Crie o diretório para armazenar o header
    file(MAKE_DIRECTORY ${CATCH_INCLUDE_DIR})

    # URL do single-header do Catch2
    set(CATCH_URL "https://github.com/catchorg/Catch2/releases/download/v2.13.10/catch.hpp")

    # Baixe o arquivo
    message(STATUS "Baixando Catch2...")
    file(DOWNLOAD ${CATCH_URL} ${CATCH_HEADER})
endif()

# Lista de fontes
set(SOURCES
        botb2.h
        Common/Utils.h
        Processor/Ticker.h
        Processor/Ticker.cpp
        Processor/Tickable.h
        Processor/Tickable.cpp
        Types/BarData.h
        Types/TickData.h
        Types/Interval.h
        Types/TimeValue.h
        )

set(INCLUDES
        Processor
        Common
        Types
        dependencies/fmt/include
        dependencies/rapidcsv/src
        ${CATCH_INCLUDE_DIR}
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${INCLUDES}
        )

target_link_libraries(${PROJECT_NAME} PUBLIC
    fmt
    rapidcsv
)

#setup tests
set(TEST_SOURCES tests/main.cpp)

add_executable(botb2-tests ${TEST_SOURCES})

target_include_directories(botb2-tests PRIVATE
    ${INCLUDES}
)

target_link_libraries(botb2-tests PRIVATE
    ${PROJECT_NAME}
)
#------------
