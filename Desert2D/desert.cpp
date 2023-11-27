#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "desert.h"
#include "helper.h"


unsigned desertVAO, desertVBO;
unsigned smallPyramidsVAO, smallPyramidsVBO;
unsigned bigPyramidVAO, bigPyramidVBO;
unsigned signatureVAO, signatureVBO;
unsigned signatureTexture;

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

void createSignature() {
    float vertices[] =
    {   //X    Y      S    T 
        -0.97, -1.0,   0.0, 0.0,  // bottom left
        -0.55, -1.0,    1.0, 0.0,    // bottom right
        -0.97, -0.95,    0.0, 1.0,  // top left
         -0.55, -0.95,    1.0, 1.0  // top right
    };

    unsigned int stride = (2 + 2) * sizeof(float);

    glGenVertexArrays(1, &signatureVAO);
    glGenBuffers(1, &signatureVBO);

    glBindVertexArray(signatureVAO);
    glBindBuffer(GL_ARRAY_BUFFER, signatureVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    //Texture
    signatureTexture = loadImageToTexture("res/signature.png");
    glBindTexture(GL_TEXTURE_2D, signatureTexture); //to set up the texture
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);   //GL_NEAREST, GL_LINEAR
    glBindTexture(GL_TEXTURE_2D, 0);
}

void createSmallPyramids() {
    float pyramidVertices[] = {
    -0.96, -0.2,
    -0.56, -0.2,
    -0.76, 0.3,
    0.6, -0.12,
    0.9, -0.12,
    0.75, 0.28,
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

// here goes the logic for the loop
void renderDesert(unsigned int shaderProgram) {
    // Use the same shader program for the desert
    glUseProgram(shaderProgram);
    int color = glGetUniformLocation(shaderProgram, "color");

    // Bind the Vertex Array Object
    glBindVertexArray(desertVAO);

    // Draw the desert
    glUniform4f(color, 0.988, 0.875, 0.416, 1.0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // Unbind VAO
    glBindVertexArray(0);

    // Unuse the shader program
    glUseProgram(0);
}

void renderSignature(unsigned int shaderProgram) {

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(shaderProgram);
    float pos = glGetUniformLocation(shaderProgram, "position");
    float alpha = glGetUniformLocation(shaderProgram, "alphaCh");
    glBindVertexArray(signatureVAO);

    glUniform1f(pos, 0);
    glUniform1f(alpha, 1.0);
    glBindTexture(GL_TEXTURE_2D, signatureTexture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);

    glUseProgram(0);
    glDisable(GL_BLEND);
}

void renderSmallPyramids(unsigned int shaderProgram) {
    // Use the same shader program for the desert
    glUseProgram(shaderProgram);
    int color = glGetUniformLocation(shaderProgram, "color");

    // Bind the Vertex Array Object
    glBindVertexArray(smallPyramidsVAO);

    // Draw the desert
    glUniform4f(color, 0.85, 0.737, 0.204, 1.0);
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
    glUniform4f(color, 0.85, bigPyramidColor, 0.204, 1.0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Unbind VAO
    glBindVertexArray(0);

    // Unuse the shader program
    glUseProgram(0);
}

void DeleteDesertVariables() {
    glDeleteBuffers(1, &desertVBO);
    glDeleteVertexArrays(1, &desertVAO);
    glDeleteBuffers(1, &smallPyramidsVBO);
    glDeleteVertexArrays(1, &smallPyramidsVAO);
    glDeleteBuffers(1, &bigPyramidVBO);
    glDeleteVertexArrays(1, &bigPyramidVAO);
    glDeleteBuffers(1, &signatureVBO);
    glDeleteVertexArrays(1, &signatureVAO);
    glDeleteTextures(1, &signatureTexture);
}
