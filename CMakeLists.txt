cmake_minimum_required(VERSION 3.28)
project(Library)

set(CMAKE_CXX_STANDARD 17)

add_executable(Library _Interface.cpp
        lib.h
        Book.h
        Reader.h
        library.h
        Reader.cpp
        project.h
        Book.cpp
        Library.cpp
)
