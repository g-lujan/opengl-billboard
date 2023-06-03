cmake_minimum_required(VERSION 3.23.2)
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(COMPILER "msvc" CACHE STRING "Enter the compiler to be used")
option(STATIC_LINKING "Static linking dependencies" OFF)

project(some_game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(COMPILER "mingw" CACHE STRING "Enter the compiler to be used")

find_package(SDL2 CONFIG REQUIRED)
if(NOT STATIC_LINKING)
 find_package(sdl2-image CONFIG REQUIRED)
endif()
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)

set(SOURCE_FILES 
	code/main.cpp
      code/external/stbi.hpp
      code/window/window.cpp
      code/window/window.hpp
      code/shape/box.hpp
      code/shape/box.cpp
      code/shape/vertices.hpp
      code/shape/billboard.hpp
      code/shape/billboard.cpp
      code/player/player.hpp
      code/collision/collision.hpp
      code/collision/collision.cpp
      code/controls/controls.hpp
      code/controls/configurations.hpp
      code/controls/configurations.cpp
      code/camera/camera.hpp
      code/camera/camera.cpp
      code/resources/resources.cpp
      code/resources/resources.hpp
      code/shaders/shader.hpp
      code/shaders/shader.cpp
)
set(SHADER_FILES shaders/box.fs shaders/box.vs shaders/billboard.vs)
set(ASSET_FILES assets/textures/container.jpg assets/textures/player.jpg)
set(ALL_PROJECT_FILES ${SOURCE_FILES} ${SHADER_FILES} ${ASSET_FILES})

# for Visual Studio debug
file(COPY assets DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY shaders DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

foreach(MODE Debug Release)
 file(COPY assets DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/${MODE}")
 file(COPY shaders DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/${MODE}")
endforeach()


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ALL_PROJECT_FILES})

# You need to add all files on the executable for them to be visible on 
# the source_group in Visual Studio
# https://stackoverflow.com/a/31653555/14815076
# (maybe remove it in prod builds)
add_executable(${PROJECT_NAME} ${ALL_PROJECT_FILES})

# order matters here!
if(STATIC_LINKING)
 target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static)
else()
 target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2)
 target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2_image)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

message(STATUS "Using compiler: ${COMPILER}")
if(COMPILER STREQUAL "mingw")
 target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Winit-self -pedantic)
elseif(COMPILER STREQUAL "msvc")
 target_compile_options(${PROJECT_NAME} PRIVATE /WX)
else()
 message(FATAL_ERROR "${COMPILER} is not a valid compiler, pick either mingw or msvc")
endif()

unset(STATIC_LINKING CACHE)