#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<string.h>
#include "removecode.h"

void printhelp(){
    /**
     * 
     * Prints help
    */
    puts("How to use:");
    puts("$ ./ccommentator filename [newfilename]");
}

void parse_args(int argc, char *argv[], char** filename, char** newfilename){

    /**
     * Parses arguments and alters filename and newfilename
     * 
     * 
    */
    switch(argc) {
        case 1:  //if only one arg is suplied (executable name) 
            // use standard io 

            //use filename as a flag to communicate the use of std io
            *filename = (char*) malloc((strlen("std")+1)*sizeof(char));

            strcpy(*filename, "std");
            break;
        case 2: //if one extra argument is suplied (missing newfilename)
            *filename = *(argv+1); //point to it using filename
             //allocate memory for newfilename as big as the size of filename plus a "comments." copied to the beginning
            *newfilename = (char*)malloc((strlen(*filename)+strlen("comments."))*sizeof(char));
            strcpy(*newfilename, "comments."); //put comments. in the beginning
            strcat(*newfilename, *filename); //add filename after comment.
            break;
        case 3: //if 2 extra arguments are suplied
            //just point to them
            *filename = *(argv+1);
            *newfilename = *(argv+2);
            break;
        default: //if more arguments -> too many arguments and print help
            puts("Error: too many arguments.");
            printhelp();
            exit(EXIT_FAILURE);


    }
}

int main(int argc, char *argv[]){

    srand(time(NULL));

    int random = rand();

    char randomname[30];

    sprintf(randomname, "tmp%d", random);
   

    char *filename = NULL, *newfilename = NULL;

    parse_args(argc, argv, &filename, &newfilename); //parse command line arguments

    if(strcmp(filename, "std")==0){
        buffer_to_file(stdin, randomname);
        removeCode(open_iofile(randomname, 0), stdout);
        remove(randomname);
    }
    else
        removeCode(open_iofile(filename, 0), open_iofile(newfilename, 1)); //remove code 
    
    //Garbage Collection
    if(argc==2 && newfilename!=NULL) free(newfilename);
    if(argc==2 && filename!=NULL) free(filename);
    //no need to collect the files since they only exist inside removeCode.


    return 0;
}