#Assignment 02 Report 

##Version v1.0.0:Project Setup

##Implementation

I created the src,bin,obj and man directories.
I copy the instructor starter code into src/ls-v1.0.0.c
I created a Makefile to the compile and link the program


##Build Process
GCC uses -c to compile the source into obj/ls.o
GCC then links the object file into bin/ls
THe -o option specifies the output filename.
make the clean removes the generated object files and the executables.

##Directory Operations
opendir() open a directory
readdir() read entries from stream
closedir() closes stream
The starter skips entries whose names begin with dot.

##Verifies tests
make:Built successfully.
./bin/ls:Listed project entries one per line
./bin/ls/ etc:Listed visible entries in /etc

##Multiple directory test
Record the result of ./bin/ls /etc /tmp here

##Remaining work
Long listing , column display , horizontal display, alphabetical sorting , colors, recursive listing , and the cirresponding report explanation

##Required resources 

Add the mandatory video viewing notes and exact teacher report question

##Test results
- Compilation with -Wall and -Wextra: passed without warnings.
- Basic listing: passed.
- Long listing of the project directory: passed.
- Long listing of /etc: passed.
- Multiple-directory listing: passed.
- File permissions and symbolic-link output: matched Ubuntu ls.


