project(Sandbox VERSION 1.0 LANGUAGES CXX)

# 源文件
file(GLOB_RECURSE srcs "${PROJECT_SOURCE_DIR}/src/*.cpp")
# 可执行文件
add_executable(${PROJECT_NAME} ${srcs})
# 链接库
target_link_libraries(${PROJECT_NAME} PUBLIC Hazel)