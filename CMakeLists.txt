cmake_minimum_required(VERSION 3.23)
project(FlappyBird)

set(CMAKE_CXX_STANDARD 20)

# Find required SDL2 packages
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Specify the source directory and the build directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_executable(FlappyBird src/main.cpp src/Game.cpp src/Game.h src/InputHandler.cpp src/InputHandler.h src/TTFManager.cpp src/TTFManager.h src/Bird.cpp src/Bird.h src/Pipe.cpp src/Pipe.h src/ConfigHelper.cpp src/ConfigHelper.h)

# STATIC stuff (Windows)
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(BUILD_FOR_WIN TRUE)
    target_link_libraries(FlappyBird SDL2::SDL2main SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image nlohmann_json::nlohmann_json mingw32)
endif()
option(STATIC_BUILD "Build a static binary." ${BUILD_FOR_WIN})

if (STATIC_BUILD)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" CONFIG)
    set(BUILD_SHARED_LIBS OFF)
endif()

# Create a custom command to copy the assets folder to the build folder
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SOURCE_DIR}/Assets ${BUILD_DIR}/Assets
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(FlappyBird SDL2::SDL2main SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image  nlohmann_json::nlohmann_json)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")