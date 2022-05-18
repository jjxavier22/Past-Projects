#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
  int fd;

    // see if the user passed in an argument
    // from Professor's source code
    if (argc == 1) {
      // it's already open
      fd = STDIN_FILENO;
      exit(0);
    }


    else {
      //open 1 or more files if passed
      for(int i=1; i <= argc-1; i++){
        fd = open(argv[i], O_RDONLY);
        //error check if file can be opened
        if (fd < 0) {
          cout << "wcat: cannot open file" << endl;
          exit(1);
        }

        char buffer[4096];
        int bytesRead = 0;
        int ret;

        //read  in file 4096 bytes at a time (Professor's code)
        while ((ret = read(fd, buffer, 4096)) > 0) {
          bytesRead += ret;
          //write out the contents of the file being read in
          write(STDOUT_FILENO, buffer, bytesRead);
          bytesRead = 0;
        }
        
        //close the file
        if (argc != 1) {
          close(fd);
        }
        //reset
        ret = 0;
      }
    }

  return 0;
}