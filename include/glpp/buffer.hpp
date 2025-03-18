#pragma once

#include "gl-backend.hpp"
#include "unique.hpp"
#include <GL/gl.h>
#include <GL/glext.h>

namespace gl {

namespace detail {

inline void deleteBuffers(GLuint buffer) {
    glDeleteBuffers(1, &buffer);
}

} // namespace detail

class Buffer : public gl::detail::Unique<GLuint, detail::deleteBuffers> {
public:
    // type could be for example GL_ARRAY_BUFFER
    Buffer(GLenum type) : type{type} {
        auto i = GLuint{};
        glGenBuffers(1, &i);
        reset(i);
    }

    void bind() const {
        glBindBuffer(type, *this);
    }

    void unbind() const {
        glBindBuffer(type, 0);
    }

    void data(GLsizeiptr size,
              const void *data,
              GLenum usage = GL_STATIC_DRAW) const {
        glBufferData(type, size, data, usage);
    }

    GLenum type = 0;
};

} // namespace gl
