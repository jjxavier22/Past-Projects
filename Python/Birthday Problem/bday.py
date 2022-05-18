#ECS HW 4- Part 2
#Jiss Xavier, 916427256

#Atleast 23 people are needed so that the probability of two of them with a birthday in common is over 0.5
#Atleast 41 people are needed so that the probability of two of them with a birthday in common is over 0.9

from  random import randint     #imports random that allows for the generating of random integers

def has_duplicates(l):  #function that uses two for loops to cross reference all values of the list against each other lookiing for duplicates
    for i in range(len(l)):
        for j in range(i+1, len(l)):
            if l[i] == l[j]:
                return True     #If a duplicate is found the function returns True
    return False    #Otherwise if no duplicates are found False is returned


#function that creates a list containing random ints between 1-365 containing specified # of elements (count)
def onetest(count):     
    bdayList = []
    for i in range(0,count):
        bdayList.append(randint(1,365))
    return bdayList     #returns the list

#function that calculates the probabilty of duplicate birthdays
def probab(count, num):
    counter = 0         #initalizes counter variable
    for  i in range(0, num):
        onetest(count)
        if (has_duplicates(onetest(count)) == True):
            counter +=1         #counts the number of duplicates that occur as the simulation is repeated 5000x
    return(counter/num)         #returns the percentage value of the probability of duplicates

#runs the simulation 5000 times for each number of people
def simulation():
    i= 2        #starts at 2 people
    while((probab(i,5000)) <= 0.91):        #keeps running simulation until 0.9 probability is printed
        print("For", end="")
        print("{:>3}".format(i), end=" ")
        print("people, the probability of 2 birthdays is ", end="")         #prints the results of the simulation
        print("{:.5f}".format((probab(i,5000))))
        i+=1        #incrementing variable for the while loop

#main loop that runs the simulation      
def main():        
    simulation()

main()      #the main loop is run
