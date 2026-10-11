#OS Assignment 02: Re-engineering the ls utility

##Student
Name: M.ZAin Shahzad
Roll number:BSDSF24M040 
Github username:zainshahzad417-dot

##Current Version
Current Version: v1.5.0.


##Description
A C implementation of a basic Unix ls utility.
It lists visible directory entries,one name per line.
It supports the current directory or multiple directory arguments.
Additional feature will be implemented incrementally.

##Build
make

##Run
./bin/ls
./bin/ls /etc
./bin/ls /etc /tmp

##Clean
make clean

##Acknowledgement
The starter code was provided by the instructor:
https://github.com/arifpucit/OS-Codes/tree/mainProgramming-Assignments/PA-02

Original file:lsv1.0.0.c
Copied to:src/ls-v1.0.0.c
 
## Supported Features
- Basic directory listing.
- Long listing with -l.
- Multiple directory arguments.
- Symbolic link destinations in long listings.

## Usage
Build: make
Basic listing: ./bin/ls
Long listing: ./bin/ls -l
Another directory: ./bin/ls -l /etc
Multiple directories: ./bin/ls -l /etc /tmp
- Default down-then-across column display.
- Automatic terminal-width detection with an 80-column fallback.


- Horizontal display with -x.
- The last -l or -x option selects the display mode.

Horizontal listing: ./bin/ls -x
Horizontal listing of another directory: ./bin/ls -x /etc


- Alphabetical sorting in every display mode using qsort().
- Case-sensitive filename comparison using strcmp().


- File-type colors in all display modes.
- Colors enabled for terminal output.
- Plain text for piped or redirected output.
