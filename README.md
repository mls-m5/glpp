# glpp

A attempt to encapsulate everything that's anoying with opengl behind something
that is less anoying.

## Convention

Everything that is just calling opengl functions should be put inside the value
classes (for example shader and program). Everything that does something extra
should be put in a free function (like create shaders and error handling)
