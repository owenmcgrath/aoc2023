cmake_minimum_required(VERSION 3.27)

project(aoc)
set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)

add_executable( ${TARGET_NAME}
    main.cpp
    lib/trie.cpp
    lib/loadInput.cpp
    one/one.cpp
    two/two.cpp
    three/three.cpp
    four/four.cpp
)

target_include_directories( ${TARGET_NAME} PRIVATE
    one/
    two/
    three/
    four/
    lib/
)
