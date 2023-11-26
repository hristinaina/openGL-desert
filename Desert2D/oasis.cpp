#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "oasis.h"


unsigned int waterVAO, waterVBO;
#define CRES 300 


void createWater(float width, float height) {
    float centerX = 0.0;
    float centerY = -0.6;
    glGenVertexArrays(1, &waterVAO);
    glGenBuffers(1, &waterVBO);

    float circle[2 * CRES + 4];

    // Add the center vertex
    circle[0] = centerX;
    circle[1] = centerY;

    for (int i = 0; i <= CRES; i++) {
        circle[2 * i + 2] = centerX + cos((3.141592 / 180) * (i * 360 / CRES)) * width;  // Xi
        circle[2 * i + 3] = centerY + sin((3.141592 / 180) * (i * 360 / CRES)) * height; // Yi
    }

    glBindVertexArray(waterVAO);
    glBindBuffer(GL_ARRAY_BUFFER, waterVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circle), circle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void renderWater(unsigned int shaderProgram) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(shaderProgram);
    int color = glGetUniformLocation(shaderProgram, "color");

    // Bind the Vertex Array Object
    glBindVertexArray(waterVAO);

    // Draw the desert
    glUniform4f(color, 0.365, 0.616, 0.871, 0.8);
    glDrawArrays(GL_TRIANGLE_FAN, 0, CRES + 2);

    // Unbind VAO
    glBindVertexArray(0);

    // Unuse the shader program
    glUseProgram(0);
    glDisable(GL_BLEND);
}