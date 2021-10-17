import grid
import input

import numpy as np
import glfw
from OpenGL import *
from OpenGL.GL import *
from OpenGL.arrays import vbo

''' startup routine '''
# playerGrid = grid.aldousBroder(2)

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
leftEBO = vbo.VBO(leftWallIndices, target=GL_ELEMENT_ARRAY_BUFFER)

bottomWallIndices = np.array( [11, 9, 12,
                               12, 14, 11]
                              , dtype = 'uint32')
bottomEBO = vbo.VBO(bottomWallIndices, target=GL_ELEMENT_ARRAY_BUFFER)

topWallIndices = np.array( [1, 3, 6,
                            6, 4, 1]
                            , dtype = 'uint32')
topEBO = vbo.VBO(topWallIndices, target=GL_ELEMENT_ARRAY_BUFFER)

rightWallIndices = np.array( [6, 7, 12,
                              12, 13, 7]
                              , dtype = 'uint32')
rightEBO = vbo.VBO(rightWallIndices, target=GL_ELEMENT_ARRAY_BUFFER)

# creates and binds vertex buffer object to contain wall vertex data
wallVBO = vbo.VBO(wallVertices)
wallVBO.bind()

# denotes how vertex data should be read from the buffer and gives the go-ahead to do this
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, None)
glEnableVertexAttribArray(0)

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
    print("Vertex shader compilation failed:", glGetShaderInfoLog(vertexShader))

# defines and binds fragment shader source code to the shader object, then compiles it
wallFragmentShaderSource = '''
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
'''
fragmentShader = glCreateShader(GL_FRAGMENT_SHADER)
glShaderSource(fragmentShader, wallFragmentShaderSource)
glCompileShader(fragmentShader)

if(not glGetShaderiv(fragmentShader, GL_COMPILE_STATUS)):
    print("Fragment shader compilation failed:", glGetShaderInfoLog(fragmentShader))

# initializes and links shader program employing defined vertex and fragment shaders
shaderProgram = glCreateProgram()
glAttachShader(shaderProgram, vertexShader)
glAttachShader(shaderProgram, fragmentShader)
glLinkProgram(shaderProgram)
glDeleteShader(vertexShader)
glDeleteShader(fragmentShader)


''' main loop '''
while(not glfw.window_should_close(window)):
    input.keyInput(window)

    # clear screen to black
    glClear(GL_COLOR_BUFFER_BIT)
    glUseProgram(shaderProgram)

    # draws an L (and extraneous corner), befitting of our current state
    cornerEBO.bind()
    glDrawElements(GL_TRIANGLES, 3*8, GL_UNSIGNED_INT, None)
    bottomEBO.bind()
    glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, None)
    leftEBO.bind()
    glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, None)

    # swap colour buffers to update display & address any events
    glfw.swap_buffers(window)
    glfw.poll_events()

# function to be used to draw current position to the screen -- it needs a *little* work...
def renderPosition():
    pass


''' exit routine '''
glfw.terminate()