#Program that draws a regular polygon with equal side lengths and angles
#depending on the user's desired number of sides

import turtle
import math

#reads inout for number of desired sides from user as an integer
numSides = int(input("How many sides would you like? "))
#formula to calculate the angle for regular polygons with 'n' nnumber of sider
angle = 360/numSides

#intializes turtle 
turtle = turtle.Turtle()

#loop that draws a side and turns the  previously calculated angle
for count in range(numSides):
    #changes the  color of the polygon to maroon
    turtle.color("Maroon")
    turtle.forward(75)
    turtle.left(angle)
    #hides the cursor for turtle
    turtle.hideturtle()
    


