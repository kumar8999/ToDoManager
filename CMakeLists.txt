cmake_minimum_required(VERSION 3.14)

project(ToDoManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ccache
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  message(STATUS "Found ccache")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

find_package(Qt5 COMPONENTS Core Widgets Quick Sql  REQUIRED)
find_package(KF5Kirigami2)
find_package(KF5I18n)

set(PROJECT_SOURCES
    src/tasklistmodel.h src/tasklistmodel.cpp
    src/sectionlistmodel.h src/sectionlistmodel.cpp
    src/projectlistmodel.h src/projectlistmodel.cpp
    src/dbmanager.cpp src/dbmanager.h
    src/main.cpp
    src/qml.qrc
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

target_link_libraries(${PROJECT_NAME}  Qt5::Core Qt5::Widgets Qt5::Quick Qt5::Sql)
target_link_libraries(${PROJECT_NAME}  KF5::Kirigami2)
target_link_libraries(${PROJECT_NAME}  KF5::I18n)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER org.kumar
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)
