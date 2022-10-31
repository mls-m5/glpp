#pragma once

#include "gl-backend.hpp"
#include "matgui/gl-error-handling.h"
#include "unique.hpp"
#include <GL/gl.h>
#include <GL/glext.h>

namespace gl {

namespace detail {
inline void destroyVertexArray(GLuint i) {
    glDeleteVertexArrays(1, &i);
}
} // namespace detail

class VertexArray : public detail::Unique<GLuint, detail::destroyVertexArray> {
public:
    VertexArray() {
        GLuint i;
        glCreateVertexArrays(1, &i);
        reset(i);
    }

    void bind() const {
        glCall(glBindVertexArray(*this));
    }

    static void unbind() {
        glBindVertexArray(0);
    }

    static void attribPointer(GLuint index,
                              GLint size,
                              GLenum type,
                              bool normalized,
                              GLsizei stride,
                              const void *pointer) {
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    }

    static void enableAttribArray(GLuint index) {
        glEnableVertexAttribArray(index);
    }
};

} // namespace gl
