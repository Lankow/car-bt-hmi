cmake_minimum_required(VERSION 3.16)

project(car-bt-hmi VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Bluetooth Svg)

qt_standard_project_setup()

qt_add_executable(appcar-bt-hmi
    main.cpp
)

qt_add_qml_module(appcar-bt-hmi
    URI car-bt-hmi
    VERSION 1.0
    QML_FILES
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
    SOURCES
        BluetoothManager.hpp BluetoothManager.cpp
        DeviceModel.hpp DeviceModel.cpp
        DataProvider.hpp DataProvider.cpp
        Gauge.hpp Gauge.cpp
        SettingsManager.hpp SettingsManager.cpp
        StateIndicator.hpp StateIndicator.cpp
        ConnectionState.hpp
    RESOURCES
        resources/Orbitron.ttf
        resources/logo.svg
)

set_target_properties(appcar-bt-hmi PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
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
