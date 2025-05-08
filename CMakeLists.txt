cmake_minimum_required(VERSION 3.28)
project(simpleSTL)

set(CMAKE_CXX_STANDARD 17)

add_executable(simpleSTL
        include/Vector.h
        include/List.h
        include/Deque.h
        include/HashTable.h
        include/RedBlackTree.h
)
