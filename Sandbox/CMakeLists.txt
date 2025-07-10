project(Sandbox VERSION 1.0 LANGUAGES CXX)

# 源文件
file(GLOB_RECURSE srcs "${PROJECT_SOURCE_DIR}/src/*.cpp")
# 可执行文件
add_executable(${PROJECT_NAME} ${srcs})
# 链接库
target_link_libraries(${PROJECT_NAME} PUBLIC Hazel)

# 获取资源文件列表 递归获取所有resources子文件
file(GLOB_RECURSE RESOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/asset/*")
# 目标拷贝目录
set(RESOURCE_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/asset")
# 添加 目标运行目录
set(RESOURCE_RUNTIME_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/asset")
# 自定义命令 拷贝并生成哑文件用于触发依赖
add_custom_command(
        OUTPUT "${RESOURCE_OUTPUT_DIR}/.copied"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/asset"
        "${RESOURCE_OUTPUT_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCE_OUTPUT_DIR}"
        "${RESOURCE_RUNTIME_DIR}"
        COMMAND ${CMAKE_COMMAND} -E touch "${RESOURCE_OUTPUT_DIR}/.copied"
        DEPENDS ${RESOURCE_FILES}
        COMMENT "Copying updated asset to both build and runtime directories"
)
# 自定义目标 执行上面的命令
add_custom_target(copy_resources ALL
        DEPENDS "${RESOURCE_OUTPUT_DIR}/.copied"
)
# 添加依赖 确保拷贝指令在主程序构建前完成
add_dependencies(${PROJECT_NAME} copy_resources)