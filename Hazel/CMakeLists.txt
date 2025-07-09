project(Hazel VERSION 1.0 LANGUAGES CXX)

# 依赖FetchContent管理三方库
include(FetchContent)

FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/Bannirui/glm.git
        GIT_TAG 	dca38025fba63bb9284023e6de55f756b9e37cec
)
FetchContent_MakeAvailable(glm)

# 3rd-party
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/GLAD)
add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/imgui)

# OpenGL的API在mac上被弃用了 防止编译器warn
add_definitions(-DGL_SILENCE_DEPRECATION)

# 源文件
file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE hdrs "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
# 生成库文件 添加头文件的目的仅仅是为了让IDEA识别到 新建文件的时候添加索引
add_library(${PROJECT_NAME} STATIC ${srcs} ${hdrs})
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
        PUBLIC glm::glm
)