#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shaderProgram.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLFirstTest", NULL, NULL);

    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        std::cout <<  "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    ShaderProgram sp("../shader_source/vshader4.vs", "../shader_source/fshader4.fs");

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f,
    };

    float vertices2[] = {
            // Position         // Color
            -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,
             0.0f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*) 0);
    glEnableVertexAttribArray(0);

    /* specify each vertices' color
    // Position attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*) 0);
    glEnableVertexAttribArray(0);
    // Color attribute pointer
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*) (3*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);
     */

    glBindBuffer(GL_ARRAY_BUFFER, 0); // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        // render
        glClearColor(0.4f, 0.4f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        sp.use();
        // set color
        double timeValue = glfwGetTime();
        float redValue = (float)(sin(timeValue) / 2.0f) + 0.5f;
        sp.set4Float("ourColor", redValue, 0.0f, 0.0f, 1.0f);
        // set position offset
        float move = float(sin(timeValue/2) / 3.0f);
        sp.set2Float("ourOffset", move, move);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    glfwTerminate();

    return 0;
}