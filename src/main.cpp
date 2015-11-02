// Preprocessor Directives
#define STB_IMAGE_IMPLEMENTATION

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// System Headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
//#include <stb_image.h>
#include <iostream>

#include "VCTApplication.h"

const int width_ = 1024;
const int height_ = 768;

void dumpGLInfo() {
    printf ("Vendor: %s\n", glGetString(GL_VENDOR));
    printf ("Renderer: %s\n", glGetString(GL_RENDERER));
    printf ("Version: %s\n", glGetString(GL_VERSION));
    printf ("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

int main(void) {

    // Load GLFW and create a window
    if(!glfwInit()) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(width_, height_, "VCT", NULL, NULL);

    // Check for Valid Context
    if (window == NULL) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        glfwTerminate();
        return EXIT_FAILURE;
    }
    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos(window, width_, height_);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return EXIT_FAILURE;
    }
    
    dumpGLInfo();

    // Initialize other openGL stuff
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); 

    double previousTime, currentTime;
    previousTime = glfwGetTime();

    VCTApplication app(width_, height_, window);
    if(!app.initialize()) {
        fprintf(stderr, "Failed to initialize TestApplication\n");
        return EXIT_FAILURE;
    }
 
    // Rendering Loop
    while (glfwWindowShouldClose(window) == false) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Set clear color and clear
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update timer
        currentTime = glfwGetTime();
        float deltaTime = float(currentTime - previousTime);
        previousTime = currentTime;

        app.update(deltaTime);
        app.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}