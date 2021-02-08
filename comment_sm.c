#include "comment_sm.h"


void setCursorState(enum cursorState *s, char cursor){
    /**
     * State Machine for both inline and multiline comments
     * takes cursor (a character) and previous state to set the next state
     * 
     * This function implements the state machine diagram
     *  illustrated in "diagram.jpeg"
     * 
     * */
    switch(*s) {
        case INSIDECOMMENT: //if inside comment 
            if(cursor=='*') *s = OUTSIDECANDIDATE; //and found a '*' it could be the end of multiline comment
            break;
        case INSIDELINECOMMENT: //if inside line comment
            if(cursor=='\n') *s = OUTSIDECOMMENT; //and found a line break the comment has ended
            else if(cursor == '\\') *s = ISLINECONTINUATION; //or found a line continuation
            break;
        case OUTSIDECOMMENT: //if not in a comment
            if(cursor == '\"') *s = ISSTRING;
            else if(cursor == '/') *s = INSIDECANDIDATE; //and found '/' it could be the beginning of a comment
            break;
        case INSIDECANDIDATE: //if it could be a comment
            if(cursor == '*') *s = INSIDECOMMENT; //and found '*' its a multiline comment
            else if(cursor == '/') *s = INSIDELINECOMMENT; //if not multiline comment and found '/' its and inline one
            else *s = OUTSIDECOMMENT; //if non of the above its just a '/' so we're back to not a comment
            break;
        case OUTSIDECANDIDATE://if it could be the end of the comment
            if(cursor == '/') *s = OUTSIDECOMMENT; //and found '/' it's definitly he end of the comment
            else *s = INSIDECOMMENT; //if no '/' found then its just a '*'
        case ISLINECONTINUATION: //if the last cursor pointed on a line continuation inside a line comment
            if(cursor != '\\') *s = INSIDELINECOMMENT; // whatever the curent character other than another backslash\
                                                         is we are still inside a line comment
            break;
        case ISSTRING:
            if(cursor == '\\') *s = ISESCAPEDCHAR;
            else if(cursor == '\"') *s = OUTSIDECOMMENT;
            break;
        case ISESCAPEDCHAR:
            *s = ISSTRING; //gotta test for escape sequences but we're dealing with comments\
                            we don't care if the string literal is valid or not. (but still, it should be done anyways)
        //No default case we're switching on an enum :3
    }
}