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
find_package(jsoncpp CONFIG REQUIRED)
find_package(CURL CONFIG REQUIRED)

set(TS_FILES LEDVisualiser_en_GB.ts)

include_directories(
    /usr/include
    /usr/local/include
    ${QT_include}
    ${jsoncpp_include}
    ${CURL_include}
)

add_executable(LEDVisualiser
    src/main.cpp
    src/ledvisualiser.cpp
    src/http_request.cpp
    src/ledvisualiser.h
    src/http_request.h
    src/ledvisualiser.ui
    src/colorselector.cpp
    src/colorselector.ui
    src/colorselector.h
    ${TS_FILES}
)

target_link_libraries(LEDVisualiser PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    jsoncpp_lib
    jsoncpp_object
    CURL::libcurl
)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
