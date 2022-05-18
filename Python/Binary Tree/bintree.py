#ECS HW 5
#Jiss Xavier, 916427256

import re   #imports the function needed to break up the txt file into specific words

#initializes the class and its attributes
class Node:
    def __init__(self, word=""):    #initial with parameters
        self.left = None        #set left node to empty
        self.right = None       #set right node to empty
        self.word = word        #word to be added to tree
        self.count = 1          #establihes variable for counter
        
    #function that joins the number of occurances next to the word to be used when printing
    def wordandCounter(self):
        result = (self.word + "(" + str(self.count) + ")")
        return result

    #function that arranges the words of the txt file into a binary tree
    def inOrder(self,nextWord):
        if self.word == nextWord:       #if a word that has already been processed is run the counter is incremented
            self.count += 1
        elif self.word == "":           #moves to next word to be added
            self.word = nextWord
        elif self.word > nextWord:      #if word is less than the node it goes to the left and if no node is there the word is instantiated as an instance of the Node class
            if self.left == None:       #checks if left is empty with no node
                self.left = Node(nextWord)      #if no node present the word is instantiated and added to the binary tree
            else:
                self.left.inOrder(nextWord)     #if a node is already present to the left the function recurses and continues till an empty spot is found

        if self.word < nextWord:
            if self.right == None:          #checks if right is empty with no node
                self.right = Node(nextWord) #if no node present the word is instantiated and added to the binary tree

            else:
                self.right.inOrder(nextWord)     #if a node is already present to the right the function recurses and continues till an empty spot is found

#prints the binary tree as an output
def treePrinting(root, wordLevel):  #reads in the node (word) and the level counter
    if root == None:
        return
    else:
        treePrinting(root.left, wordLevel+1)        #recurses treePrinting function for left nodes
        print(wordLevel*"  "  + root.wordandCounter())      #multiplies the level counter with a space to get the corresponding spacing of the binary tree and calls function need to add the counter value
        treePrinting(root.right, wordLevel+1)       #recurses treePrinting function for right nodes

#splits the file being read in into indvidual trees to be added to the binary tree
def fileProcessor(fileName):
    root = Node()       #sets the root as the first node
    file = open(fileName)       #opens the read in file
    for text in file:
        text = re.sub("[^\w]+", " ", text)      #strips the words by spacing and punctation using re and a for loop
        wordList = text.split()
        for i in wordList:
            i = i.strip()           #words are seperated
            root.inOrder(i)         #words are run through the binary tree process function
    file.close()                    #file is closed
    return root

def main():
    
    fileInput= input("Please enter the file to be arranged: ")      #reads in user input for file name
    try:
        root = fileProcessor(fileInput)     #the read in file is opened and split using fileProcessor function
        treePrinting(root,0)                #feeds root and sets 0 as the counter for level as parameters of the treePrinting function

    except FileNotFoundError:       #ensures file entered is valid
        print("The entered file doesn't exist. \nTry entering the path of the file and try again.")
        
    except KeyboardInterrupt:   #catches ctrl c to stop program
        print("\nYou cancelled the program.")
    except:                     #catches all other errors
        print("Invalid Input, please try again")

#main loop is executed
main()
                            
    
    
