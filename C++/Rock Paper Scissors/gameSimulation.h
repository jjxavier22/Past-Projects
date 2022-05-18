#include <iostream>
#include <string>
// Created by Jiss Xavier on 2019-04-17.
//

#ifndef UNTITLED_FUNCTIONS_H
#define UNTITLED_FUNCTIONS_H

#endif //UNTITLED_FUNCTIONS_H

//.h file that declares all functions

void readingInput(std::string& userInput);      //function that gets user input
void singleCaseConverter(std::string& userInput);   //converts the input to lowercase making for easier comparisons
void inputChecker(std::string& userInput);      //checks if the input is valid
bool gameOutcome(std::string& userChoice, std::string computerChoice);  //runs the game and returns true or false based on the result
std::string computerMove(int ComputerNumberPassed); //takes in the random # generated and assigns corresponding move and returns the move
std::string ltrim(std::string& userInput);      //trims white space to the left
std::string rtrim(std::string& userInput);      //trims white space to the right