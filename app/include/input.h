/* 
    Declares functions for processing user input
*/

#include <glfw/glfw3.h>

/*********************************************************************************
 *  @brief resizes window to match framebuffer whenever the latter is resized
 *
 *  @param window   GLFW window whose framebuffer was resized
 *  @param width    new width of framebuffer
 *  @param height   new height of framebuffer
 *********************************************************************************/
extern void framebufSizeCallback(GLFWwindow* window, int width, int height);

/*********************************************************************************
 *  @brief processes keyboard input (where wasd and arrow keys control player 
 *         movement, escape closes window)
 *
 *  @param window GLFW window whose input is to be processed
 *  @returns int corresponding to movement direction:
 *                  0 - none
 *                  1 - up
 *                  2 - right
 *                  3 - down
 *                  4 - left
 *********************************************************************************/
extern int keyInput(GLFWwindow* window);