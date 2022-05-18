#ECS HW 3- Part 2
#Jiss Xavier, 916427256

#Limitations: Approximates at most one root of the function

#function that computes the approximation for the roots of the given function
def functionRootCalculator(a,b,c):
    global xCurrent
    #sets the initial value of the root that will be updated as the program runs
    xInitial = 5000000000     #sets the initial baseline value
    
    while True:
        xCurrent = (xInitial - ((((xInitial**3)+(a*(xInitial**2))+(b*xInitial)+c)) / ((3*(xInitial**2))+(2*a*xInitial)+b)))    #formula to approximate a root
        valueDiscrepancy = xInitial - xCurrent      #determines the difference between the actual value and the approximation
        acceptable = 10 ** (-10)                    #checks if the discrepency is small enough to be considered negligible
        if abs(valueDiscrepancy) < acceptable:      #if value meets criteria loop breaks and the approximation value is returned
            break
        xInitial = xCurrent                         #updates the approximation value if criteria above is not met
    return xCurrent                                 #returns the approximation

#function that checks the accuarcy of the approximation
def errorChecker(a,b,c):
    global yValueError
    yValueError = ((xCurrent**3) +  (a*(xCurrent**2)) + (b*(xCurrent)) + c)         #plugs the approximation into the given function and produces output
    return yValueError                                                              #output - 0 determines error reading, so the output is returned

def fancyPrint(w,y,z):                  #prints the expression entered as an equation with no zero values and no +- value conflicts
        global fancyFunction
    
        if w > 0:
            w_f = "+{0}x^2".format(w)
        if w < 0:
            w_f = "{0}x^2".format(w)
        if w == 0:
            w_f = ""

        if y > 0:
            y_f = "+{0}x".format(y)
        if y < 0:
            y_f = "{0}x".format(y)
        if y == 0:
            y_f = ""

        if z > 0:
            z_f = "+{0}".format(z)
        if z < 0:
            z_f = "{0}".format(z)
        if z == 0:
            z_f = ""

        
        print("The approximate solution of ", end="")           
        print("x^3{0}{1}{2}".format(w_f, y_f, z_f), end=" is: ")        #prints the approximation of the root of the function
        print("{:.7f}".format(xCurrent))

def main():

        try:

                #reads three user coefficient inputs
                userInput1 = int(input("Enter the integer coefficient of x^2: "))
                userInput2 = int(input("Enter the integer coefficient of x: "))
                userInput3 = int(input("Enter the integer constant term: "))
                
                functionRootCalculator(userInput1, userInput2, userInput3)          #runs function to find approximate root
                errorChecker(userInput1, userInput2, userInput3)                    #runs function to check the error of the approximation
                fancyPrint(userInput1, userInput2, userInput3)
                
                
                print("The error is ", end="")              #prints the approximation and its error value
                print(yValueError)


        #makes ctrl D the command to exit the program
        except EOFError:
            exit

        #catches input data type error
        except ValueError:
            print("Please enter an integer coefficient\n")

        #catches zero division error
        except ZeroDivisionError:
            print("The coefficients you have entered cause a zero division error when computing for the root.\n") 


        #catches all other errors
        except:
            print("Please enter an integer coefficient\n")

#runs the main loop
main()
