#pragma once

#include <stdexcept>
#include <string>

namespace gl {

struct ShaderCompilationError : std::runtime_error {
    ShaderCompilationError(const std::string &what) : runtime_error{what} {
    }
};

struct ProgramLinkError : std::runtime_error {
    ProgramLinkError(const std::string &what) : runtime_error{what} {
    }
};

struct ContextError : std::runtime_error {
    ContextError(const std::string &what) : runtime_error{what} {
    }
};

struct LookupError : std::runtime_error {
    LookupError(const std::string &what) : runtime_error{what} {
    }
};

} // namespace gl
