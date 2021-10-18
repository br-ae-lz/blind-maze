import grid
import input

import numpy as np
import glfw
from OpenGL import *
from OpenGL.GL import *
from OpenGL.arrays import vbo

''' OpenGL setup '''
# checks user's OpenGL version (only creates window if sufficient)
glfw.init()
glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 3)
glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 3)
glfw.window_hint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE)

# ensures window is created successfully while pointing to it as the current context
window = glfw.create_window(800, 800, "Blind Maze", None, None)
if (not window):
    print("ERROR: Failed to create GLFW window")
    glfw.terminate()
    exit()
glfw.make_context_current(window)

# defines window area to be used in px
glViewport(0, 0, 800, 800)
# binds callback for if window is resized
glfw.set_framebuffer_size_callback(window, input.framebufSizeCallback)

# creates and binds vertex array object for walls and openings
wallVAO = GLuint(0)
glGenVertexArrays(1, wallVAO)
glBindVertexArray(wallVAO)

# initializes vertex data corresponding to all vertices necessary for drawing walls and openings
# (vertices laid out as "wall corners" -- four corners are drawn by default, so we draw walls by connecting them)
wallVertices = np.array( [-0.8,  0.8, 0.0,  # 0 - top left corner; top left
                          -0.6,  0.8, 0.0,  # 1 - top left corner; top right
                          -0.8,  0.6, 0.0,  # 2 - top left corner; bottom left
                          -0.6,  0.6, 0.0,  # 3 - top left corner; bottom right
  
                           0.6,  0.8, 0.0,  # 4 - top right corner; top left
                           0.8,  0.8, 0.0,  # 5 - top right corner; top right
                           0.6,  0.6, 0.0,  # 6 - top right corner; bottom left
                           0.8,  0.6, 0.0,  # 7 - top right corner; bottom right
   
                          -0.8, -0.6, 0.0,  # 8 - bottom left corner; top left
                          -0.6, -0.6, 0.0,  # 9 - bottom left corner; top right
                          -0.8, -0.8, 0.0,  # 10 - bottom left corner; bottom left
                          -0.6, -0.8, 0.0,  # 11 - bottom left corner; bottom right
                           
                           0.6, -0.6, 0.0,  # 12 - bottom right corner; top left
                           0.8, -0.6, 0.0,  # 13 - bottom right corner; top right
                           0.6, -0.8, 0.0,  # 14 - bottom right corner; bottom left
                           0.8, -0.8, 0.0]  # 15 - bottom right corner; bottom right
                          , dtype = 'float32')

# creates and binds vertex buffer object to contain wall vertex data
wallVBO = vbo.VBO(wallVertices)
wallVBO.bind()

# defines triangle indices for drawing walls from vertex data and binds them to corresponding element buffer objects
cornerIndices = np.array( [0, 1, 2,     # top left corner
                           2, 3, 1,
                           4, 5, 6,     # top right corner
                           6, 7, 5,
                           8, 9, 10,    # bottom left corner
                           10, 11, 9,
                           12, 13, 14,  # bottom right corner
                           14, 15, 13]
                          , dtype = 'uint32')
cornerEBO = vbo.VBO(cornerIndices, target=GL_ELEMENT_ARRAY_BUFFER)

leftWallIndices = np.array( [2, 3, 8,       
                             8, 9, 3]
                            , dtype = 'uint32')
leftWallEBO = vbo.VBO(leftWallIndices, target=GL_ELEMENT_ARRAY_BUFFER)

bottomWallIndices = np.array( [11, 9, 12,
                               12, 14, 11]
                              , dtype = 'uint32')
bottomWallEBO = vbo.VBO(bottomWallIndices, target=GL_ELEMENT_ARRAY_BUFFER)

topWallIndices = np.array( [1, 3, 6,
                            6, 4, 1]
                            , dtype = 'uint32')
topWallEBO = vbo.VBO(topWallIndices, target=GL_ELEMENT_ARRAY_BUFFER)

