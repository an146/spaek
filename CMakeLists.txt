cmake_minimum_required(VERSION 3.1)

project(spaek LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets Charts REQUIRED)

add_executable(${PROJECT_NAME}
    "main.cpp"
    "approximationmodel.cpp"
    "dataset.cpp"
    "fit.cpp"
    "tablewidget.cpp"
    "voigt.cpp"
)
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE faddeeva Qt5::Core Qt5::Widgets Qt5::Charts)
