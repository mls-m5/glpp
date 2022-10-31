#pragma once

#include "GL/gl.h"

template <class T>
class VecT;

using Vec = VecT<double>;
using Vecf = VecT<float>;

namespace gl {

template <typename T>
GLenum type();

#ifdef GL_DOUBLE
template <>
constexpr inline GLenum type<double>() {
    return GL_DOUBLE;
}
#endif

template <>
constexpr inline GLenum type<float>() {
    return GL_FLOAT;
}

template <>
constexpr inline GLenum type<GLuint>() {
    return GL_UNSIGNED_INT;
}

template <>
constexpr inline GLenum type<GLint>() {
    return GL_INT;
}

template <>
constexpr inline GLenum type<GLubyte>() {
    return GL_UNSIGNED_BYTE;
}

template <>
constexpr inline GLenum type<GLbyte>() {
    return GL_BYTE;
}

#ifdef GL_DOUBLE
template <>
constexpr inline GLenum type<::Vec>() {
    return GL_DOUBLE;
}
#endif

template <>
constexpr inline GLenum type<::Vecf>() {
    return GL_FLOAT;
}

} // namespace gl
