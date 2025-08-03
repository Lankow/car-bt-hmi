cmake_minimum_required(VERSION 3.16)

project(car-bt-hmi VERSION 0.1 LANGUAGES CXX)

set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/android")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Bluetooth Svg)

qt_standard_project_setup()


qt_add_executable(appcar-bt-hmi
    main.cpp
)

qt_add_qml_module(appcar-bt-hmi
    URI car-bt-hmi
    VERSION 1.0
    SOURCES
        Gauge.hpp Gauge.cpp
        StateIndicator.hpp StateIndicator.cpp
        ConnectionState.hpp
        DataProvider.hpp DataProvider.cpp
        DeviceModel.hpp DeviceModel.cpp
        SettingsManager.hpp SettingsManager.cpp
        BluetoothManager.hpp BluetoothManager.cpp
        ObdService.hpp ObdService.cpp
    QML_FILES
        Main.qml
        Vignette.qml
        LoadingScreen.qml
        ScreenOverlay.qml
        MenuState.qml
        ScreenTransition.qml
        MenuIcon.qml
        SideMenu.qml
        MenuHeader.qml
        MainMenu.qml
        MenuFooter.qml
        MenuEntry.qml
        Clock.qml
        DeviceMenu.qml
        DeviceList.qml
        ObdMenu.qml
        SettingsMenu.qml
        MenuNumberInput.qml
        InfoMenu.qml
        MenuTextBlock.qml
        ConfirmMenu.qml
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
