/*
    Defines functions for maze generation
*/

#include <random>
#include <vector>
#include <iostream>

/*********************************************************************************
 *  @brief returns a size*size uniform spanning tree maze generated by the
 *         Aldous-Broder algorithm 
 *
 *  @param size dictates size of the generated maze (min 2, max 99)
 *  @returns size*size uniform spanning tree maze
 *********************************************************************************/
std::vector<std::vector<int>> aldousBroder(const int size) 
{
    // begin assuming movement is allowed in any direction (in order: left, right, up, down)
    bool moveOptions[4] = {true, true, true, true};

    unsigned int cellsVisited = 0;

    // initialize random engine and distributions
    std::random_device rd;
    std::mt19937 randEngine(rd());
    std::uniform_int_distribution<int> directionDist(1, 4);
    std::uniform_int_distribution<int> gridDist(1, size*2 - 1);

    // initialize blank grid
    std::vector<std::vector<int>> grid((size*2 + 1), std::vector<int> ((size*2 + 1), 0));

    // pick a random grid cell
    int row = 0, col = 0;
    while ( (row % 2 != 1) || (col % 2 != 1) ) 
    {
        row = gridDist(randEngine);
        col = gridDist(randEngine);
    }

    // determine initial movement options from starting position
    if (row == 1)                   // vertical cases
    {
        moveOptions[2] = false;
    } 
    else if (row == (size*2)-1)
    {
        moveOptions[3] = false;
    } 
    if (col == 1)       // horizontal cases
    {
        moveOptions[0] = false;
    } 
    else if (col == (size*2)-1)
    {
        moveOptions[1] = false;
    } 

    // main algo loop; runs until all cells have been visited
    while (cellsVisited != size*size)
    {
        // randomly choose movement direction from those available
        int currentMove = directionDist(randEngine);

        // for chosen movement direction, carve a parth to, mark, and count the target cell
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

    return grid;
}

