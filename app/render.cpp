/*
    Contains data and functions used to render graphics
*/

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <glfw/glfw3.h>


unsigned int wallVAO;
unsigned int wallVBO;
unsigned int exitVAO;
unsigned int exitVBO;

unsigned int cornerEBO;
unsigned int leftWallEBO;
unsigned int rightWallEBO;
unsigned int bottomWallEBO;
unsigned int topWallEBO;
unsigned int topExitEBO;
unsigned int rightExitEBO;
unsigned int bottomExitEBO;
unsigned int leftExitEBO;

unsigned int wallShader;
unsigned int exitShader;

/*********************************************************************************
 * @brief Define and store all vertex data necessary for future rendering.
 *********************************************************************************/
void initRenderData() { 
    glGenVertexArrays(1, &wallVAO);
    glBindVertexArray(wallVAO);

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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cornerEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cornerIndices), cornerIndices, GL_STATIC_DRAW);

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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, leftWallEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(leftWallIndices), leftWallIndices, GL_STATIC_DRAW);

    glGenBuffers(1, &rightWallEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rightWallEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rightWallIndices), rightWallIndices, GL_STATIC_DRAW);

    glGenBuffers(1, &bottomWallEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bottomWallEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bottomWallIndices), bottomWallIndices, GL_STATIC_DRAW);

    glGenBuffers(1, &topWallEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, topWallEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(topWallIndices), topWallIndices, GL_STATIC_DRAW);

    // Configure how wall vertex data is read from buffers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &exitVAO);
    glBindVertexArray(exitVAO);

    // Initialize vertex data for drawing exits
    float exitVertices[] = {
        -0.9,  1.0, 0.0,
         0.9,  1.0, 0.0,
         0.0,  0.4, 0.0,

         1.0,  0.9, 0.0,
         1.0, -0.9, 0.0,
         0.4,  0.0, 0.0,

        -0.9, -1.0, 0.0,
         0.9, -1.0, 0.0,
         0.0, -0.4, 0.0,
        
        -1.0,  0.9, 0.0,
        -1.0, -0.9, 0.0,
        -0.4,  0.0, 0.0
    };

    // Populate VBO with exit vertex data
    glGenBuffers(1, &exitVBO);
    glBindBuffer(GL_ARRAY_BUFFER, exitVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(exitVertices), exitVertices, GL_STATIC_DRAW);

    // Define indices of triangles that will denote exits and bind them to EBOs
    uint32_t topExitIndices[] = {0, 1, 2};
    uint32_t rightExitIndices[] = {3, 4, 5};
    uint32_t bottomExitIndices[] = {6, 7, 8};
    uint32_t leftExitIndices[] = {9, 10, 11};

    glGenBuffers(1, &topExitEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, topExitEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(float), topExitIndices, GL_STATIC_DRAW);
 
    glGenBuffers(1, &rightExitEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rightExitEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(float), rightExitIndices, GL_STATIC_DRAW);

    glGenBuffers(1, &bottomExitEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bottomExitEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(float), bottomExitIndices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &leftExitEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, leftExitEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(float), leftExitIndices, GL_STATIC_DRAW);

    // Specify how exit vertex data is read from buffers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // Clean up state before drawing
    glBindVertexArray(0);
    glBindBuffer(1, 0);

    // Compile vertex shader and wall and exit fragment shaders
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    const char *wallFragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
        "}\0";

    unsigned int wallFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(wallFragmentShader, 1, &wallFragmentShaderSource, NULL);
    glCompileShader(wallFragmentShader);
 
    const char *exitFragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 1.0f, 0.75f, 1.0f);\n"
        "}\0";
    
    unsigned int exitFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(exitFragmentShader, 1, &exitFragmentShaderSource, NULL);
    glCompileShader(exitFragmentShader);
    
    // Report shader compilation errors (if any)
    int status;
    char logString[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetShaderInfoLog(vertexShader, 512, NULL, logString);
        std::cout << "ERROR: Vertex shader compilation failed -- " << logString << std::endl;
    }
    glGetShaderiv(wallFragmentShader, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetShaderInfoLog(wallFragmentShader, 512, NULL, logString);
        std::cout << "ERROR: Wall fragment shader compilation failed -- " << logString << std::endl;
    }
    glGetShaderiv(exitFragmentShader, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetShaderInfoLog(exitFragmentShader, 512, NULL, logString);
        std::cout << "ERROR: Exit fragment shader compilation failed -- " << logString << std::endl;
    }

    // Link compiled shaders
    wallShader = glCreateProgram();
    glAttachShader(wallShader, vertexShader);
    glAttachShader(wallShader, wallFragmentShader);
    glLinkProgram(wallShader); 
    exitShader = glCreateProgram();
    glAttachShader(exitShader, vertexShader);
    glAttachShader(exitShader, exitFragmentShader);
    glLinkProgram(exitShader);

    // Report shader linking errors (if any)
    glGetProgramiv(wallShader, GL_LINK_STATUS, &status);
    if(!status) {
        glGetProgramInfoLog(wallShader, 512, NULL, logString);
        std::cout << "ERROR: Wall shader linking failed -- " << logString << std::endl;
    }
    glGetProgramiv(exitShader, GL_LINK_STATUS, &status);
    if(!status) {
        glGetProgramInfoLog(exitShader, 512, NULL, logString);
        std::cout << "ERROR: Exit shader linking failed -- " << logString << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(wallFragmentShader);
    glDeleteShader(exitFragmentShader);
}

/*********************************************************************************
 * @brief Draws the player's current surroundings to the screen. (This is called
 *         on a need-be basis to reduce GPU usage.)
 * 
 * @param grid the generated maze currently in play
 * @param pos two element array of current row and column coordinates, respectively
 *********************************************************************************/
void renderPosition(std::vector<std::vector<int>> grid, int *pos, GLFWwindow *window) {
    // Clear screen to black
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(wallShader);
    glBindVertexArray(wallVAO);
    
    // Draw all corners
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cornerEBO);
    glDrawElements(GL_TRIANGLES, 3*8, GL_UNSIGNED_INT, 0);

    // Draw surrounding walls
    if (grid[pos[0]-1][pos[1]] == 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, topWallEBO);
        glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, 0);
    }
    if (grid[pos[0]][pos[1]+1] == 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rightWallEBO);
        glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, 0);
    }
    if (grid[pos[0]+1][pos[1]] == 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bottomWallEBO);
        glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, 0);
    }
    if (grid[pos[0]][pos[1]-1] == 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, leftWallEBO);
        glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, 0); 
    }

    glUseProgram(exitShader);
    glBindVertexArray(exitVAO);

    // Draw surrounding exits
    if (grid[pos[0]-1][pos[1]] == -1 || grid[pos[0]-1][pos[1]] == 2) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, topExitEBO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    }
    if (grid[pos[0]][pos[1]+1] == -1 || grid[pos[0]][pos[1]+1] == 2) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rightExitEBO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    }
    if (grid[pos[0]+1][pos[1]] == -1 || grid[pos[0]+1][pos[1]] == 2) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bottomExitEBO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    }
    if (grid[pos[0]][pos[1]-1] == -1 || grid[pos[0]][pos[1]-1] == 2) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, leftExitEBO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    }

    glfwSwapBuffers(window);
}
