cmake_minimum_required(VERSION 3.5)

project(LEDVisualiser LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES LEDVisualiser_en_GB.ts)

add_executable(LEDVisualiser
    main.cpp
    ledvisualiser.cpp
    http_request.cpp
    ledvisualiser.h
    http_request.h
    ledvisualiser.ui
    ${TS_FILES}
)

target_link_libraries(LEDVisualiser PRIVATE Qt${QT_VERSION_MAJOR}::Widgets curl jsoncpp)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
