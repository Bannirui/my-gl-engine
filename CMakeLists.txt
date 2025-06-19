cmake_minimum_required(VERSION 3.15)

# 项目信息
project(my_tutorial
        VERSION 1.0
        LANGUAGES CXX
)

# cpp标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")
set(source_dir "${PROJECT_SOURCE_DIR}/src/")

# 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 头文件目录
include_directories(include)

# 源文件
file(GLOB_RECURSE srcs "${source_dir}/*.cpp")

# 编译输出指定源码文件的汇编
foreach(f_name main.cpp Log.cpp)
    get_filename_component(s_name ${f_name} NAME_WE)
    add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${s_name}.i
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${s_name}.s
            # 预编译.i文件
            COMMAND ${CMAKE_CXX_COMPILER} -E -O0
                -I${CMAKE_SOURCE_DIR}/include -I${CMAKE_SOURCE_DIR}/src
                ${CMAKE_SOURCE_DIR}/src/${f_name}
                -o ${CMAKE_CURRENT_BINARY_DIR}/${s_name}.i
            # 默认AT&T风格 -masm=intel
            COMMAND ${CMAKE_CXX_COMPILER} -S -fverbose-asm -O0
                -I${CMAKE_SOURCE_DIR}/include -I${CMAKE_SOURCE_DIR}/src
                ${CMAKE_SOURCE_DIR}/src/${f_name}
                -o ${CMAKE_CURRENT_BINARY_DIR}/${s_name}.s
            DEPENDS ${CMAKE_SOURCE_DIR}/src/${f_name}
            COMMENT "Generating .i and assembly(.s) for ${s_name}"
    )
    # make view_asm_main
    add_custom_target(view_${s_name}
            DEPENDS
                ${CMAKE_CURRENT_BINARY_DIR}/${s_name}.i
                ${CMAKE_CURRENT_BINARY_DIR}/${s_name}.s
    )
endforeach()

# 可执行文件
add_executable(${PROJECT_NAME} ${srcs})