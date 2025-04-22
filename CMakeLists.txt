cmake_minimum_required(VERSION 3.26)

project(oop)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)

###############################################################################
# Fetch SFML
include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

set(WARNINGS_AS_ERRORS OFF)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        2.6.1
        GIT_SHALLOW    1
)

FetchContent_MakeAvailable(SFML)

###############################################################################
# System packages

find_package(Threads REQUIRED)
if(APPLE)
elseif(UNIX)
    find_package(X11 REQUIRED)
endif()

###############################################################################
# Executable

add_executable(${PROJECT_NAME}
        main.cpp
        generated/src/Helper.cpp
        env_fixes.h
)

include(cmake/CompilerFlags.cmake)

###############################################################################
# OpenMP

find_package(OpenMP)

if(OpenMP_CXX_FOUND)
    message(STATUS "Found OpenMP")
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _OPENMP)
else()
    message(WARNING "OpenMP not found — building without OpenMP support")
endif()


###############################################################################
# Include + Link

target_include_directories(${PROJECT_NAME}
        SYSTEM PRIVATE
        generated/include
        ${SFML_SOURCE_DIR}/include
)

target_link_directories(${PROJECT_NAME}
        PRIVATE ${SFML_BINARY_DIR}/lib
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        Threads::Threads
)

if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE X11)
endif()

###############################################################################
# Install

install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

###############################################################################
# Windows DLL copy for SFML audio

if (WIN32 AND SFML_BUILD_AUDIO)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SFML_SOURCE_DIR}/extlibs/bin/x64/openal32.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()

###############################################################################
# Copy resources

include(cmake/CopyHelper.cmake)
copy_files(FILES tastatura.txt)
# copy_files(FILES tastatura.txt config.json DIRECTORY images sounds)
# copy_files(DIRECTORY images sounds)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -ffast-math")
