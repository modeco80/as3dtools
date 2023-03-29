cmake_minimum_required(VERSION 3.10)

# Prohibit in-source tree builds.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are strictly prohibited.")
endif()

include(cmake/Policies.cmake)

project(As3dTools
        VERSION 1.0.0
        LANGUAGES C CXX
        DESCRIPTION "Tools for working with the Air Strike 3D games"
        )

include(FetchContent)

# declare dependencies
FetchContent_Declare(indicators
        GIT_REPOSITORY https://github.com/p-ranav/indicators.git
        )

FetchContent_Declare(argparse
        GIT_REPOSITORY https://github.com/p-ranav/argparse.git
        )

FetchContent_MakeAvailable(indicators argparse)


add_subdirectory(src/as3d)
add_subdirectory(src/tools)