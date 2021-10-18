# functions for processing user input go here!
from OpenGL.GL import *
import glfw

''' callback function for when window is resized '''
def framebufSizeCallback(window, width, height):
    glViewport(0, 0, width, height)


''' processes keyboard input '''
def keyInput(window):
    # if escape is pressed, notes that the window should close
    if (glfw.get_key(window, glfw.KEY_ESCAPE) == glfw.PRESS):
        glfw.set_window_should_close(window, True)
    
    # if a movement direction is pressed, return its appropriate value
    if (glfw.get_key(window, glfw.KEY_W) == glfw.PRESS or glfw.get_key(window, glfw.KEY_UP) == glfw.PRESS):
        return 1
    if (glfw.get_key(window, glfw.KEY_D) == glfw.PRESS or glfw.get_key(window, glfw.KEY_RIGHT) == glfw.PRESS):
        return 2
    if (glfw.get_key(window, glfw.KEY_S) == glfw.PRESS or glfw.get_key(window, glfw.KEY_DOWN) == glfw.PRESS):
        return 3
    if (glfw.get_key(window, glfw.KEY_A) == glfw.PRESS or glfw.get_key(window, glfw.KEY_LEFT) == glfw.PRESS):
        return 4

    return 0