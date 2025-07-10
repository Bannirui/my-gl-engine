project(Hazel VERSION 1.0 LANGUAGES CXX)

# 依赖的三方库
include(${CMAKE_SOURCE_DIR}/cmake/spdlog.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/glad.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/glfw.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/imgui.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/glm.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/stb.cmake)

# 开始编译自己的项目
file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE hdrs "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
# 生成库文件 添加头文件的目的仅仅是为了让IDEA识别到 新建文件的时候添加索引
add_library(${PROJECT_NAME} STATIC ${srcs} ${hdrs})
# public供Sandbox使用Hazel中的头文件
target_include_directories(${PROJECT_NAME}
        SYSTEM PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
# PCH
target_precompile_headers(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/hzpch.h")
# lib
target_link_libraries(${PROJECT_NAME}
        PUBLIC spdlog::spdlog
        PUBLIC glad
        PUBLIC glfw
        PUBLIC imgui
        PUBLIC glm::glm
        PUBLIC stb_image
)

if (APPLE)
    # OpenGL的API在mac上被弃用了 防止编译器warn
    add_definitions(-DGL_SILENCE_DEPRECATION)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE dl)
elseif(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
endif()