project(Sandbox VERSION 1.0 LANGUAGES CXX)

# 源文件
file(GLOB_RECURSE srcs "${PROJECT_SOURCE_DIR}/src/*.cpp")
# 可执行文件
add_executable(${PROJECT_NAME} ${srcs})
# 链接库
target_link_libraries(${PROJECT_NAME} PUBLIC Hazel)

# 拷贝资源文件到构建目录和运行目录
add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/asset"
            "${CMAKE_CURRENT_BINARY_DIR}/asset"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/asset"
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/asset"
        COMMENT "Copying assets to build and runtime directories"
)
