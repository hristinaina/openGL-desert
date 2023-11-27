#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "sky.h"

#define CRES 300 
unsigned sunVAO, sunVBO;

float r = 0.8;      //Poluprecnik kruznice po kojoj se trougao krece, mora biti manji od najmanje apsolutne vrednosti y koordinate temena
float rotationSpeed = 0.1;


void createSun(float centerX, float centerY, float width, float height) {
    float circle[2 * CRES + 4];

    // Add the center vertex
    circle[0] = centerX;
    circle[1] = centerY;

    for (int i = 0; i <= CRES; i++) {
        circle[2 * i + 2] = centerX + cos((3.141592 / 180) * (i * 360 / CRES)) * width;  // Xi
        circle[2 * i + 3] = centerY + sin((3.141592 / 180) * (i * 360 / CRES)) * height; // Yi
    }

    // Create Vertex Array Object and Vertex Buffer Object
    glGenVertexArrays(1, &sunVAO);
    glGenBuffers(1, &sunVBO);

    // Bind the Vertex Array Object
    glBindVertexArray(sunVAO);

    // Bind and initialize the Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circle), circle, GL_STATIC_DRAW);

    // Set attribute pointers
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void renderSun(unsigned int shaderProgram) {
    glUseProgram(shaderProgram);
    int color = glGetUniformLocation(shaderProgram, "color");
    unsigned int uPosLoc = glGetUniformLocation(shaderProgram, "uPos");

    glBindVertexArray(sunVAO);

    glUniform4f(color, 1.0, 0.996, 0.71, 1.0);
    float delta = r * (sin(glfwGetTime() * rotationSpeed));
    glUniform2f(uPosLoc, r * cos(glfwGetTime() * rotationSpeed), delta);
    glDrawArrays(GL_TRIANGLE_FAN, 0, CRES + 2);
    glClearColor(0.361 + delta/2, 0.655 + delta/2, 0.8 + delta/2, 1.0);

    glBindVertexArray(0);

    glUseProgram(0);
}