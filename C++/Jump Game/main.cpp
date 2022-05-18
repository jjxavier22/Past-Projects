#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "vectorPrinting.h"

//reads off the command line
int main(int argc, char** argv){
    //any vector with one element can not have a solution
    if(argc < 2){
        std::cout << "There is no solution to the given game." << std::endl;
    }

    //if multiple elements are found then the vector is tested for a solution
    else{

        int index = 0;      //index variable that helps track the solution

        std::vector <int> solutionVector;      //vector in which the indexes of the solution are stored, it begins empty

        bool possibleSolution = true;          //bool variable that stays true if a possible solution is possible and turns false when no solution is found


        //vector that takes the arguments provided and stores them to be used to find the shortest jump solution
        std::vector <int> gameVector(argc-1);//
        for (int i = 1; i < argc; ++i){
            gameVector[i-1] = std::stoi(argv[i]);
        }


        while (index != gameVector.size() - 1)      //checks to see if the last index has been reached
        {
            solutionVector.push_back(index);        //pushes the indexes of the jumps made on the path to the solution

            //accounts for no possible solution if no argument is passed
            if(gameVector[index] == 0)
            {
                std::cout << "There is no solution to the given game."<< std::endl;
                possibleSolution = false;
                break;
            }

            //checks whether the solution can directly be found jumping right
            else if(gameVector[index] + index + gameVector[gameVector[index]+ index] == (gameVector.size() - 1))
            {
                index = gameVector[index]+ index;
                solutionVector.push_back(index);
                index = gameVector[index] + index;
            }

            //checks if the index on the left has already been to before if not we go there
            else if(std::find(solutionVector.begin(), solutionVector.end(), index - gameVector[index]) != solutionVector.end() )
            {
                index = gameVector[index] + index;
            }

            // checks if default jump to the left can be made
            else if(index - gameVector[index] <= 0)
            {
                index = gameVector[index]+ index;
            }

            //if the values after a jump on the left and right are identical it checks to see if we have been to either index before
            else if(gameVector[gameVector[index]+ index] == gameVector[index - gameVector[index]] && std::find(solutionVector.begin(), solutionVector.end(), index + gameVector[index]) == solutionVector.end())
            {
                index = gameVector[index] + index;
            }

            //defaults to jumping left if no if statements are satisfied
            else
            {
                index = index - gameVector[index];
            }
        }
        solutionVector.push_back(index);     //pushes back 0 as solution if one argument is passed.

        //if a possible solution is found the path of the jumps are printed, the solution vector
        if(possibleSolution == true)
        {
            printVector(solutionVector);        //function that prints out the solution set of the given game if possible
        }
    }

    return 0;
}

//Assistance from CS tutor Max & Daniel at CSIF