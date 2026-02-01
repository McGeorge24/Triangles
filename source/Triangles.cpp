#include <glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include "shaders.h"
//#include <khrplatform.h>

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static void GLCheckError()
{
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL: ERROR] " << error << std::endl;
    }
}



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "FlekiDorf", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    float positions[8] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };

    unsigned int indeces[6] = {
        0, 1, 2,
        2, 3, 0
    };
 
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, 2*sizeof(float), 0);
    
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indeces, GL_STATIC_DRAW);



    std::string vertexShader;
    ParseShader("resources/shaders/vertex.shader", vertexShader);

    std::string fragmentShader;
    ParseShader("resources/shaders/fragment.shader", fragmentShader);

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader, "u_Color");
    if (location == -1)
        std::cout << "Failed to locate u_Color";
    glUniform4f(location, 0.4f, 0.1f, 0.8f, 1.0f);
    
    float red = 0.11f, green = 0.34f, blue = 0.68f, red_change = 0.01f, blue_change = 0.01f, green_change = 0.01f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        GLCheckError();


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        red += red_change; if ((red >= 0.9f) || (red <=0.1f)) red_change *= -1;
        green += green_change; if ((green >= 0.9f) || (blue <= 0.1f)) green_change *= -1;
        blue += blue_change; if ((blue >= 0.9f) || (blue <= 0.1f)) blue_change *= -1;
        glUniform4f(location, red, green, blue, 1.0f);
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   2. Use the Team Explorer window to connect to source control