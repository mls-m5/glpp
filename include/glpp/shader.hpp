#pragma once

#include "error.h"
#include "errors.hpp"
#include "gl-backend.hpp"
#include "unique.hpp"
#include <GL/gl.h>
#include <GL/glext.h>
#include <stdexcept>
#include <string>
#include <string_view>

namespace gl {

class Shader : public detail::Unique<GLuint, glDeleteShader> {
public:
    Shader(GLenum type) : Unique{glCreateShader(type)} {
    }

    GLint iv(GLenum name) {
        GLint i = 0;
        glGetShaderiv(*this, name, &i);
        return i;
    }

    std::string infoLog() {
        GLint infoLen = iv(GL_INFO_LOG_LENGTH);
        auto str = std::string{};
        str.resize(infoLen);
        glGetShaderInfoLog(*this, infoLen, nullptr, str.data());
        return str;
    }

    void source(std::string_view src) {
        const GLint lenghts[1] = {static_cast<GLint>(src.size())};
        auto data = src.data();
        glShaderSource(*this, 1, &data, lenghts);
    }

    void compile() {
        glCompileShader(*this);
    }
};

inline Shader loadShader(GLenum type, const std::string_view src) {
    auto shader = Shader{type};

    if (!shader) {
        throw ContextError{"Could not compile shader. Check if window "
                           "and context is started properly"};
    }

    shader.source(src);
    shader.compile();
    GLint isCompiled = shader.iv(GL_COMPILE_STATUS);

    if (!isCompiled) {
        throw ShaderCompilationError{"error when compiling shader:\n " +
                                     shader.infoLog()};
    }

    return shader;
}

} // namespace gl
