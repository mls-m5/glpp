cmake_minimum_required(VERSION 3.22)


function(demo name)
    add_executable(${name}-glpp-demo ${name}-demo.cpp)
    target_link_libraries(${name}-glpp-demo
        MatGui
        SDL2_image
        glpp
        )
endfunction()

demo(basic)
