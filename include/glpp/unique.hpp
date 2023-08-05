#pragma once

#include <memory>

namespace gl {
namespace detail {

template <typename T, void (*DestroyFunction)(T)>
class Unique {
public:
    Unique() = default;
    Unique(const Unique &) = delete;
    Unique &operator=(const Unique &) = delete;

    Unique(Unique &&other) {
        reset(other._p);
        other._p = {};
    }

    Unique &operator=(Unique &&other) {
        reset(other._p);
        other._p = {};
        return *this;
    }

    Unique &operator=(T value) {
        reset(value);
        return *this;
    }

    Unique(T value) : _p{value} {
    }

    ~Unique() {
        clear();
    }

    void clear() {
        if (_p) {
            DestroyFunction(_p);
        }
    }

    void reset(T value = {}) {
        if (_p) {
            DestroyFunction(_p);
        }
        _p = value;
    }

    T get() const {
        return _p;
    }

    operator T() const {
        return get();
    }

private:
    T _p;
};

} // namespace detail
} // namespace gl
