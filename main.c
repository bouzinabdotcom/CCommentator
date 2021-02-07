#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "comment_sm.h"

void printhelp(){
    /**
     * 
     * Prints help
    */
    puts("How to use:");
    puts("$ ./ccommentator filename [newfilename]");
}

FILE * open_iofile(char * filename, int io) {
    /**
     * Function that opens input or output file depending on io parameter
     * io == 0 : reading input file
     * io == 1 : writing to output file
     * if file can't be opened: stops execution
     * else it returns a pointer on it
     * */

    FILE *f = NULL; //pointer to filename
    
    if(f = fopen(filename, (io ? "w" : "r"))) //if filename is openned for reading/writing succesfully
        return f; //return pointer
    else { //error handling for opening for reading/writing problems (ex: permissions)
        printf("Error: couldn\'t open file for %s.\n", (io ? "writing" : "reading")); 
        printf("file: %s\n", filename);

        exit(EXIT_FAILURE);
    }

    
}



void removeCode(FILE * f, FILE * nf) {

    /**
     * 
     * Function that does the reading and writing 
     * if is comment do nothing
     * else write to output file
     * 
    */
    char c, cc; //variables that hold characters for testing and writing
    enum cursorState cs = OUTSIDECOMMENT; //initialise state of cursor to outside comment.. entry state
    int wasInsideCandidate = 0; //holds previous insidecandidate state
    int wasOutsideCandidate = 0; //holds previous outsidecomment state



    while((c=fgetc(f)) != EOF) { //read characters one at a time from filename

        setCursorState(&cs, c); //set the cursor state for the current character

        switch(cs){
            case OUTSIDECOMMENT: //if we are outside of comments
                wasInsideCandidate = 0; //reinnitialize previous inside candidate state
                if(wasOutsideCandidate){ //if the previous state was OUTSIDECANDIDATE
                    fseek(f, ftell(f) - 2, SEEK_SET); //move cursor 2 chars back  
                    cc = fgetc(f); //read previously omitTed char OUTSIDECANDIDATE
                    fputc(cc, nf); //write it to newfilename
                    cc = fgetc(f); //read a char == c
                    fputc(cc, nf); //write it to newfilename
                    wasOutsideCandidate = 0; //set prev state to 0
                }
                else //if it wasnt a candidate
                    if(c=='\n') //if it's a line break
                    fputc(c, nf); //write it
                    else fputc(' ', nf); //if its any other character print a space
                break;
            //if we are inside a comment whatever it's type
            case INSIDECOMMENT:
            case INSIDELINECOMMENT:
                if(wasInsideCandidate || wasOutsideCandidate){ 
                    /**
                     * in both cases where the cursor was OUTSIDECANDIDATE or INSIDECANDIDATE
                     * we need to write the previous character since it's inside a comment
                     * 
                    */
                    fseek(f, ftell(f) - 2, SEEK_SET); //take cursor 2 chars back
                    cc = fgetc(f); //read previously omitTed char
                    fputc(cc, nf); //write it
                    fseek(f, ftell(f) + 1, SEEK_SET); //move the cursor one char (c)
                    wasOutsideCandidate = 0; //reset both previous states
                    wasInsideCandidate=0;


                }
                fputc(c, nf); //write c
                break;
            case INSIDECANDIDATE:   //if the cursor is pointing on a candidate to a comment start
                wasInsideCandidate=1; // save that state 
                break;
            case OUTSIDECANDIDATE: // if the cursor is pointing on a candidate to a comment end
                wasOutsideCandidate = 1; // save that state 
                break;
            //no default case (enum)


        }
        
    }




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

   

    char *filename = NULL, *newfilename = NULL;

    parse_args(argc, argv, &filename, &newfilename); //parse command line arguments

    if(strcmp(filename, "std")==0)
        removeCode(stdin, stdout);
    
    else
        removeCode(open_iofile(filename, 0), open_iofile(newfilename, 1)); //remove code 
    
    //Garbage Collection
    if(argc==2 && newfilename!=NULL) free(newfilename);
    //no need to collect the files since they only exist inside removeCode.


    return 0;
}