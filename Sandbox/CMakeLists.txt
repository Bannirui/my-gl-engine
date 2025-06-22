project(Sandbox)
set(source_dir "${PROJECT_SOURCE_DIR}/src")

# 头文件目录
include_directories(include)

# 源文件
file(GLOB_RECURSE srcs "${source_dir}/*.cpp")

# 可执行文件
add_executable(${PROJECT_NAME} ${srcs})

# 链接库 自动继承头文件路径${LibName}/include
target_link_libraries(${PROJECT_NAME} PRIVATE Hazel)