cmake_minimum_required(VERSION 3.10)
project(raytracing_one_weekend)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include 디렉토리 추가
include_directories(${PROJECT_SOURCE_DIR}/include)

# 소스 파일 수집
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 실행 파일 생성
add_executable(${PROJECT_NAME} ${SOURCES})

# 컴파일 옵션
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
