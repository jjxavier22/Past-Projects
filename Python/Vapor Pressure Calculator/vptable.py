#imports math inorder to use the exp operative later in the code
import math

#Function that makes the table of vapor pressure for certain temps
def calculatingVaporPressure():
    
    #print statement that makes the title and heading of the table
    print("temp \t pressure")
    print("____ \t ________")

    #For loop that begins at -20 and runs till 50 in increments of 5
    for i in  range (-20, 51, 5):
        
        #Formula for Vapor Pressure
        vaporPressure = (6.112 * math.exp((17.67 * i) / (i + 243.5)))
        
        #Ensuring that the floating point value for Vapor Pressure is to
        #2 decimal places
        vaporPressure = "{:.2f}".format(vaporPressure)
        
        #Formats the values of the table to the right
        print("{:>4}  {:>11}".format(i, vaporPressure))

#Runs the predefined function
calculatingVaporPressure()
