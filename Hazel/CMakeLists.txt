project(Hazel)
set(header_dir "${PROJECT_SOURCE_DIR}/include")
set(source_dir "${PROJECT_SOURCE_DIR}/src")

# 头文件目录
include_directories(include)

# 源文件
file(GLOB_RECURSE srcs "${source_dir}/*.cpp")

# lib
add_library(${PROJECT_NAME} STATIC ${srcs})
# 将当目录Eng/include设置为头文件搜索路路径 供其他目标引用
target_include_directories(${PROJECT_NAME} PUBLIC ${header_dir})