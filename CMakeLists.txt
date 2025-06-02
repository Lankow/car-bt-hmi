cmake_minimum_required(VERSION 3.16)

project(car-bt-hmi VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Bluetooth)

qt_standard_project_setup()

qt_add_executable(appcar-bt-hmi
    main.cpp
)

qt_add_qml_module(appcar-bt-hmi
    URI car-bt-hmi
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES BluetoothManager.hpp BluetoothManager.cpp
        SOURCES
        SOURCES
        QML_FILES DeviceList.qml
        SOURCES DeviceModel.hpp DeviceModel.cpp
        SOURCES
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appcar-bt-hmi PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appcar-bt-hmi
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appcar-bt-hmi
    PRIVATE Qt6::Quick Qt6::Bluetooth
)

include(GNUInstallDirs)
install(TARGETS appcar-bt-hmi
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