rightWallIndices = np.array( [6, 7, 12,
                              12, 13, 7]
                              , dtype = 'uint32')
rightWallEBO = vbo.VBO(rightWallIndices, target=GL_ELEMENT_ARRAY_BUFFER)

# denotes how wall vertex data should be read from the buffer and gives the go-ahead to do this
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, None)
glEnableVertexAttribArray(0)

# unbinds wall VAO and VBO so we can define equivalent objects for exits
glBindVertexArray(0)
wallVBO.bind()

# creates and binds vertex array object for exits
exitVAO = GLuint(0)
glGenVertexArrays(1, exitVAO)
glBindVertexArray(exitVAO)

# initializes vertex data corresponding to all vertices necessary for drawing exits
exitVertices = np.array( [-0.9,  1.0, 0.0,  # 0-2 - top exit
                           0.9,  1.0, 0.0,  
                           0.0,  0.4, 0.0,   
                          
                           1.0,  0.9, 0.0,  # 3-5 - right exit
                           1.0, -0.9, 0.0,  
                           0.4,  0.0, 0.0,
                          
                          -0.9, -1.0, 0.0,  # 6-8 - bottom exit
                           0.9, -1.0, 0.0,
                           0.0, -0.4, 0.0,
                           
                          -1.0,  0.9, 0.0,  # 9-11 - left exit
                          -1.0, -0.9, 0.0,
                          -0.4,  0.0, 0.0]
                          , dtype = 'float32')

# creates and binds vertex buffer object to contain exit vertex data
exitVBO = vbo.VBO(exitVertices)
exitVBO.bind()

# binds triangle indices for drawing exits from vertex data to corresponding element buffer objects
topExitEBO = vbo.VBO(np.array([0, 1, 2], dtype = 'uint32'), target=GL_ELEMENT_ARRAY_BUFFER)
rightExitEBO = vbo.VBO(np.array([3, 4, 5], dtype = 'uint32'), target=GL_ELEMENT_ARRAY_BUFFER)
bottomExitEBO = vbo.VBO(np.array([6, 7, 8], dtype = 'uint32'), target=GL_ELEMENT_ARRAY_BUFFER)
leftExitEBO = vbo.VBO(np.array([9, 10, 11], dtype = 'uint32'), target=GL_ELEMENT_ARRAY_BUFFER)

# denotes how exit vertex data should be read from the buffer and gives the go-ahead to do this
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, None)
glEnableVertexAttribArray(0)

# unbinds exit VAO and VBO to clean state for drawing
glBindVertexArray(0)
exitVBO.bind()

# defines and binds vertex shader source to shader object, then compiles it
vertexShaderSource = '''
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
'''
vertexShader = glCreateShader(GL_VERTEX_SHADER)
glShaderSource(vertexShader, vertexShaderSource)
glCompileShader(vertexShader)

if(not glGetShaderiv(vertexShader, GL_COMPILE_STATUS)):
    print("ERROR: Vertex shader compilation failed:", glGetShaderInfoLog(vertexShader))

# defines and binds each fragment shader's source code to shader objects and compiles them
wallFragmentShaderSource = '''
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
'''
wallFragmentShader = glCreateShader(GL_FRAGMENT_SHADER)
glShaderSource(wallFragmentShader, wallFragmentShaderSource)
glCompileShader(wallFragmentShader)

if(not glGetShaderiv(wallFragmentShader, GL_COMPILE_STATUS)):
    print("ERROR: Wall fragment shader compilation failed:", glGetShaderInfoLog(wallFragmentShader))

exitFragmentShaderSource = '''
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 1.0f, 0.75f, 1.0f);
}
'''
exitFragmentShader = glCreateShader(GL_FRAGMENT_SHADER)
glShaderSource(exitFragmentShader, exitFragmentShaderSource)
glCompileShader(exitFragmentShader)

if(not glGetShaderiv(exitFragmentShader, GL_COMPILE_STATUS)):
    print("ERROR: Exit fragment shader compilation failed:", glGetShaderInfoLog(exitFragmentShader))

