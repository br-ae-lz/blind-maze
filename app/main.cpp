/* 
    Contains initialization code & main game loop
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
        std::cout << "ERROR: Failed to initialize GLAD" << std::endl;
        return -1;
    }   

    // define window area to be used in px
    glViewport(0, 0, 800, 800);
    // binds callback for if window is resized
    glfwSetFramebufferSizeCallback(window, framebufSizeCallback);

    // initialize vertex data corresponding to all vertices necessary for drawing walls and openings
    // (vertices are laid out as "wall corners"; four corners are drawn by default, so we draw walls by connecting them)
    float wallVertices[] = {
        -0.8,  0.8, 0.0,  // 0 - top left corner; top left
        -0.6,  0.8, 0.0,  // 1 - top left corner; top right
        -0.8,  0.6, 0.0,  // 2 - top left corner; bottom left
        -0.6,  0.6, 0.0,  // 3 - top left corner; bottom right
  
         0.6,  0.8, 0.0,  // 4 - top right corner; top left
         0.8,  0.8, 0.0,  // 5 - top right corner; top right
         0.6,  0.6, 0.0,  // 6 - top right corner; bottom left
         0.8,  0.6, 0.0,  // 7 - top right corner; bottom right
   
        -0.8, -0.6, 0.0,  // 8 - bottom left corner; top left
        -0.6, -0.6, 0.0,  // 9 - bottom left corner; top right
        -0.8, -0.8, 0.0,  // 10 - bottom left corner; bottom left
        -0.6, -0.8, 0.0,  // 11 - bottom left corner; bottom right
                           
         0.6, -0.6, 0.0,  // 12 - bottom right corner; top left
         0.8, -0.6, 0.0,  // 13 - bottom right corner; top right
         0.6, -0.8, 0.0,  // 14 - bottom right corner; bottom left
         0.8, -0.8, 0.0   // 15 - bottom right corner; bottom right
    };

    // create and fill a VBO with wall vertex data 
    unsigned int wallVBO;
    glGenBuffers(1, &wallVBO);
    glBindBuffer(GL_ARRAY_BUFFER, wallVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(wallVertices), wallVertices, GL_STATIC_DRAW);

    // define triangle indices for drawing walls from vertex data and bind them to corresponding EBO
    uint32_t cornerIndices[] = {
        0, 1, 2,     // top left corner
        2, 3, 1,
        4, 5, 6,     // top right corner
        6, 7, 5,
        8, 9, 10,    // bottom left corner
        10, 11, 9,
        12, 13, 14,  // bottom right corner
        14, 15, 13
    };

    unsigned int cornerEBO;
    glGenBuffers(1, &cornerEBO);
    glBindBuffer(GL_ARRAY_BUFFER, cornerEBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cornerIndices), cornerIndices, GL_ELEMENT_ARRAY_BUFFER);


    aldousBroder(3);

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}