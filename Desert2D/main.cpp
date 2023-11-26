
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "helper.h"


unsigned desertVAO, desertVBO;

GLFWwindow* initWindow() {
    if (!glfwInit())
    {
        std::cout << "GLFW Biblioteka se nije ucitala! :(\n";
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    unsigned int wWidth = 800;
    unsigned int wHeight = 800;
    const char wTitle[] = "Pustinja";
    window = glfwCreateWindow(wWidth, wHeight, wTitle, NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Prozor nije napravljen! :(\n";
        glfwTerminate();
        exit(2);
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW nije mogao da se ucita! :'(\n";
        exit(3);
    }

    return window;
}


void createDesert() {
    // todo add vertices, VAO and VBO
    // Desert vertices
    float desertVertices[] = {
        -1.0, 0.0,
         1.0, 0.0,
        -1.0, -1.0,
         1.0, -1.0
    };

    // Create Vertex Array Object and Vertex Buffer Object
    glGenVertexArrays(1, &desertVAO);
    glGenBuffers(1, &desertVBO);

    // Bind the Vertex Array Object
    glBindVertexArray(desertVAO);

    // Bind and initialize the Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, desertVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(desertVertices), desertVertices, GL_STATIC_DRAW);

    // Set attribute pointers
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// here goes the logic for the loop
void renderDesert(unsigned int shaderProgram) {
     // Use the same shader program for the desert
    glUseProgram(shaderProgram);
    int color = glGetUniformLocation(shaderProgram, "color");

    // Bind the Vertex Array Object
    glBindVertexArray(desertVAO);

    // Draw the desert
    glUniform3f(color, 0.949, 0.733, 0.4);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // Unbind VAO
    glBindVertexArray(0);

    // Unuse the shader program
    glUseProgram(0);
}


int main(void)
{
    GLFWwindow* window = initWindow();
    
    createDesert();
    //todo add other create functions here...

    unsigned int basicShader = createShader("basic.vert", "basic.frag");
    glClearColor(0.506, 0.922, 1.0, 1.0);

    while (!glfwWindowShouldClose(window))
    {
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        
        glClear(GL_COLOR_BUFFER_BIT);

        renderDesert(basicShader);
        //todo render what you have created

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    //todo delete and deallcoate memory
    glDeleteBuffers(1, &desertVBO);
    glDeleteVertexArrays(1, &desertVAO);
    glDeleteProgram(basicShader);

    glfwTerminate();
    return 0;
}