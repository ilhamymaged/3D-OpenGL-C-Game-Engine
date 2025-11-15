cmake_minimum_required (VERSION 3.10)
project ("3D Game Engine")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(Vendor/glfw)
add_subdirectory(Vendor/imgui)

file(GLOB_RECURSE SRC_FILES Core/*.cpp Renderer/*.cpp Editor/*.cpp Scene/*.cpp)
list(APPEND SRC_FILES GameEngine.cpp Vendor/glad/src/glad.c 
Vendor/stb/stb_image.cpp Vendor/tiny_obj_loader/tiny_obj_loader.cpp)

add_executable (CMakeTarget ${SRC_FILES})

target_include_directories(CMakeTarget PRIVATE 
    Core 
    Editor
    Renderer
    Scene
    Vendor/entt
    Vendor/glm  
    Vendor/glad/include
    Vendor/KHR
    Vendor/stb
    Vendor/tiny_obj_loader
)

target_link_libraries(CMakeTarget PRIVATE glfw ImGui)

if (WIN32)
    target_link_libraries(CMakeTarget PRIVATE opengl32)
endif()