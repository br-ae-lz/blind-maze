/* 
    Contains initialization code & main game loop
*/

#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <grid.h>
#include <input.h>


/*********************************************************************************
 *  @brief Main game loop
 *********************************************************************************/
int main() 
{
    // Check user's OpenGL version (and create window only if sufficient)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Blind Maze", NULL, NULL);
    if (!window)
    {
        std::cout << "ERROR: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "ERROR: Failed to initialize GLAD" << std::endl;
        return -1;
    }   

    glViewport(0, 0, 800, 800);
    glfwSetFramebufferSizeCallback(window, framebufSizeCallback);

    // Initialize vertex data for drawing walls and openings
    // (These vertices define a square in each corner of the screen -- walls are made by connecting them)
    float wallVertices[] = {
        -0.8,  0.8, 0.0,  // 0 - top left (of top left corner)
        -0.6,  0.8, 0.0,  // 1 - top right
        -0.8,  0.6, 0.0,  // 2 - bottom left
        -0.6,  0.6, 0.0,  // 3 - bottom right
  
         0.6,  0.8, 0.0,  // 4 - top left (of top right corner)
         0.8,  0.8, 0.0,  // 5 - top right
         0.6,  0.6, 0.0,  // 6 - bottom left
         0.8,  0.6, 0.0,  // 7 - bottom right
   
        -0.8, -0.6, 0.0,  // 8 - top left (of bottom left corner)
        -0.6, -0.6, 0.0,  // 9 - top right
        -0.8, -0.8, 0.0,  // 10 - bottom left
        -0.6, -0.8, 0.0,  // 11 - bottom right
                           
         0.6, -0.6, 0.0,  // 12 - top left (of bottom right corner)
         0.8, -0.6, 0.0,  // 13 - top right
         0.6, -0.8, 0.0,  // 14 - bottom left
         0.8, -0.8, 0.0   // 15 - bottom right
    };

    // Populate new VBO with wall vertex data 
    unsigned int wallVBO;
    glGenBuffers(1, &wallVBO);
    glBindBuffer(GL_ARRAY_BUFFER, wallVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(wallVertices), wallVertices, GL_STATIC_DRAW);

    // Define the indices of two triangles that will draw each corner using wallVertices data and
    // bind them to corresponding EBO
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