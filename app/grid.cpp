/*
    Defines functions for maze generation and analysis
*/

#include <random>
#include <vector>
#include <iostream>

/*********************************************************************************
 * @brief Returns a uniform spanning tree maze generated by the Aldous-Broder 
 *        algorithm.
 *
 * @param size dictates size of the generated maze (min 2, max 99)
 * @returns size*size uniform spanning tree maze
 *********************************************************************************/
std::vector<std::vector<int>> createMaze(const int size) 
{
    // Initialize array assuming movement is allowed in any direction (in order: left, right, up, down)
    std::vector<bool> moveOptions = {true, true, true, true};
    unsigned int cellsVisited = 0;

    // Initialize random generator objects and grid
    std::random_device rd;
    std::mt19937 randEngine(rd());
    std::uniform_int_distribution<int> directionDist(1, 4);
    std::uniform_int_distribution<int> gridDist(1, size*2 - 1); 
    std::vector<std::vector<int>> grid((size*2 + 1), std::vector<int> ((size*2 + 1), 0));

    // Pick random grid cell
    int row = 0, col = 0;
    while ( (row % 2 != 1) || (col % 2 != 1) ) 
    {
        row = gridDist(randEngine);
        col = gridDist(randEngine);
    }

    // Restrict initial movement options as necessary
    if (row == 1)                   
        moveOptions[2] = false;
    else if (row == (size*2)-1)
        moveOptions[3] = false;
    if (col == 1)       
        moveOptions[0] = false;
    else if (col == (size*2)-1)
        moveOptions[1] = false;

    // Main loop (runs until all cells have been visited)
    while (cellsVisited != size*size)
    {
        // Randomly choose valid movement direction
        int currentMove = directionDist(randEngine);

        // carve a parth to, mark, and count target cell
        // if previously unvisited, then reevaluate movement options from said cell
        if (currentMove == 0)   // left movement routine
        {
            col -= 2;
            if (grid[row][col] != 2)
            {
                grid[row][col] = 2;
                grid[row][col+1] = 1;
                cellsVisited += 1;
            }

            if (moveOptions[1])
            {
                
            }
            
        }

        ++cellsVisited;
    } 

    // Rendering test grid return
    /*
    std::vector<std::vector<int>> grid = { {0,  0, 0, 2, 0},
                                           {0,  0, 1, 1, 0},
                                           {0,  0, 1, 0, 0},
                                           {0,  1, 1, 0, 0},
                                           {0, -1, 0, 0, 0}
    };
    */

    return grid;
}

/*********************************************************************************
 * @brief Locates the player's position in the given maze and stores their
 *        coordinates in a variable passed by the caller.
 * @param grid the generated maze currently in play
 * @param pos array to be populated with row and column coordinates
 *********************************************************************************/
void findPlayerPos(std::vector<std::vector<int>> grid, int *pos) {
    // Rendering test grid starting pos

    //pos[0] = 3;
    //pos[1] = 1;
}