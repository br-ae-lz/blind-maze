/* 
    Contains initialization code & main game loop
*/

#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <grid.h>
#include <input.h>
#include <render.h>


int main() 
{
    // Check user's OpenGL version (and create window only if sufficient)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 800, "Blind Maze", NULL, NULL);
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
    initRenderData();

    // Prepare to render initial player position 
    std::vector<std::vector<int>> playerGrid = createMaze(3);
    int pos[2];
    findPlayerPos(playerGrid, pos);


    int lastInputStatus = 0;
    bool exitReached = false;

    // Main loop begins
    while (!glfwWindowShouldClose(window) && !exitReached)
    { 
        renderPosition(playerGrid, pos, window);

        // Record key pressed upon player input
        glfwWaitEvents();
        int inputStatus = keyInput(window);

        // Process movement input once pressed key has been released
        if (lastInputStatus == 0) {
            switch(inputStatus) {
                case 1:     // Up 
                    if (playerGrid[pos[0]-1][pos[1]] > 0)
                        pos[0]--;
                    break;

                case 2:     // Right  
                    if (playerGrid[pos[0]][pos[1]+1] > 0)
                        pos[1]++;
                    break;

                case 3:     // Down 
                    if (playerGrid[pos[0]+1][pos[1]] > 0)
                        pos[0]++;
                    break;
                    
                case 4:     // Left 
                    if (playerGrid[pos[0]][pos[1]-1] > 0)
                        pos[1]--;
                    break;
            }
        }

        // Exit loop if player has escaped
        if (playerGrid[pos[0]][pos[1]] == 2)
            exitReached = true;

        lastInputStatus = inputStatus;
    }

    glfwTerminate();
    return 0;
}