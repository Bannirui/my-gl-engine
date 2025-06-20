cmake_minimum_required(VERSION 3.15)

# 项目信息
project(my-cpp-tutorial
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
foreach(f_path ${srcs})
    # 不带扩展名人文件名main
    get_filename_component(s_name ${f_path} NAME_WE)
    # 输出.i .s文件
    set(i_file ${CMAKE_CURRENT_BINARY_DIR}/${s_name}.i)
    set(s_file ${CMAKE_CURRENT_BINARY_DIR}/${s_name}.s)
    add_custom_command(
            OUTPUT ${i_file} ${s_file}
            # 预编译.i文件
            COMMAND ${CMAKE_CXX_COMPILER} -E -O0
                -I${CMAKE_SOURCE_DIR}/include -I${CMAKE_SOURCE_DIR}/src
                ${f_path}
                -o ${i_file}
            # 默认AT&T风格 -masm=intel
            COMMAND ${CMAKE_CXX_COMPILER} -S -fverbose-asm -O0
                -I${CMAKE_SOURCE_DIR}/include -I${CMAKE_SOURCE_DIR}/src
                ${f_path}
                -o ${s_file}
            DEPENDS ${f_path}
            COMMENT "Generating ${s_name}.i and ${s_name}.s"
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