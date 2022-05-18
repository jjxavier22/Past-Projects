#include <iostream>
#include <string>
#include "gameSimulation.h"
#include <random>


int main(int argc, char** argv) {
    //int seed= time(null);
    //int count= 3;
    int seed = std::stoi(argv[1]);      //finding the seed and count off the command line
    int count = argc;


    std::minstd_rand rng(seed);         //initializing the random # generator with the argument received for seed from the command line
    std::string choice;
    bool game = true;

    while(game == true){                //while loop that runs till the exit is executed when the user enters no
        std::string userChoice;
        readingInput(userChoice);
        singleCaseConverter(userChoice);        //functions to read in the user's input and check whether it is valid
        inputChecker(userChoice);

        int computerNumberPassed;
        std::uniform_int_distribution<> int_dis(0, 2);
        computerNumberPassed = int_dis(rng);            //creates a random number between 0 and 2
        std::string computerChoice = computerMove(computerNumberPassed);        //the random number is passed and assigned to the corresponding computer move


        if(gameOutcome(userChoice, computerChoice)== true){     //if the game ties the while loop runs again and the game repeats
            continue;
        }
        else{
            bool continuationChoice = true;

            while(continuationChoice == true)               //if someone wins the user is prompted with the choice to continue
            {
                std::cout << "Would you like to replay the game?"<< std::endl;
                std::cout << "Enter (Y)es or (N)o: ";
                getline (std::cin,choice);
                singleCaseConverter(choice);
                if(choice == "y"|| choice == "yes" || choice == "(y)es") {          //if user enters yes the game begins again
                    break;
                }
                else if(choice == "n"|| choice == "no" || choice == "(n)o"){        //if user enters no the game and programs exits
                    exit(0);
                }

            }           //if the user enters an invalid input to continue, they are reprompted
        }
    }
}
