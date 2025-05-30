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


add_library(
    vl_lib STATIC
    "lib/vl/common/vl_list.h"    
    "lib/vl/common/vl_list.c"
    "lib/vl/compiler/lexer.h"    
    "lib/vl/compiler/lexer.c"    
    "lib/vl/vm/ops.h"    
    "lib/vl/vm/vm.h"
    "lib/vl/vm/vm.c"    
)
target_include_directories(vl_lib PUBLIC "lib/")
vl_default_options(vl_lib)

add_executable(
    vl
    "main.c"
)
vl_default_options(vl_lib)
target_link_libraries(vl PUBLIC vl_lib)