

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "Program.h"

using namespace std;

extern "C" {
#include "y.tab.h"
    extern FILE *yyin;
    extern int yylex();
    extern int yyparse();
    extern char *yytext;
    extern int  lineno;
}

extern Program program;

int main(int argc, char **argv)
{
    FILE *file;

    file = stdin; 

    if (!file)
    {
        fprintf(stderr, "Unable to open file %s", argv[1]);
        return 1;
    }

    yyin = file;

    do
    {
        yyparse();
    } while (!feof(yyin));

    // Here is where we use a visitor to create the assembly
    //AssemblyVisitor asmv(std::cout);
    //asmv.Visit(program);

    return 0;
}

extern "C" void yyerror(char *s)
{ 
    fprintf(stderr, "Syntax error on line #%d: %s\n", lineno, s);
    fprintf(stderr, "Last token was \"%s\"\n", yytext);
    exit(1);
}
