//Jiss Xavier
//916427256

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

//function that seperates the > and & with spaces so it can be processed easier
string initialLineParser(string readLine){
  unsigned int length= readLine.length();

  //loops the line read in and adds a space before and after a '>' if found
  for(unsigned int idx = 0; idx < length; idx++){
    if(readLine[idx] == '>'){
      readLine.insert(idx, " ");
      readLine.insert(idx+2 , " ");
      length += 2;
      idx += 2;
    }
    //loops the line read in and adds a space before and after a '&' if found
    else if(readLine[idx] == '&'){
      
      readLine.insert(idx, " ");
      readLine.insert(idx+2 , " ");
      length += 2;
      idx += 2;
    }
  }

  //returns the altered string
  return readLine;
}


//This function runs the linux shell commands, reads in the commannd array, the path string, and i which holds the number of inputs
int runCommand(char *commandArray[], string path, int  i){
  pid_t pid; //, wpid;
  int status;
  int redirectionIndex = 0;
  int saved_stdout;

  //saves the value of stdout to be used to restore stdout after redirection
  saved_stdout = dup(1);
  
  //forks and creates a new child process to execute the coommand
  pid = fork();
  char error_message[30] = "An error has occurred\n";

  //char array in which the path of the executable is store so it can be passed to execv
  char tempForPath[4096];
  strcpy(tempForPath, path.c_str());

  //sets the index after the last input to NULL
  commandArray[i-1] = nullptr;

  //loops through the command checking if redirection is specified
  for(int edx=0; edx < i-1; edx++){
    if(strcmp(commandArray[edx], ">") == 0){
      //store the index of the '>'
      redirectionIndex = edx;
    }
  }

  //when a redirection command call is made
  if(redirectionIndex != 0){
    char *filePath[4096];
    //finds the path of the file right after the '>'
    filePath[0] = commandArray[redirectionIndex+1];
    //sets '>' and filepath to null leaving only the command
    commandArray[redirectionIndex+1] = nullptr;
    commandArray[redirectionIndex] = nullptr;
    //file to be written to is opened and STDOUT is replaced with the file
    int redirect = open(filePath[0], O_CREAT|O_RDWR|O_TRUNC, 0644);
    //returns an error if file can't be opened
    if(redirect == -1){
      write(STDERR_FILENO, error_message, strlen(error_message));
    }
    dup2(redirect, STDOUT_FILENO);
    //close the file
    close(redirect);
  }
  

  if (pid == 0){
    //execv command fails throw error
    if (execv((const char*)tempForPath, commandArray) == -1){ 
      write(STDERR_FILENO, error_message, strlen(error_message));
    }
    exit(1);
  } else if (pid < 0) {
    // Error forking
    write(STDERR_FILENO, error_message, strlen(error_message));
  } else {
    //no errors detected
    do {
      //restore STDOUT after a redirection command
      dup2(saved_stdout, 1);
      close(saved_stdout);
      //wait for process to complete before promting user for next input
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));

  }
  return 1;
}

//function that reads in the parallel input and passes it to runCommand to execute in parallel
 void runParallelCommand(char *commandArray[], string finalPath, string path, int  i){
    runCommand(commandArray, finalPath, i);
    int index[4096];
    int operatorCount = 0;
    
    //for loop to determine the indexes of the & and the number of &
    for(int counter=0; counter < (i-1); counter++){
      if(strcmp(commandArray[counter], "&") == 0){
        index[operatorCount] = counter;
        operatorCount++;
      }
    }

    //runs the commands in parallel using runCommand
    for(int counter=0; counter < operatorCount; counter++){
      if((index[counter])+1 < i-1){
        commandArray[0] = commandArray[(index[counter])+1];
        finalPath = path + (string)commandArray[0];
        runCommand(commandArray, finalPath, i);
      }
    }
    //*Note to Self* Parallel processes fail with redirection check redirection and runParallelCommand
}



