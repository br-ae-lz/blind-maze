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