# initializes and links shader programs for walls and exits
wallShader = glCreateProgram()
glAttachShader(wallShader, vertexShader)
glAttachShader(wallShader, wallFragmentShader)
glLinkProgram(wallShader)

exitShader = glCreateProgram()
glAttachShader(exitShader, vertexShader)
glAttachShader(exitShader, exitFragmentShader)
glLinkProgram(exitShader)

glDeleteShader(vertexShader)
glDeleteShader(wallFragmentShader)
glDeleteShader(exitFragmentShader)


''' game setup '''
# generates grid
playerGrid = grid.aldousBroder(4)

# determines player starting position, which is one cell inwards from the entry
playerpos = np.where(playerGrid == -1)
playerRow = playerpos[0][0]
playerCol = playerpos[1][0]

if (playerRow == 0):
    playerRow += 1
elif (playerRow == (len(playerGrid) - 1)):
    playerRow -= 1
elif (playerCol == 0):
    playerCol += 1
elif (playerCol == (len(playerGrid) - 1)):
    playerCol -= 1

# draws the player's surroundings in their current position to the screen
# (thus handling drawing on a need-be basis to reduce gpu usage)
def renderPosition(row, col, grid):
    # clear screen to black
    glClear(GL_COLOR_BUFFER_BIT)

    # draw corners
    glUseProgram(wallShader)
    glBindVertexArray(wallVAO)

    cornerEBO.bind()
    glDrawElements(GL_TRIANGLES, 3*8, GL_UNSIGNED_INT, None)

    # draw surrounding walls
    if (grid[row-1][col] == 0):
        topWallEBO.bind()
        glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, None)
    if (grid[row][col+1] == 0):
        rightWallEBO.bind()
        glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, None)
    if (grid[row+1][col] == 0):
        bottomWallEBO.bind()
        glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, None)
    if (grid[row][col-1] == 0):
        leftWallEBO.bind()
        glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, None)
    
    # draw surrounding exits
    glUseProgram(exitShader)
    glBindVertexArray(exitVAO)

    if (grid[row-1][col] < 0):
        topExitEBO.bind()
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, None)
    if (grid[row][col+1] < 0):
        rightExitEBO.bind()
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, None)
    if (grid[row+1][col] < 0):
        bottomExitEBO.bind()
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, None)
    if (grid[row][col-1] < 0):
        leftExitEBO.bind()
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, None)

    # swap colour buffers to update display
    glfw.swap_buffers(window)

# draws the player's initial surroundings
renderPosition(playerRow, playerCol, playerGrid)

''' main loop '''
lastInputStatus = 0
# processes player input and essentially waits for them to win
while(not glfw.window_should_close(window)):
    # waits for the player to do something
    glfw.wait_events()

    # record whether input is for movement (if so, direction is included)
    inputStatus = input.keyInput(window)

    # processes movement input only if previously pressed movement key has been released
    if (lastInputStatus == 0):
        if inputStatus == 1:    # up movement
            if (playerGrid[playerRow-1][playerCol] > 0):
                playerRow -= 1
            elif (playerGrid[playerRow-1][playerCol] == -2):
                break
        elif inputStatus == 2:  # right movement
            if (playerGrid[playerRow][playerCol+1] > 0):
                playerCol += 1
            elif (playerGrid[playerRow][playerCol+1] == -2):
                break
        elif inputStatus == 3:  # down movement
            if (playerGrid[playerRow+1][playerCol] > 0):
                playerRow += 1
            elif (playerGrid[playerRow+1][playerCol] == -2):
                break
        elif inputStatus == 4:  # left movement
            if (playerGrid[playerRow][playerCol-1] > 0):
                playerCol -= 1
            elif (playerGrid[playerRow][playerCol-1] == -2):
                break

    # update the screen to show movement and satisfy events like the window resize callback
    renderPosition(playerRow, playerCol, playerGrid)

    lastInputStatus = inputStatus


''' exit routine '''
glfw.terminate()