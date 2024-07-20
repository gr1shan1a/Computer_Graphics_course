#include <stdio.h>

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <GL/gl.h>

GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f
};

GLuint indices[] = {
        0, 1, 2, 3,  // Front face
        4, 5, 6, 7,  // Back face
        0, 4, 5, 1,  // Left face
        3, 7, 6, 2,  // Right face
        0, 3, 7, 4,  // Bottom face
        1, 2, 6, 5   // Top face
};

GLfloat scale = 1.0f;
GLfloat rotateX = 0.0f;
GLfloat rotateY = 0.0f;
GLfloat translateX = 0.0f;
GLfloat translateY = 0.0f;
GLfloat translateZ = 0.0f;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_W:
                translateZ -= 0.1f;
                break;
            case GLFW_KEY_S:
                translateZ += 0.1f;
                break;
            case GLFW_KEY_A:
                translateX -= 0.1f;
                break;
            case GLFW_KEY_D:
                translateX += 0.1f;
                break;
            case GLFW_KEY_R:
                scale += 0.1f;
                break;
            case GLFW_KEY_F:
                scale -= 0.1f;
                if (scale < 0.1f) scale = 0.1f;
                break;
            case GLFW_KEY_UP:
                rotateX += 0.1f;
                break;
            case GLFW_KEY_DOWN:
                rotateX -= 0.1f;
                break;
            case GLFW_KEY_LEFT:
                rotateY += 0.1f;
                break;
            case GLFW_KEY_RIGHT:
                rotateY -= 0.1f;
                break;
        }
    }
}

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Interactive 3D Model Control", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, 800, 600);

    glfwSetKeyCallback(window, keyCallback);

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(translateX, translateY, translateZ);
        glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
        glScalef(scale, scale, scale);

        glBindVertexArray(VAO);
        glDrawElements(GL_LINE_LOOP, 24, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();

    return 0;
}
