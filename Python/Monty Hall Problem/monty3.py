#ECS HW 2- Part 3
#Jiss Xavier, 916427256


#Used to import random integer function
from  random import randint
#import turtle to draw histograms
import turtle
#sets a scale that determines the size of the histogrma
scale = 250


#initializing a counter varaible for wins caused by montyalways
montyAlwaysCounter = 0

def montyalways():
    #set a random int to prize and chosen door
    prizeDoor = randint(1,3)
    doorChosen = randint(1,3)

    #make the variable as global so it can be accessed from inside the function
    global montyAlwaysCounter

    #if the player switches from an incorrect door, they always end up winning so the counter is incremented
    if  doorChosen != prizeDoor:
        montyAlwaysCounter = montyAlwaysCounter +1
    

#initializing a counter varaible for wins caused by montynever
montyNeverCounter = 0

def  montynever():

    #set a random int to prize and chosen door
    prizeDoor = randint(1,3)
    doorChosen = randint(1,3)

    #make the variable as global so it can be accessed from inside the function
    global montyNeverCounter

    #if the door chosen is the prize door and the player never switches, they always end up winning so the counter is incremented
    if doorChosen == prizeDoor:
        montyNeverCounter = montyNeverCounter +1
        

def printingTexts():        #Creates all the text found on the histogram (title, axis labels, values)
    
    turtle.penup()
    turtle.goto(0,-160)
    turtle.write("Percentage of games won if you switch always or never", False, "center", ("Arial", 10, "normal"))     #Prints Title of Histogram
    turtle.goto(0,-150)
    turtle.write("The Monty Hall Problem: " + str(userInput) + " games", False, "center",("Arial",10, "normal"))        #Prints the Subtitle
    turtle.goto(-60,-136)
    turtle.write("Always", False, "center",("Arial",10, "normal"))      #Prints Axis Labels
    turtle.goto(70,-136)
    turtle.write("Never", False, "center",("Arial",10, "normal"))       #Prints Axis Labels
    turtle.goto(70, (scale*(montyNeverCounter/userInput))-120)          #Prints the value of the graph above the corresponding bar
    turtle.write("%.7f"  % (montyNeverCounter/userInput), False, "center",("Arial",10, "normal"))
    turtle.goto(-60, (scale*(montyAlwaysCounter/userInput))-120)
    turtle.write("%.7f"  % (montyAlwaysCounter/userInput), False, "center",("Arial",10, "normal"))

def printingLines():        #Prints the x axis of the histogram

    turtle.goto(-120,-120)
    turtle.pendown()
    turtle.forward(250)


def printingHistograms():       #Prints the bars of the histogram

    turtle.penup()
    turtle.goto(-100,-120)
    turtle.pendown()
    turtle.begin_fill()         #Fills and draws the first rectangle that is drawn as the bar of the histogram
    turtle.color("black")
    turtle.lt(90)
    turtle.forward(scale*(montyAlwaysCounter/userInput))    #Length of the bar is found from previous calculations
    turtle.rt(90)
    turtle.forward(80)
    turtle.rt(90)
    turtle.forward(scale*(montyAlwaysCounter/userInput))
    turtle.end_fill()
    turtle.lt(90)               #Fills and draws the second rectangle that is drawn as the bar of the histogram
    turtle.forward(50)
    turtle.begin_fill()
    turtle.color("black")
    turtle.lt(90)
    turtle.forward(scale*(montyNeverCounter/userInput))     #Length of the bar is found from previous calculations
    turtle.rt(90)
    turtle.forward(80)
    turtle.rt(90)
    turtle.forward(scale*(montyNeverCounter/userInput))
    turtle.end_fill()
    turtle.hideturtle()         #Hides the cursor
    
    


#setting a function for the main code
def main():

    
    try:
        #reads user input for desired number of games
        global userInput
        userInput = int(input("Number of games to play: "))



        #if else loop to catch zero or non positive numbers to which the program is not applicable
        if userInput <= 0:
            print("Please enter a positive integer.")
        else:

            #initialized here so that the graphics  screen appears after a valid input has been made
            global turtle
            turtle  =  turtle.Turtle()
            #creates a for loop that runs the simulation for the users desired number of games
            for i in range(userInput):
                montyalways()
                montynever()

            #prints the results of the simulatiion
            print("Out of", userInput, "games:")
            print("Always switching wins: " +  "{:0.7f}".format(montyAlwaysCounter/userInput),"(" + str(montyAlwaysCounter), "games)")
            print("Never switching wins: " +  "{:0.7f}".format(montyNeverCounter/userInput),"(" + str(montyNeverCounter), "games)")
            
            printingTexts()     #executes the histogram drawing  functions
            printingLines()
            printingHistograms()

    #understand ctrl c as the  commannd to terminate the program
    except KeyboardInterrupt:
        print("You cancelled the  operation.")

    #catches all other invalid user inputs
    except:
        print("Please  enter a positive integer")
        exit

    
    
#runs the main loop 
main()

