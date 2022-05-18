#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]) {
  int fd;

  // see if the user passed in an argument
  if (argc == 1) {
    // it's already open
    //fd = STDIN_FILENO;
    cout << "wgrep: searchterm [file ...]" << endl;
    exit(1);
  }

    
  // read from standard input if argc == 2
  if (argc == 2){
    fd = STDIN_FILENO; 
    if (fd < 0) {
      cout << "wgrep: cannot open file" << endl;
      exit(1);
    }  
  }

  //otherwise open the file passed
  else {
    fd = open(argv[2], O_RDONLY);
    if (fd < 0) {
      cout << "wgrep: cannot open file" << endl;
      exit(1);
    }
  }
  

  char buffer[100000];
  //stores the contents of the file read in
  string stringBuffer;
  int bytesRead = 0;
  int bytesFinal = 0;
  int ret;
        
  //reads the file in at 1000000 bytes at a time
  while ((ret = read(fd, buffer, 100000)) > 0) {

    string matchedLine;
    string matchFinal = "";
        
          
    bytesRead += ret;
          
    //contents of file appended to the string    
    stringBuffer.append(buffer, bytesRead);

    int j = 0;
    //while loop that goes checking for matches
    while ((int)stringBuffer.find(argv[1],j) != -1){
      int charNumber = stringBuffer.find(argv[1],j);
      
      //match is found
      if(charNumber != -1){
        int i = charNumber;
        //if match is found, it counter goes to the beggining of the line
        while(stringBuffer[i-1] != '\n' && i != 0){
          i--;
        }
        
        int length = stringBuffer.length();
        //the contents of the line containg the key word is passed to the string variable
        while(stringBuffer[i] != '\n' && i != length){
          matchedLine.push_back(stringBuffer[i]);
          i++;
        }

        //adjusting the counter so lines that contain the word twice aren't printted twice           
        j = i;
        
        //Each line is pushed into the final string one by one
        bool var = true;
        if(var){
          matchFinal.append(matchedLine);
          matchFinal.push_back('\n');
          matchedLine.clear();
        }
        
        else {
          matchedLine.clear();
        }

        bytesRead = matchFinal.length();
        bytesFinal = matchFinal.length();
                    
      }
    }

    //buffer is cleared
    memset(buffer, 0, 100000);
    //final string is copied into the buffer
    strcpy(buffer, matchFinal.c_str());
    bytesRead = 0;
  }
  
  //final resut is written out
  write(STDOUT_FILENO, buffer, bytesFinal);

  if (argc != 1) {
    close(fd);
  }
  
  ret = 0;
  return 0;
}