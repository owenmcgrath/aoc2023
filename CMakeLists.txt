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
    five/five.cpp
    six/six.cpp
    seven/seven.cpp
    eight/eight.cpp
    nine/nine.cpp
    ten/ten.cpp
    eleven/eleven.cpp
)

target_include_directories( ${TARGET_NAME} PRIVATE
    one/
    two/
    three/
    four/
    five/
    six/
    lib/
    seven/
    eight/
    nine/
    ten/
    eleven/
)
