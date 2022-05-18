//
// Created by Jiss Xavier on 2019-04-17.
//
#include <iostream>
#include <string>
#include "gameSimulation.h"

//function that assigns a move to the computer based on  the random number generated
std::string computerMove(int computerNumberPassed){

    std::string computerChoice;
    int computerNumber = computerNumberPassed;

    if (computerNumber == 0) {
        computerChoice = "rock";
    } else if (computerNumber == 1) {
        computerChoice = "paper";
    } else if (computerNumber == 2){
        computerChoice = "scissors";
    }
    return computerChoice;
}

//compares the user and computers move to see who wins, if its a tie true is returned and the game begins again
bool gameOutcome(std::string& userChoice, std::string computerChoice){


    if(computerChoice == "rock" && (userChoice == "rock" || userChoice == "r"|| userChoice == "(r)ock"|| userChoice == "(r)")) {
        std::cout << "The ai played rock." << std::endl;
        std::cout << "You and the AI both played rock." << std::endl;
        std::cout << "Keep playing until someone wins." << std::endl;

        return true;


    } else if (computerChoice == "rock" && (userChoice == "scissors" || userChoice == "s"|| userChoice == "(s)cissors" || userChoice == "(s)")) {
        std::cout << "The ai played rock." << std::endl;
        std::cout << "The AI wins :(" << std::endl;

        return false;

    } else if (computerChoice == "paper" && (userChoice == "paper" || userChoice == "p"|| userChoice == "(p)aper"|| userChoice == "(p)")) {
        std::cout << "The ai played paper." << std::endl;
        std::cout << "You and the AI both played paper." << std::endl;
        std::cout << "Keep playing until someone wins." << std::endl;

        return true;


    } else if (computerChoice == "paper" && (userChoice == "rock" || userChoice == "r"|| userChoice == "(r)ock"|| userChoice == "(r)")) {
        std::cout << "The ai played paper." << std::endl;
        std::cout << "The AI wins :(" << std::endl;

        return false;

    } else if (computerChoice == "scissors" && (userChoice == "scissors" || userChoice == "s" || userChoice == "(s)cissors" || userChoice == "(s)")) {
        std::cout << "The ai played scissors." << std::endl;
        std::cout << "You and the AI both played scissors." << std::endl;
        std::cout << "Keep playing until someone wins." << std::endl;

        return true;

    } else if (computerChoice == "scissors" && (userChoice == "paper" || userChoice == "p" || userChoice == "(p)aper"|| userChoice == "(p)")) {
        std::cout << "The ai played scissors." << std::endl;
        std::cout << "The AI wins :(" << std::endl;

        return false;

    } else if (computerChoice == "scissors" && (userChoice == "rock" || userChoice == "r"|| userChoice == "(r)ock"|| userChoice == "(r)")) {
        std::cout << "The ai played scissors." << std::endl;
        std::cout << "You win!" << std::endl;

        return false;
    }
    else if (computerChoice == "paper" && (userChoice == "scissors" || userChoice == "s" || userChoice == "(s)cissors" || userChoice == "(s)")) {
        std::cout << "The ai played paper." << std::endl;
        std::cout << "You win!" << std::endl;

        return false;
    }
    else if (computerChoice == "rock" && (userChoice == "paper" || userChoice == "p" || userChoice == "(p)aper"|| userChoice == "(p)")) {
        std::cout << "The ai played rock." << std::endl;
        std::cout << "You win!" << std::endl;

        return false;
    }
    return false;
}


