#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const char* vertexShaderSource = R"glsl(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 vColor;

uniform mat4 uMVP;

void main() {
    vColor = aColor;
    gl_Position = uMVP * vec4(aPos, 1.0);
}
)glsl";

static const char* fragmentShaderSource = R"glsl(
#version 330 core
in vec3 vColor;
out vec4 FragColor;
void main() {
    FragColor = vec4(vColor, 1.0);
}
)glsl";

static GLuint compileShader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    GLint ok; glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint len; glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> buf(len);
        glGetShaderInfoLog(shader, len, nullptr, buf.data());
        std::cerr << "Shader compile error: " << buf.data() << std::endl;
    }
    return shader;
}

static GLuint linkProgram(GLuint vs, GLuint fs) {
    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);
    GLint ok; glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint len; glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> buf(len);
        glGetProgramInfoLog(prog, len, nullptr, buf.data());
        std::cerr << "Program link error: " << buf.data() << std::endl;
    }
    return prog;
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Starter - Spinning Cube", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    GLuint vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    GLuint shader = linkProgram(vs, fs);
    glDeleteShader(vs); glDeleteShader(fs);

    float vertices[] = {
        // positions         // colors
        -0.5f, -0.5f, -0.5f,  0.8f, 0.1f, 0.1f,
         0.5f, -0.5f, -0.5f,  0.8f, 0.1f, 0.1f,
         0.5f,  0.5f, -0.5f,  0.8f, 0.1f, 0.1f,
         0.5f,  0.5f, -0.5f,  0.8f, 0.1f, 0.1f,
        -0.5f,  0.5f, -0.5f,  0.8f, 0.1f, 0.1f,
        -0.5f, -0.5f, -0.5f,  0.8f, 0.1f, 0.1f,

        -0.5f, -0.5f,  0.5f,  0.1f, 0.8f, 0.1f,
         0.5f, -0.5f,  0.5f,  0.1f, 0.8f, 0.1f,
         0.5f,  0.5f,  0.5f,  0.1f, 0.8f, 0.1f,
         0.5f,  0.5f,  0.5f,  0.1f, 0.8f, 0.1f,
        -0.5f,  0.5f,  0.5f,  0.1f, 0.8f, 0.1f,
        -0.5f, -0.5f,  0.5f,  0.1f, 0.8f, 0.1f,

        -0.5f,  0.5f,  0.5f,  0.1f, 0.1f, 0.8f,
        -0.5f,  0.5f, -0.5f,  0.1f, 0.1f, 0.8f,
        -0.5f, -0.5f, -0.5f,  0.1f, 0.1f, 0.8f,
        -0.5f, -0.5f, -0.5f,  0.1f, 0.1f, 0.8f,
        -0.5f, -0.5f,  0.5f,  0.1f, 0.1f, 0.8f,
        -0.5f,  0.5f,  0.5f,  0.1f, 0.1f, 0.8f,

         0.5f,  0.5f,  0.5f,  0.8f, 0.8f, 0.1f,
         0.5f,  0.5f, -0.5f,  0.8f, 0.8f, 0.1f,
         0.5f, -0.5f, -0.5f,  0.8f, 0.8f, 0.1f,
         0.5f, -0.5f, -0.5f,  0.8f, 0.8f, 0.1f,
         0.5f, -0.5f,  0.5f,  0.8f, 0.8f, 0.1f,
         0.5f,  0.5f,  0.5f,  0.8f, 0.8f, 0.1f,

        -0.5f, -0.5f, -0.5f,  0.1f, 0.8f, 0.8f,
         0.5f, -0.5f, -0.5f,  0.1f, 0.8f, 0.8f,
         0.5f, -0.5f,  0.5f,  0.1f, 0.8f, 0.8f,
         0.5f, -0.5f,  0.5f,  0.1f, 0.8f, 0.8f,
        -0.5f, -0.5f,  0.5f,  0.1f, 0.8f, 0.8f,
        -0.5f, -0.5f, -0.5f,  0.1f, 0.8f, 0.8f,

        -0.5f,  0.5f, -0.5f,  0.8f, 0.1f, 0.8f,
         0.5f,  0.5f, -0.5f,  0.8f, 0.1f, 0.8f,
         0.5f,  0.5f,  0.5f,  0.8f, 0.1f, 0.8f,
         0.5f,  0.5f,  0.5f,  0.8f, 0.1f, 0.8f,
        -0.5f,  0.5f,  0.5f,  0.8f, 0.1f, 0.8f,
        -0.5f,  0.5f, -0.5f,  0.8f, 0.1f, 0.8f
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window)) {
        float width, height;
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        width = (float)w; height = (float)h;
        glViewport(0, 0, w, h);

        glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);

        glm::mat4 proj = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 model = glm::mat4(1.0f);
        float t = (float)glfwGetTime();
        model = glm::rotate(model, t * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        glm::mat4 mvp = proj * view * model;
        GLuint loc = glGetUniformLocation(shader, "uMVP");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mvp));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
