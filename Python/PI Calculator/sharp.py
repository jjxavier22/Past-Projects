#Computing and Printing Improved Approximations of Pi

#Initializing the value for pi at 0 to which resulting values from the formula
#for pi shown below is added on to.

piTotal = 0

#loop that runs 50 times acting as a sigma sign by implementing the summation of
#new found  values to the existing value of pi
for i in range (0,51):
    
    #formula to find  pi
    piValue = (2* (-1)**i * 3**(1/2 - i)) / (2*i +1)
    
    #new found values are added to the existing value of pi increasing accuaracy
    piTotal = piTotal + piValue
    
    #condition to ensure every  5th term  of pi is printed
    if(i%5 == 0 and i != 0):
        print("After" , i , "terms, the approximation is " , piTotal)



#The calculation for pi becomes redundant or negliable after the 30th term
#since it exceeds the bits of the output meaning the change occurs beyond
#the last decimal value printed and therefore isn't visible to the user.
 
