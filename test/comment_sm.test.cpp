#define CATCH_CONFIG_MAIN

#include "../comment_sm.h" //must be here to be taken into consideration before creating the main function by catch2
#include <iostream>
#include <cstdlib> 

using namespace std;

#define MMAX 128

char r = (char ) rand() % MMAX; 

#include "catch2/catch.hpp"



enum cursorState state;

TEST_CASE( "Random character is in ascii (0-127)", "[statemachine]" ) {

    REQUIRE( r >= 0  );
    REQUIRE( r < MMAX  );
}

//positive cases

TEST_CASE( "State Machine detects comment candidates when outside comment", "[statemachine]" ) {

    state = OUTSIDECOMMENT;

    setCursorState(&state, '/');

    REQUIRE( state == INSIDECANDIDATE );
}

TEST_CASE( "State Machine detects inline comment when candidate", "[statemachine]" ) {
    
    state = INSIDECANDIDATE;

    setCursorState(&state, '/');

    REQUIRE( state == INSIDELINECOMMENT );
}


TEST_CASE( "State Machine detects multiline comment when candidate", "[statemachine]" ) {
    
    state = INSIDECANDIDATE;

    setCursorState(&state, '*');

    REQUIRE( state == INSIDECOMMENT );
}

TEST_CASE( "State Machine detects outside inline comment when inside comment", "[statemachine]" ) {
    state = INSIDELINECOMMENT;

    setCursorState(&state, '\n');

    REQUIRE( state == OUTSIDECOMMENT );
}

TEST_CASE( "State Machine detects outside multiline comment candidates when inside comment", "[statemachine]" ) {
    state = INSIDECOMMENT;

    setCursorState(&state, '*');

    REQUIRE( state == OUTSIDECANDIDATE );
}

TEST_CASE( "State Machine detects outside multiline comment when candidate", "[statemachine]" ) {
    state = OUTSIDECANDIDATE;

    setCursorState(&state, '/');

    REQUIRE( state == OUTSIDECOMMENT );
}

//negative cases

TEST_CASE( "State Machine doesn't detect comment candidates when outside comment", "[statemachine]" ) {

    state = OUTSIDECOMMENT;
    if(r == '/') ++r%=MMAX;
    setCursorState(&state, r);

    REQUIRE( state == OUTSIDECOMMENT );
}

TEST_CASE( "State Machine doesn't detect inline comment when candidate", "[statemachine]" ) {
    
    state = INSIDECANDIDATE;
    if(r == '/' || r == '*') ++r%=MMAX;
    setCursorState(&state, r);

    REQUIRE( state == OUTSIDECOMMENT );
}


TEST_CASE( "State Machine doesn't detect multiline comment when candidate", "[statemachine]" ) {
    
    state = INSIDECANDIDATE;

    if(r == '/' || r == '*') ++r%=MMAX;
    setCursorState(&state, r);

    REQUIRE( state == OUTSIDECOMMENT );
}

TEST_CASE( "State Machine doesn't detect outside inline comment when inside comment", "[statemachine]" ) {
    state = INSIDELINECOMMENT;
    if(r == '\n') ++r%=MMAX;
    setCursorState(&state, r);

    REQUIRE( state == INSIDELINECOMMENT );
}

TEST_CASE( "State Machine doesn't detect outside multiline comment candidates when inside comment", "[statemachine]" ) {
    state = INSIDECOMMENT;
    if(r == '*') ++r%=MMAX;
    setCursorState(&state, r);

    REQUIRE( state == INSIDECOMMENT );
}

TEST_CASE( "State Machine doesn't detect outside multiline comment when candidate", "[statemachine]" ) {
    state = OUTSIDECANDIDATE;
    if(r == '/') ++r%=MMAX;
    setCursorState(&state, r);

    REQUIRE( state == INSIDECOMMENT );
}