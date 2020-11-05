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

void removeCode(char *filename, char *newfilename) {

    /**
     * 
     * Function that does all the io
     * reads filename
     * writes to newfilename
     * 
    */
    FILE *f = NULL; //pointer on filename
    FILE *nf = NULL; //pointer on newfilename
    char c, cc; //variables that hold characters for testing and writing
    enum cursorState cs = OUTSIDECOMMENT; //initialise state of cursor to outside comment.. entry state
    int wasInsideCandidate = 0; //holds previous insidecandidate state
    int wasOutsideCandidate = 0; //holds previous outsidecomment state


    if((f = fopen(filename, "r"))) { //if filename is openned for reading succesfully

        if((nf = fopen(newfilename, "w"))){ // if newfilename is openned for writing successfully

            while((c=fgetc(f)) != EOF) { //read characters one at a time from filename

                setCursorState(&cs, c); //set the cursor state for the current character

                if(cs==OUTSIDECOMMENT) { //if we are outside of comments
                    
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
                }else if (cs==INSIDECOMMENT || cs==INSIDELINECOMMENT){ //if we are inside a comment whatever it's type
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
                }else if(cs==INSIDECANDIDATE) wasInsideCandidate=1; //if the cursor is pointing on a candidate to a comment start save that state 
                else if(cs==OUTSIDECANDIDATE) wasOutsideCandidate = 1; //if the cursor is pointing on a candidate to a comment end save that state 
            }

            fclose(nf); //close newfilename
        }
        else{ //error handling for opening for reading problems (ex: permissions)
            puts("Error: couldn\'t open file for writing.");
            printf("file: %s\n", newfilename);
            exit(EXIT_FAILURE);
        }

        fclose(f); //close filename

    }
    else{ //error handling for opening for reading problems (ex: permissions)
        puts("Error: couldn\'t open file for reading.");
        printf("file: %s\n", filename);

        exit(EXIT_FAILURE);
    }


}

void parse_args(int argc, char *argv[], char** filename, char** newfilename){

    /**
     * Parses arguments and alters filename and newfilename
     * 
     * 
    */
    switch(argc) {
        case 1:  //if only on arg is suplied (executable name)
            // handle error
            puts("Error: Please specify a file"); 
            printhelp();
            exit(EXIT_FAILURE);
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

    removeCode(filename, newfilename); //remove code
    
    //Garbage Collection
    if(argc==2 && newfilename!=NULL) free(newfilename);
    return 0;
}