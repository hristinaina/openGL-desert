
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "helper.h"


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
}

void renderDesert() {
    // here goes the logic for the loop
}


int main(void)
{
    GLFWwindow* window = initWindow();
    
    createDesert();
    //todo add other create functions here...

    //unsigned int unifiedShader = createShader("basic.vert", "basic.frag");

    while (!glfwWindowShouldClose(window))
    {
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        
        glClear(GL_COLOR_BUFFER_BIT);

        renderDesert();
        //todo render what you have created

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    //todo delete and deallcoate memory
    //glDeleteProgram(unifiedShader);

    glfwTerminate();
    return 0;
}