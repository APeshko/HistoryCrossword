cmake_minimum_required(VERSION 3.10)
project(HistoryCrossword)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(HistoryCrossword ${SOURCES})
target_link_libraries(HistoryCrossword sfml-graphics sfml-window sfml-system)
