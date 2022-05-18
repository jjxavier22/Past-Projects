#ECS HW 2- Part 2
#Jiss Xavier, 916427256

#Used to import random integer function
from  random import randint

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

#setting a function for the main code
def main():
    
    try:
        #reads user input for desired number of games
        userInput = int(input("Number of games to play: "))

        #if else loop to catch zero or non positive numbers to which the program is not applicable
        if userInput <= 0:
            print("Please enter a positive integer.")
        else:

            #creates a for loop that runs the simulation for the users desired number of games
            for i in range(userInput):
                montyalways()
                montynever()

            #prints the results of the simulatiion
            print("Out of", userInput, "games:")
            print("Always switching wins: " +  "{:0.7f}".format(montyAlwaysCounter/userInput),"(" + str(montyAlwaysCounter), "games)")
            print("Never switching wins: " +  "{:0.7f}".format(montyNeverCounter/userInput),"(" + str(montyNeverCounter), "games)")

    #understand ctrl c as the  commannd to terminate the program
    except KeyboardInterrupt:
        print("You cancelled the  operation.")

    #catches all other invalid user inputs
    except:
        print("Please  enter a positive integer")

#runs the main loop
main()
