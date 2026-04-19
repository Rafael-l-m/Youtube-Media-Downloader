cmake_minimum_required(VERSION 4.2)
project(MediaDownloader)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Configure Qt Path
if (APPLE)
    set(CMAKE_PREFIX_PATH "/Users/aguam/Applications/Qt/6.11.0/macos")
elseif (WIN32)
    set(CMAKE_PREFIX_PATH "C:/Qt/6.11.0/mingw_64")
elseif (UNIX AND NOT APPLE)
    set(CMAKE_PREFIX_PATH "/home/rafael/Applications/Qt/6.11.0/gcc_64")
endif ()

# Test Use-after-free (Azan)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
#set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")

# include all .h files
include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(Qt6 COMPONENTS
        Concurrent
        Core
        Gui
        Network
        Sql
        Widgets
        REQUIRED)

add_executable(MediaDownloader main.cpp
        include/constants/Core_Constants.hpp
        include/constants/Db_Constants.hpp
        include/constants/Download_Constants.hpp
        include/constants/Ui_Constants.hpp
        include/constants/Update_Constants.hpp
        include/container/Download.hpp
        src/container/Download.cpp
        include/container/ToolsPath.hpp
        src/container/ToolsPath.cpp
        include/core/BasicTools.hpp
        include/core/CryptoManager.hpp
        src/core/CryptoManager.cpp
        include/core/IdIndexMap.hpp
        src/core/IdIndexMap.cpp
        include/core/SharedStorage.hpp
        src/core/SharedStorage.cpp
        include/db/DataBase.hpp
        src/db/DataBase.cpp
        include/db/DbClient.hpp
        src/db/DbClient.cpp
        include/db/DbManager.hpp
        src/db/DbManager.cpp
        include/db/DbServer.hpp
        src/db/DbServer.cpp
        include/db/Operation.hpp
        include/db/Request.hpp
        include/db/Specification.hpp
        include/download/DownloadManager.hpp
        src/download/DownloadManager.cpp
        include/download/DownloadWorker.hpp
        src/download/DownloadWorker.cpp
        include/ui/DownloadCard.hpp
        src/ui/DownloadCard.cpp
        include/ui/DownloadConfig.hpp
        src/ui/DownloadConfig.cpp
        include/ui/GlassWidget.hpp
        src/ui/GlassWidget.cpp
        src/ui/MainWindow.cpp
        include/ui/MainWindow.hpp
        include/ui/NoticeView.hpp
        src/ui/NoticeView.cpp
        include/ui/SettingsView.hpp
        src/ui/SettingsView.cpp
        include/ui/ShowItags.hpp
        src/ui/ShowItags.cpp
        include/update/UpdateChecker.hpp
        src/update/UpdateChecker.cpp
)

target_link_libraries(MediaDownloader PRIVATE
        Qt::Concurrent
        Qt::Core
        Qt::Gui
        Qt::Network
        Qt::Sql
        Qt::Widgets
)

if (UNIX OR APPLE)
    # import libsodium
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SODIUM REQUIRED libsodium)

    target_include_directories(MediaDownloader PRIVATE ${SODIUM_INCLUDE_DIRS})
    target_link_directories(MediaDownloader PRIVATE ${SODIUM_LIBRARY_DIRS})
    target_link_libraries(MediaDownloader PRIVATE ${SODIUM_LIBRARIES})

    # import boost
    find_package(Boost REQUIRED)
    include_directories(${Boost_INCLUDE_DIRS})

elseif (WIN32)
    set_target_properties(MediaDownloader PROPERTIES WIN32_EXECUTABLE TRUE)

    set(APP_ICON "${CMAKE_SOURCE_DIR}/resources/icons/AppIcon.ico")
    target_sources(MediaDownloader PRIVATE resources/MediaDownloader.rc)
    target_compile_definitions(MediaDownloader PRIVATE APP_ICON_PATH="${APP_ICON}")

    #import boost
    set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/external/boost_1_90_0")
    target_include_directories(MediaDownloader PRIVATE ${BOOST_ROOT})

    # import libsodium
    set(LIBSODIUM_ROOT "${CMAKE_SOURCE_DIR}/external/libsodium")
    target_include_directories(MediaDownloader PRIVATE ${LIBSODIUM_ROOT}/include)
    target_link_directories(MediaDownloader PRIVATE ${LIBSODIUM_ROOT}/lib)
    target_link_libraries(MediaDownloader PRIVATE libsodium)
endif ()

if (APPLE)
    set_target_properties(MediaDownloader PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_ICON_FILE AppIcon.icns
    )

    add_custom_command(TARGET MediaDownloader POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/translations
            $<TARGET_BUNDLE_DIR:MediaDownloader>/Contents/Resources/translations
    )

    add_custom_command(TARGET MediaDownloader POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/resources/icons
            $<TARGET_BUNDLE_DIR:MediaDownloader>/Contents/Resources/icons
    )

    add_custom_command(TARGET MediaDownloader POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/resources/icons/AppIcon.icns
            $<TARGET_BUNDLE_DIR:MediaDownloader>/Contents/Resources/AppIcon.icns
    )

elseif(WIN32)
    add_custom_command(TARGET MediaDownloader POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/translations
            $<TARGET_FILE_DIR:MediaDownloader>/translations
    )

    add_custom_command(TARGET MediaDownloader POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/resources/icons
            $<TARGET_FILE_DIR:MediaDownloader>/resources/icons
    )

    if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        set(DEBUG_SUFFIX)
        if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
            set(DEBUG_SUFFIX "d")
        endif ()
        set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
            if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
                set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
            endif ()
        endif ()
        if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        endif ()
        foreach (QT_LIB Core Gui Widgets)
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
        endforeach (QT_LIB)
    endif ()

elseif (UNIX AND NOT APPLE)
    add_custom_command(TARGET MediaDownloader POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/translations
            $<TARGET_FILE_DIR:MediaDownloader>/translations
    )

    add_custom_command(TARGET MediaDownloader POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/resources/icons
            $<TARGET_FILE_DIR:MediaDownloader>/resources/icons
    )
endif ()
