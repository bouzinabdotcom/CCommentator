
enum cursorState {
    INSIDECOMMENT, OUTSIDECOMMENT, INSIDECANDIDATE, OUTSIDECANDIDATE, INSIDELINECOMMENT, ISLINECONTINUATION
}; //enum that takes one of the state values at time

void setCursorState(enum cursorState*, char);