/* 
    Defines functions for processing user input
*/

#include <glad/glad.h>
#include <glfw/glfw3.h>

/*********************************************************************************
 *  @brief Resizes window to match framebuffer whenever the latter is resized.
 *         (Parameters are passed automatically when called as a callback.)
 *
 *  @param window   window whose framebuffer was resized
 *  @param width    new width of framebuffer
 *  @param height   new height of framebuffer
 *********************************************************************************/
void framebufSizeCallback(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);
}

/*********************************************************************************
 *  @brief Uses GLFW to process keyboard input.
 *
 *  @param window GLFW window whose input is to be processed
 *  @returns int corresponding to movement direction:
 *          0 - none    1 - up      4 - left
 *          2 - right   3 - down 
 *********************************************************************************/
int keyInput(GLFWwindow* window) 
{
    // Close window if escape key is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
    {
        glfwSetWindowShouldClose(window, true);
    }

    // Return movement direction if corresponding key is pressed
    if ( (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) ) 
        return 1;
    if ( (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) ) 
        return 2;
    if ( (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) ) 
        return 3;
    if ( (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) ) 
        return 4;

    return 0;
}