cmake_minimum_required(VERSION 3.10)
project(lab_5)

set(CMAKE_CXX_STANDARD 11)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)


add_executable(lab_5 src/main.cpp src/mainwindow.cpp src/mainwindow.h)


target_link_libraries(lab_5 PRIVATE Qt6::Widgets MyLibrary)


add_custom_command(TARGET lab_5 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libMyLibrary.dll
    $<TARGET_FILE_DIR:lab_5>
)