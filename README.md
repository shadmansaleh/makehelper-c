Makehelper is a small utility for genarating
simple Makefiles.

It is mainly for small projects where you are
using a few files and all are going to get
complied to a single binary.  And you don't feel
like doing 

    gcc 1.c 2.c 3.c 4.c -o out

all the time Nor do you want to write a build
script for it .  Plus theres no point in compiling
the files that haven't been changed.

If you are writting in c/c++ you can just use
this. 

    makehelper -u -o program_name

if you use -u makehelper will search for c files
in your directory and subderectories and create a
Makefile with default flags to complie a binary
named programe_name

It allows you to specify all the flags as
commandline arguments checkout    

    makehelper -h

By defalut it uses clang.

If you wana change The default flags they are in
the main.c :)
