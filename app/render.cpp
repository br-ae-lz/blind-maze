/*
    Contains data and functions used to render graphics
*/

#include <vector>
#include <glad/glad.h>
#include <glfw/glfw3.h>


unsigned int wallVBO;

unsigned int cornerEBO;
unsigned int leftWallEBO;
unsigned int rightWallEBO;
unsigned int bottomWallEBO;
unsigned int topWallEBO;

/*********************************************************************************
 * @brief Define and store all vertex data necessary for future rendering
 *        into appropriate buffers.
 *********************************************************************************/
void initRenderData() {
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

    // Populate VBO with wall vertex data 
    glGenBuffers(1, &wallVBO);
    glBindBuffer(GL_ARRAY_BUFFER, wallVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(wallVertices), wallVertices, GL_STATIC_DRAW);

    // Define the indices of two triangles that will draw each corner using wallVertices data and
    // bind them to an EBO
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
    glGenBuffers(1, &cornerEBO);
    glBindBuffer(GL_ARRAY_BUFFER, cornerEBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cornerIndices), cornerIndices, GL_ELEMENT_ARRAY_BUFFER);

    // Define indices of two triangles that will draw each wall and bind them to EBOs
    uint32_t leftWallIndices[] = {
        2, 3, 8,
        8, 9, 3
    }; 
    uint32_t bottomWallIndices[] = {
        11, 9, 12,
        12, 14, 11
    };
    uint32_t topWallIndices[] = { 
        1, 3, 6,
        6, 4, 1
    }; 
    uint32_t rightWallIndices[] = {
        6, 7, 12,
        12, 13, 7
    };

    glGenBuffers(1, &leftWallEBO);
    glBindBuffer(GL_ARRAY_BUFFER, leftWallEBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(leftWallIndices), leftWallIndices, GL_ELEMENT_ARRAY_BUFFER);

    glGenBuffers(1, &rightWallEBO);
    glBindBuffer(GL_ARRAY_BUFFER, rightWallEBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rightWallIndices), rightWallIndices, GL_ELEMENT_ARRAY_BUFFER);

    glGenBuffers(1, &bottomWallEBO);
    glBindBuffer(GL_ARRAY_BUFFER, bottomWallEBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bottomWallIndices), bottomWallIndices, GL_ELEMENT_ARRAY_BUFFER);

    glGenBuffers(1, &topWallEBO);
    glBindBuffer(GL_ARRAY_BUFFER, topWallEBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(topWallIndices), topWallIndices, GL_ELEMENT_ARRAY_BUFFER);
}

/*********************************************************************************
 * @brief Draws the player's current surroundings to the screen. (This is called
 *         on a need-be basis to reduce GPU usage.)
 * 
 * @param grid the generated maze currently in play
 * @param pos two element array of current row and column coordinates, respectively
 *********************************************************************************/
void renderPosition(std::vector<std::vector<int>> grid, int &pos, GLFWwindow* window) {
    glfwSwapBuffers(window);
}
