#pragma once

#include <string_view>
#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include <GL/gl.h>
#include <GL/glext.h>
#include <iostream>
#include <vector>

#include <stdexcept>

bool HandleOpenGLDebugMessages(GLuint count) {
    // Allocate memory for the parameters
    std::vector<GLenum> sources(count);
    std::vector<GLenum> types(count);
    std::vector<GLuint> ids(count);
    std::vector<GLenum> severities(count);
    std::vector<GLsizei> lengths(count);
    std::vector<GLchar> messageLog(
        1024 * count); // Assuming an average length of 1024 chars per message

    // Get the debug messages
    GLuint receivedMessages = glGetDebugMessageLog(count,
                                                   messageLog.size(),
                                                   sources.data(),
                                                   types.data(),
                                                   ids.data(),
                                                   severities.data(),
                                                   lengths.data(),
                                                   messageLog.data());

    // Check if we received any messages
    if (receivedMessages == 0) {
        std::cout << "No more OpenGL debug messages retrieved." << std::endl;
        return false;
    }

    // Process and print each message
    size_t offset = 0;
    for (GLuint i = 0; i < receivedMessages; ++i) {
        std::string message(messageLog.data() + offset, lengths[i]);
        offset += lengths[i];

        std::cout << "Debug Message " << i + 1 << "/" << receivedMessages
                  << std::endl;
        std::cout << "Source: " << sources[i] << std::endl;
        std::cout << "Type: " << types[i] << std::endl;
        std::cout << "ID: " << ids[i] << std::endl;
        std::cout << "Severity: " << severities[i] << std::endl;
        std::cout << "Message: " << message << std::endl;
        std::cout << "------------------------------" << std::endl;
    }
    return true;
}

inline int checkGlError2(std::string_view file,
                         std::string_view line,
                         std::string_view op) {
#ifndef NO_GRAPHICS
    bool ret = false;
    for (auto error = glGetError(); error; error = glGetError()) {
        while (HandleOpenGLDebugMessages(3)) {
        };

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
        std::string fullErrorMessage = std::string(file) + ":" +
                                       std::string{line} + " - " +
                                       std::string(op) + " : " + std::string(c);
        throw std::runtime_error{fullErrorMessage};
    }
    return ret;
#else
    return false;
#endif
}

#ifndef glCall
#define glCall(call)                                                           \
    call;                                                                      \
    try {                                                                      \
        checkGlError2(__FILE__, std::to_string(__LINE__), #call);              \
    }                                                                          \
    catch (std::runtime_error & e) {                                           \
        throw e;                                                               \
    }                                                                          \
    do {                                                                       \
    } while (false)

#endif
