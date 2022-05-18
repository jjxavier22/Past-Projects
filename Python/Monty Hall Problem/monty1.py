#ECS HW 2- Part 1
#Jiss Xavier, 916427256

#Used to import random integer function
from  random import randint

#function where the player always switches door
def montyalways():
    #Setting a random int for the price door between 1-3
    prizeDoor = randint(1,3)

    #Picking a random number between 1-3 for the door the player chooses
    doorChosen = randint(1,3)

    #If the door chosen is the prize door and the player switches it should
    #always evaluate to false meaning the player loses.
    if prizeDoor == doorChosen:
        print(False)
    #else player switches and ends  up winning so result is True
    else:
        print(True)

#function where the player never switches from their chosen door
def  montynever():

    #assigns random int for prize door
    prizeDoor = randint(1,3)

    #assigns random int to the door the player chooses
    doorChosen = randint(1,3)

    #same logic found above but reversed
    if prizeDoor == doorChosen:
        print(True)
    else:
        print(False)


#Two lines found below can be uncommented to visually test the program.
        
#montynever()
#montyalways()
