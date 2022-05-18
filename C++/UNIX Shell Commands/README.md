These C++ Programs implement a few different UNIX utilities, simple versions of commonly used commands such as "cat", "grep", "zip" and "unzip".

The program "wcat" is a simple program. Generally, it reads a file as specified by the user and prints its contents.

The second program "wgrep", a variant of the UNIX tool "grep". This tool looks through a file, line by line, trying to find a user-specified search term in the line. If a line has the word within it, the line is printed out, otherwise it is not. 

The third and fourth programs "wzip" and "wunzip" come in pairs. The type of compression used here is a simple form of compression called run-length encoding (RLE). RLE is quite simple: when you encounter n characters of the same type in a row, the compression tool wzip will turn that into the number n and a single instance of the character. "wzip" performs the compression and "wunzip" reverses the compression.