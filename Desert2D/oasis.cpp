#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>

#include "helper.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "oasis.h"


unsigned int waterVAO, waterVBO;
unsigned int grassVAO, grassVBO;
unsigned int fishVAO, fishVBO;
unsigned grassTexture;
unsigned fishTexture;
#define CRES 300 
float fishX = 0.0f;  // Initial X position of the fish
float speed = 0.2f;  // Speed of the fish movement

void createGrass() {

    float vertices[] =
    {   //X    Y      S    T 
        -0.45, -0.8,   0.0, 0.0,  // bottom left
        0.45, -0.8,    1.0, 0.0,    // bottom right
        -0.45, -0.4,    0.0, 1.0,  // top left
         0.45, -0.4,    1.0, 1.0  // top right
    };

    unsigned int stride = (2 + 2) * sizeof(float);

    glGenVertexArrays(1, &grassVAO);
    glGenBuffers(1, &grassVBO);

    glBindVertexArray(grassVAO);
    glBindBuffer(GL_ARRAY_BUFFER, grassVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    //Texture
    grassTexture = loadImageToTexture("res/grass_texture.png"); 
    glBindTexture(GL_TEXTURE_2D, grassTexture); //to set up the texture
    glGenerateMipmap(GL_TEXTURE_2D); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);   //GL_NEAREST, GL_LINEAR
    glBindTexture(GL_TEXTURE_2D, 0);

}


void createFish() {

    float vertices[] =
    {   //X    Y      S    T 
        -0.1, -0.7,   0.0, 0.0,  // bottom left
        0.1, -0.7,    1.0, 0.0,    // bottom right
        -0.1, -0.5,    0.0, 1.0,  // top left
        0.1, -0.5,    1.0, 1.0  // top right
    };

    unsigned int stride = (2 + 2) * sizeof(float);

    glGenVertexArrays(1, &fishVAO);
    glGenBuffers(1, &fishVBO);

    glBindVertexArray(fishVAO);
    glBindBuffer(GL_ARRAY_BUFFER, fishVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    //Texture
    fishTexture = loadImageToTexture("res/fish.png");
    glBindTexture(GL_TEXTURE_2D, fishTexture); //to set up the texture
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);   //GL_NEAREST, GL_LINEAR
    glBindTexture(GL_TEXTURE_2D, 0);

}

void createWater(float width, float height) {
    float centerX = 0.0;
    float centerY = -0.6;

    float circle[2 * CRES + 4];

    // Add the center vertex
    circle[0] = centerX;
    circle[1] = centerY;

    for (int i = 0; i <= CRES; i++) {
        circle[2 * i + 2] = centerX + cos((3.141592 / 180) * (i * 360 / CRES)) * width;  // Xi
        circle[2 * i + 3] = centerY + sin((3.141592 / 180) * (i * 360 / CRES)) * height; // Yi
    }

    glGenVertexArrays(1, &waterVAO);
    glGenBuffers(1, &waterVBO);

    glBindVertexArray(waterVAO);
    glBindBuffer(GL_ARRAY_BUFFER, waterVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circle), circle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void renderGrass(unsigned int shaderProgram) {

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(shaderProgram);
    float pos = glGetUniformLocation(shaderProgram, "position");
    glBindVertexArray(grassVAO);

    glUniform1f(pos, 0);
    glBindTexture(GL_TEXTURE_2D, grassTexture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);

    glUseProgram(0);
    glDisable(GL_BLEND);
}

//todo dodati uniformu za promjenu lokacije
void renderFish(unsigned int shaderProgram) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    fishX = sin(glfwGetTime() * speed) / 4;  //dozovliti da ide od 0 do 0.3 pa onda obrunto

    glUseProgram(shaderProgram);
    float pos = glGetUniformLocation(shaderProgram, "position");
    glBindVertexArray(fishVAO);

    glUniform1f(pos, fishX);
    glBindTexture(GL_TEXTURE_2D, fishTexture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);

    glUseProgram(0);
    glDisable(GL_BLEND);
}

void renderWater(unsigned int shaderProgram) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(shaderProgram);
    int color = glGetUniformLocation(shaderProgram, "color");

    // Bind the Vertex Array Object
    glBindVertexArray(waterVAO);

    // Draw
    glUniform4f(color, 0.365, 0.616, 0.871, 0.75);
    glDrawArrays(GL_TRIANGLE_FAN, 0, CRES + 2);

    // Unbind VAO
    glBindVertexArray(0);

    // Unuse the shader program
    glUseProgram(0);
    glDisable(GL_BLEND);
}

void DeleteOasisVariables() {
    glDeleteBuffers(1, &waterVBO);
    glDeleteVertexArrays(1, &waterVAO);
    glDeleteBuffers(1, &grassVBO);
    glDeleteVertexArrays(1, &grassVAO);
    glDeleteTextures(1, &grassTexture);
    glDeleteBuffers(1, &fishVBO);
    glDeleteVertexArrays(1, &fishVAO);
    glDeleteTextures(1, &fishTexture);
}
