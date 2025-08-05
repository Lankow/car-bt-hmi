cmake_minimum_required(VERSION 3.16)

project(car-bt-hmi VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Bluetooth Svg)

qt_standard_project_setup()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/include/*.hpp
)

qt_add_executable(appcar-bt-hmi
    main.cpp
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(appcar-bt-hmi
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)

file(GLOB_RECURSE QML_FILES CONFIGURE_DEPENDS
    RELATIVE ${CMAKE_SOURCE_DIR}
    qml/*.qml
)

qt_add_qml_module(appcar-bt-hmi
    URI car-bt-hmi
    VERSION 1.0
    QML_FILES ${QML_FILES}
)

qt_add_resources(appcar-bt-hmi "resources"
    PREFIX /
    FILES
        fonts/Orbitron.ttf
        resources/logo.svg
)

set_target_properties(appcar-bt-hmi PROPERTIES
    QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appcar-bt-hmi
    PRIVATE APP_VERSION="${PROJECT_VERSION}"
)

target_link_libraries(appcar-bt-hmi
    PRIVATE Qt6::Quick Qt6::Bluetooth Qt6::Svg
)

include(GNUInstallDirs)
install(TARGETS appcar-bt-hmi
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
