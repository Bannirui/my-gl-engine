project(Hazel VERSION 1.0 LANGUAGES CXX)

# 3rd-party
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/GLAD)
add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/imgui)

# OpenGL的API在mac上被弃用了 防止编译器warn
add_definitions(-DGL_SILENCE_DEPRECATION)

# 源文件
file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
# 生成库文件
add_library(${PROJECT_NAME} STATIC ${srcs})
# public供Sandbox使用Hazel中的头文件
target_include_directories(${PROJECT_NAME}
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
# PCH
target_precompile_headers(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/hzpch.h")
# lib
target_link_libraries(${PROJECT_NAME}
        PUBLIC spdlog
        PUBLIC glad
        PUBLIC glfw
        PUBLIC imgui
)
