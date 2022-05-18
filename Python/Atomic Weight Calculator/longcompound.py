#ECS Extra Credit 4
#Jiss Xavier, 916427256

#Limitations: The program is not smart enough to determine if certain elements can form real compounds like H4O but it would still calculate the atomic weight

import re   #imports the function used to analyze and break up the input

def readDictionary():   #function that  imports the file atomic_weights.txt and stores the data in a dictionary called to elementDict which will later be used to cross refrence
    global elementDict
    global nameDict
    
    elementDict = {}
    nameDict = {}
    atomicMassFile = open("atomic_weights.txt", "r")
    for line in atomicMassFile.readlines():
        line = line.split('\t')   #splits each column of the line into individual pieces  making it easier to find atomic mass and symbol
        atomicWeight  = line[0]
        atomicSymbol = line[1]
        elementName = line[2].strip('\n') #reads in the third column as the element names
       
        elementDict[atomicSymbol] = atomicWeight    #creates dictionary containing both atomic symbol and mass
        nameDict[atomicSymbol] = elementName        #creates another dictionary containing both atomic symbol and name
    

def readingUserInput(): #function that reads the user input and splits it into parts as elements of a list 
    
    global elementSymbols, readCompound
    global components, elementalComposition
    readCompound = input('Chemical Composition: ')  #reads the user's input
    elementSymbols = re.findall(r'[A-Z][a-z]*' '|' r'\d{1,2}' '|' r'-\d{1,2}' '|' r'[a-z][a-z]*', readCompound) #analyzes the userinput storing the elements and the coeffiecents as elements of a list called elementSymbols
    components = [elementSymbols for elementSymbols in elementSymbols if not elementSymbols.isdigit()]  #catches invaliid user input by checking if inputs are valid element symbols
    elementalComposition = []       #creates a list to store the names of the elements in the compound
    for i in components:
        if i.isdigit() == False and i not in elementDict:
            continue
        else:
            elementalComposition.append(nameDict[i])    #adds element names to the list as the symbols are succesfully matched to the dictionary
    
 
def calculatingAtomicMass():    #function that computes the atomic weight of the entered compound
    totalMass = 0
    for i in range(0, len(elementSymbols)):     #runs a for loop going through the elements of the list containg elements and coeffiecents

            if elementSymbols[i].isdigit() == False and elementSymbols[i] not in elementDict:   #If the list item is not a coeffiecent or a real element, the user is prompted to try again
                        print('Please enter a chemically valid compound.')
                        return
            elif (elementSymbols[i] in elementDict):    #if the element is in the dictionary its molar mass is pulled and assigned to that element
                molarMass= elementDict[elementSymbols[i]]


                if (i != len(elementSymbols) -1):   #checks if the last element of the elementSymbols list is the one being not checked

                    if elementSymbols[i+1].isdigit() == True:    # looks at the element to the right and checks if it is a coeffecieint
                        totalMass = totalMass + (float(molarMass) * (int(elementSymbols[i+1])))     #the molar mass is multiplied by the coeffiecent and added to total mass
                    


                    else:   #if the element to the right is not a coeffiecent but another element then it is multiplied by 1 and added to the total mass
                        totalMass = (totalMass + float(molarMass))
            
                else:
                    totalMass = (totalMass + float(molarMass))  #for the last element of the list, if it is just an element then it is multiplied by 1 and added to total mass


    if(totalMass <=0):  #No chemical compound has a mass of 0 or less so an error message is printed
        print('Please enter a chemically valid compound.')
        
    else:          #prints the atomic weight of the compound
        print("The atomic weight of", readCompound, "is", end=" ")
        print("{:.2f}".format(totalMass))

    #takes care of the printing of the element names when there is one element present in the compound
    if len(elementalComposition) == 1:
        print('The element that makes up the compound is', elementalComposition[0])

    #prints names of two elements with no commas obeying established grammar rules
    elif len(elementalComposition) == 2:
        print('The 2 elements that make up the compound are', elementalComposition[0], 'and', elementalComposition[1])

    #prints names of multiple elements with corresponding commas obeying established grammar rules
    elif len(elementalComposition) > 2:
        finalElement = elementalComposition.pop(len(elementalComposition)-1)        #stores the last element present in order to print it last
        print('The elements that make up the compound are', ', '.join(elementalComposition)+ ', and', finalElement)
    
        

def main():
    readDictionary()    #runs the function that reads the file and makes a dictionary

    while(True):    #makes the program repeat endlessly until the program is terminated
        try:
            readingUserInput()
            calculatingAtomicMass()
        except EOFError:    #Makes Ctrl-D an exit operation
            exit
            return False
        except KeyboardInterrupt:   #Makes Ctrl-C an exit operation
            exit
            return False
        except ValueError:  #Catches ValueError and prints an error prompt
            print('Please enter a chemically valid compound.')
    

main()
