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
        cout << "wunzip: file1 [file2 ...]" << endl;
        exit(1);
    }
    //if the user passed an  argument then proceed
    else {
        //string to store the contents of the file/files being read
        string stringBuffer;

        //opening one or many files
        for(int i=1; i <= argc-1; i++){
            fd = open(argv[i], O_RDONLY);
        
            //error checking
            if (fd < 0) {
                cout << "wzip: cannot open file" << endl;
                exit(1);
            }

            char buffer[4096];
            int bytesRead = 0;
            int totalBytes;

            //read in 5 bytes at a time, then clear the string at the end
            while ((totalBytes = read(fd, buffer, 5)) > 0) {
                bytesRead += totalBytes;

                //add the first four bytes corresponding to the count to the string
                stringBuffer.append(buffer, totalBytes-1);
                //convert that to an in
                int x = ( unsigned char )(*(stringBuffer.c_str()));

                //print the letter count times thus uncompressing
                for(int f = 0; f < x; f++){
                    write(STDOUT_FILENO, &(buffer[4]), 1);
                }

                //clear the string
                stringBuffer.clear();

                //clear the buffer
                memset(buffer, 0, 4096);
                bytesRead = 0;
            }

            if (argc != 1) {
                close(fd);
            }
            totalBytes = 0;
        }
    }

    return 0;

}