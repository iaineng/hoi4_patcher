cmake_minimum_required(VERSION 3.20)
project(hoi4_patcher VERSION 1.0)

# 设置C++标准为C++20 (由于很多编译器还未完全支持C++23，我们使用C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 添加可执行文件
add_executable(hoi4_patcher 
    src/main.cpp
    src/pattern_matcher.cpp
    src/file_utils.cpp
)

target_include_directories(hoi4_patcher PRIVATE src)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 如果是MSVC编译器，启用UTF-8编码支持
if(MSVC)
    add_compile_options(/utf-8)
endif()
