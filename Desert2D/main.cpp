
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "helper.h"
#include "desert.h"
#include "oasis.h"

float bigPyramidColor = 0.737;  //sets the green color value. Lesser the value, stronger the red color
float colorSpeedChange = 0.005;
bool showTexture = true;

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


int main(void)
{
    GLFWwindow* window = initWindow();
    
    createDesert();
    createSmallPyramids();
    createBigPyramid();
    createWater(0.37, 0.15);
    createGrass();
    createFish();
    //todo add other create functions here...

    unsigned int basicShader = createShader("basic.vert", "basic.frag");
    unsigned int textureShader = createShader("texture.vert", "texture.frag");
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

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        {
            showTexture = false;
        }

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        {
            showTexture = true;
        }

        renderDesert(basicShader);
        renderSmallPyramids(basicShader);
        renderBigPyramid(basicShader, bigPyramidColor);
        renderWater(basicShader);
        if (showTexture)
            renderGrass(textureShader);
        else
            renderFish(textureShader);
        //todo render what you have created

        glfwSwapBuffers(window);
    }


    //todo delete and deallcoate memory
    DeleteDesertVariables();
    DeleteOasisVariables();
    glDeleteProgram(basicShader);

    glfwTerminate();
    return 0;
}