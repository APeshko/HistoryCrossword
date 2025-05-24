cmake_minimum_required(VERSION 3.5)
project(HistoryCrossword VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройка Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

# Добавление ресурсов (JSON-файлы кроссвордов и стили)
qt_add_resources(resources "resources"
    PREFIX "/"
    FILES
        resources/styles.qss
        resources/data/level1.json
        resources/data/level2.json
        resources/data/level3.json
)

# Core библиотека (интерфейсы)
add_library(core INTERFACE)
target_include_directories(core INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/core
)

# Data слой (работа с данными)
add_library(data STATIC
    src/data/crossworddata.cpp
    src/data/jsoncrosswordloader.cpp
)
target_include_directories(data PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/data
)
target_link_libraries(data PRIVATE core)

# Logic слой (бизнес-логика)
add_library(logic STATIC
    src/logic/answerchecker.cpp
)
target_include_directories(logic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/logic
)
target_link_libraries(logic PRIVATE core data)

# UI слой (пользовательский интерфейс)
add_library(ui STATIC
    src/ui/inputfieldfactory.cpp
    src/ui/mainwindow.cpp
    src/ui/levelselect.cpp
    src/ui/crosswordwidget.cpp
)
target_include_directories(ui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/include/models
)
target_link_libraries(ui PRIVATE 
    core 
    data 
    logic 
    Qt6::Widgets
)

# Основное приложение
add_executable(HistoryCrossword
    src/main.cpp
)
target_link_libraries(HistoryCrossword PRIVATE 
    core 
    data 
    logic 
    ui
)

# Установка исполняемого файла
install(TARGETS HistoryCrossword
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
