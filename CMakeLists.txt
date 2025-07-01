cmake_minimum_required(VERSION 3.16)

project(car-bt-hmi VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Bluetooth Svg)

qt_standard_project_setup()

add_executable(appcar-bt-hmi
    src/main.cpp
)

target_sources(appcar-bt-hmi
    PRIVATE
        src/BluetoothManager.cpp
        src/DeviceModel.cpp
        src/DataProvider.cpp
        src/Gauge.cpp
        src/SettingsManager.cpp
        src/StateIndicator.cpp

        include/BluetoothManager.hpp
        include/DeviceModel.hpp
        include/DataProvider.hpp
        include/Gauge.hpp
        include/SettingsManager.hpp
        include/StateIndicator.hpp
        include/ConnectionState.hpp
)

qt_add_resources(appcar-bt-hmi "qml_resources"
    PREFIX "/car-bt-hmi"
    FILES
        qml/Main.qml
        qml/DeviceList.qml
        qml/LoadingScreen.qml
        qml/MenuButton.qml
        qml/MenuFooter.qml
        qml/MenuHeader.qml
        qml/MenuIcon.qml
        qml/ScreenOverlay.qml
        qml/SideMenu.qml
        qml/Vignette.qml
        qml/menus/MainMenu.qml
        qml/menus/DeviceMenu.qml
        qml/menus/SettingsMenu.qml
        resources/Orbitron.ttf
        resources/logo.svg
)

target_include_directories(appcar-bt-hmi
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(appcar-bt-hmi
    PRIVATE Qt6::Quick Qt6::Bluetooth Qt6::Svg
)

set_target_properties(appcar-bt-hmi PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

include(GNUInstallDirs)
install(TARGETS appcar-bt-hmi
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
