cmake_minimum_required(VERSION 3.21)

project(vl LANGUAGES C)

function(vl_default_options TARGET)
    set_target_properties(
        ${TARGET} PROPERTIES
        C_STANDARD 99
        C_STANDARD_REQUIRED ON
    )

    if(MSVC)
        target_compile_options(${TARGET} PRIVATE /W4)
    else()
        target_compile_options(${TARGET} PRIVATE -Wall -Wextra -pedantic)
    endif()
endfunction(vl_default_options)

add_executable(vl
    "compiler/main.c"
    "compiler/lexer.h"
    "compiler/lexer.c"
    "compiler/list.h"
    "compiler/list.c"
)

add_executable(vlvm
    "vm/main.c"
    "vm/vm.h"
    "vm/vm.c"
    "vm/ops.h"
)

vl_default_options(vl)
vl_default_options(vlvm)