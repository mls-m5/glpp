#pragma once

#include <string_view>
#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include <GL/gl.h>
#include <GL/glext.h>

#include <stdexcept>

inline int checkGlError2(std::string_view op) {
#ifndef NO_GRAPHICS
    bool ret = false;
    for (auto error = glGetError(); error; error = glGetError()) {
        std::string_view c = {};
        switch (error) {
        case 0x0500:
            c = "GL_INVALID_ENUM";
            break;
        case 0x0501:
            c = "GL_INVALID_VALUE";
            break;
        case 0x0502:
            c = "GL_INVALID_OPERATION";
            break;
        case 0x0503:
            c = "GL_STACK_OVERFLOW";
            break;
        case 0x0504:
            c = "GL_STACK_UNDERFLOW";
            break;
        case 0x0505:
            c = "GL_OUT_OF_MEMORY";
            break;
        case 0x0506:
            c = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        case 0x0507:
            c = "GL_CONTEXT_LOST";
            break;
        case 0x8031:
            c = "GL_TABLE_TOO_LARGE1";
            break;
        }
        throw std::runtime_error{std::string{op} + " : " + std::string{c}};
    }
    return ret;
#else
    return false;
#endif
}

#ifndef glCall
#define glCall(call)                                                           \
    call;                                                                      \
    checkGlError2(#call)

#endif
