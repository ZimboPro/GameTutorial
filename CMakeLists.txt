cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(pong)

set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_FLAGS "-Wall -Werror -stdlib=libc++")

include(FetchContent)

FetchContent_Declare(
    sfml
    URL https://www.sfml-dev.org/files/SFML-2.5.0-sources.zip
)

FetchContent_GetProperties(sfml)

if(NOT sfml_POPULATED)
  FetchContent_Populate(sfml)
  add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()

include_directories(
    ${sfml_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(
    pong
    src/Pang.cpp
    src/Game.cpp
    src/SplashScreen.cpp
    src/MainMenu.cpp
)

target_link_libraries(pong sfml-graphics sfml-window sfml-system sfml-audio)