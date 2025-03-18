#pragma once

#include "errors.hpp"
#include "gl-backend.hpp"
#include "shader.hpp"
#include "unique.hpp"
#include <GL/gl.h>
#include <GL/glext.h>
#include <string>

namespace gl {

class Program : public detail::Unique<GLuint, glDeleteProgram> {
public:
    Program() {
        reset(glCreateProgram());
        if (!*this) {
            throw ContextError{"could not create shader program"};
        }
    }

    void attach(GLint shader) {
        glAttachShader(*this, shader);
    }

    void detach(GLint shader) {
        glDetachShader(*this, shader);
    }

    GLint iv(GLenum name) const {
        auto i = GLint{};
        glGetProgramiv(*this, name, &i);
        return i;
    }

    std::string infoLog() const {
        auto len = iv(GL_INFO_LOG_LENGTH);
        auto text = std::string{};
        text.resize(len);
        glGetProgramInfoLog(*this, len, nullptr, text.data());
        return text;
    }

    void link() const {
        glLinkProgram(*this);
    }

    GLint uniform(const char *name, bool soft = false) const {
        auto u = glGetUniformLocation(*this, name);
        if (u < 0 && !soft) {
            throw LookupError{"could not find uniform " + std::string{name}};
        }
        return u;
    }

    GLint attribute(const char *name, bool soft = false) const {
        auto a = glGetAttribLocation(*this, name);
        if (a < 0 && !soft) {
            throw LookupError{"could not find attribute " + std::string{name}};
        }
        return a;
    }

    void use() {
        glCall(glUseProgram(*this));
    }
};

inline Program createProgram(std::string_view vertexSrc,
                             std::string fragmentSrc) {
    auto vertexShader = loadShader(GL_VERTEX_SHADER, vertexSrc);
    auto fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSrc);

    auto program = Program{};
    program.attach(vertexShader);
    program.attach(fragmentShader);

    glCall(program.link());
    if (!program.iv(GL_LINK_STATUS)) {
        throw ProgramLinkError{"failed to link shader program:\n" +
                               program.infoLog()};
    }

    program.detach(vertexShader);
    program.detach(fragmentShader);

    return program;
}

} // namespace gl
