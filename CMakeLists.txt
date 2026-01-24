cmake_minimum_required(VERSION 3.16)
project(moulin LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(moulin main.c)

if(MSVC)
    # MSVC suggests its own *_s versions of scanf, strcpy and friends.
    # The standard functions are used on purpose, to stay portable.
    target_compile_definitions(moulin PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
