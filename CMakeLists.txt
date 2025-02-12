# CMakeLists.txt
cmake_minimum_required(VERSION 3.30)
project(C___learn)

set(CMAKE_CXX_STANDARD 14)

# 查找并使用 Threads 包
find_package(Threads REQUIRED)

# 添加所有源文件到可执行文件
add_executable(C___learn
        main.cpp
        pthread/my_pthread.cpp
        C++11/auto.cpp
)

# 链接 pthread 库
target_link_libraries(C___learn PRIVATE ${CMAKE_THREAD_LIBS_INIT})

# 添加头文件目录（如果需要）
include_directories(pthread)
