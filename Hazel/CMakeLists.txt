project(Hazel)
set(source_dir "${PROJECT_SOURCE_DIR}/src")

# 3rd-party
add_subdirectory(vendor)

# 头文件目录
include_directories(include/Hazel)
# spdlog
include_directories(vendor/spdlog/include)

# 源文件
file(GLOB_RECURSE srcs "${source_dir}/*.cpp")

# lib
add_library(${PROJECT_NAME} STATIC ${srcs})
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog)

# 将当目录Eng/include设置为头文件搜索路路径 供其他目标引用
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
# spdlog
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/vendor/spdlog/include")