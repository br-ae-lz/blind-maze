import grid

playerGrid = grid.aldousBroder(14)


''' debug code for viewing algorithm result '''
import pygame as pg

pg.init()

BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
BLUE =  (  0,   0, 255)
GREEN = (  0, 255,   0)
RED =   (255,   0,   0)

# initializes the screen with a grid-based resolution 
screen = pg.display.set_mode(size=(len(playerGrid)*50, len(playerGrid)*50))

done = False
clock = pg.time.Clock()
# Clear the screen and set the screen background
screen.fill(WHITE)
while not done:
    # limits the loop to running 10 times per second, saving CPU
    clock.tick(10)
    
    # lets the user close the window if they request to, ends loop
    for event in pg.event.get():
        if event.type == pg.QUIT:
            done = True
    for i in range(len(playerGrid)):
        for j in range(len(playerGrid)):
            if playerGrid[i, j] == 1 or playerGrid [i,j] == 2:
                pass
            else:
                pg.draw.line(screen, BLACK, [50*j, 24 + i*50], [50*(j+1), 24 + i*50], 50)
            
    pg.display.flip()