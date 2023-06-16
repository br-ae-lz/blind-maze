/* 
    Declares functions used to render graphics
*/

/*********************************************************************************
 * @brief Define and store all vertex data necessary for future rendering
 *        into appropriate buffers.
 *********************************************************************************/
void initRenderData();

/*********************************************************************************
 * @brief Draws the player's current surroundings to the screen.
 * 
 * @param grid the generated maze currently in play
 * @param pos two element array of current row and column coordinates, respectively
 * @param window GLFW window being treated as the main context
 *********************************************************************************/
void renderPosition(std::vector<std::vector<int>> grid, int &pos, GLFWwindow* window);
