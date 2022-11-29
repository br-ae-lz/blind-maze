/* 
    contains initialization code + main game loop
*/

#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <grid.h>
#include <input.h>


/*********************************************************************************
 *  @brief main game loop
 *********************************************************************************/
int main() 
{
    // check user's OpenGL version (and create window only if sufficient)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ensure window is created successfully then point to it as the current context
    GLFWwindow* window = glfwCreateWindow(800, 800, "Blind Maze", NULL, NULL);
    if (!window)
    {
        std::cout << "ERROR: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // ensure GLAD is initialized correctly
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }   

    // define window area to be used in px
    glViewport(0, 0, 800, 800);
    // binds callback for if window is resized
    glfwSetFramebufferSizeCallback(window, framebufSizeCallback);

    aldousBroder(3);

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}