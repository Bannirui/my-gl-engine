project(Hazel)
set(source_dir "${PROJECT_SOURCE_DIR}/src")

# 3rd-party
add_subdirectory(vendor)

# 头文件目录 spdlog
include_directories(vendor/spdlog/include)

# 源文件
file(GLOB_RECURSE srcs "${source_dir}/*.cpp")

# lib
add_library(${PROJECT_NAME} STATIC ${srcs})
# PCH
target_precompile_headers(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/hzpch.h")

# link spdlog
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog)

# 头文件搜索路径
file(GLOB_RECURSE headers_dir LIST_DIRECTORIES true "${CMAKE_SOURCE_DIR}/include")
foreach (dir ${headers_dir})
    if(IS_DIRECTORY ${dir})
        list(APPEND my_headers_dir ${dir})
    endif ()
endforeach ()
target_include_directories(${PROJECT_NAME} PRIVATE ${my_headers_dir})

# public供其他目标引用
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
# spdlog
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/vendor/spdlog/include")