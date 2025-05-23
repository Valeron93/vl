cmake_minimum_required(VERSION 3.21)

project(vl LANGUAGES C)

add_executable(vl 
    "src/main.c"
    "src/lexer.h"
    "src/lexer.c"
    "src/list.h"
    "src/list.c"
)

set_target_properties(vl PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()