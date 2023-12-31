
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
#include "sky.h"

float bigPyramidColor = 0.737;  //sets the green color value. Lesser the value, stronger the red color
float colorSpeedChange = 0.0005;
bool showTexture = true;
bool paused = false;
bool restared = false;

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
    
    createStars();
    createDesert();
    createSmallPyramids();
    createBigPyramid();
    createWater(0.37, 0.15);
    createGrass();
    createFish();
    createSun(0.0, 0.0, 0.07, 0.1);
    createMoon(0.0, 0.0, 0.07, 0.1);
    createSignature();

    unsigned int basicShader = createShader("basic.vert", "basic.frag");
    unsigned int textureShader = createShader("texture.vert", "texture.frag");
    unsigned int rotationShader = createShader("rotation.vert", "basic.frag");
    glClearColor(0.337, 0.451, 0.51, 1.0);

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

        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        {
            paused = true;
        }

        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            restared = true;
            paused = false;
        }

        renderStars(textureShader);
        renderSun(rotationShader, paused, restared);
        renderMoon(rotationShader);
        renderDesert(basicShader);
        renderSmallPyramids(basicShader);
        renderBigPyramid(basicShader, bigPyramidColor);
        if (!showTexture)
            renderFish(textureShader);
        renderWater(basicShader);
        if (showTexture)
            renderGrass(textureShader);
        renderSignature(textureShader);

        glfwSwapBuffers(window);
        restared = false;
    }

    DeleteDesertVariables();
    DeleteOasisVariables();
    DeleteSkyVariables();
    glDeleteProgram(basicShader);

    glfwTerminate();
    return 0;
}