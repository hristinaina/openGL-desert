
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
unsigned smallPyramidsVAO, smallPyramidsVBO;
unsigned bigPyramidVAO, bigPyramidVBO;

float bigPyramidColor = 0.737;  //sets the green color value. Lesser the value, stronger the red color
float colorSpeedChange = 0.005;

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
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    window = glfwCreateWindow(mode->width, mode->height, "Desert", monitor, NULL);
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

void createSmallPyramids() {
    float pyramidVertices[] = {
    -0.96, -0.3,
    -0.56, -0.3,
    -0.76, 0.3,
    0.6, -0.15,
    0.9, -0.15,
    0.75, 0.25,
    };

    // Create Vertex Array Object and Vertex Buffer Object
    glGenVertexArrays(1, &smallPyramidsVAO);
    glGenBuffers(1, &smallPyramidsVBO);

    // Bind the Vertex Array Object
    glBindVertexArray(smallPyramidsVAO);

    // Bind and initialize the Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, smallPyramidsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertices), pyramidVertices, GL_STATIC_DRAW);

    // Set attribute pointers
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void createBigPyramid() {
    float pyramidVertices[] = {
    -0.3, 0.0,
    0.3, -0.0,
    0.0, 0.6,
    };

    // Create Vertex Array Object and Vertex Buffer Object
    glGenVertexArrays(1, &bigPyramidVAO);
    glGenBuffers(1, &bigPyramidVBO);

    // Bind the Vertex Array Object
    glBindVertexArray(bigPyramidVAO);

    // Bind and initialize the Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, bigPyramidVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertices), pyramidVertices, GL_STATIC_DRAW);

    // Set attribute pointers
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void renderSmallPyramids(unsigned int shaderProgram) {
    // Use the same shader program for the desert
    glUseProgram(shaderProgram);
    int color = glGetUniformLocation(shaderProgram, "color");

    // Bind the Vertex Array Object
    glBindVertexArray(smallPyramidsVAO);

    // Draw the desert
    glUniform3f(color, 0.85, 0.737, 0.204);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Unbind VAO
    glBindVertexArray(0);

    // Unuse the shader program
    glUseProgram(0);
}

void renderBigPyramid(unsigned int shaderProgram, float bigPyramidColor) {
    // Use the same shader program for the desert
    glUseProgram(shaderProgram);
    int color = glGetUniformLocation(shaderProgram, "color");

    // Bind the Vertex Array Object
    glBindVertexArray(bigPyramidVAO);

    // Draw the desert
    glUniform3f(color, 0.85, bigPyramidColor, 0.204);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Unbind VAO
    glBindVertexArray(0);

    // Unuse the shader program
    glUseProgram(0);
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
    glUniform3f(color, 0.988, 0.875, 0.416);
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
    createSmallPyramids();
    createBigPyramid();
    //todo add other create functions here...

    unsigned int basicShader = createShader("basic.vert", "basic.frag");
    glClearColor(0.671, 0.882, 1.0, 1.0);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            if (bigPyramidColor + colorSpeedChange >= 0.0)
                bigPyramidColor -= colorSpeedChange;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            if (bigPyramidColor + colorSpeedChange <= 0.737)
                bigPyramidColor += colorSpeedChange;
        }

        renderDesert(basicShader);
        renderSmallPyramids(basicShader);
        renderBigPyramid(basicShader, bigPyramidColor);
        //todo render what you have created

        glfwSwapBuffers(window);
    }


    //todo delete and deallcoate memory
    glDeleteBuffers(1, &desertVBO);
    glDeleteVertexArrays(1, &desertVAO);
    glDeleteProgram(basicShader);

    glfwTerminate();
    return 0;
}