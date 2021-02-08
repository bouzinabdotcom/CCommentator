#define CATCH_CONFIG_MAIN

#include<stdio.h>
#include "../removecode.h"
#include<string.h>
#include<stdlib.h>

#include "catch2/catch.hpp"


char * istr = NULL, *ostr = NULL;
size_t ilen, olen;

FILE* input = NULL;
FILE* output = NULL; 

void before(const char* teststr) {
    input = open_memstream(&istr, &ilen);
    output = open_memstream(&ostr, &olen);

    fprintf(input, "%s", teststr);
    buffer_to_file(input, "tmp");
    removeCode(open_iofile("tmp", 0), output);
    remove("tmp");
    fflush(input);
    fflush(output);
}

void after() {
    istr = NULL;
    ostr = NULL;
    fclose(input);
    fclose(output);
}


//positive tests

TEST_CASE("leave inline comments", "[removecode]") {
    before("//test\n");

    REQUIRE(strcmp(istr, ostr) == 0);

    after();
    
}

TEST_CASE("leave multiline comments", "[removecode]") {
    before("/*test\ntest2    test \n\n\n **/");
    
    REQUIRE(strcmp(istr, ostr) == 0);

    after();
}

TEST_CASE("leave non closed multiline comments", "[removecode]") {
    before("/*test\ntest2    test \n\n\n **** kjsjlkqdjlsq");
    
    REQUIRE(strcmp(istr, ostr) == 0);

    after();
}

TEST_CASE("remove code", "[removecode]") {
    before("main(){}");

    REQUIRE(strcmp("        ", ostr) == 0);

    after();
}

TEST_CASE("remove code and leave comment", "[removecode]") {
    before("//test\nmain(){\n/*\ntest\n*/\n}");

    REQUIRE(strcmp("//test\n       \n/*\ntest\n*/\n ", ostr) == 0);

    after();
}

TEST_CASE("leave comments with line continuations", "[removecode]") {
    before("//test\\\ntestestetsets\\\ntest");

    REQUIRE(strcmp("//test\\\ntestestetsets\\\ntest", ostr) == 0);

    after();
}

TEST_CASE("leave comments with line continuations and remove the rest", "[removecode]") {
    before("//test\\\ntestestetsets\\\ntest\nmain(){}");

    REQUIRE(strcmp("//test\\\ntestestetsets\\\ntest\n        ", ostr) == 0);

    after();
}

//negative tests

TEST_CASE("do not leave multiline comments inside string litterals", "[removecode]") {
    before("printf(\"/* Not a comment. */\\n\");");

    REQUIRE(strcmp("                                 ", ostr) == 0);

    after();
}

TEST_CASE("do not leave line comments inside string litterals", "[removecode]") {
    before("printf(\"// Not a comment.\\n\");");

    REQUIRE(strcmp("                              ", ostr) == 0);

    after();
}