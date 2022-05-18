#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    int fd;

    // see if the user passed in an argument
    if (argc == 1) {
        // it's already open
        cout << "wzip: file1 [file2 ...]" << endl;
        exit(1);
    }
    else {
        //string to store the contents of the file/files being read
        string stringBuffer;

        //int to count how many times a letter repeats
        int count = 1;

        //opens one or many files
        for(int i=1; i <= argc-1; i++){
            fd = open(argv[i], O_RDONLY);
        
            //error checking
            if (fd < 0) {
                cout << "wzip: cannot open file" << endl;
                exit(1);
            }

            char buffer[100000];
            int bytesRead = 0;
            int ret;
            
            //read in the file contents and store in a string
            while ((ret = read(fd, buffer, 100000)) > 0) {
                bytesRead += ret;
                stringBuffer.append(buffer, bytesRead);
                bytesRead = 0;
            }

            if (argc != 1) {
                close(fd);
            }
            ret = 0;
        }
            
        //iterate through file contents
        for (int i=0; i < (int)stringBuffer.length(); i++){
            //check for repeats and keep count of how many repeats
            while(stringBuffer[i] == stringBuffer[i+1]){
                count ++;
                i++;
            }
            
            //write the count into the first 4 bytes
            write(STDOUT_FILENO, &(count), 4);
            //write the letter into the last symbol
            write(STDOUT_FILENO, &(stringBuffer[i]), 1);
            
            //reset the count once a miss match is found
            count = 1;
        }   
    }

    return 0;

}