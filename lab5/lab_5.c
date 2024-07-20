#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

float a = 1;
float scale = 1.0f;
float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 0.0f;
float posX = 0.0f;
float posY = 0.0f;
float posZ = 0.0f;

struct Vector {
    float x;
    float y;
    float z;
};

struct Vector vector(float x, float y, float z) {
    struct Vector result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

void drawFace(struct Vector v1, struct Vector v2, struct Vector v3, float r, float g, float b) {
    glBegin(GL_TRIANGLES);
    glColor3f(r, g, b);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glEnd();
}

void scaleVertex(struct Vector *vertex, float scale) {
    vertex->x *= scale;
    vertex->y *= scale;
    vertex->z *= scale;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    float delta = 0.05f;
    float scaleDelta = 0.001f; // Added scaleDelta

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_W:
                posY += delta;
                break;
            case GLFW_KEY_S:
                posY -= delta;
                break;
            case GLFW_KEY_A:
                posX -= delta;
                break;
            case GLFW_KEY_D:
                posX += delta;
                break;
            case GLFW_KEY_Q:
                angleZ += 3.0f;
                break;
            case GLFW_KEY_E:
                angleZ -= 3.0f;
                break;
            case GLFW_KEY_R:
                angleX += 3.0f;
                break;
            case GLFW_KEY_F:
                angleX -= 3.0f;
                break;
            case GLFW_KEY_T:
                angleY += 3.0f;
                break;
            case GLFW_KEY_G:
                angleY -= 3.0f;
                break;
            case GLFW_KEY_UP:
                scale += scaleDelta;
                break;
            case GLFW_KEY_DOWN:
                scale -= scaleDelta;
                break;
        }
    }
}

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Tetrahedron", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    struct Vector v[] = {
            vector(0, 0, a * sqrt(6) / 4),
            vector(a / sqrt(3), 0, -a * sqrt(6) / 12),
            vector(-a / sqrt(12), a / 2, -a * sqrt(6) / 12),
            vector(-a / sqrt(12), -a / 2, -a * sqrt(6) / 12)
    };

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2); // Adjust the perspective

    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE); // Enable backface culling

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();

        glTranslatef(posX, posY, posZ);
        glRotatef(angleX, 1.0f, 0.0f, 0.0f);
        glRotatef(angleY, 0.0f, 1.0f, 0.0f);
        glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
        glRotatef(angleX, 0.5f, 0.5f, 0.5f);

        if (posZ >= 0) drawFace(v[0], v[1], v[2], 0.0f, 0.0f, 0.5f); // Dark blue
        if (posZ <= 0) drawFace(v[0], v[1], v[3], 0.0f, 0.5f, 0.0f); // Dark green
        if (posY >= 0) drawFace(v[0], v[2], v[3], 1.0f, 0.4f, 0.2f); // Orange
        if (posY <= 0) drawFace(v[1], v[2], v[3], 1.0f, 0.0f, 0.0f); // Red

        glColor3f(0.0f, 0.0f, 0.0f);




        for (int i = 0; i < 4; i++) {
            scaleVertex(&v[i], scale); // Apply scaling to each vertex
        }

        glBegin(GL_LINE_LOOP);
        glVertex3f(v[0].x, v[0].y, v[0].z);
        glVertex3f(v[1].x, v[1].y, v[1].z);
        glVertex3f(v[2].x, v[2].y, v[2].z);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex3f(v[0].x, v[0].y, v[0].z);
        glVertex3f(v[3].x, v[3].y, v[3].z);
        glVertex3f(v[1].x, v[1].y, v[1].z);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex3f(v[0].x, v[0].y, v[0].z);
        glVertex3f(v[2].x, v[2].y, v[2].z);
        glVertex3f(v[3].x, v[3].y, v[3].z);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex3f(v[1].x, v[1].y, v[1].z);
        glVertex3f(v[3].x, v[3].y, v[3].z);
        glVertex3f(v[2].x, v[2].y, v[2].z);
        glEnd();

        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