int main(int argc, char *argv[]) {

  char error_message[30] = "An error has occurred\n";

  if(argc == 1){
    //normal shell experience
    cout << "Interactive Mode!" << endl;
  }

  else if (argc == 2) {
    //open the file containing commands that is passed in
    ifstream file(argv[1]);
    
    //file fails to open
    if (file.fail()){
      write(STDERR_FILENO, error_message, strlen(error_message));
      exit(1);
    }

    //read in file
    else {
      string readLine;
      string path[4];
      int numOfPaths = 1;
      path[0] = "/bin/";
      
      while (getline(file, readLine)) {

        readLine = initialLineParser(readLine);

        istringstream iss(readLine);
        char *commandArray[4096];
        //keeps track of number of inputs
        int i=0;
        //keeps track of which part of path contains executable
        int pathIndex = 0;
        //will hold the path of the executable
        string finalPath;
        
        do {
          string commandParts;
          // Get the word from the istringstream
          iss >> commandParts;

          //check to make sure it isn't a built in command
          if(i == 0 && (commandParts.compare("cd") != 0) && (commandParts.compare("exit") != 0) && (commandParts.compare("path") != 0) && (commandParts.compare("") != 0)){

            //iterate through paths to check where the executable is located
            for(int k=0; k < numOfPaths; k++){
              string testPath;
              //combines path and command
              testPath = path[k] + commandParts;
              char testTemp[4096];
              strcpy(testTemp, testPath.c_str());

              //if access is not found check next path index
              if(access(&(testTemp[0]), X_OK) == -1 && k != (numOfPaths-1)){
                continue;
              }

              //if no executtable path is found, error will be thrown since invalid path is set
              else if(access(&(testTemp[0]), X_OK) == -1 && k == (numOfPaths-1)){
                pathIndex = k;
              }
              //executable is found so path index is set accordingly
              else if(access(&(testTemp[0]), X_OK) == 0){
                pathIndex = k;
                break;
              }
              
            }
          }

          //append the default path and the command specified together
          if(i == 0 && (commandParts.compare("cd") != 0) && (commandParts.compare("exit") != 0) && (commandParts.compare("path") != 0) && (commandParts.compare("") != 0)){
            //puts the final path of the executable together
            finalPath = path[pathIndex] + commandParts;
          }
          
          //parsed input is converted from string to a char *[]
          char temp[4096];
          strcpy(temp, commandParts.c_str());
          char* tempPointer = strdup(temp);
          commandArray[i] = tempPointer;

          i++;
        } while (iss);
        //input is parsed





        //empty line enter then reprompt
        if(strcmp(commandArray[0], "") == 0){
          continue;
        }

        //implements the built in cd
        if(strcmp(commandArray[0], "cd") == 0){
          commandArray[i-1] = nullptr;
          //no path is passed to cd
          if(commandArray[1] == NULL){
            write(STDERR_FILENO, error_message, strlen(error_message));
          }
          //changes to specified directory
          else {
            if (chdir(commandArray[1]) != 0) {
              write(STDERR_FILENO, error_message, strlen(error_message));
            }
          } 
          
        }


        //implements built in exit function
        else if (strcmp(commandArray[0], "exit") == 0){
          commandArray[i-1] = nullptr;
          if(commandArray[1] == NULL){
            exit(0);
          }
          //if anything is specifed after exit error is prompted
          else {
            write(STDERR_FILENO, error_message, strlen(error_message));
          }

        }


        //built in path command
        else if (strcmp(commandArray[0], "path") == 0){
          //i = number of inputs + 1
          numOfPaths = 0;
          commandArray[i-1] = nullptr;

          //sets path to blank
          if(i == 2){
            path[0] = "";
          }
          //specified path is set
          else if (i > 2){
            for (int j=0; j < i-2; j++){
              path[j] = commandArray[j+1];
              numOfPaths ++;
              if(strcmp(commandArray[j+1], "bin/") != 0){
                path[j].append("/");
              }
              else if(strcmp(commandArray[j+1], "bin/") == 0){
                path[j].insert(0,"/");
              }
            }
          }
        }


        //checks if proper redirection command is specified
        else if (strcmp(commandArray[1], ">") == 0){
          commandArray[i-1] = nullptr;

          //no redirection file is specified
          if(commandArray[2] == NULL){
            write(STDERR_FILENO, error_message, strlen(error_message));
          }
          //more than file path is specified
          else if(i > 3){
            write(STDERR_FILENO, error_message, strlen(error_message));
          }
        }
        //redirection with no command
        else if (strcmp(commandArray[0], ">") == 0){
          write(STDERR_FILENO, error_message, strlen(error_message));
        }

        else if (strcmp(commandArray[0], "&") == 0){
          commandArray[i-1] = nullptr;
          continue;
        }
        
        //after all error checking and built in commands, the command is run using execv
        else {

          //checks if it is a parallel procss
          bool parallelProcess = false;
          for(int udx=0; udx < (i-1); udx++){
            if(strcmp(commandArray[udx], "&") == 0){
              parallelProcess = true;
              break;
            }
          }

        
          if(parallelProcess){
            runParallelCommand(commandArray, finalPath, path[pathIndex], i);
          }
          else {
            runCommand(commandArray, finalPath, i);
          }
          
        }
        
      }

    }
  }

  //neither bash mode or interactive mode is initialized thus shell exits
  else {
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }
  

}


