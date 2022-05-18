//
// Created by Jiss Xavier on 2019-04-17.
//
#include <iostream>
#include <string>
#include "gameSimulation.h"
#include <random>

//reads in the input
void readingInput(std::string& userInput){
    std::cout << "Enter (R)ock, (P)aper, or (S)cissors for your move: " ;
    getline (std::cin,userInput);


}

//trims the white space before and after the input and converts the input to lowercase
void singleCaseConverter(std::string& userInput){
    userInput = ltrim(userInput);
    userInput = rtrim(userInput);
    for (int i=0;i<userInput.length();i++){
        userInput[i]=tolower(userInput[i]);
    }

}

//checks to see if the input is valid or not and reprompts otherwise
void inputChecker(std::string& userInput){
    while (userInput != "rock" && userInput != "r" && userInput != "(r)ock"
    && userInput != "paper" && userInput != "p" && userInput != "(p)aper"
    && userInput != "s" && userInput != "scissors" && userInput != "(s)cissors" ) {
        std::cout << "Enter (R)ock, (P)aper, or (S)cissors for your move: ";
        getline(std::cin, userInput);
        for (int i=0;i<userInput.length();i++){
            userInput[i]=tolower(userInput[i]);
        }
    }

}



