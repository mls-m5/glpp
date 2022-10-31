#pragma once

#include "gl-backend.hpp"
#include "unique.hpp"
#include <GL/gl.h>
#include <GL/glext.h>

namespace detail {

inline void deleteBuffers(GLuint buffer) {
    glDeleteBuffers(1, &buffer);
}

} // namespace detail

class Buffer : gl::detail::Unique<GLuint, detail::deleteBuffers> {
public:
    // type could be for example GL_ARRAY_BUFFER
    Buffer(GLenum type) : type{type} {
        GLuint i;
        glGenBuffers(1, &i);
        reset(i);
    }

    void bind() const {
        glBindBuffer(type, *this);
    }

    void data(GLsizeiptr size,
              const void *data,
              GLenum usage = GL_STATIC_DRAW) const {
        glBufferData(type, size, data, usage);
    }

    GLenum type = 0;
};
