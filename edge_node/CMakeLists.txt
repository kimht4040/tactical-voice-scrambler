cmake_minimum_required(VERSION 3.10)

project(TacticalVoiceScrambler CXX)

# C++17 표준 적용
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 나중을 대비한 스레드 라이브러리 추가
find_package(Threads REQUIRED)

# src 폴더의 main.cpp를 엮어서 edge_node라는 실행파일 생성
add_executable(edge_node src/udp_test.cpp)

target_link_libraries(edge_node PRIVATE Threads::Threads)