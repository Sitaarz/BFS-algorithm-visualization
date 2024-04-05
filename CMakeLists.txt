cmake_minimum_required(VERSION 3.16)

project(C_connection VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appC_connection
    main.cpp
)

qt_add_qml_module(appC_connection
    URI C_connection
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES BFS_class.h BFS_class.cpp
    SOURCES Node.h Node.cpp
    RESOURCES
    assets/images/linegraphsymbol_120645.ico
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appC_connection PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appC_connection
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appC_connection
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appC_connection
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
