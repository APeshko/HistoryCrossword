cmake_minimum_required(VERSION 3.5)
project(HistoryCrossword)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_resources(resources "resources"
    PREFIX "/"
    FILES
        resources/styles.qss
        resources/data/level1.json
        resources/data/level2.json
        resources/data/level3.json
)

add_executable(HistoryCrossword
    src/main.cpp
    src/mainwindow.cpp
    src/levelselect.cpp
    src/crosswordwidget.cpp
    src/crossword.cpp
    include/mainwindow.h
    include/levelselect.h
    include/crosswordwidget.h
    include/crossword.h
    include/question.h
)

target_link_libraries(HistoryCrossword PRIVATE Qt6::Widgets)
