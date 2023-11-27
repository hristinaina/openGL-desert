#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>

#include "helper.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "sky.h"

#define CRES 300 
unsigned sunVAO, sunVBO;
unsigned moonVAO, moonVBO;
unsigned starsVAO, starsVBO;
unsigned starsTexture;

float r = 0.8;      //The radiuis of the circle along which the sun/moon moves
float rotationSpeed = 0.1;

float initialTime = glfwGetTime();
float xLast, yLast;

void createStars() {
    float vertices[] =
    {   //X    Y      S    T 
        -1.0, 0.0,   0.0, 0.0,  // bottom left
        1.0, 0.0,    1.0, 0.0,    // bottom right
        -1.0, 1.0,    0.0, 1.0,  // top left
         1.0, 1.0,    1.0, 1.0  // top right
    };

    unsigned int stride = (2 + 2) * sizeof(float);

    glGenVertexArrays(1, &starsVAO);
    glGenBuffers(1, &starsVBO);

    glBindVertexArray(starsVAO);
    glBindBuffer(GL_ARRAY_BUFFER, starsVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    //Texture
    starsTexture = loadImageToTexture("res/stars.png");
    glBindTexture(GL_TEXTURE_2D, starsTexture); //to set up the texture
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);   //GL_NEAREST, GL_LINEAR
    glBindTexture(GL_TEXTURE_2D, 0);

}

void createSun(float centerX, float centerY, float width, float height) {
    float circle[2 * CRES + 4];

    // Add the center vertex
    circle[0] = centerX;
    circle[1] = centerY;

    for (int i = 0; i <= CRES; i++) {
        circle[2 * i + 2] = centerX + cos((3.141592 / 180) * (i * 360 / CRES)) * width;  // Xi
        circle[2 * i + 3] = centerY + sin((3.141592 / 180) * (i * 360 / CRES)) * height; // Yi
    }

    glGenVertexArrays(1, &sunVAO);
    glGenBuffers(1, &sunVBO);

    glBindVertexArray(sunVAO);

    glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circle), circle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void createMoon(float centerX, float centerY, float width, float height) {
    float circle[2 * CRES + 4];

    // Add the center vertex
    circle[0] = centerX;
    circle[1] = centerY;

    for (int i = 0; i <= CRES; i++) {
        circle[2 * i + 2] = centerX + cos((3.141592 / 180) * (i * 360 / CRES)) * width;  // Xi
        circle[2 * i + 3] = centerY + sin((3.141592 / 180) * (i * 360 / CRES)) * height; // Yi
    }

    glGenVertexArrays(1, &moonVAO);
    glGenBuffers(1, &moonVBO);

    glBindVertexArray(moonVAO);

    glBindBuffer(GL_ARRAY_BUFFER, moonVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circle), circle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void renderStars(unsigned int shaderProgram) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(shaderProgram);
    float pos = glGetUniformLocation(shaderProgram, "position");
    glBindVertexArray(starsVAO);

    glUniform1f(pos, 0);
    glBindTexture(GL_TEXTURE_2D, starsTexture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);

    glUseProgram(0);
    glDisable(GL_BLEND);
}

void updateVariables(float paused, float restared) {
    float ydelta = r * (sin((glfwGetTime() - initialTime) * rotationSpeed));
    float xdelta = r * (cos((glfwGetTime() - initialTime) * rotationSpeed));
    if (!paused) {
        xLast = xdelta;
        yLast = ydelta;
    }
    if (restared) {
        initialTime = glfwGetTime();
    }
}

void renderSun(unsigned int shaderProgram, float paused, float restared) {
    glUseProgram(shaderProgram);
    int color = glGetUniformLocation(shaderProgram, "color");
    unsigned int uPosLoc = glGetUniformLocation(shaderProgram, "uPos");

    glBindVertexArray(sunVAO);

    glUniform4f(color, 1.0, 0.996, 0.71, 1.0);
    updateVariables(paused, restared);
    glUniform2f(uPosLoc, xLast , yLast);
    glDrawArrays(GL_TRIANGLE_FAN, 0, CRES + 2);
    glClearColor(0.361 + yLast/2, 0.655 + yLast/2, 0.8 + yLast/2, 1.0);

    glBindVertexArray(0);

    glUseProgram(0);
}

void renderMoon(unsigned int shaderProgram) {
    glUseProgram(shaderProgram);
    int color = glGetUniformLocation(shaderProgram, "color");
    unsigned int uPosLoc = glGetUniformLocation(shaderProgram, "uPos");

    glBindVertexArray(moonVAO);

    glUniform4f(color, 0.929, 0.929, 0.929, 1.0);
    glUniform2f(uPosLoc, - xLast, - yLast);
    glDrawArrays(GL_TRIANGLE_FAN, (CRES + 2) / 4, (CRES + 2)/2);

    glBindVertexArray(0);

    glUseProgram(0);
}

void DeleteSkyVariables() {
    glDeleteBuffers(1, &sunVBO);
    glDeleteVertexArrays(1, &sunVAO);
    glDeleteBuffers(1, &moonVBO);
    glDeleteVertexArrays(1, &moonVAO);
    glDeleteBuffers(1, &starsVBO);
    glDeleteVertexArrays(1, &starsVAO);
    glDeleteTextures(1, &starsTexture);
}
