#include <stdio.h>
#include <stdlib.h>
#include "removecode.h"
#include "comment_sm.h"



void buffer_to_file(FILE * buffer, char * tmpfilename) {
    FILE * tmpfile = fopen(tmpfilename, "w");
    char c;
    if(tmpfile != NULL) {
        while((c = fgetc(buffer)) != EOF) {
            fputc(c, tmpfile);
        }
        fclose(tmpfile);
    }else{
        puts("error: can\'t open file.");
        exit(EXIT_FAILURE);
    }

    
}

FILE * open_iofile(const char * filename, int io) {
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

            case ISESCAPEDCHAR:
            case ISSTRING:
            case OUTSIDECOMMENT: //if we are outside of comments
                wasInsideCandidate = 0; //reinnitialize previous inside candidate state
                if(wasOutsideCandidate){ //if the previous state was OUTSIDECANDIDATE
                    fseek(f, -2, SEEK_CUR); //move cursor 2 chars back  
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
                    fseek(f, -2, SEEK_CUR); //take cursor 2 chars back
                    
                    cc = fgetc(f); //read previously omitTed char
                    fputc(cc, nf); //write it
                    fseek(f, 1, SEEK_CUR); //move the cursor one char (c)
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
            case ISLINECONTINUATION: //if the cursor is pointing on a line continuation or a backslash in general
                fputc(c, nf); //write c
                break;
            //no default case (enum)



        }

        
    }




}