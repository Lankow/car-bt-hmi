cmake_minimum_required(VERSION 3.16)

project(car-bt-hmi VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Bluetooth Svg)

qt_standard_project_setup()

add_executable(appcar-bt-hmi
    src/main.cpp
)

qt_add_qml_module(appcar-bt-hmi
    URI car-bt-hmi
    VERSION 1.0
    SOURCES
        include/BluetoothManager.hpp src/BluetoothManager.cpp
        include/DeviceModel.hpp src/DeviceModel.cpp
        include/DataProvider.hpp src/DataProvider.cpp
        include/Gauge.hpp src/Gauge.cpp
        include/SettingsManager.hpp src/SettingsManager.cpp
        include/StateIndicator.hpp src/StateIndicator.cpp
        include/ConnectionState.hpp

    QML_FILES
        qml/Main.qml
        qml/DeviceList.qml
        qml/LoadingScreen.qml
        qml/MenuEntry.qml
        qml/MenuFooter.qml
        qml/MenuHeader.qml
        qml/MenuIcon.qml
        qml/ScreenOverlay.qml
        qml/SideMenu.qml
        qml/Vignette.qml
        qml/MainMenu.qml
        qml/DeviceMenu.qml
        qml/SettingsMenu.qml
        qml/ScreenTransition.qml
        qml/InfoMenu.qml
        qml/ObdMenu.qml
        qml/ConfirmMenu.qml
        qml/MenuState.qml

    RESOURCES
        resources/Orbitron.ttf
        resources/logo.svg
        QML_FILES qml/MenuTextBlock.qml
        QML_FILES qml/Clock.qml
)

target_compile_definitions(appcar-bt-hmi
    PRIVATE
    APP_VERSION="${PROJECT_VERSION}"
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
