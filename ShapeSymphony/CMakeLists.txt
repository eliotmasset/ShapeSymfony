cmake_minimum_required(VERSION 3.5)

project(ShapeSymphony VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        rungraphicsview.cpp
        rungraphicsview.h
        circleitem.cpp
        circleitem.h
)

qt_add_resources(DarkTheme.qss DarkTheme.qss
    PREFIX "/theme/"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ShapeSymphony
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ShapeSymphony APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ShapeSymphony SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ShapeSymphony
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ShapeSymphony PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(ShapeSymphony PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ShapeSymphony
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ShapeSymphony)
endif()

add_library(QtAwesome STATIC QtAwesome.cpp QtAwesome.h QtAwesomeFree.qrc QtAwesomeAnim.cpp QtAwesomeAnim.h)

target_link_libraries(QtAwesome
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_link_libraries(ShapeSymphony PRIVATE
    QtAwesome
)

