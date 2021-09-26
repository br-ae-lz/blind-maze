import grid
import input
from OpenGL.GL import *
import glfw
import numpy as np


''' startup routine '''
# playerGrid = grid.aldousBroder(2)

# checks user's version (only creates their window if sufficient)
glfw.init()
glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 3)
glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 3)

# creates window, points to it as the current context
window = glfw.create_window(800, 800, "Blind Maze", None, None)
glfw.make_context_current(window)
# if window failed to be created, properly terminate
if (not window):
    print("Failed to create GLFW window")
    glfw.terminate()
    exit()

# defines window area to be used in px
glViewport(0, 0, 800, 800)
# binds callback for if window is resized
glfw.set_framebuffer_size_callback(window, input.framebufSizeCallback)

vbo = 0
glGenBuffers(1, vbo)


''' main loop '''
while(not glfw.window_should_close(window)):
    input.keyInput(window)

    # rendering stuff; clear colour buffer
    glClear(GL_COLOR_BUFFER_BIT)

    # swap colour buffers to update display and address any events
    glfw.swap_buffers(window)
    glfw.poll_events()


''' exit routine '''
glfw.terminate()