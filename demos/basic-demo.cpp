#include "glm/ext/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "glpp/buffer.hpp"
#include "glpp/program.hpp"
#include "glpp/vertexarray.hpp"
#include "matgui/application.h"
#include "matgui/main.h"
#include "matgui/window.h"
#include <GL/gl.h>
#include <array>
#include <glm/gtc/type_ptr.hpp>

namespace {

const auto vertexSrc = R"_(
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 mvp;

out vec4 vColor; // specify a color output to the fragment shader

void main()
{
    gl_Position = mvp * vec4(aPos, 1.0);
    vColor = vec4(0.5, 0.4, 0.0, 1.0);
}
)_";

const auto fragmentSrc = R"_(
#version 330 core
out vec4 fColor;

in vec4 vColor;

void main()
{
    fColor = vColor;
}
)_";

using namespace matgui;
using namespace gl;
using namespace glm;

struct MainWindow : public Window {
    Program program = gl::createProgram(vertexSrc, fragmentSrc);
    std::array<float, 9> vertices = {
        // clang-format off
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        // clang-format on
    };

    VertexArray vao;
    Buffer vbo{GL_ARRAY_BUFFER};

    int mvpPointer = program.uniform("mvp");

    mat4 mvp = identity<mat4>();

    float time = 0;

    MainWindow(int argc, char **argv) : Window("glpp", 800, 600, true) {
        vao.bind();
        vbo.bind();

        vbo.data(sizeof(vertices), vertices.data());
        vao.attribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void *)0);
        vao.enableAttribArray(0);

        Application::ContinuousUpdates(true);
    }

    void draw() override {
        Window::draw();

        time += .01;

        mvp = rotate(identity<mat4>(), time, {0, 0, 1});

        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();

        glUniformMatrix4fv(mvpPointer, 1, false, value_ptr(mvp));

        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};

} // namespace

MATGUI_MAIN(MainWindow);
