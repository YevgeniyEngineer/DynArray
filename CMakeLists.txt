cmake_minimum_required(VERSION 3.18)

project(DynArray)
set(CMAKE_CXX_STANDARD 17)

find_package(TBB REQUIRED)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/src/main.cpp
)
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/include
)
target_link_libraries(${PROJECT_NAME}
    TBB::tbb
)