//
// Created by Jiss Xavier on 2019-04-29.
//

#include "vectorPrinting.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

//function to print the indexes pushed into the solution vector
void printVector(std::vector <int> solutionVector){
    std::cout << "The solution is: {";
    for(int i = 0; i < (solutionVector.size() - 1 ); i++)
    {
        std::cout << solutionVector[i] << ',';
    }
    std::cout << solutionVector[solutionVector.size() - 1] ;
    std::cout << "}";
}