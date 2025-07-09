project(Hazel VERSION 1.0 LANGUAGES CXX)

# 依赖FetchContent管理三方库
include(FetchContent)

# glad的代码生成依赖py和glad
find_package(Python3 REQUIRED COMPONENTS Interpreter)
set(GLAD_VENV "${CMAKE_BINARY_DIR}/.venv")
set(GLAD_PYTHON "${GLAD_VENV}/bin/python")
# 检查glad命令是否可用
execute_process(
        COMMAND ${Python3_EXECUTABLE} -m glad --version
        RESULT_VARIABLE GLAD_RESULT
        OUTPUT_VARIABLE GLAD_VERSION
        ERROR_VARIABLE GLAD_ERROR
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_STRIP_TRAILING_WHITESPACE
)
if(NOT GLAD_RESULT EQUAL 0)
    message(STATUS "Glad not found. Setting up local virtualenv...")
    # 创建.venv
    execute_process(
            COMMAND ${Python3_EXECUTABLE} -m venv ${GLAD_VENV}
            RESULT_VARIABLE VENV_RESULT
    )
    if(NOT VENV_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to create virtualenv at ${GLAD_VENV}")
    endif()
    # 安装glad到虚拟环境中
    execute_process(
            COMMAND ${GLAD_VENV}/bin/pip install glad
            RESULT_VARIABLE PIP_RESULT
            OUTPUT_VARIABLE PIP_OUT
            ERROR_VARIABLE PIP_ERR
    )
    if(NOT PIP_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to install glad in virtualenv:\n${PIP_ERR}")
    endif()
    message(STATUS "Glad installed successfully in ${GLAD_VENV}")
endif()

# spdlog
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY	https://github.com/Bannirui/spdlog.git
        GIT_TAG 	    4397dac510274c7ccf79b5f40b1b747033c12dda
)
# glfw
FetchContent_Declare(
        glfw
        GIT_REPOSITORY	https://github.com/Bannirui/glfw.git
        GIT_TAG 	    506c11ba43b901dbcc4d90449f46de67cf000af4
)
# glad
FetchContent_Declare(
        glad
        GIT_REPOSITORY	https://github.com/Bannirui/glad.git
        GIT_TAG 	    431786d8126e4f383a81e36f47b61a5d52a1c20d
)
# imgui
FetchContent_Declare(
        imgui
        GIT_REPOSITORY	https://github.com/Bannirui/imgui.git
        GIT_TAG 	    fd75bdccb033e74afeba44f500edc8fcef7eb023
)
# glm
FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/Bannirui/glm.git
        GIT_TAG 	    dca38025fba63bb9284023e6de55f756b9e37cec
)
# 下载依赖的源码
FetchContent_MakeAvailable(spdlog glfw glad imgui glm)

# glad2没有现成的代码 用py生成glad代码
set(GLAD_GENERATED_DIR "${CMAKE_BINARY_DIR}/generated/glad")
file(MAKE_DIRECTORY ${GLAD_GENERATED_DIR})
add_custom_command(
        OUTPUT
            ${GLAD_GENERATED_DIR}/src/glad.c
            ${GLAD_GENERATED_DIR}/include/glad/glad.h
        COMMAND ${GLAD_PYTHON} -m glad
          --generator c
          --spec gl
          --api gl=3.3
          --profile core
          --out-path ${GLAD_GENERATED_DIR}
        COMMENT "Generating glad loader with glad2"
        VERBATIM
)
# 自定义目标glad-gen
add_custom_target(glad-gen
        DEPENDS
        ${GLAD_GENERATED_DIR}/src/glad.c
        ${GLAD_GENERATED_DIR}/include/glad/glad.h
)
# glad
add_library(glad STATIC
        ${GLAD_GENERATED_DIR}/src/glad.c
)
target_include_directories(glad PUBLIC ${GLAD_GENERATED_DIR}/include)
add_dependencies(glad glad-gen)

# ImGui
file(GLOB IMGUI_SOURCES
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui PUBLIC glfw)

# OpenGL的API在mac上被弃用了 防止编译器warn
add_definitions(-DGL_SILENCE_DEPRECATION)
# 源文件
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
)

# Platform-specific OpenGL linkage
if (APPLE)
    add_definitions(-DGL_SILENCE_DEPRECATION)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE dl)
elseif(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
endif()