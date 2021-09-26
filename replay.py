# replay stuff goes here!

from OpenGL.GL import *
import glfw
import numpy as np

''' keeping pictureGrid() here for future reference '''
# """ saves input grid as a .jpg image in the folder "temp" in project root """
# # currently half-finished because saving an image of the grid with the window hidden is not possible for pyGame
# def pictureGrid(grid):

#     pg.init()
    
#     BLACK = (0, 0, 0)
#     WHITE = (255, 255, 255)
#     BLUE =  (  0,   0, 255)
#     GREEN = (  0, 255,   0)
#     RED =   (255,   0,   0)
    
#     # initializes the screen with a grid-based resolution 
#     screen = pg.display.set_mode(size=(len(grid)*50, len(grid)*50), flags = pg.HIDDEN)
#     pg.display.iconify()
    
#     done = False
#     clock = pg.time.Clock()

#     # Clear the screen and set the screen background
#     screen.fill(WHITE)

#     while not done:
#         pass
#         # limits the loop to running 10 times per second, saving CPU
#         clock.tick(10)
        
#         # lets the user close the window if they request to, ends loop
#         for event in pg.event.get():
#             if event.type == pg.QUIT:
#                 done = True

#         for i in range(len(grid)):
#             for j in range(len(grid)):
#                 if grid[i][j] == ' ':
#                     pass
#                 else:
#                     pg.draw.line(screen, BLACK, [50*j, 24 + i*50], [50*(j+1), 24 + i*50], 50)
                
#         pg.display.flip()
    
#     pg.image.save(screen, "temp\grid_pic.jpg")
