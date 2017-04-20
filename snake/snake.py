from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import cv2, sys

window = 0                                             # glut window number
width, height = 1500, 1000                               # window size
field_width, field_height = 50, 50                     # internal resolution
snake = [(15, 15),(15, 15),(15, 15)]                                       # snake list of (x, u) positions
global snake_direction
snake_direction = (1, 0)
snake_length = 1;                                    # snake movement direction

# def addition((x1, y1), (x2, y2)):    
#     return (x1 + x2, y1 + y2)
def addition(p1, p2):    
    return (p1[0] + p2[0], p1[1] + p2[1])

def init(width, height, internal_width, internal_height):
    glViewport(0, 0, width, height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluOrtho2D(0.0, internal_width, 0.0, internal_height)#, 0.0, 1.0)
    glMatrixMode (GL_MODELVIEW)
    glLoadIdentity()

def draw_rect(x, y, width, height):
    glBegin(GL_QUADS)                                  # start drawing a rectangle
    glVertex2f(x, y)                                   # bottom left point
    glVertex2f(x + width, y)                           # bottom right point
    glVertex2f(x + width, y + height)                  # top right point
    glVertex2f(x, y + height)                          # top left point
    glEnd()                                            # done drawing a rectangle

def draw_snake():
    glColor3f(1.0, 1.0, 1.0)  # set color to white
    for x, y in snake:        # go through each (x, y) entry
        #
        draw_rect(x, y, 1, 1) # draw it at (x, y) with width=1 and height=1

def foodPuruse():                         
    from random import randrange
    xFood = randrange(0,500)
    yFood = randrange(0,500)
    glColor3f(1.0,1.0, 1.0)
    draw_rect(200, 400, 15,15)
    glFlush()
    eatenFlag = True
    #print 'Food at ' +str(xFood) + str(yFood)

def draw():                                            # draw is called all the time
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) # clear the screen
    glLoadIdentity()                                   # reset position
    init(width, height, field_width, field_height)
    draw_snake()
    foodPuruse()
    glutSwapBuffers()

def update(value):

    snake.insert(0, addition(snake[0], snake_direction))      # insert new position in the beginning of the snake list
    snake.pop()                                        # remove the last element
    glutTimerFunc(interval, update, 0)                 # trigger next update

def keyBoardInput(key, x, y):
    if key=='q':
        exit()
    if key=='w':
        global snake_direction
        snake_direction = (0,1)
    if key=='s':
        global snake_direction
        snake_direction = (0,-1)
    if key=='a':
        global snake_direction
        snake_direction = (-1,0)
    if key=='d':
        global snake_direction
        snake_direction = (1,0)


#if __name__ == '__main__':
    #Note: snake dir (1, 0) means that its current movement
    #direction is x=1 and y=0, which means it moves to the right.
interval = 100 # update interval in milliseconds
glutInitWindowPosition(0, 0)                           # set window position
# initialization
glutInit()                                             # initialize glut
glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH)
glutInitWindowSize(width, height)                      # set window size
window = glutCreateWindow(b"Snake Game")              # create window with title
glutDisplayFunc(draw)
glutKeyboardFunc(keyBoardInput)                                 # set draw function callback
glutIdleFunc(draw)                                     # draw all the time
glutTimerFunc(interval, update, 0)                     # trigger next update
glutMainLoop()                                         # start everything
